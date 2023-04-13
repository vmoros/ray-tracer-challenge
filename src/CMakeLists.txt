if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=cppcoreguidelines* -checks=-cppcoreguidelines-avoid-magic-numbers -warnings-as-errors=*)

add_library(stuff STATIC tuple.cc color.cc canvas.cc matrix.cc
    ray.cc sphere.cc light.cc material.cc world.cc camera.cc
    intersection.cc shape.cc plane.cc)
target_include_directories(stuff PUBLIC inc)

add_subdirectory(projects)