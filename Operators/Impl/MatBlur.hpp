/*!
 *  \file   MatBlur.hpp
 *  \brief  Definition of MatBlur primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatBlur_hpp
#define MatBlur_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatBlur MatBlur.hpp "MatBlur.hpp"
 *  \brief MatBlur primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatBlur : public Beagle::GP::Primitive {

public:

  //! MatBlur allocator type.
  typedef Beagle::AllocatorT<MatBlur,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatBlur handle type.
  typedef Beagle::PointerT<MatBlur,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatBlur bag type.
  typedef Beagle::ContainerT<MatBlur,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatBlur();
  virtual ~MatBlur() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatBlur_hpp