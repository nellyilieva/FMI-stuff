#!/bin/bash

# check for everything

src="$1"
dst="$2"
str="$3"

find "$src" -type f | while read -r file; do
    filename=$(basename "$file")
    if echo "$filename " | grep -q "$str"; then
        relative_path="${file#"$src"/}"
        destination_dir=$(dirname "$dst/$relative_path")

        mkdir -p "$destination_dir" || {
            echo "Error: Failed to create directory '$destination_dir'. Skipping move for '$file'."
            continue
        }

        mv "$file" "$destination_dir/" || {
            echo "Error: Failed to move file '$file' to '$destination_dir/'. Skipping."
        }
    fi
done

# files=$(find "$1" -type f -name "*${3}*")

# while IFS= read -r file; do

#     cp --parents "$file" "$2"
#     rm "$file"

# done < <(echo "$files")