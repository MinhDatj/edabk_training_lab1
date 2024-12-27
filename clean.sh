#!/bin/bash

file1="LinkList.exe"
file2="name.txt"
if [ -f "$file1" ]; then
	rm "$file1"
fi
if [ -f "$file2" ]; then
	rm "$file2"
fi
	
