#!/bin/bash

if [[ $# -eq 0 ]]; then
    echo "Scripts must take in 1(or 2) arguments"
    exit 1
fi

if [[ ! -d $1 || ! -r $1 ]]; then
    echo "First argument must be a readable directory"
    exit 2
fi

if [[ -n $2 ]]; then
    find "$1" -maxdepth 2 -type f -printf "%n %p\n" | while read -r line; do
        count=$(echo "$line" | cut -d ' ' -f2)

        if [[ "$count" -ge "$2" ]]; then
            echo "$line"
        fi
    done
else
    find "$1" -maxdepth 2 -type l -printf "%p %Y\n" | while read -r line; do  
        if echo "$line" | grep -q "(no type)$"; then
            echo "$line"
        fi
    done
fi

# p -> full path; Y -> type of target; if symlink is broken -> no type