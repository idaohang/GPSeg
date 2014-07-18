/*!
 *  \file   MatThresh.hpp
 *  \brief  Definition of MatThresh primitive used in the image threshold problem.
 *
 *  \brief threshold to zero method,
 *  \param threshod = 100
 *  \param para maxvalue 255 is useless.
 *
 *  \author Li Yuejiang
 */

#ifndef MatThresh_hpp
#define MatThresh_hpp

#include <beagle/GP.hpp>
#include <string>

#ifdef BEAGLE_HAVE_RTTI
#include <typeinfo>
#endif // BEAGLE_HAVE_RTTI

/*!
 *  \class MatThresh MatThresh.hpp "MatThresh.hpp"
 *  \brief MatThresh primitive that threshold one image
 */
class MatThresh : public Beagle::GP::Primitive {

public:

  //! MatThresh allocator type.
  typedef Beagle::AllocatorT<MatThresh,Beagle::GP::Primitive::Alloc>
          Alloc;
  //!< MatThresh handle type.
  typedef Beagle::PointerT<MatThresh,Beagle::GP::Primitive::Handle>
          Handle;
  //!< MatThresh bag type.
  typedef Beagle::ContainerT<MatThresh,Beagle::GP::Primitive::Bag>
          Bag;

  explicit MatThresh();
  virtual ~MatThresh() { }

#ifdef BEAGLE_HAVE_RTTI
  virtual const std::type_info* getArgType(unsigned int inN, Beagle::GP::Context& ioContext) const;
  virtual const std::type_info* getReturnType(Beagle::GP::Context& ioContext) const;
#endif // BEAGLE_HAVE_RTTI

  virtual void                  execute(Beagle::GP::Datum& outDatum, Beagle::GP::Context& ioContext);
};
#endif // MatThresh_hpp
