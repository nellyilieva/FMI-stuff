#!/bin/bash

# checks

files=$(find "$2" -type f -name "*.txt")

echo "$files" | while read -r file; do
    cat "$1" | while read -r word; do
        if [[ -z "$word" ]]; then
            continue;
        fi

        stars=$(printf '%*s' "${#word}" | tr ' ' '*')

        sed -E -i "s/(^|[^[:alnum:]_])$word([^[:alnum:]_]|$)/\1$stars\2/g" "$file"
    done
done

# ^ → start of the line, or
# [^[:alnum:]_] → a character that is not a letter (a-z), digit (0-9), or underscore (_)
# \1 -> group 1