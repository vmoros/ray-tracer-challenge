include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
FetchContent_MakeAvailable(googletest)

add_executable(all_tests tuple_test.cc color_test.cc canvas_test.cc)
target_link_libraries(all_tests GTest::gtest_main stuff)

include(GoogleTest)
gtest_discover_tests(all_tests)