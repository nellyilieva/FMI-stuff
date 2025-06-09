#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Needs 1 arg"
    exit 1
fi

if [[ ! -f "${1}" ]]; then
    echo "Needs to be file"
    exit 1
fi

i=1

while IFS= read -r line; do
    line=$(cat $(line) | cut -d ' ' -f4-)
    lines+="$i.$line\n"
    i=$((i+1))
done < ${1}

echo -e ${lines} | sort -k2 -t '"'

# awk 'BEGIN { line=1; }{$3=line".";output=$3;for (f=4;f<=NF;f++) {output=output" "$f;}print output;line++;}'  "$1" | sort -t' ' -k2,2