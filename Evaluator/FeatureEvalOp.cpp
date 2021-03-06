
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
#include <QFont>

using namespace Beagle;

// count the number of true pixels in mask image
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
    GP::EvaluationOp("FeatureEvalOp"),
    _bestFitness(0.0)
  //mFilename(NULL),
  //mFilenameDefault(inFilename)
{

    // init Gassian Distribution
    double _gd[] = {0.13362, 0.16152, 0.1936, 0.23014, 0.27134, 0.31732, 0.36812, 0.42372, 0.48392, 0.5485, 0.61708, 0.68916, 0.76418, 0.84148, 0.92034, 1, 0.92034, 0.84148, 0.76418, 0.68916, 0.61708, 0.5485, 0.48392, 0.42372, 0.36812, 0.31732, 0.27134, 0.23014, 0.1936, 0.16152, 0.13362};
    for(int i=0; i<31; i++)
    {
        _dGaussianDist[i] = _gd[i];
    }

//    // initialize plotter
//    _custamplot = new QCustomPlot();

//    // plot for individual statistics
//    _custamplot->addGraph();
//    _custamplot->graph(0)->setLineStyle(QCPGraph::lsNone);
//    _custamplot->graph(0)->setScatterStyle(QCP::ScatterStyle(QCP::ScatterStyle::ssCircle));
//    _custamplot->graph(0)->setPen(QPen(Qt::blue));
//    _custamplot->graph(0)->setName("Recall");
//    _custamplot->addGraph();
//    _custamplot->graph(1)->setPen(QPen(Qt::red));
//    _custamplot->graph(1)->setLineStyle(QCPGraph::lsNone);
//    _custamplot->graph(1)->setScatterStyle(QCP::ScatterStyle(QCP::ScatterStyle::ssCross));;
//    _custamplot->graph(1)->setName("Precision");
//    _custamplot->addGraph();
//    _custamplot->graph(2)->setPen(QPen(Qt::green));
//    _custamplot->graph(2)->setLineStyle(QCPGraph::lsNone);
//    _custamplot->graph(2)->setScatterStyle(QCP::ScatterStyle(QCP::ScatterStyle::ssTriangle));;
//    _custamplot->graph(2)->setName("Fitness");
//    _custamplot->xAxis->setRange(0, 255);
//    _custamplot->yAxis->setRange(0, 1.0);
//    _custamplot->xAxis->setLabel("Threshold");
//    _custamplot->yAxis->setLabel("Value");
//    _custamplot->setRangeDrag(Qt::Horizontal);
//    _custamplot->setRangeZoom(Qt::Horizontal);
//    _custamplot->legend->setVisible(true);

//    _custamplot->legend->setPositionStyle(QCPLegend::psRight);
//    _custamplot->legend->setBrush(QBrush(QColor(255,255,255,230)));

//    //_custamplot->show();
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

    // calculate the response matrix
    Mat lResult;
    inIndividual.run(lResult, ioContext);

    // Normalize to Interval [0 ,255]
    cv::Mat norm;
    cv::normalize( lResult.getWrappedValue(), norm, 0, 255, cv::NORM_MINMAX, CV_8UC1, cv::Mat() );

    // show Normalized Response Value
    cv::imshow("Response", norm);
    cv::waitKey(1);

    // vectors to save statistics
    std::vector<double> vprecision, vrecall, vfitness;
    int maxIndex = 0;
    double lFitness = 0;

    // set 31 thresholds, and get the best fitness value.
    for (int c = 1; c < 32; c++)
    {
        // set a detection threshold
        int threshold = 8 * c;

        // thresholding to get detected mask
        FeatureEvalOp::detectFeaturePts(norm, _detMask, threshold);

        // calculate recall and precision
        double recall, precision, fitness;
        FeatureEvalOp::calculateStatistics(_detMask, _trgMask, _trgPixelNum, recall, precision, fitness, false);
        vprecision.push_back(precision); vrecall.push_back(recall); vfitness.push_back(fitness);

        // save best fitness value and its index
        if (lFitness < fitness)
        {
            lFitness = fitness;
            maxIndex = c-1;
        }
    }

    // display detection result of best individual
    if (lFitness > _bestFitness)
    {
        FeatureEvalOp::detectFeaturePts(norm, _detMask, (maxIndex+1)*8);
        // calculate recall and precision
        double recall, precision, fitness;
        FeatureEvalOp::calculateStatistics(_detMask, _trgMask, _trgPixelNum, recall, precision, fitness, true);
        _bestFitness = lFitness;
    }

    // output fitness value and tree statistics
    int iTreeDepth = inIndividual.getMaxTreeDepth();
    int iTreeNodesNo = inIndividual.getTotalNodes();
    std::cout << "Fitness value:  " << lFitness << "; TreeDepth: " << iTreeDepth << "; TreeNodes:" << iTreeNodesNo <<  std::endl;

    // return a fitness value with penalty
    return new FitnessSimple(_dGaussianDist[maxIndex]*lFitness);
}


/*!
 *  \brief Post-initialization.
 *  \param ioSystem System of the evolution.
 */
void FeatureEvalOp::postInit(Beagle::System& ioSystem)
{
    GP::EvaluationOp::postInit(ioSystem);
}


/*!
 *  \brief Read data
 *  \param inFilename Name of the file.
 *  \param inSizeData Number of entry in the data base.
 *  \throw InternalException When the file format is not valid.
 */
void FeatureEvalOp::readData(Beagle::string inFilename, unsigned int inSizeData)
{
}

void FeatureEvalOp::setOriginImage(QString filename)
{
    // populate features
    if (filename == "") return;

    std::cout << "Populate Features... from file:" << filename.toAscii().data() << std::endl;
    cv::Mat i;
    cv::Mat origin = cv::imread(filename.toAscii().data());

    cv::cvtColor(origin, i, CV_BGR2GRAY);
    i.convertTo(_i.getWrappedValue(), CV_32FC1);
    cv::Mat hsv;
    cv::cvtColor(origin, hsv, CV_BGR2HSV);

    cv::Mat rgbA[3];
    cv::split(origin, rgbA);
    rgbA[2].convertTo(_r.getWrappedValue(), CV_32FC1);
    rgbA[1].convertTo(_g.getWrappedValue(), CV_32FC1);
    rgbA[0].convertTo(_b.getWrappedValue(), CV_32FC1);

    cv::Mat hsvA[3];
    cv::split(hsv, hsvA);
    hsvA[2].convertTo(_v.getWrappedValue(), CV_32FC1);
    hsvA[1].convertTo(_s.getWrappedValue(), CV_32FC1);
    hsvA[0].convertTo(_h.getWrappedValue(), CV_32FC1);

    std::cout << "Feature I [ cols : " <<  _i.getWrappedValue().cols << "; rows : " <<  _i.getWrappedValue().rows << " ] Chan:" << _i.getWrappedValue().channels() << std::endl;
    std::cout << "Feature R [ cols : " <<  _r.getWrappedValue().cols << "; rows : " <<  _r.getWrappedValue().rows << " ] Chan:" << _r.getWrappedValue().channels() << std::endl;
    std::cout << "Feature G [ cols : " <<  _g.getWrappedValue().cols << "; rows : " <<  _g.getWrappedValue().rows << " ] Chan:" << _g.getWrappedValue().channels() << std::endl;
    std::cout << "Feature B [ cols : " <<  _b.getWrappedValue().cols << "; rows : " <<  _b.getWrappedValue().rows << " ] Chan:" << _b.getWrappedValue().channels() << std::endl;
    std::cout << "Feature V [ cols : " <<  _v.getWrappedValue().cols << "; rows : " <<  _v.getWrappedValue().rows << " ] Chan:" << _v.getWrappedValue().channels() << std::endl;
    std::cout << "Feature S [ cols : " <<  _s.getWrappedValue().cols << "; rows : " <<  _s.getWrappedValue().rows << " ] Chan:" << _s.getWrappedValue().channels() << std::endl;
    std::cout << "Feature H [ cols : " <<  _h.getWrappedValue().cols << "; rows : " <<  _h.getWrappedValue().rows << " ] Chan:" << _h.getWrappedValue().channels() << std::endl;

    cv::waitKey(1);
}

void FeatureEvalOp::setObjectMask(QString filename)
{
    if (filename == "") return;
    // populate target
    std::cout << "Populate Target..." << std::endl;
    _trgMask = cv::imread(filename.toAscii().data(),0);
    _trgPixelNum = countPts(_trgMask);
    std::cout << "Total target points:" << _trgPixelNum << std::endl;
    std::cout << "Mask [ cols : " <<  _trgMask.cols << "; rows : " <<  _trgMask.rows << " ] " << std::endl;
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
