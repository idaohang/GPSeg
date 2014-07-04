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
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.7.2.1 $
 *  $Date: 2007/05/09 01:51:24 $
 */

/*!
 *  \defgroup Spambase Spambase Example
 *  \brief SPAM e-mail database (spambase): Machine learning using strongly-typed GP
 *     with Open BEAGLE.
 *
 *  \par Objective
 *  Find a program the will successfully predict whether a given e-mail is spam
 *  or not from some extracted features.
 *
 *  \par Comments
 *  The evolved programs works on floating-point values AND Booleans values.
 *  The programs must return a Boolean value which must be true if e-mail is
 *  spam, and false otherwise. Don't expect too much from this program as
 *  it is quite basic and not oriented toward performance. It is there mainly
 *  to illustrate the use of strongly-typed GP with Open BEAGLE.
 *
 *  \par Terminal set
 *  - IN0, IN1, ...  up to IN56, the e-mail features.      [floating-point]
 *  - 0 and 1, two Boolean constants.                      [Boolean]
 *  - Ephemeral constants randomly generated in $[0,100]$  [floating-point]
 *
 *  \par Function set
 *  - AND               [Inputs: Booleans,        Output: Boolean]
 *  - OR                [Input:  Boolean,         Output: Boolean]
 *  - NOT               [Inputs: Booleans,        Output: Boolean]
 *  - +                 [Inputs: floating-points, Output: floating-point]
 *  - -                 [Inputs: floating-points, Output: floating-point]
 *  - *                 [Inputs: floating-points, Output: floating-point]
 *  - /                 [Inputs: floating-points, Output: floating-point]
 *  - <                 [Inputs: floating-points, Output: Booleans]
 *  - ==                [Inputs: floating-points, Output: Booleans]
 *  - if-then-else      [1st Input: Boolean, 2nd & 3rd Input: floating-points,
 *                       Output: floating-point]
 *
 *  \par Fitness cases
 *  A random sample of 400 e-mails over the database, re-chosen for
 *  each fitness evaluation.
 *
 *  \par Hits
 *  Number of correct outputs obtained over the 400 fitness cases.
 *
 *  \par Raw fitness
 *  Ignored (always 0).
 *
 *  \par Standardized fitness
 *  Rate of correct outputs over the fitness cases where
 *  the desired output was 0 (non-spam).
 *
 *  \par Adjusted fitness
 *  Rate of correct outputs over the fitness cases where
 *  the desired output was 1 (spam).
 *
 *  \par Normalized fitness
 *  Rate of correct outputs obtained over all the 400 fitness cases.
 *
 *  \par Stopping criteria
 *  When the best individual scores 400 hits or when the evolution reaches
 *  the maximum number of generations.
 *
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
#include "../Operands/Mat.hpp"

/*!
 *  \class FeatureEvalOp FeatureEvalOp.hpp "FeatureEvalOp.hpp"
 *  \brief The individual evaluation class operator for the Image feature extraction problem.
 *  \ingroup Spambase
 */
class FeatureEvalOp : public Beagle::GP::EvaluationOp {

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

public:
    static int countPts(const cv::Mat &img);
    // detect pts with threshold
    static void detectFeaturePts(const cv::Mat & result, cv::Mat & detected_mask, int threshold);
    // calculate recall, precision, fitness value
    static void calculateStatistics(const cv::Mat & detected_mask, const cv::Mat & desired_mask, int desiredTotalNumPts, double & recall, double & precision, double & fitness, bool isShow = true);


protected:
  //Beagle::String::Handle                     mFilename;        //!< Filename containing the data.
  //Beagle::string                             mFilenameDefault; //!< Default filename used.
  //Beagle::Mat I, Ix, Iy, Ix2, Iy2, IxIy, AIx2, AIy2, AIxIy;
  //Beagle::Mat _xx, _xy, _xz, _yy, _yz, _zz;
  //Beagle::Mat _f[24];

  // features
  Beagle::Mat _r, _g, _b, _h, _s, _v, _i;

  //Gaussian distribution
  double _dGaussianDist[31];

  //cv::Mat									mTrainingImg;
  cv::Mat									_detected_cormsk;
  cv::Mat									_desired_cormsk;
  int										num_desired;
  cv::Mat 									mOutput;

};

#endif // FeatureEvalOp_hpp
