/*!
 *  \file   MatThresh.cpp
 *  \brief  Implementation of the class MatThresh.
 *  \author Li Yuejiang
 */
#include <beagle/GP.hpp>
#include "../Operands/Mat.hpp"
#include "Impl/MatThresh.hpp"

#include <cmath>
#include <fstream>

using namespace Beagle;
/*!
 *  \brief Construct a new MatThresh primitive.
 */
MatThresh::MatThresh() :
    Beagle::GP::Primitive(1, "MatThresh")
{ }


#ifdef BEAGLE_HAVE_RTTI

/*!
 *  \brief Return the Double tag needed as input for the primitive MatThresh.
 *  \param inN Index of the argument to get the tag.
 *  \param ioContext Evolutionary context.
 *  \return RTTO type_info tagging the data type Double.
 *  \throw AssertException If the index inN given is > to 1.
 */
const std::type_info* MatThresh::getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const
{
    Beagle_AssertM(inN < 1);
    return &typeid(Mat);
}


/*!
 *  \brief Return the string tagging the Bool type returned but the primitive MatThresh.
 *  \param ioContext Evolutionary context.
 *  \return RTTI type_info tagging the Bool type returned.
 */
const std::type_info* MatThresh::getReturnType(Beagle::GP::Context& ioContext) const
{
    return &typeid(Mat);
}

#endif // BEAGLE_HAVE_RTTI

/*!
 *  \brief Execute the Add operation between two Mat, returning a Mat.
 *  \param outDatum Result of the Add.
 *  \param ioContext Evolutionary context.
 */
void MatThresh::execute(GP::Datum& outDatum, GP::Context& ioContext)
{
    Mat& lResult = castObjectT<Mat&>(outDatum);
    Mat lArg;
    get1stArgument(lArg, ioContext);
    // threshold to zero method,
    // para threshod = 100
    // para maxvalue 255 is useless.
    cv::threshold( lArg.getWrappedValue(), lResult.getWrappedValue(), 100., 255., cv::THRESH_TOZERO);
}
