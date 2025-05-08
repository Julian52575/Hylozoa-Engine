cmake_minimum_required(VERSION 3.14)
project(Hylozoa-Engine)
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( hylozoa
    ${SRC_FILES}
)
target_link_libraries(hylozoa
)
