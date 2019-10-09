cmake_minimum_required(VERSION 3.14)
project(search_utils_lib)

include_directories(includes)
#add_subdirectory(test)
add_executable(search includes/search.cpp)
#target_link_libraries(test sort_lib)

set(CMAKE_CXX_STANDARD 17)
