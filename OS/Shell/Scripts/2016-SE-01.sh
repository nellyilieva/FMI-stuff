# Напишете shell скрипт, който по подаден един позиционен параметър, ако този параметър
# е директория, намира всички symlink-ове в нея и под-директориите ѝ с несъществуващ destination.

#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Need 1 arg"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "Needs to be dir"
    exit 1
fi

find "$1" -type l | while read -r s; do
    if [[ ! -e "$s" ]]; then   #e -> does it exist
        echo "$s"
    fi
done
