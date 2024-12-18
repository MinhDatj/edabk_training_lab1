#!/bin/bash

SOURCE="/mnt/d/C++ projects \(devcpp\)/Projects/LinkList/LinkList.c"
OUTPUT="~/training/LinkList.exe"

#gcc $SOURCE -o $OUTPUT
gcc /mnt/d/C++\ projects\ \(devcpp\)/Projects/LinkList/LinkList.c -o ~/training/LinkList.exe

echo "Compilation completed! Program's location is: $(pwd)/LinkList.exe"

