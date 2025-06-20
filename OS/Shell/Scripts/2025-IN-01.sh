#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    exit 1
fi

if [[ ! -f "$1" ]]; then
    exit 1
fi

if [[ $(id -u) -ne 0 ]]; then
    exit 1
fi

while IFS= read -r line; do

    dir="$(echo "$line" | cut -d' ' -f1)"
    typ="$(echo "$line" | cut -d' ' -f2)"
    bits="$(echo "$line" | cut -d' ' -f3)"

    if [[ ! -d "$dir" ]]; then
        echo "not dir"
        continue
    fi

    pref=""

    if [[ "$typ" == "A" ]]; then
        pref="/"
    elif [[ "$typ" == "T" ]]; then
        pref="-"
    fi

    find "${dir}" -mindepth 1 -type f -perm "${pref}${bits}" -print0 | while IFS= read -r -d '' f; do
        chmod 775 "$f"
    done

    find "${dir}" -mindepth 1 -type d -perm "${pref}${bits}" -print0 | while IFS= read -r -d '' d; do
        chmod 755 "$d"
    done

done < "$1"