#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "There must be 1 arg"
    exit 1
fi

if [[ ! -d "${1}" ]]; then
    echo "Must be log dir"
    exit 1
fi

dir="$1"

find "$dir" -type f -name "*.txt" | while read -r file; do
    friend=$(basename "$(dirname "$file")") # извлича името на приятеля
    lines=$(wc -l < "$file")                # брой редове в лога
    echo "$friend $lines"                   # печата "приятел брой"
done | awk '
{
    count[$1] += $2
}
END {
    for (f in count)
        print count[f], f
}
' | sort -nr | head -n 10        # сортира и извежда топ 10