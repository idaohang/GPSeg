/*!
 *  \file   MatIy.hpp
 *  \brief  Definition of MatIy primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatIy_hpp
#define MatIy_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatIy MatIy.hpp "MatIy.hpp"
 *  \brief MatIy primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatIy : public Beagle::GP::Primitive {

public:

  //! MatIy allocator type.
  typedef Beagle::AllocatorT<MatIy,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatIy handle type.
  typedef Beagle::PointerT<MatIy,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatIy bag type.
  typedef Beagle::ContainerT<MatIy,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatIy();
  virtual ~MatIy() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatIy_hpp
