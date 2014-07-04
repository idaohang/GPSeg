/*!
 *  \file   MatAdd.cpp
 *  \brief  Implementation of the class MatAdd.
 *  \author Li Yuejiang
 */
#include <beagle/GP.hpp>
#include "../Mat.hpp"
#include "Impl/MatAdd.hpp"

#include <cmath>
#include <fstream>

using namespace Beagle;
/*!
 *  \brief Construct a new MatAdd primitive.
 */
MatAdd::MatAdd() :
  Beagle::GP::Primitive(2, "MatAdd")
{ }


#ifdef BEAGLE_HAVE_RTTI

/*!
 *  \brief Return the Double tag needed as input for the primitive MatAdd.
 *  \param inN Index of the argument to get the tag.
 *  \param ioContext Evolutionary context.
 *  \return RTTO type_info tagging the data type Double.
 *  \throw AssertException If the index inN given is > to 1.
 */
const std::type_info* MatAdd::getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const
{
  Beagle_AssertM(inN < 2);
  return &typeid(Mat);
}


/*!
 *  \brief Return the string tagging the Bool type returned but the primitive MatAdd.
 *  \param ioContext Evolutionary context.
 *  \return RTTI type_info tagging the Bool type returned.
 */
const std::type_info* MatAdd::getReturnType(Beagle::GP::Context& ioContext) const
{
  return &typeid(Mat);
}

#endif // BEAGLE_HAVE_RTTI


/*!
 *  \brief Execute the Add operation between two Mat, returning a Mat.
 *  \param outDatum Result of the Add.
 *  \param ioContext Evolutionary context.
 */
void MatAdd::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
  Mat& lResult = castObjectT<Mat&>(outDatum);
  Mat lArgs[2];
  getArguments(lArgs, sizeof(Mat), ioContext);
  lResult = lArgs[0] + lArgs[1];
}
