/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1K 7P4
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   FeatureEvalOp.hpp
 *  \brief  Definition of the type FeatureEvalOp.
 *  \author LEE
 *  \author YUEJIANG
 */

/*!
 *  \defgroup Image Segmentation
 *  \brief Image Seg: Machine learning using strongly-typed GP
 *     with Open BEAGLE.
 *
 *  \par Objective
 *  Find a program the will successfully segment the image
 *
 *  \par Comments
 *  Don't expect too much from this program as
 *  it is quite basic and not oriented toward performance. It is there mainly
 *  to illustrate the use of strongly-typed GP with Open BEAGLE.
 *
 *  \par Terminal set
 *  - Features channels of image
 *  - Ephemeral constants randomly generated in $[0,1]$  [floating-point]
 *
 *  \par Function set
 *  - +                 [Inputs: Mats,   Output: Mat]
 *  - -                 [Inputs: Mats,   Output: Mat]
 *  - *                 [Inputs: Mats,   Output: Mat]
 *  - /                 [Inputs: Mats,   Output: Mat]
 *  - BLUR              [Inputs: Mats,   Output: Mat]
 *  - Ix                [Inputs: Mats,   Output: Mat]
 *  - Iy                [Inputs: Mats,   Output: Mat]
 *
 *
 *  \par Fitness cases
 *
 *  \par Hits
 *  \par Raw fitness
 *  \par Standardized fitness
 *  \par Adjusted fitness
 *  \par Normalized fitness
 *  Rate of correct outputs obtained over all the 400 fitness cases.
 *
 *  \par Stopping criteria
 *  \par Reference
 *  Machine learning repository, http://www.ics.uci.edu/~mlearn/MLRepository.html
 *
 */

#ifndef FeatureEvalOp_hpp
#define FeatureEvalOp_hpp

#include <beagle/GP.hpp>
#include <string>
#include <vector>
#include <opencv2\opencv.hpp>
#include <QObject>
#include "../Operands/Mat.hpp"

/*!
 *  \class FeatureEvalOp FeatureEvalOp.hpp "FeatureEvalOp.hpp"
 *  \brief The individual evaluation class operator for the Image feature extraction problem.
 *  \ingroup Spambase
 */
class FeatureEvalOp : public QObject, public Beagle::GP::EvaluationOp {
    Q_OBJECT
public:

    //! FeatureEvalOp allocator type.
    typedef Beagle::AllocatorT<FeatureEvalOp,Beagle::GP::EvaluationOp::Alloc>
    Alloc;
    //!< FeatureEvalOp handle type.
    typedef Beagle::PointerT<FeatureEvalOp,Beagle::GP::EvaluationOp::Handle>
    Handle;
    //!< FeatureEvalOp bag type.
    typedef Beagle::ContainerT<FeatureEvalOp,Beagle::GP::EvaluationOp::Bag>
    Bag;

    explicit FeatureEvalOp(Beagle::string inFilename="spambase.data");

    virtual void initialize(Beagle::System& ioSystem);
    virtual Beagle::Fitness::Handle evaluate(Beagle::GP::Individual& inIndividual,
                                             Beagle::GP::Context& ioContext);
    virtual void postInit(Beagle::System& ioSystem);
    void readData(Beagle::string inFilename, unsigned int inSizeData);

    void setOriginImage(QString );
    void setObjectMask(QString);

public:
    static int countPts(const cv::Mat &img);
    // detect pts with threshold
    static void detectFeaturePts(const cv::Mat & result, cv::Mat & detected_mask, int threshold);
    // calculate recall, precision, fitness value
    static void calculateStatistics(const cv::Mat & detected_mask, const cv::Mat & desired_mask, int desiredTotalNumPts, double & recall, double & precision, double & fitness, bool isShow = true);

protected:
    //Gaussian distribution
    double _dGaussianDist[31];

    // Origin Image
    cv::Mat									_originImage;
    // Detected Result represented by Binary Mask
    cv::Mat									_detMask;
    // Target of Evolutionary Computation represented by Binary Mask
    cv::Mat									_trgMask;
    // Number of Pixels in Target Mask
    int										_trgPixelNum;
    // Features
    Beagle::Mat _r, _g, _b, _h, _s, _v, _i;

    // store best fitness value acheived
    float _bestFitness;

signals:

};

#endif // FeatureEvalOp_hpp
