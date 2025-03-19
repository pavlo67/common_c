cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(common_c)

# external libs ----------------------------------------------------------

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(jsoncpp REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAMERA REQUIRED libcamera)               # sudo apt install libcamera-dev
find_library(LIBCAMERA_LIBRARY libcamera.so REQUIRED)
find_library(LIBCAMERA_BASE_LIBRARY libcamera-base.so REQUIRED)
set(LIBCAMERA_LIBRARIES "${LIBCAMERA_LIBRARY}" "${LIBCAMERA_BASE_LIBRARY}")
include_directories(${CAMERA_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)                                # sudo apt install libsdl2-dev libsdl2-2.0-0
include_directories(${SDL2_INCLUDE_DIRS})


# project libs -----------------------------------------------------------

include_directories(./)


# keyboard probe -------------------------------------------------------

add_executable(keyboard_probe
        lib/helpers/probes/keyboard.cpp
        lib/helpers/keyboard.cpp
)

# jsoncpp probe --------------------------------------------------------

add_executable(jsoncpp
        lib/json/probes/jsoncpp.cpp
)
target_link_libraries(jsoncpp jsoncpp_lib)

# jsoncpp_append probe -------------------------------------------------

add_executable(jsoncpp_append
        lib/json/probes/jsoncpp_append.cpp
)
target_link_libraries(jsoncpp_append jsoncpp_lib)

# video probe ----------------------------------------------------------

add_executable(video_probe
        lib/video_in/probes/video.cpp
        lib/video_in/in_libcamera.cpp
        lib/video_in/libcamera.cpp
        lib/video_out/out_window.cpp
        lib/helpers/time.cpp
)
target_link_libraries(video_probe ${OpenCV_LIBS} ${LIBCAMERA_LIBRARIES})


# libcamera probe --------------------------------------------------------

add_executable(libcamera_probe
        lib/video_in/probes/libcamera.cpp
        lib/video_in/libcamera.cpp
        lib/helpers/time.cpp
)
target_link_libraries(libcamera_probe ${OpenCV_LIBS} ${LIBCAMERA_LIBRARIES})


## performance test -----------------------------------------------------
#
#add_executable(performance_test apps/performance_test/main.cpp
#        lib/timing/timing.cpp lib/timing/timing.h
#)
#target_link_libraries(performance_test ${OpenCV_LIBS})
#
#


