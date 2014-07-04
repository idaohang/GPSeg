/*!
 *  \file   MatSquare.hpp
 *  \brief  Definition of MatSquare primitive used in the image add problem.
 *  \author Li Yuejiang
 */

#ifndef MatSquare_hpp
#define MatSquare_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatSquare MatSquare.hpp "MatSquare.hpp"
 *  \brief MatSquare primitive that compare the order of two Double and return a Bool.
 *  \ingroup Spambase
 */
class MatSquare : public Beagle::GP::Primitive {

public:

  //! MatSquare allocator type.
  typedef Beagle::AllocatorT<MatSquare,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatSquare handle type.
  typedef Beagle::PointerT<MatSquare,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatSquare bag type.
  typedef Beagle::ContainerT<MatSquare,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatSquare();
  virtual ~MatSquare() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatSquare_hpp