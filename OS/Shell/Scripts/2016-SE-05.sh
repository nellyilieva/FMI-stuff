# file="$(basename $1)" -> basename is a Unix command that extracts the filename from a path, removing any leading directory components

#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 args"
    exit 1
fi

if [[ ! -f "${1}" || ! -f "${2}" ]]; then
    echo "Needs to be files"
    exit 1
fi

file1=$(basename "$1")
file2=$(basename "$2")

firstLines=$(grep "$file1" "$1" | wc -l)
secondLines=$(grep "$file2" "$2" | wc -l)

if [[ $firstLines -gt $secondLines ]]; then
    cut -d ' ' -f4- ${1} | sort > "$file1.songs"  # we extract from field 4 to the end of the line
else
    cut -d ' ' -f4- ${2} | sort > "$file2.songs"
fi