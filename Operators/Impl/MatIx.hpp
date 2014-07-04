/*!
 *  \file   MatIx.hpp
 *  \brief  Definition of MatIx primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatIx_hpp
#define MatIx_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatIx MatIx.hpp "MatIx.hpp"
 *  \brief MatIx primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatIx : public Beagle::GP::Primitive {

public:

  //! MatIx allocator type.
  typedef Beagle::AllocatorT<MatIx,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatIx handle type.
  typedef Beagle::PointerT<MatIx,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatIx bag type.
  typedef Beagle::ContainerT<MatIx,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatIx();
  virtual ~MatIx() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatIx_hpp
