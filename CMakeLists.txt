cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
SET(OSX_MAJOR_VERSION 10)
SET(OSX_MINOR_VERSION 15)
SET(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk)
SET(MACOSX_DEPLOYMENT_TARGET ${OSX_MAJOR_VERSION}.${OSX_MINOR_VERSION})
SET(CMAKE_CXX_FLAGS "--sysroot ${CMAKE_OSX_SYSROOT} ${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
MESSAGE("Setting MACOSX_DEPLOYMENT_TARGET to '${MACOSX_DEPLOYMENT_TARGET}'.")
project(rotations)


include_directories(rotations/includes)

find_package(Catch2 REQUIRED)

set(SOURCES
        "rotations/includes/Matrix.cpp"
        "rotations/includes/EulerAngle.cpp"
        "rotations/includes/PRV.cpp"
        "rotations/includes/RotationParameters.cpp"
        rotations/includes/Quaternion.hpp rotations/includes/Quaternion.cpp)

add_executable(rotations ${SOURCES} rotations/src/main.cpp)

add_executable(rotations_test ${SOURCES} rotations/test/test.cpp rotations/test/EulerAngleTest.cpp rotations/test/MatrixTest.cpp rotations/test/QuaternionTest.cpp)
target_link_libraries(rotations_test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(rotations_test)
