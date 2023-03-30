include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_executable(doub_test doub_test.cpp)
target_link_libraries(doub_test GTest::gtest_main doubler)

include(GoogleTest)
gtest_discover_tests(doub_test)