# Declare project, source file
cmake_minimum_required(VERSION 3.20)
project(Hylozoa-Engine)
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Exclude main
#list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp) #removing main
message(STATUS "Compiling sources:\n ${SRC_FILES}\n...")

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCMAKE_COMPILATION_")

# Conan integration ?
# list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
include(${CMAKE_TOOLCHAIN_FILE})
message (STATUS "Toolchain: ${CMAKE_TOOLCHAIN_FILE}")

# Install libs
find_library(R-ENGINE NAMES rengine REQUIRED)
find_library(R-ENGINE-GRAPHICS NAMES rengine_graphics_sfml REQUIRED)
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics audio)
find_package(nlohmann_json REQUIRED)
find_package(Lua REQUIRED)

# Define the target
add_executable(hylozoa-engine ${SRC_FILES})
set_target_properties(hylozoa-engine PROPERTIES LINKER_LANGUAGE CXX)

# Link libs
target_link_libraries(hylozoa-engine PUBLIC
    nlohmann_json::nlohmann_json
    lua::lua
    rengine
    rengine_graphics_sfml
)

# Include headers
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
target_include_directories(hylozoa-engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<TARGET_PROPERTY:nlohmann_json::nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>
)

if (WIN32)
    message(STATUS "Configuring for Windows")
endif (WIN32)
if (UNIX)
    message(STATUS "Configuring for Unix")
endif (UNIX)
