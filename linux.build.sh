#!/bin/bash
# build everything and generate a new wheel.
# the windows binaries need to already be up to date

make clean
make
cp -rvf bin/* tokenex
python3 setup.py bdist_wheel
