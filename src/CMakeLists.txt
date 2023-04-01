set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=cppcoreguidelines* -warnings-as-errors=*)

add_library(tuple tuple.cc)
target_include_directories(tuple PUBLIC inc)