#!/bin/bash
RED='\033[0;31m'
NC='\033[0m' # No Color
BIN_NAME="hylozoa-engine"
FLAGS=""
BUILD_TYPE="RELEASE"

if [[ "$1" == "debug" ]]; then
    echo -e "$RED Compiling debug binary.$NC"
    BUILD_TYPE="DEBUG"  # debug build
fi
cmake -B build -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=$BUILD_TYPE
if cmake --build build;then
    chmod a+x build/$BIN_NAME
    mv build/$BIN_NAME $BIN_NAME
    echo "$BIN_NAME has been succesfuly built !"
else
    echo "Build failed. Do you have librengine.so in your path ? /usr/lib"
    exit 84
fi