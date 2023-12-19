cmake_minimum_required(VERSION 2.6)
project(cppKit-learn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
enable_testing()

add_subdirectory(googletest)
add_library(core
        src/lib/core/Tensor.tpp
        src/lib/core/View.tpp
        src/lib/core/iterator/Index.cpp
        src/lib/core/iterator/Iterator.tpp
        src/lib/core/iterator/Range.tpp
        )
target_include_directories(core PUBLIC src/lib/core)

add_executable(test_app src/test/main.cpp)
target_include_directories(test_app PUBLIC src/test ./)
target_link_libraries(test_app core gtest_main gmock_main)

add_executable(playground_app src/test/playground.cpp)
target_link_libraries(playground_app core)