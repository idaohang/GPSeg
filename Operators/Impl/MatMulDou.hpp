/*!
 *  \file   MatMulDou.hpp
 *  \brief  Definition of MatMulDou primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatMulDou_hpp
#define MatMulDou_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatMulDou MatMulDou.hpp "MatMulDou.hpp"
 *  \brief MatMulDou primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatMulDou : public Beagle::GP::Primitive {

public:

  //! MatMulDou allocator type.
  typedef Beagle::AllocatorT<MatMulDou,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatMulDou handle type.
  typedef Beagle::PointerT<MatMulDou,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatMulDou bag type.
  typedef Beagle::ContainerT<MatMulDou,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatMulDou();
  virtual ~MatMulDou() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatMulDou_hpp