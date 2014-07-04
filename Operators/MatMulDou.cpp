/*!
 *  \file   MatMulDou.cpp
 *  \brief  Implementation of the class MatMulDou.
 *  \author Li Yuejiang
 */
#include <beagle/GP.hpp>
#include "../Mat.hpp"
#include "Impl/MatMulDou.hpp"

#include <cmath>
#include <fstream>

using namespace Beagle;
/*!
 *  \brief Construct a new MatMulDou primitive.
 */
MatMulDou::MatMulDou() :
  Beagle::GP::Primitive(2, "MatMulDou")
{ }


#ifdef BEAGLE_HAVE_RTTI

/*!
 *  \brief Return the Double tag needed as input for the primitive MatMulDou.
 *  \param inN Index of the argument to get the tag.
 *  \param ioContext Evolutionary context.
 *  \return RTTO type_info tagging the data type Double.
 *  \throw AssertException If the index inN given is > to 1.
 */
const std::type_info* MatMulDou::getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const
{
  Beagle_AssertM(inN < 2);
  return inN==0?&typeid(Beagle::Mat):&typeid(Double);
}


/*!
 *  \brief Return the string tagging the Bool type returned but the primitive MatMulDou.
 *  \param ioContext Evolutionary context.
 *  \return RTTI type_info tagging the Bool type returned.
 */
const std::type_info* MatMulDou::getReturnType(Beagle::GP::Context& ioContext) const
{
  return &typeid(Beagle::Mat);
}

#endif // BEAGLE_HAVE_RTTI


/*!
 *  \brief Execute the Add operation between two Mat, returning a Mat.
 *  \param outDatum Result of the Add.
 *  \param ioContext Evolutionary context.
 */
void MatMulDou::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
  Beagle_StackTraceBeginM();
  Mat& lResult = castObjectT<Mat&>(outDatum);
  get1stArgument(lResult, ioContext);
  Double lArg2;
  get2ndArgument(lArg2, ioContext);
  lResult = lResult*lArg2;
  Beagle_StackTraceEndM("void MatMulDou::execute(GP::Datum& outDatum, GP::Context& ioContext)");
}
