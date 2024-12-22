#!/bin/bash

#SOURCE=$1
git clone $1

REPO_NAME=$(basename "$1" .git)

if [ -d "$REPO_NAME" ]; then
	echo "successfully cloned into $REPO_NAME"
	cd "$REPO_NAME" || exit
	echo "Now in directory: $(pwd)"
else 
	echo "Failed to clone reposistory."
	exit 1
fi
