cmake_minimum_required(VERSION 3.10)
project(SortingTests)

set(CMAKE_CXX_STANDARD 11)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.10.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test files
add_executable(
  tests
  ./include/sort.hpp
  ./include/sort.cpp
  ./include/DataGenerator.hpp
  ./Test/sort.test.cpp
  ./Test/main.test.cpp
)

target_link_libraries(
  tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)