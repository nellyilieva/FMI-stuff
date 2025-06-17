#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Needs 1 arg"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "Needs to be file"
    exit 1
fi

WAKEUP='/proc/acpi/wakeup'

cat "$1" | while read -r line; do
    clean_line=$(echo "${line}" | cut -d '#' -f1)

    if [[ "${clean_line}" =~ ^\s*$ ]]; then
        continue
    fi

    name=$(echo "$clean_line" | awk ' {print $1} ' )   # read name new_st < <(echo "${clean_line}")
    new_st=$(echo "$clean_line" | awk ' {print $2} ' )

    if [[ -z "$name" || -z "$new_st" ]]; then
        echo "Warning: Invalid line format: $line"
        continue
    fi

    if [[ "$new_st" != "enabled" && "$new_st" != "disabled" ]]; then
        echo "Warning: Invalid state '$new_st' for device '$name'. Must be 'enabled' or 'disabled'"
        continue
    fi

    if ! grep -qE "^\s*${name}\b" "$WAKEUP"; then
        echo "Warning: ${name} not found"
        continue
    fi

    st=$(cat "$WAKEUP" | awk -v "name=${name}" '$1 == name { print $3 }')

    if [[ "*${new_st}" != "$st" ]]; then
        echo "Changing $name: $st -> *$new_st"
        echo "$name" > "$WAKEUP"
    else
        echo "$name: already $st"
    fi
done