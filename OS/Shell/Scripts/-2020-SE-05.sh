#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    echo "args-3"
    exit 1
fi

if [[ ! -f "${1}" || ! -f "${2}" || ! -d "${3}" ]]; then
    echo "args types"
    exit 1
fi

find "$3" -type f -name "*.cfg" | while read -r f; do
    invalid_lines=()
    line_num=0
    valid=true

    cat "$f" | while IFS= read -r line; do
        $line_num=(($line_num + 1))

        if [[ -z "$line" || "$line" =~ ^[[:space:]]*# ]]; then
            continue
        fi

        if ! [[ "$line" =~ ^[[:space:]]*\{[[:space:]]*([a-zA-Z0-9-]+;?)[[:space:]]*\}[[:space:]]*\;[[:space:]]*$ ]]; then
            invalid_lines+=("Line $line_num:$line")
            valid=false
        fi
    done

    if ! $valid; then
        # echo "Error in $(basename "$f"):"
        printf '%s\n' "${invalid_lines[@]}"
    else
        cat "$f" >> "$2"
        echo "" >> "$2"

        if ! grep -q "^$username:" "$password_file"; then
            password=$(pwgen 16 1)
            echo "$username:$(echo -n "$password" | md5sum | cut -d' ' -f1)" >> "$1"
            echo "$username $password"
        fi
    fi
done