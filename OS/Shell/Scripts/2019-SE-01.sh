#!/bin/bash

# a
maxNum=0
temp=$(mktemp)

while read -r line; do
    if ! echo "$line" | grep -Eq "^[-]?[0-9]+$"; then
        continue
    fi

    echo "$line" >> "$temp"

    if [[ "$line" == -* ]]; then
        abs=$(echo "$line" | cut -d '-' -f2)
    else
        abs="$line"
    fi

    if [[ "$abs" -gt "$maxNum" ]]; then
        maxNum="$abs"
    fi
done

sort -n "$temp" | uniq | while read -r num; do
    if [[ "$num" == -* ]]; then
        abs=$(echo "$num" | cut -d '-' -f2)
    else
        abs="$num"
    fi

    if [[ "$abs" -eq "$maxNum" ]]; then
        echo "$num"
    fi
done

rm "$temp"

# b
maxSum=0
temp=$(mktemp)

while read -r line; do
    if ! echo "$line" | grep -Eq "^[-]?[0-9]+$"; then
        continue
    fi

    if [[ "$line" == -* ]]; then
        abs=$(echo "$line" | cut -d '-' -f2)
    else
        abs="$line"
    fi

    digitSum=0
    for digit in $(echo "$abs" | fold -w1); do   # fold -w <width> -w 1 means: break the input into lines, each 1 character wide.
        digitSum=$((digitSum + digit))
    done

    echo "$line $digitSum" >> "$temp"

    if [[ "$digitSum" -gt "$maxSum" ]]; then
        maxSum="$digitSum"
    fi
done

awk -v max="$maxSum" '$2 == max { print $1 }' "$temp" | sort -n | uniq | head -n 1

rm "$temp"