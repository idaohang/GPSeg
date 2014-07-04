
/*!
 *  \file   FeatureEvalOp.cpp
 *  \brief  Implementation of the class FeatureEvalOp.
 *  \author Li Yuejiang
 */

#include <beagle/GP.hpp>
#include "FeatureEvalOp.hpp"

#include <cmath>
#include <fstream>
#include <algorithm>
#include <qstring.h>

using namespace Beagle;

int FeatureEvalOp::countPts(const cv::Mat & img)
{
    assert(img.type() == CV_8UC1);

    cv::Size size = img.size();
    if( img.isContinuous())
    {
        size.width *= size.height;
        size.height = 1;
    }

    int result = 0;

    for( int i = 0; i < size.height; i++ )
    {
        uchar* p_img = (uchar*)(img.data + img.step*i);


        for( int j = 0; j < size.width; j++ )
        {
            if(p_img[j])
            {
                result++;
            }
        }

    }
    return result;
}

/*!
 *  \brief Construct a new feature detector evaluation operator.
 *  \param inFilename Default filename used.
 */
FeatureEvalOp::FeatureEvalOp(Beagle::string inFilename) :
  GP::EvaluationOp("FeatureEvalOp")//,
  //mFilename(NULL),
  //mFilenameDefault(inFilename)
{

	// init Gassian Distribution
    double _gd[] = {0.13362, 0.16152, 0.1936, 0.23014, 0.27134, 0.31732, 0.36812, 0.42372, 0.48392, 0.5485, 0.61708, 0.68916, 0.76418, 0.84148, 0.92034, 1, 0.92034, 0.84148, 0.76418, 0.68916, 0.61708, 0.5485, 0.48392, 0.42372, 0.36812, 0.31732, 0.27134, 0.23014, 0.1936, 0.16152, 0.13362};
	for(int i=0; i<31; i++)
	{
        _dGaussianDist[i] = _gd[i];
	}

    // populate features
    std::cout << "Populate Features...";

    _r.getWrappedValue() = cv::imread("r.bmp",0);
    _g.getWrappedValue() = cv::imread("g.bmp",0);
    _b.getWrappedValue() = cv::imread("b.bmp",0);
    _h.getWrappedValue() = cv::imread("h.bmp",0);
    _s.getWrappedValue() = cv::imread("s.bmp",0);
    _v.getWrappedValue() = cv::imread("v.bmp",0);
    _i.getWrappedValue() = cv::imread("i.bmp",0);

//    cv::Mat _r = cv::imread("r.bmp",0);
//    cv::Mat _g = cv::imread("g.bmp",0);
//    cv::Mat _b = cv::imread("b.bmp",0);
//    cv::Mat _h = cv::imread("h.bmp",0);
//    cv::Mat _s = cv::imread("s.bmp",0);
//    cv::Mat _v = cv::imread("v.bmp",0);
//    cv::Mat _i = cv::imread("i.bmp",0);

//    std::cout << _r.cols << ":" << _r.rows << ":" << _r.type() << std::endl;
//    std::cout << CV_8UC1 << ":" << CV_8UC3 << ":" << CV_8U << std::endl;
//    cv::imshow("r", _r);
//    cv::waitKey(5);
    //std::cout << "Mask [ cols : " <<  _i.getWrappedValue().cols << "; rows : " <<  _i.getWrappedValue().rows << " ] " << std::endl;

    // populate target
    std::cout << "Populate Target...";
    _desired_cormsk = cv::imread("mask.bmp",0);
    num_desired = countPts(_desired_cormsk);
    std::cout << "Total target points:" << num_desired << std::endl;
    std::cout << "Mask [ cols : " <<  _desired_cormsk.cols << "; rows : " <<  _desired_cormsk.rows << " ] " << std::endl;

}


/*!
 *  \brief Initialize the feature detector evaluation operator.
 *  \param ioSystem System of the evolution.
 */
void FeatureEvalOp::initialize(Beagle::System& ioSystem)
{
  Beagle::GP::EvaluationOp::initialize(ioSystem);
}


/*!
 *  \brief Evaluate the individual fitness for the feature detection problem.
 *  \param inIndividual Individual to evaluate.
 *  \param ioContext Evolutionary context.
 *  \return Handle to the fitness measure,
 */
Fitness::Handle FeatureEvalOp::evaluate(GP::Individual& inIndividual, GP::Context& ioContext)
{
    setValue("r", _r, ioContext);
    setValue("g", _g, ioContext);
    setValue("b", _b, ioContext);
    setValue("h", _h, ioContext);
    setValue("s", _s, ioContext);
    setValue("v", _v, ioContext);
    setValue("i", _i, ioContext);

    Mat lResult;

    inIndividual.run(lResult, ioContext);
	
	int iTreeDepth = inIndividual.getMaxTreeDepth();
	int iTreeNodesNo = inIndividual.getTotalNodes();

	cv::Mat_<float>& result = lResult.getWrappedValue();
    cv::Mat norm;
    // normalizing to period [0, 255]
    cv::normalize( result, norm, 0, 255, cv::NORM_MINMAX, CV_8UC1, cv::Mat() );

    cv::imshow("Response", norm);
    cv::waitKey(1);

	std::vector<double> vprecision, vrecall;

	int max_thre = 0;
	double lFitness = 0;
    for (int c = 1; c < 32; c++)
    {
        // set a detection threshold
        int threshold = 8 * c;
        // calculate detected pts
        cv::Mat matDetectedPts;
        FeatureEvalOp::detectFeaturePts(norm, matDetectedPts, threshold);
        // calculate recall and precision
        double recall, precision, fitness;
        FeatureEvalOp::calculateStatistics(matDetectedPts, _desired_cormsk, num_desired, recall, precision, fitness, false);
        vprecision.push_back(precision);
        vrecall.push_back(recall);
		if (lFitness < fitness) 
		{
			lFitness = fitness;
			max_thre = c-1;
		}
    }

	std::cout << "Fitness value:  " << lFitness << "; TreeDepth: " << iTreeDepth << "; TreeNodes:" << iTreeNodesNo <<  std::endl;
	return new FitnessSimple(_dGaussianDist[max_thre]*lFitness);
}


/*!
 *  \brief Post-initialization hook the spambase evaluation operator.
 *  \param ioSystem System of the evolution.
 */
void FeatureEvalOp::postInit(Beagle::System& ioSystem)
{
	GP::EvaluationOp::postInit(ioSystem);
}


/*!
 *  \brief Read data of the spambase problem.
 *  \param inFilename Name of the file in which the spambase problem data are.
 *  \param inSizeData Number of entry in the data base.
 *  \throw InternalException When the file format is not valid.
 */
void FeatureEvalOp::readData(Beagle::string inFilename, unsigned int inSizeData)
{
}


/*!
 *  \brief extract feature points from reponse image.
 *  \param result in interest points reponse mat
 *  \param ptsMask out a mask image with 255 indicate detected feature points
 */
void FeatureEvalOp::detectFeaturePts(const cv::Mat & result, cv::Mat & ptsMask, int threshold)
{
    ptsMask = cv::Mat::zeros(result.size(), CV_8UC1);

    // threshold to obtain feature pts
    for( int j = 0; j < result.rows ; j++ )
    {
        for( int i = 0; i < result.cols; i++ )
        {
            if( (int) result.at<uchar>(j,i) > threshold )
            {
                ptsMask.at<uchar>(j,i) = 255;
            }
        }
    }
}

void FeatureEvalOp::calculateStatistics(const cv::Mat &detected_mask, const cv::Mat &desired_mask, int desiredTotalNumPts, double &recall, double &precision, double &fitness, bool isShow)
{
    int num_matched, num_response;
	
    num_response = countPts(detected_mask);
	
    if (isShow) {
        cv::imshow("Detected Points", detected_mask);
        cv::waitKey(1);
    }

    cv::Mat matMatchedPts = detected_mask & desired_mask;
	
    num_matched = countPts(matMatchedPts);

    if (isShow) {
        cv::imshow("Matched Points", matMatchedPts);
        cv::waitKey(1);
    }
    if (num_response == 0) precision = 0;
    else precision = (double)num_matched/num_response;

    recall = (double)num_matched/desiredTotalNumPts;

    fitness = (recall*precision)/(0.8*recall + 0.2*precision);
}
