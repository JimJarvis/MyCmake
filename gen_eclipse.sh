#!/bin/bash
# arg1: give a build directory name. Defaults to 'project'

BUILD_DIR=project
if [ $# -eq 1 ]; then
    BUILD_DIR=$1
fi

mkdir $BUILD_DIR
cd $BUILD_DIR
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 -DCMAKE_BUILD_TYPE=Release ../cmake/
cd ..

echo
echo Patch eclipse project configurations:
python patch_eclipse.py $BUILD_DIR

echo
echo DONE
