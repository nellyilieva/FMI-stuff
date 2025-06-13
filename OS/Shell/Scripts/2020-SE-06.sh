#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    echo "3 args"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "arg file"
    exit 2
fi

if [[ -z "$2" || -z "$3" ]]; then
    echo "args empty"
    exit 1
fi

file="${1}"
key="${2}"
value="${3}"

date=$(date)
user=$(whoami)

temp_file=$(mktemp)
found=false

if ! [[ "$key" =~ ^[a-zA-Z0-9_]+$ ]]; then
    echo "key format"
    exit 1
fi

if ! [[ "$value" =~ ^[a-zA-Z0-9_]+$ ]]; then
    echo "val format"
    exit 1
fi

cat "$file" | while read -r line; do
    lkey=$(echo "$line" | cut -d '=' -f1 | xargs)
    lval=$(echo "$line" | cut -d '=' -f2 | xargs)

    if [[ "$key" == "$lkey" ]]; then
        if [[ "$value" != "$lval" ]]; then
            echo "# $line # edited at $date by $user" >> "$temp_file"
            echo "$key = $value # added at $date by $user" >> "$temp_file"
        else
            echo "$line" >> "$temp_file"
        fi
        found=true
    else
        echo "$line" >> "$temp_file"
    fi
done

if ! $found; then
    echo "$key = $value"
fi

mv "$temp_file" "$file"