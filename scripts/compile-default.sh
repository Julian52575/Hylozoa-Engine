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
if [[ ! -d "./build/" ]];
then
    echo "Error: No 'build/' directory."
    exit 84
fi

#Arguments

#Script
cd build/
cmake .. -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=Debug
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

echo -e "Success: check the build folder.\nClearning current path..."
mv --verbose hylozoa.exe ..
