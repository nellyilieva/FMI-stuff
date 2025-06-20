#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    exit 1
fi

if [[ ! -f "$1" || ! -f "$2" ]]; then
    exit 1
fi

# for line in file, we take the laguage, the options, the dir
# maybe first we create the exit dir with the needed name
# then we create the command

input_base=$(basename "$2")
input_name="${input_base%.*}"
# basename "$input_base" .g4

while read -r line; do

    language=$(echo "$line" | cut -d ' ' -f1)
    options=$(echo "$line" | awk '{ for (i = 2; i < NF; ++i) printf $i }' | xargs)
    dir=$(echo "$line" | awk ' { print $NF } ')

    if [[ ! -d "$dir" ]]; then
        exit 1
    fi

    full_path="${dir}/${input_name}"
    mkdir -p "$full_path"

    cmd="antlr4 -Dlanguage=${language}"

    if ! echo "$options" | grep -qw "listener"; then
        cmd+=" -no-listener"
    fi

    if echo "$options" | grep -qw "visitor"; then
        cmd+=" -visitor"
    fi

    cmd+=" -o ${full_path} ${2}"

    echo "$cmd"

done < "$1"