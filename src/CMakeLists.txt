add_library(doubler doubler.cpp)
target_include_directories(doubler PUBLIC inc)

add_executable(HEY main.cpp)
target_link_libraries(HEY PUBLIC doubler)