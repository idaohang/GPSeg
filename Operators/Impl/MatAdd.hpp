/*!
 *  \file   MatAdd.hpp
 *  \brief  Definition of MatAdd primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatAdd_hpp
#define MatAdd_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatAdd MatAdd.hpp "MatAdd.hpp"
 *  \brief MatAdd primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatAdd : public Beagle::GP::Primitive {

public:

  //! MatAdd allocator type.
  typedef Beagle::AllocatorT<MatAdd,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatAdd handle type.
  typedef Beagle::PointerT<MatAdd,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatAdd bag type.
  typedef Beagle::ContainerT<MatAdd,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatAdd();
  virtual ~MatAdd() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatAdd_hpp