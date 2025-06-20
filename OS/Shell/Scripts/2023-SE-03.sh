#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Wring count args"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "First arg must be dir"
    exit 1
fi

# files=$(find "$1" -type f )

ocurrences=$(mktemp)

while read -r f; do
    cat "$f" | grep -E -o '[a-z]+' | sort | uniq -c | awk ' $1 >= 3 {print $2} ' >> "$ocurrences"
done < <(find "${1}" -type f)

count_files=$(find "$1" -type f | wc -l)

cat "$ocurrences" | sort | uniq -c | sort -nr | awk -v num="$count_files" ' $1 >= num/2 { print $2 } ' | head -n 10

rm "$ocurrences"