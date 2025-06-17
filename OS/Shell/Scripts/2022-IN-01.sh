#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "2 args"
    exit 1
fi

if [[ ! -d "$1" || ! -d "$2" ]]; then
    echo "Not dir"
    exit 1
fi

if [[ -n "$(find "$2" -mindepth 1 -printf "%p\n")" ]]; then
    echo "Not empty"
    exit 1
fi

find "$1" -type f ! -name '.*.swp' | while read -r f; do
    dest="${f/#$1/$2}"   # dest=$(echo "$f" | sed "s|^$1|$2|")
    mkdir -p "$(dirname "$dest")"
    cp -- "$f" "$dest"
done