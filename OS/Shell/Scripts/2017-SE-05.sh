#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 arg"
    exit 1
fi

if [[ ! -d "${1}" ]]; then
    echo "Needs to be dir"
    exit 1
fi

if [[ -z $2 ]]; then
    echo "Second argument must be a non-empty string"
fi

files=$(find "$1" -maxdepth 1 -type f -printf "%f\n" | grep -E "^vmlinuz-[0-9]*\.[0-9]*\.[0-9]*-${2}")
result=$(echo "$files"| sort -r -n -t '.' -k2 | head -n1)  # wrong sort :(

echo "$result"