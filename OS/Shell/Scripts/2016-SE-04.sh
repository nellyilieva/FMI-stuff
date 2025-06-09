#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 args"
    exit 1
fi

if [[ ! $1 =~ ^-?[0-9]+$ || ! $2 =~ ^-?[0-9]+$ ]]; then  # '^[1-9][0-9]*$'
    echo "It is not a number"
    exit 1
fi

min="$1"
max="$2"

if (( min > max )); then
    echo "First number must be less than or equal to second number"
    exit 1
fi

mkdir -p a b c

find . -type f | while IFS= read -r file; do
    lines=$(cat "$file" | wc -l)

    if [[ lines -lt "$min" ]]; then
        mv "$file" a/
    else if [[ ${lines} -gt "$min" && ${lines} -lt "$max" ]]; then
        mv "$file" b/
    else
        mv "$file" c/
    fi
done