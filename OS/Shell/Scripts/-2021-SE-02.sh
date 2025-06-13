#!/bin/bash

if [[ "${#}" -eq 0 ]]; then
    echo "0"
    exit 1
fi

for file in "${@}"; do
    bump_serial "${file}"
done

