#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "args mismatch"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "not directory"
    exit 2
fi

graph=$(mktemp)

while read -r file; do
    className=$(cat "${file}" | cut -d ":" -f1 | cut -d ' ' -f2)

    if [[ ! "$className"  =~ ^[^0-9][a-zA-Z0-9_]*$ ]]; then
        continue
    fi

    if ! grep -q "^${className}$" "${graph}"; then
        echo "$className" >> "$graph"
    fi

    descendant=$(cat "${file}" | awk -F ':' ' $2!="" {print $2} ' | tr ',' '\n')

    if [[ -z ${descendant} ]]; then
        continue
    fi

    while read -r mode parent; do

        if [[ ! $parent  =~ ^[^0-9][a-zA-Z0-9_]*$ ]]; then
            continue
        fi

        if ! grep -q "^${parent}$" "$graph"; then
            echo "$parent" >> "$graph"
        fi

        echo "${parent} -> ${className}" >> "$graph"

    done < <(echo "${descendant}" | sed -E 's/^ //g' )

done < <(find ${1} -type f -name "*.h" 2>/dev/null)

sort "$graph" > "$2"
# dag-get ${graph} > ${2}
rm "${graph}"