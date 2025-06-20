#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Need 2 args"
    exit 1
fi

if [[ ! -d "${1}" ]]; then
    echo "${1}: not a directory" >&2
    exit 2
fi

if [[ ! -e "${2}" || -d "${2}" ]]; then
    echo "wrong second arg"
    exit 3
fi

camera="$1"
library="$2"

while read -r f; do

done < <(find "$camera" -type f -name "*.jpg")
