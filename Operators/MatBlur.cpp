/*!
 *  \file   MatBlur.cpp
 *  \brief  Implementation of the class MatBlur.
 *  \author Li Yuejiang
 */
#include <beagle/GP.hpp>
#include "../Mat.hpp"
#include "Impl/MatBlur.hpp"

#include <cmath>
#include <fstream>

using namespace Beagle;
/*!
 *  \brief Construct a new MatBlur primitive.
 */
MatBlur::MatBlur() :
  Beagle::GP::Primitive(1, "MatBlur")
{ }


#ifdef BEAGLE_HAVE_RTTI

/*!
 *  \brief Return the Double tag needed as input for the primitive MatBlur.
 *  \param inN Index of the argument to get the tag.
 *  \param ioContext Evolutionary context.
 *  \return RTTO type_info tagging the data type Double.
 *  \throw AssertException If the index inN given is > to 1.
 */
const std::type_info* MatBlur::getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const
{
  Beagle_AssertM(inN < 1);
  return &typeid(Mat);
}


/*!
 *  \brief Return the string tagging the Bool type returned but the primitive MatBlur.
 *  \param ioContext Evolutionary context.
 *  \return RTTI type_info tagging the Bool type returned.
 */
const std::type_info* MatBlur::getReturnType(Beagle::GP::Context& ioContext) const
{
  return &typeid(Mat);
}

#endif // BEAGLE_HAVE_RTTI


/*!
 *  \brief Execute the Add operation between two Mat, returning a Mat.
 *  \param outDatum Result of the Blur.
 *  \param ioContext Evolutionary context.
 */
void MatBlur::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
  Mat& lResult = castObjectT<Mat&>(outDatum);
  Mat lArg;
  get1stArgument(lArg, ioContext);
  cv::boxFilter(lArg.getWrappedValue(), lResult.getWrappedValue(), lArg.getWrappedValue().depth(), cv::Size(2, 2), cv::Point(-1,-1), false, cv::BORDER_DEFAULT );
}
