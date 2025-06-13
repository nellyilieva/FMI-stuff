#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 args"
    exit 1
fi

if [[ ! -f "${1}" || ! -f "${2}" ]]; then
    echo "Needs to be files"
    exit 1
fi

if ! echo "$1" | grep -q "^.*\.csv$"; then  # echo gives the file name as string, so we use it here
	echo "ERROR"
	exit 2
fi

if ! echo "$2" | grep -q "^.*\.csv$"; then
	echo "ERROR"
	exit 2
fi

cat "$1" | cut -d ',' -f 2- | sort | uniq | while read -r TEXT; do
    lines=$(cat "$1" | grep "^[1-9][0-9]*,${TEXT}$")
    echo "${lines}" | sort -t ',' -n -k 1 | head -n 1 >> "$2"
done  # done < <(cat "$1" | cut -d ',' -f 2- | sort | uniq)

# my idea is to extraxt every line's id, then compare the line one by one with evry other line... we can save the id's in temp file
# we can just extract evry string from the lines, then compare it to every line and save the lines with the same string in lines
# then we just sort this lines by id, head -n1 and write it to the second file