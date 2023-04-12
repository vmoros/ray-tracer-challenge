cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_options(-fsanitize=address -fsanitize=undefined)
# add_link_options(-fsanitize=address -fsanitize=undefined)

# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE
# "include-what-you-use;-Xiwyu;--mapping_file=/opt/homebrew/opt/llvm/include/c++/v1/libcxx.imp")
# I want to use IWYU but it has weird suggestions, even after adding the mapping file.
# For example, it says to add "#include <fwd>" for "std::string", which makes no sense
# It also wants to change a lot of my includes from <> to "", which I dislike
# I would use it only to remove, not to add, but it doesn't have that feature

project(RayTracer)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)