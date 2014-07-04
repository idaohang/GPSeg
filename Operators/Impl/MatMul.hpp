/*!
 *  \file   MatMul.hpp
 *  \brief  Definition of MatMul primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatMul_hpp
#define MatMul_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatMul MatMul.hpp "MatMul.hpp"
 *  \brief MatMul primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatMul : public Beagle::GP::Primitive {

public:

  //! MatMul allocator type.
  typedef Beagle::AllocatorT<MatMul,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatMul handle type.
  typedef Beagle::PointerT<MatMul,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatMul bag type.
  typedef Beagle::ContainerT<MatMul,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatMul();
  virtual ~MatMul() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatMul_hpp
