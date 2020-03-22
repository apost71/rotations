cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
SET(OSX_MAJOR_VERSION 10)
SET(OSX_MINOR_VERSION 15)
SET(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk)
SET(MACOSX_DEPLOYMENT_TARGET ${OSX_MAJOR_VERSION}.${OSX_MINOR_VERSION})
SET(CMAKE_CXX_FLAGS "--sysroot ${CMAKE_OSX_SYSROOT} ${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
MESSAGE("Setting MACOSX_DEPLOYMENT_TARGET to '${MACOSX_DEPLOYMENT_TARGET}'.")
project(rotations)


include_directories(rotations/includes)

find_package(Catch2 REQUIRED)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(SOURCES
        rotations/includes/math/Matrix.hpp
        "rotations/includes/math/Matrix.cpp"
        "rotations/includes/EulerAngle.cpp"
        "rotations/includes/PRV.cpp"
        "rotations/includes/RotationParameters.cpp"
        rotations/includes/Quaternion.hpp
        rotations/includes/Quaternion.cpp
        rotations/includes/math/Vector.cpp
        rotations/includes/math/Vector.hpp
        rotations/includes/CRP.hpp
        rotations/includes/CRP.cpp
        rotations/includes/MRP.cpp
        rotations/includes/MRP.hpp
        "rotations/includes/RotationIntegrator.hpp" rotations/includes/AttitudeDetermination/TriadMethod.cpp rotations/includes/AttitudeDetermination/TriadMethod.hpp rotations/test/AttitudeDeterminationTest.cpp rotations/includes/AttitudeDetermination/DavenportQ.cpp rotations/includes/AttitudeDetermination/DavenportQ.hpp rotations/includes/AttitudeDetermination/AttitudeDetermination.cpp rotations/includes/AttitudeDetermination/AttitudeDetermination.hpp)

add_executable(rotations ${SOURCES} rotations/src/main.cpp)
target_link_libraries (rotations Eigen3::Eigen)


add_executable(rotations_test ${SOURCES} rotations/test/test.cpp rotations/test/RotationParametersTest.cpp rotations/test/MatrixTest.cpp rotations/test/QuaternionTest.cpp rotations/test/VectorTest.cpp)
target_link_libraries(rotations_test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(rotations_test)
