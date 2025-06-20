#!/bin/bash

if [[ "$#" -ne 1 ]]; then
    echo "Usage: $0 <spec_file>" >&2
    exit 1
fi

spec_file="$1"
if [[ ! -f "$spec_file" ]]; then
    echo "Error: '$spec_file' is not a valid file." >&2
    exit 1
fi

# We'll store the latest rule for each path in a temporary file (path -> line),
# and at the end, process the file line by line.

tmpfile=$(mktemp)
trap 'rm -f "$tmpfile"' EXIT

# Save the last occurrence of each path (simulate associative array):
# We do this by reading all lines and overwriting previous occurrences
# (just append lines, then use awk to keep last occurrence).

while IFS= read -r line; do
    # skip empty and comment lines
    if [[ -z "$line" || "$line" =~ ^# ]]; then
        continue
    fi
    # Extract the path (first field, before first space)
    path=$(echo "$line" | cut -d' ' -f1)
    # Remove old line for this path from tmpfile
    grep -v -F -- "$path " "$tmpfile" > "${tmpfile}.tmp" 2>/dev/null || true
    mv "${tmpfile}.tmp" "$tmpfile" 2>/dev/null || true
    # Append current line to tmpfile
    echo "$line" >> "$tmpfile"
done < "$spec_file"

# Now process tmpfile line by line
while IFS= read -r line; do
    # Parse line fields one by one (no arrays!)
    # Format can be:
    # <filename> file <permissions>
    # <dirname> dir <permissions>
    # <linkname> symlink <target>
    # <filename> nonexistant
    # Possibly owner:group before permissions

    # Get path and type first
    path=$(echo "$line" | cut -d' ' -f1)
    type=$(echo "$line" | cut -d' ' -f2)

    # Initialize variables
    owner=""
    group=""
    perms=""
    target=""

    # If type == nonexistant, no more fields
    if [[ "$type" == "nonexistant" ]]; then
        # Ensure path does not exist
        if [[ -e "$path" || -L "$path" ]]; then
            rm -rf "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to remove $path" >&2
            fi
        fi
        continue
    fi

    # If type is symlink, target is the last field
    if [[ "$type" == "symlink" ]]; then
        # target is everything after 'symlink '
        target=$(echo "$line" | sed -E "s|^$path symlink ||")
    else
        # For file or dir, next field can be owner:group or permissions
        third=$(echo "$line" | cut -d' ' -f3)

        # Check if third contains ':', then it's owner:group
        if echo "$third" | grep -q ":"; then
            owner=$(echo "$third" | cut -d':' -f1)
            group=$(echo "$third" | cut -d':' -f2)
            # permissions is field 4
            perms=$(echo "$line" | cut -d' ' -f4)
        else
            # No owner:group, perms is field 3
            perms="$third"
        fi
    fi

    # Create parent dir if needed
    parentdir=$(dirname "$path")
    if [[ ! -d "$parentdir" ]]; then
        mkdir -p "$parentdir" 2>/dev/null
        if [[ $? -ne 0 ]]; then
            echo "Failed to create directory $parentdir" >&2
        fi
    fi

    # Now process according to type

    if [[ "$type" == "file" ]]; then
        # If exists but not regular file, delete
        if [[ -e "$path" && ! -f "$path" ]]; then
            rm -rf "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to remove $path" >&2
            fi
        fi
        # Create file if not exists
        if [[ ! -f "$path" ]]; then
            touch "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to create file $path" >&2
            fi
        fi
        # Set permissions if needed
        chmod "$perms" "$path" 2>/dev/null
        if [[ $? -ne 0 ]]; then
            echo "Failed to chmod $path" >&2
        fi
    elif [[ "$type" == "dir" ]]; then
        # If exists but not directory, delete
        if [[ -e "$path" && ! -d "$path" ]]; then
            rm -rf "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to remove $path" >&2
            fi
        fi
        # Create directory if not exists
        if [[ ! -d "$path" ]]; then
            mkdir -p "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to create directory $path" >&2
            fi
        fi
        # Set permissions if needed
        chmod "$perms" "$path" 2>/dev/null
        if [[ $? -ne 0 ]]; then
            echo "Failed to chmod $path" >&2
        fi
    elif [[ "$type" == "symlink" ]]; then
        # If exists but not symlink or points elsewhere, delete
        if [[ -L "$path" ]]; then
            current_target=$(readlink "$path")
            if [[ "$current_target" != "$target" ]]; then
                rm "$path" 2>/dev/null
                if [[ $? -ne 0 ]]; then
                    echo "Failed to remove symlink $path" >&2
                fi
            fi
        elif [[ -e "$path" ]]; then
            rm -rf "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to remove $path" >&2
            fi
        fi
        # Create symlink if doesn't exist
        if [[ ! -L "$path" ]]; then
            ln -s "$target" "$path" 2>/dev/null
            if [[ $? -ne 0 ]]; then
                echo "Failed to create symlink $path -> $target" >&2
            fi
        fi
    fi

    # Finally, set owner and group if given
    if [[ -n "$owner" && -n "$group" ]]; then
        chown "$owner":"$group" "$path" 2>/dev/null
        if [[ $? -ne 0 ]]; then
            echo "Failed to chown $path to $owner:$group" >&2
        fi
    fi

done < "$tmpfile"
