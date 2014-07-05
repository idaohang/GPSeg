cmake_minimum_required(VERSION 2.8 FATAL_ERROR) 

project(GPIMAGEPROC)
set(EXE_NAME GPIMAGEPROC)
set(PROJECT_NAME GPIMAGEPROC)

set(DEFAULT FALSE)

set(BEAGLE_INCLUDE_DIRS C:/GP/beagle-3.0.3/PACC
                        C:/GP/beagle-3.0.3/beagle/include
                        C:/GP/beagle-3.0.3/beagle/GA/include
                        C:/GP/beagle-3.0.3/beagle/GP/include
                        )
include_directories(${BEAGLE_INCLUDE_DIRS})

set(GP_LIBS 
                        C:/GP/beagle-3.0.3/MSVCPP/pacc-math/Debug/pacc-math.lib
                        C:/GP/beagle-3.0.3/MSVCPP/pacc-util/Debug/pacc-util.lib
                        C:/GP/beagle-3.0.3/MSVCPP/pacc-xml/Debug/pacc-xml.lib
                        C:/GP/beagle-3.0.3/MSVCPP/beagle/Debug/beagle.lib
                        C:/GP/beagle-3.0.3/MSVCPP/beagle-GP/Debug/beagle-GP.lib
                        C:/GP/beagle-3.0.3/MSVCPP/beagle-GA/Debug/beagle-GA.lib
                        )
# Package for OpenCV
include_directories("C:/opencv/opencv/build/include")
set(OpenCV_LIBS C:/opencv/opencv/build/x86/vc10/lib/opencv_gpu247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_contrib247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_legacy247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_objdetect247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_calib3d247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_features2d247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_video247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_highgui247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_ml247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_nonfree247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_imgproc247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_flann247d.lib
                C:/opencv/opencv/build/x86/vc10/lib/opencv_core247d.lib
)
#include(C:/OpenCV/build/install/OpenCVConfig.cmake)
#set(OpenCV "C:/OpenCV/build/cmake")
#find_package(OpenCV REQUIRED)

# Package for Qt
find_package(Qt4 REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL QtNetwork QtXml  REQUIRED)
include(${QT_USE_FILE})
list(APPEND ADDITIONAL_LIBS ${QT_LIBRARIES})

SET(CMAKE_CXX_FLAGS_DEBUG "/MTd")
################################################################################
if(BUILD)
  # Qt
  if(NOT QT4_FOUND)
    message(WARNING "Qt4 is needed for the app! It will not be built!")
    set(BUILD FALSE)
  endif()

  # OpenGL
  find_package(OpenGL REQUIRED)
  if(OPENGL_FOUND AND OPENGL_GLU_FOUND)
    list(APPEND ADDITIONAL_LIBS ${OPENGL_LIBRARIES})
  else()
    message(WARNING "OpenGL & GLU are needed for the app! It will not be built!")
    set(BUILD FALSE)
  endif()
endif()
################################################################################

set(INCS
)

set(IMPL_INCS
        Operands/EphemeralPercent.hpp
        Operands/Mat.hpp
	Operators/Impl/MatAdd.hpp
	Operators/Impl/MatSub.hpp
	Operators/Impl/MatMul.hpp
	Operators/Impl/MatMulDou.hpp
	Operators/Impl/MatSquare.hpp
	Operators/Impl/MatBlur.hpp
	Operators/Impl/MatIx.hpp
	Operators/Impl/MatIy.hpp
        Evaluator/FeatureEvalOp.hpp
)

set(SRCS
        Operands/EphemeralPercent.cpp
	Operators/MatAdd.cpp
	Operators/MatSub.cpp
	Operators/MatMul.cpp
	Operators/MatMulDou.cpp
	Operators/MatSquare.cpp
	Operators/MatBlur.cpp
	Operators/MatIx.cpp
	Operators/MatIy.cpp
	main.cpp    
        mainwindow.cpp
        Thread/Impl/SegController.cpp
        Thread/Impl/SegEvolver.cpp
        Thread/EvolveThread.cpp
        Evaluator/FeatureEvalOp.cpp
)

set(MOC_MAIN_WINDOW_INC     mainwindow.h)
set(MOC_SEG_CONTROLLER_INC  Thread/SegController.h)
set(MOC_SEG_EVOLVER_INC     Thread/SegEvolver.h)
set(MOC_EVOLVE_THREAD_INC   Thread/EvolveThread.h)
set(UI_MAIN_WINDOW          mainwindow.ui)

QT4_WRAP_CPP(MOC_MAIN_WINDOW_SRC        ${MOC_MAIN_WINDOW_INC})
QT4_WRAP_CPP(MOC_SEG_CONTROLLER_SRC     ${MOC_SEG_CONTROLLER_INC})
QT4_WRAP_CPP(MOC_SEG_EVOLVER_SRC        ${MOC_SEG_EVOLVER_INC})
QT4_WRAP_CPP(MOC_EVOLVE_THREAD_SRC      ${MOC_EVOLVE_THREAD_INC})
QT4_WRAP_UI(UI_MAIN_WINDOW_INC          ${UI_MAIN_WINDOW})

include_directories(${CMAKE_CURRENT_BINARY_DIR}) # For the ui files

list(APPEND INCS    ${MOC_MAIN_WINDOW_INC}
                    ${UI_MAIN_WINDOW_INC}
                    ${MOC_SEG_CONTROLLER_INC}
                    ${MOC_SEG_EVOLVER_INC}
                    ${MOC_EVOLVE_THREAD_INC}
)

list(APPEND SRCS    ${MOC_MAIN_WINDOW_SRC}
                    ${MOC_SEG_CONTROLLER_SRC}
                    ${MOC_SEG_EVOLVER_SRC}
                    ${MOC_EVOLVE_THREAD_SRC}
)

add_executable(${EXE_NAME} ${SRCS} ${INCS} ${IMPL_INCS})
target_link_libraries(${EXE_NAME} ${SUBSYS_LIBS} ${ADDITIONAL_LIBS} ${OpenCV_LIBS} ${GP_LIBS} GlU32 )
