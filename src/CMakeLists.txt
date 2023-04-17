if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=cppcoreguidelines*
        -checks=-cppcoreguidelines-avoid-magic-numbers -warnings-as-errors=*)

add_library(stuff STATIC tuple.cc color.cc canvas.cc matrix.cc
        ray.cc sphere.cc light.cc material.cc world.cc camera.cc
        intersection.cc shape.cc plane.cc pattern.cc cube.cc)
target_include_directories(stuff PUBLIC inc)

set(OpenMP_C_FLAGS "-fopenmp -I/opt/homebrew/opt/libomp/include")
set(OpenMP_C_LIB_NAMES "libomp")
set(OpenMP_libomp_LIBRARY "omp")
find_package(OpenMP REQUIRED)

target_link_libraries(stuff PUBLIC OpenMP::OpenMP_CXX)

add_subdirectory(projects)