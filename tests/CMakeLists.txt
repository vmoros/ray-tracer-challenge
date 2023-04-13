include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
  SYSTEM
)
FetchContent_MakeAvailable(googletest)

add_executable(all_tests tuple_test.cc color_test.cc canvas_test.cc
    matrix_test.cc ray_test.cc sphere_test.cc light_test.cc
    material_test.cc world_test.cc camera_test.cc intersection_test.cc
    shape_test.cc plane_test.cc)
target_link_libraries(all_tests GTest::gtest_main stuff)

include(GoogleTest)
gtest_discover_tests(all_tests)