cmake_minimum_required(VERSION 3.14)
project(UAV_Quality_Tooling)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(test_spsc test_spsc_queue.cpp)

target_link_libraries(test_spsc 
    PRIVATE 
    GTest::gtest_main  
    pthread           
)

include(GoogleTest)
gtest_discover_tests(test_spsc)