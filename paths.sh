#!/bin/bash

BASE_PATH="<your-path-to-workspace>/.lib"
export PATH="$PATH:$BASE_PATH"
export PATH="$PATH:$BASE_PATH/z3/bin"
export JAVA_HOME="$BASE_PATH/openlogic-openjdk-17.0.13+11-linux-x64"
export PATH="$JAVA_HOME/bin:$PATH"
export PATH="$PATH:$BASE_PATH/CIVL-1.22_5854/bin"
export PATH="$PATH:$BASE_PATH/clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04/bin"
export LD_LIBRARY_PATH="$BASE_PATH/libtinfo5_6.3-2/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH"
export LD_LIBRARY_PATH="$BASE_PATH/clang+llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04/lib:$LD_LIBRARY_PATH"
