#!/bin/bash

if [[ "${#}" -eq 0 ]]; then
    echo "Needs more args"
    exit 1
fi

replacements=$(mktemp)

for arg in "$@"; do
    if [[ "$arg" =~ ^-R ]]; then
        echo "$arg" >> "$replacements"
    fi
done

if [[ ! -s "$replacements" ]]; then
    echo "No replacement arguments (-R) given"
    rm "$replacements"
    exit 1
fi

for file in "$@"; do
    if [[ "$file" =~ ^-R ]]; then
        continue
    fi

    if [[ ! -f "$file" ]]; then
        echo "Warning: $file is not a file, skipping"
        continue
    fi

    temp=$(mktemp)
    cp "$file" "$temp"

    while read -r rep; do
        old="$(echo "$rep" | cut -c 3- | cut -d'=' -f1)"
        new="$(echo "$rep" | cut -c 3- | cut -d'=' -f2)"

        # Use pwgen or fallback if not installed for unique token
        token=$(command -v pwgen &>/dev/null && pwgen 64 1 || echo "__UNIQ__TOKEN__")

        sed -Ei "s/(^| )${old}( |$)/\1${new}${token}\2/g" "$temp"
    done < "$replacements"

    sed -E "s/(^| )([^[:space:]]*)[[:alnum:]_]{8,}( |$)/\1\2\3/g" "$temp" > "$file"

    rm "$temp"
done

rm "$replacements"

# We want to replace whole words exactly, without accidentally replacing words multiple times.
# To do that, when we replace old with new, we temporarily append a unique token to the new word.
# token=$(command -v pwgen &>/dev/null && pwgen 64 1 || echo "__UNIQ__TOKEN__")
