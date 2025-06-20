#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 args"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "Needs to be file"
    exit 1
fi

# if [[ ! ${1} =~ .*.csv ]]; then
#     echo "must be csv file"
#     exit 1
# fi

constel=$(cat "$1" | awk -F',' -v t="$2" ' $5 == t && $4 != "--" { print $4 } ' | sort | uniq -c | sort -nr | head -n1 | awk '{ print $2 }')

if [[ -z "$constel" ]]; then
    echo "no constellation"
    exit 2
fi

res=$(cat "$1" | awk -F',' -v c="$constel" '$4 == c && $7 != "--" { print $7, $1 } ' | sort -n | head -n1 | cut -d' ' -f2-)

echo "$res"