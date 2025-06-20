#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    exit 1
fi

if [[ -z "$1" ]]; then
    exit 1
fi

if [[ ! -f "$2" ]]; then
    exit 1
fi

teams=$(cat "$2" | cut -d' ' -f3 | sort | uniq)

while read -r team; do
    echo "; team "$team""
    zones="$(cat "$2" | awk -v team=$team ' $3==team { print $2 } ')"
    servers="$(cat "$2" | awk -v team=$team ' $3==team { print $1 } ')"

    while IFS= read -r zone; do
        while IFS= read -r server; do
            echo "${zone} IN NS ${server}.${1}."
        done < <(echo "$servers")
    done < <(echo "$zones")

done < <(echo "$teams")