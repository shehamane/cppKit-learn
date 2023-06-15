cmake_minimum_required(VERSION 2.6)
project(cppKit-learn)


enable_testing()
add_subdirectory(googletest)
include_directories(src/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_library(core
        src/lib/core/Tensor.tpp
        src/lib/core/View.tpp
        src/lib/core/iterator/Index.cpp
        src/lib/core/iterator/Iterator.tpp
        )
target_include_directories(core PUBLIC
        src/lib/core
        )
add_executable(test_app
        src/test/test.cpp
        )

target_link_libraries(test_app core)