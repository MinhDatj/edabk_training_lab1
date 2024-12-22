#!/bin/bash

#SOURCE=$1
git clone "$1" && cd "$(basename "$1" .git)"

#run and automatically cd into your repo by ". ./clone.sh <repo_name>"
