##
## Hylozoa Engine
## compile-default.sh
## Compiles Hylozoa with the default settings
## Must be run at root
##
##

# Error handling
if [[ ! -f "./CMakeLists.txt" ]];
then
    echo "Error: No 'CMakeLists.txt' on current directory: aborting..."
    exit 84
fi

#Arguments

#Script
cmake -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Debug \
    -S=./
    -B=build/ \
    -DCMAKE_INSTALL_PREFIX=.

if [[ $? -ne 0 ]];
then
    echo "An error occured when building with cmake.."
    exit 84
fi
make
if [[ $? -ne 0 ]];
then
    echo "An error occured when compiling..."
    exit 84
fi

echo "Success: check the build folder"
