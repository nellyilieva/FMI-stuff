#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    exit 1
fi

if [[ -z "$(echo "$1" | egrep "^[0-9]*$")" ]]; then
    exit 2
fi

unitsFile="base.csv"
prefixFile="prefix.csv"

prefix="$(cat "$prefixFile" | tail -n +2 | cut -d, -f2-3 | grep -E "^${2}," | cut -d, -f2)"

if [[ -z "$prefix" ]]; then
    exit 3
fi

base="$(cat "$unitsFile" | tail -n +2 | cut -d, -f2-3 | grep -E "^${3},")"

if [[ -z "$base" ]]; then
    exit 4
fi

baserow="$(cat "$unitsFile" | tail -n +2 | grep -E "${base}")"

info="("$(echo "$baserow" | awk -F, ' { print $3", "$1 } ')")"
num="$(echo "${1} * ${prefix}" | bc)"

echo ""${num}" "${2}" "${info}""
