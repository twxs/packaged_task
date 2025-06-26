cmake_minimum_required(VERSION 3.50)

project(packaged_task VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(packaged_task main.cpp)
target_compile_features(packaged_task PRIVATE cxx_std_20)
target_compile_options(packaged_task PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries(packaged_task PRIVATE gtest gtest_main)

add_test(NAME packaged_task_test COMMAND packaged_task)