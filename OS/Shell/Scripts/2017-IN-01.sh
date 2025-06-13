#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    echo "Needs 3 args"
    exit 1
fi

# file check
# check with -z if there is string with not 0 length
# check if key2 is in the file

key1="$2"
key2="$3"

vals1=$(cat "$1" | grep -E "^${key1}=" | cut -d '=' -f 2)
vals2=$(cat "$1" | grep -E "^${key2}=" | cut -d '=' -f 2)

for v in $vals1; do
    newVals=$(echo "$vals2" | sed "s/ *${v} *//g")
    vals2="$newVals"
done

sed -i "s/${key2}=.*/${key2}=${vals2}/g" "$1"