#!/usr/bin/bash

# Since cmake 3.22, the following environment variables specify a default value when there is no explicit configuration
# given on the first run.

CMAKE_BUILD_TYPE=Release
CMAKE_CXX_COMPILER=/usr/bin/x86_64-linux-gnu-g++-11
CMAKE_C_COMPILER=/usr/bin/x86_64-linux-gnu-gcc-11

# For previous versions of cmake, make an environment variable that can be passed along in the command-line.
CMAKE_ARGS=" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
CMAKE_ARGS+=" -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
CMAKE_ARGS+=" -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}"
