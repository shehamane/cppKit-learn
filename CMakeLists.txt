cmake_minimum_required(VERSION 2.6)
project(cppKit-learn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CORE src/lib/core/Tensor.h src/lib/core/View.h)
set(TEST src/test/test.cpp)

add_executable(test ${TEST} ${CORE})