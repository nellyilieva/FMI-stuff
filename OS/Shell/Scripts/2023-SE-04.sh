#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "The argument must be a directory"
    exit 2
fi

hashes=$(mktemp)
bytes_saved=0
groups=0
last_hash=""
last_file=""
group_counted=0

find "$1" -type f -print0 2>/dev/null | xargs -0 sha256sum 2>/dev/null | sort > "$hashes"

while read -r hash path; do
    if [[ "$hash" == "$last_hash" ]]; then
        if [[ -f "$path" && -f "$last_file" ]]; then
            size=$(stat -c%s "$path")
            rm "$path"
            ln "$last_file" "$path"
            bytes_saved=$((bytes_saved + size))
            if [[ $group_counted -eq 0 ]]; then
                groups=$((groups + 1))
                group_counted=1
            fi
        fi
    else
        last_hash="$hash"
        last_file="$path"
        group_counted=0
    fi
done < "$hashes"

echo "Deduplicated groups: $groups"
echo "Disk space saved: $bytes_saved bytes"

rm "$hashes"
