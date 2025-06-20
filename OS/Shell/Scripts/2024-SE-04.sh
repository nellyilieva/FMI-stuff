#!/bin/bash

# checks

file="$1"
bakefile="bakefile"

rule=$(grep -E "^${file}:" "$bakefile")

if [[ -z "$rule" ]]; then
    if [[ ! -f "$file" ]]; then
        echo "Error: file '$file' not found and no rule to build it"
        exit 2
    fi
    echo "Already built: $file"
    exit 0
fi

deps=$(echo "$rule" | cut -d ':' -f2)
cmd=$(echo "$rule" | cut -d ':' -f3-)

for dep in $deps; do
    ./bake.sh "$dep"
done

rebuild=false
if [[ ! -f "$file" ]]; then
    rebuild=true
else
    for dep in $deps; do
        if [[ "$dep" -nt "$file" ]]; then
            rebuild=true
            break
        fi
    done
fi

if $rebuild; then
    echo "Building: $file"
    eval "$cmd"
else
    echo "Up to date: $file"
fi