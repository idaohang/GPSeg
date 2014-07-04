/*!
 *  \file   MatIx.cpp
 *  \brief  Implementation of the class MatIx.
 *  \author Li Yuejiang
 */
#include <beagle/GP.hpp>
#include "../Mat.hpp"
#include "Impl/MatIx.hpp"

#include <cmath>
#include <fstream>

using namespace Beagle;
/*!
 *  \brief Construct a new MatIx primitive.
 */
MatIx::MatIx() :
  Beagle::GP::Primitive(1, "MatIx")
{ }


#ifdef BEAGLE_HAVE_RTTI

/*!
 *  \brief Return the Double tag needed as input for the primitive MatIx.
 *  \param inN Index of the argument to get the tag.
 *  \param ioContext Evolutionary context.
 *  \return RTTO type_info tagging the data type Double.
 *  \throw AssertException If the index inN given is > to 1.
 */
const std::type_info* MatIx::getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const
{
  Beagle_AssertM(inN < 1);
  return &typeid(Mat);
}


/*!
 *  \brief Return the string tagging the Bool type returned but the primitive MatIx.
 *  \param ioContext Evolutionary context.
 *  \return RTTI type_info tagging the Bool type returned.
 */
const std::type_info* MatIx::getReturnType(Beagle::GP::Context& ioContext) const
{
  return &typeid(Mat);
}

#endif // BEAGLE_HAVE_RTTI


/*!
 *  \brief Execute the Add operation between two Mat, returning a Mat.
 *  \param outDatum Result of the Blur.
 *  \param ioContext Evolutionary context.
 */
void MatIx::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
  Mat& lResult = castObjectT<Mat&>(outDatum);
  Mat lArg;
  get1stArgument(lArg, ioContext);
  cv::Sobel( lArg.getWrappedValue(), lResult.getWrappedValue(), CV_32F, 1, 0, 3, 8, 0, cv::BORDER_DEFAULT );
}
