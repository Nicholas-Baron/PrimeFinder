#!/bin/bash

FILE="lint.txt"

echo Output File: $FILE

BIG_OPTIONS="-format-style='none' Prime_Finder.cpp Is_Prime.cpp *.hpp -- -std=c++17"

echo Using following options | tee $FILE
echo

clang-tidy -dump-config | tee -a $FILE

echo
echo Starting General Clean | tee -a $FILE
echo

clang-tidy $BIG_OPTIONS  | tee -a $FILE

echo Done | tee -a $FILE
