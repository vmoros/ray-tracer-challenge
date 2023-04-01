set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=cppcoreguidelines* -warnings-as-errors=*)

add_library(stuff tuple.cc color.cc canvas.cc matrix.cc)
target_include_directories(stuff PUBLIC inc)
