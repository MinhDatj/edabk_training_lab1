#!/bin/bash

if [ ! -f LinkList.exe ]; then #flag -f checks if a path is a regular file
	echo "File LinkList.exe not found!" 
	exit 1
fi

while IFS= read -r file
do
	if [ -f "$file" ]; then
		rm "$file"
		echo "Deleted: $file"
	else 
		echo "File not found: $file"
	fi
done
