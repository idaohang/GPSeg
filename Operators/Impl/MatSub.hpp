/*!
 *  \file   MatSub.hpp
 *  \brief  Definition of MatSub primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatSub_hpp
#define MatSub_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatSub MatSub.hpp "MatSub.hpp"
 *  \brief MatSub primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatSub : public Beagle::GP::Primitive {

public:

  //! MatSub allocator type.
  typedef Beagle::AllocatorT<MatSub,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatSub handle type.
  typedef Beagle::PointerT<MatSub,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatSub bag type.
  typedef Beagle::ContainerT<MatSub,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatSub();
  virtual ~MatSub() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatSub_hpp