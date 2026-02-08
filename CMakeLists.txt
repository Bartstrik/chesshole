cmake_minimum_required(VERSION 3.10)
project(chesshole)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main)

### External libs
add_subdirectory(../third_party/raylib raylib_build)


### This Project
#source files
target_sources(main PRIVATE
    src/main.cpp
)

#header files
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

###linking
target_link_libraries(main PRIVATE raylib)