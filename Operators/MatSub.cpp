/*!
 *  \file   MatSub.cpp
 *  \brief  Implementation of the class MatSub.
 *  \author Li Yuejiang
 */
#include <beagle/GP.hpp>
#include "../Mat.hpp"
#include "Impl/MatSub.hpp"

#include <cmath>
#include <fstream>

using namespace Beagle;
/*!
 *  \brief Construct a new MatSub primitive.
 */
MatSub::MatSub() :
  Beagle::GP::Primitive(2, "MatSub")
{ }


#ifdef BEAGLE_HAVE_RTTI

/*!
 *  \brief Return the Double tag needed as input for the primitive MatSub.
 *  \param inN Index of the argument to get the tag.
 *  \param ioContext Evolutionary context.
 *  \return RTTO type_info tagging the data type Double.
 *  \throw AssertException If the index inN given is > to 1.
 */
const std::type_info* MatSub::getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const
{
  Beagle_AssertM(inN < 2);
  return &typeid(Mat);
}


/*!
 *  \brief Return the string tagging the Bool type returned but the primitive MatSub.
 *  \param ioContext Evolutionary context.
 *  \return RTTI type_info tagging the Bool type returned.
 */
const std::type_info* MatSub::getReturnType(Beagle::GP::Context& ioContext) const
{
  return &typeid(Mat);
}

#endif // BEAGLE_HAVE_RTTI


/*!
 *  \brief Execute the Add operation between two Mat, returning a Mat.
 *  \param outDatum Result of the Add.
 *  \param ioContext Evolutionary context.
 */
void MatSub::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
  Mat& lResult = castObjectT<Mat&>(outDatum);
  Mat lArgs[2];
  getArguments(lArgs, sizeof(Mat), ioContext);
  lResult = lArgs[0] - lArgs[1];
}
