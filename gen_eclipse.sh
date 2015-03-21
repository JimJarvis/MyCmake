#!/bin/bash
# arg1: give a build directory name. Defaults to 'project'

BUILD_DIR=ubuntu

if [ $# -eq 1 ]; then
    BUILD_DIR=$1
fi

if [ ! -d $BUILD_DIR ]; then
    mkdir $BUILD_DIR
    cd $BUILD_DIR
    cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 -DCMAKE_BUILD_TYPE=Release ../cmake/
    cd ..
else
    echo $BUILD_DIR already exists.
fi

echo
echo Patch eclipse project configurations:
python patch_eclipse.py $BUILD_DIR GTest test

echo
echo DONE
