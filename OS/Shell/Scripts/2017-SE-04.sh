#!/bin/bash

[[ "${#}" -ge 1 ]] || { echo "wrong args" >&2; exit 1; }
[[ -d "${1}" ]] || { echo "${1}: must be a dir" >&2; exit 2; }

broken=0

find "${1}" -type l | while read file; do
    if [[ -e "${file}" ]]; then   # check if the file that the sl points to exist => check if is valid symlink
        if [[ "$#" -eq 2 ]]; then
            echo "$(basename "${file}") -> $(readlink "${file}")" >> "$2"
        else
            echo "$(basename "${file}") -> $(readlink "${file}")"
        fi
    else
        broken=$((broken + 1))
    fi
done

if [[ "$#" -eq 2 ]]; then
    echo "Broken symlinks: ${broken}" >> "$2"
else
    echo "Broken symlinks: ${broken}"
fi


# readlink -f "$symlink" -> връща реалната дестинация.
# [[ -e "$target" ]] -> проверява дали дестинацията съществува.