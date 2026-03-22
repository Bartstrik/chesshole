cmake_minimum_required(VERSION 3.10)
project(chesshole)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(main)

### External libs
add_subdirectory(raylib raylib_build)


### This Project
#defines
target_compile_definitions(main
    PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
)

#source files
target_sources(main PRIVATE
    src/main.cpp
    src/common.cpp
    src/chess.cpp
    src/render.cpp
    src/lexer.cpp
)

#header files
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

###linking
target_link_libraries(main PRIVATE raylib)
