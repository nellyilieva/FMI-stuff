#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    echo "Needs 3 args"
    exit 1
fi

# check if first 2 are files; check with -z 3 exist

f=$(cat "$1" | awk -F':' -v n="$3" ' $1 == n { print $2 }' | grep -o -E '[0-9]+(\.[0-9]+)?')
s=$(cat "$2" | awk -F':' -v n="$3" ' $1 == n { print $2 }' | grep -o -E '[0-9]+(\.[0-9]+)?')

# check with -z if exist

if [[ "$f" -gt "$s" ]]; then
    echo "$1"
    exit 0
elif [[ "$f" -lt "$s" ]]; then
    echo "$1"
    exit 0
else
    echo "same or no"
    exit 0
fi