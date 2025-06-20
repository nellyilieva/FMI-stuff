#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Need only 1 arg"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "Needs to be dir"
    exit 1
fi

hash=$(find "${1}" -mindepth 1 -maxdepth 1 -type f -exec sha256sum {} \;)
sorted_hash=$(echo "$hash" | cut -d ' ' -f1 | sort | uniq)

echo "$sorted_hash" | while read -r h; do
    # Get all files with the same hash (same measurement)
    files=$(echo "$hash" | grep -E "${h}" | cut -d ' ' -f2-)
    files_inodes=""

    # Collect filenames and their inode numbers
    echo "$files" | while read -r f; do
        curr=$(stat "${f}" --printf "%n %i")
        tmp=$(echo -e "${files_inodes}\n${curr}")
        files_inodes=$tmp
    done

    # Extract inode numbers
    inodes=$(echo "${files_inodes}" | tail -n +2 | cut -d ' ' -f 2 | sort)
	uniq_ind=$(echo "${inodes}" | uniq)

    # Count total files and unique inodes
	ind_count=$(echo "${inodes}" | wc -l)
	ind_lines=$(echo "${uniq_ind}" | wc -l)

    # Separate files by inode frequency:
    # Find which inodes are hardlinks (appear more than once)
    hardlink_inodes=""
    separate_inodes=""
    for inode in $uniq_ind; do
        count=$(grep -c " $inode\$" <<< "$files_inodes")
        if (( count > 1 )); then
            hardlink_inodes+="$inode"$'\n'
        else
            separate_inodes+="$inode"$'\n'
        fi
    done

	# Rule 3 check: are there both hardlink groups and separate files?
    if [[ -n "$hardlink_inodes" && -n "$separate_inodes" ]]; then
        # Mixed case: 
        # Delete all separate files, and reduce hardlink groups by one file

        # Delete separate files (one per inode)
        for inode in $separate_inodes; do
            file_to_delete=$(grep " $inode\$" <<< "$files_inodes" | cut -d ' ' -f1)
            echo "Deleting separate file: $file_to_delete"
            rm -f -- "$file_to_delete"
        done

        # For each hardlink group, keep one and delete the rest
        for inode in $hardlink_inodes; do
            files_for_inode=$(grep " $inode\$" <<< "$files_inodes" | cut -d ' ' -f1)
            # keep first, delete rest
            first=1
            while IFS= read -r file; do
                if (( first == 1 )); then
                    first=0
                else
                    echo "Deleting hardlink: $file"
                    rm -f -- "$file"
                fi
            done <<< "$files_for_inode"
        done

    else
        # Only separate files or only hardlink groups

        if (( ind_count == ind_lines )); then
            # All files have unique inodes (separate files)
            # Keep one file, delete the rest
            files_to_delete=$(echo "$files" | head -n -1)
            while IFS= read -r fdel; do
                echo "Deleting duplicate file: $fdel"
                rm -f -- "$fdel"
            done <<< "$files_to_delete"

        else
            # Only hardlink groups present
            # For each hardlink group keep one, delete the rest
            for inode in $uniq_ind; do
                files_for_inode=$(grep " $inode\$" <<< "$files_inodes" | cut -d ' ' -f1)
                count=$(wc -l <<< "$files_for_inode")
                if (( count > 1 )); then
                    first=1
                    while IFS= read -r file; do
                        if (( first == 1 )); then
                            first=0
                        else
                            echo "Deleting hardlink: $file"
                            rm -f -- "$file"
                        fi
                    done <<< "$files_for_inode"
                fi
            done
        fi
    fi

done
