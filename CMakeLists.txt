cmake_minimum_required(VERSION 2.6)
project(cppKit-learn)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
enable_testing()

add_subdirectory(googletest)
add_library(core
        src/lib/core/Tensor.tpp
        src/lib/core/View.tpp
        src/lib/core/indexing/Index.cpp
        src/lib/core/indexing/Iterator.tpp
        src/lib/core/indexing/Range.tpp
        )

add_library(math
        src/lib/math/broadcasting.cpp
        src/lib/math/operators.cpp
        src/lib/math/operations.cpp
)
target_include_directories(core PUBLIC src/lib/core)
target_include_directories(core PUBLIC src/lib/core/indexing)
target_include_directories(core PUBLIC src/lib/math)

target_include_directories(math PUBLIC src/lib/core)
target_include_directories(math PUBLIC src/lib/math)


add_executable(test_app src/test/main.cpp)
target_include_directories(test_app PUBLIC src/test ./)
target_link_libraries(test_app core gtest_main gmock_main)

add_executable(playground_app src/test/playground.cpp)
target_link_libraries(playground_app core math)