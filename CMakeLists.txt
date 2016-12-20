cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME TimeLapse)
add_definitions(-DMODULE_NAME=\"TimeLapse\")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_C_COMPILER /usr/local/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
add_definitions(-Wall)
add_definitions(-fPIC)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
# c++ 11 option
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
  add_definitions(-std=c++1z)
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.
    Please use a different C++ compiler.")
endif()
project(TimeLapse)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
  ADD_DEFINITIONS(-std=c++1z)
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.
    Please use a different C++ compiler.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Threads)


find_package(OpenCV 3 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

find_package(DanLib REQUIRED)

include_directories(${DanLib_INCLUDE_DIR})

include_directories(src)

set(CMAKE_DEBUG_POSTFIX d)

add_executable(
  TimeLapse
  src/TimeLapse.cpp
  )

target_link_libraries(
  TimeLapse
  ${OpenCV_LIBRARIES}
  )
