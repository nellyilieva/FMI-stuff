#!/bin/bash

N=10

if [ "${1}" = "-n" ]; then
	N=${2}
    shift 2
fi

temp=$(mktemp)

for f in "$@"; do
    id=$(echo "$f" | cut -d '.' -f1)   # id="${f%.log}" -> remove .log from the end

    tail -n "$N" "$f" | while read -r line; do
        time=$(echo "$line" | cut -d ' ' -f1,2)
        data=$(echo "$line" | cut -d ' ' -f3-)

        echo "$time $id $data"
    done
done >> "$temp"

cat "$temp" | sort -t ' ' -k1,2

# rm "$temp"