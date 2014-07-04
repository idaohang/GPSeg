/*!
 *  \file   beagle/Mat.hpp
 *  \brief  Definition of type Mat and related operators.
 *  \author Li Yuejiang
 */

#ifndef Beagle_Mat_hpp
#define Beagle_Mat_hpp

#include <beagle/config.hpp>
#include <beagle/macros.hpp>
#include <beagle/WrapperT.hpp>
#include <beagle/ArrayT.hpp>
#include <beagle\GP\AddT.hpp>
#include <beagle/GP/MultiplyT.hpp>
#include <opencv2\opencv.hpp>
#include <beagle\Double.hpp>

namespace Beagle {

/*!
 *  \brief Beagle wrapper of the atomic Mat type.
 *  \ingroup Adapt
 */
typedef WrapperT< cv::Mat_<float> >
        Mat;

/*!
 *  \brief Beagle array of the atomic Mat type.
 *  \ingroup Adapt
 */
typedef ArrayT< cv::Mat_<float> >
        MatArray;

//typedef GP::AddT<Mat> AddMat;
//typedef GP::SubtractT<Mat> SubMat;
/*!
 *  \brief Evaluate absolute value of a Beagle::Mat.
 *  \param inValue Mat to evaluate the absolute value.
 *  \return Absolute value of the input.
 *  \ingroup Adapt
 */
template <>
inline Mat absolute(const Mat& inValue)
{
  Beagle_StackTraceBeginM();
  return Mat(cv::abs(inValue.getWrappedValue()));
  Beagle_StackTraceEndM("Mat absolute(const Mat& inValue)");
}
}

/*!
 *  \brief Bitwise Multiple two Mat.
 *  \param inLeftMat Left value to add.
 *  \param inRightMat Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Mat operator*(const Beagle::Mat& inLeftMat, const Beagle::Mat& inRightMat)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.getWrappedValue().mul( inRightMat.getWrappedValue() );
  Beagle_StackTraceEndM("Mat operator+(const Mat& inLeftMat, const Mat& inRightMat)");
}

/*!
 *  \brief Add two Mat.
 *  \param inLeftMat Left value to add.
 *  \param inRightMat Right value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Mat operator+(const Beagle::Mat& inLeftMat, const Beagle::Mat& inRightMat)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.getWrappedValue() + inRightMat.getWrappedValue();
  Beagle_StackTraceEndM("Mat operator+(const Mat& inLeftMat, const Mat& inRightMat)");
}

/*!
 *  \brief Add a Mat to a Mat.
 *  \param inLeftMat Left value to which the right one is added.
 *  \param inRightMat Value to add.
 *  \return Result of the addition.
 */
inline
Beagle::Mat operator+=(Beagle::Mat& inLeftMat, const Beagle::Mat& inRightMat)
{
  Beagle_StackTraceBeginM();
  inLeftMat.getWrappedValue() += inRightMat.getWrappedValue();
  return inLeftMat;
  Beagle_StackTraceEndM("Mat operator+=(Mat& inLeftMat, const Mat& inRightMat)");
}

/*!
 *  \brief Subtract two Mat.
 *  \param inLeftMat Left value to subtract.
 *  \param inRightMat Right value to subtract.
 *  \return Result of the subtract.
 */
inline
Beagle::Mat operator-(const Beagle::Mat& inLeftMat, const Beagle::Mat& inRightMat)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.getWrappedValue() - inRightMat.getWrappedValue();
  Beagle_StackTraceEndM("Mat operator-(const Mat& inLeftMat, const Mat& inRightMat)");
}

/*!
 *  \brief Subtract a Mat from a Mat.
 *  \param inLeftMat Left value from which the right Mat is subtracted.
 *  \param inRightMat Value to subtract.
 *  \return Result of the subtraction.
 */
inline
Beagle::Mat operator-=(Beagle::Mat& inLeftMat, const Beagle::Mat& inRightMat)
{
  Beagle_StackTraceBeginM();
  inLeftMat.getWrappedValue() -= inRightMat.getWrappedValue();
  return inLeftMat;
  Beagle_StackTraceEndM("Mat operator-=(Mat& inLeftMat, const Mat& inRightMat)");
}

/*!
 *  \brief Multiply a Mat with a Mat.
 *  \param inLeftMat Left value to multiply.
 *  \param inRightMat Right value to multiply.
 *  \return Result of the multiply.
 */
inline
Beagle::Mat operator*(const Beagle::Mat& inLeftMat, Beagle::Double inRightDouble)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.getWrappedValue() * inRightDouble.getWrappedValue();
  Beagle_StackTraceEndM("Mat operator*(const Mat& inLeftMat, double inRightDouble)");
}

/*!
 *  \brief Multiply a Mat with a double.
 *  \param inLeftMat Left value from which the right double is multiplied.
 *  \param inRightDouble Right value to multiply.
 *  \return Result of the multiplication.
 */
inline
Beagle::Mat operator*=(Beagle::Mat& inLeftMat, Beagle::Double inRightDouble)
{
  Beagle_StackTraceBeginM();
  inLeftMat.getWrappedValue() *= inRightDouble.getWrappedValue();
  return inLeftMat;
  Beagle_StackTraceEndM("Mat operator*=(Mat& inLeftMat, double inRightDouble)");
}


/*!
 *  \brief Divide a Mat with a double.
 *  \param inLeftMat Left value to divide.
 *  \param inRightDouble Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Mat operator/(const Beagle::Mat& inLeftMat, Beagle::Double inRightDouble)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.getWrappedValue() / inRightDouble.getWrappedValue();
  Beagle_StackTraceEndM("Mat operator/(const Mat& inLeftMat, double inRightDouble)");
}

/*!
 *  \brief Divide a Mat with a double.
 *  \param inLeftMat Left value from which the right double is divided.
 *  \param inRightDouble Right value to divide.
 *  \return Result of the division.
 */
inline
Beagle::Mat operator/=(Beagle::Mat& inLeftMat, Beagle::Double inRightDouble)
{
  Beagle_StackTraceBeginM();
  inLeftMat.getWrappedValue() /= inRightDouble.getWrappedValue();
  return inLeftMat;
  Beagle_StackTraceEndM("Mat operator/=(Mat& inLeftMat, double inRightDouble)");
}

/*!
 *  \brief     Test whether an Mat is equal to another.
 *  \param     inLeftBool  Left Mat compared.
 *  \param     inRightBool Right Mat compared.
 *  \return    True if left Mat is equal to the right one, false if not.
 *  \par Note:
 *     The operator is defined relatively to the function isEqual of Beagle::Bool.
 */
inline bool operator==(const cv::Mat_<float>& inLeftMat, const cv::Mat_<float>& inRightMat)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.at<float>(0,0) == inRightMat.at<float>(0,0);
  Beagle_StackTraceEndM("bool operator==(const Bool& inLeftBool, const Bool& inRightBool)");
}

/*!
 *  \brief     Test whether an Mat is less than another.
 *  \param     inLeftBool  Left Mat compared.
 *  \param     inRightBool Right Mat compared.
 *  \return    True if left Mat is equal to the right one, false if not.
 *  \par Note:
 *     The operator is defined relatively to the function isEqual of Beagle::Bool.
 */
inline bool operator<(const cv::Mat_<float>& inLeftMat, const cv::Mat_<float>& inRightMat)
{
  Beagle_StackTraceBeginM();
  return inLeftMat.at<float>(0,0) < inRightMat.at<float>(0,0);
  Beagle_StackTraceEndM("bool operator<(const cv::Mat_<float>& inLeftMat, const cv::Mat_<float>& inRightMat)");
}

inline std::ostringstream& operator<< (std::ostringstream& out, const cv::Mat& mtx)
{
	Beagle_StackTraceBeginM();
    return out;
	Beagle_StackTraceEndM("bool operator<(const cv::Mat_<float>& inLeftMat, const cv::Mat_<float>& inRightMat)");
}

inline std::istringstream& operator>> (std::istringstream& in, const cv::Mat& mtx)
{
    return in;
}
#endif // Beagle_Mat_hpp



