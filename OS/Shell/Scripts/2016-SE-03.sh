# while IFS=: read -r username _ _ _ _ homedir _
# IFS=':' → tells read to split fields using : as delimiter.

# read -r → reads the line as-is (without interpreting backslashes).
# Fields:
# username
# _ → skipped field (we ignore password, group ID, etc.)
# $homedir → home directory
# The final _ skips the shell.


#!/bin/bash

if [[ $(id -u) -ne 0 ]]; then
    echo "Not from root"
    exit 1
fi

cat /etc/passwd | while read -r usr; do
    username=$(echo "$usr" | cut -d ':' -f1)
    homedir=$(echo "$usr" | cut -d ':' -f6)

    if [[ -z "$username" || -z "$homedir" ]]; then   # -z check is string has zero length
        continue
    fi

    if [[ ! -d "$homedir" ]]; then
        echo "No homedir exist"
        continue
    fi

    owner=$(stat -c %U "$homedir")   #-c %U -> only owner username
    perm=$(stat -c "%a" "$homedir")

    if [[ "$owner" == "$username" ]]; then
        owner_perm=$(( perm / 100 ))
        if (( (owner_perm & 2) == 0 )); then
            echo "$owner", missing write permission
        fi
    else
        echo "$username does not own $homedir, skipping write check"
    fi
done
