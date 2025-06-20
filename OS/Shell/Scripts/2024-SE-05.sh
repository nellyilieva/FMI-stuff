#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "must have 2 args"
    exit 1
fi

if [[ ! -f "$2" ]]; then
    echo "the second arg '$2' must be file"
    exit 1
fi

if [[ -z "$1" ]]; then
    echo "The first arg '$1' is empty"
    exit 1
fi

cmd="$1"

value=$("$cmd" 2>/dev/null)
status=$?

if [[ "$status" -ne 0 ]]; then
    exit 3
fi

if ! [[ "$value" =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
    exit 3
fi

timestamp="$(date '+%Y-%m-%d %H:%M')"
day_of_week="$(date '+%u')"
hour_of_day="$(date '+%H')"

echo "${timestamp}|${day_of_week}|${hour_of_day}|${value}" >> "$2"

values=$(awk -F'|' -v d="$day_of_week" -v h="$hour_of_day" ' $2 == d && $3 == h { print $4 } ' "$2")

count=$(echo "$values" | wc -l)

if [[ "$count" -le 1 ]]; then
    exit 0
fi

sum=0
for v in $values; do
    sum=$(echo "$sum + $v" | bc -l)
done

avg=$(echo "$sum / $count" | bc -l)

lower=$(echo "$avg / 2" | bc -l)
upper=$(echo "$avg * 2" | bc -l)

comp1=$(echo "$value < $lower" | bc -l)
comp2=$(echo "$value > $upper" | bc -l)

if [[ "$comp1" -eq 1 || "$comp2" -eq 1 ]]; then
    dt=$(date '+%Y-%m-%d %H')
    echo "$dt: $value abnormal"
    exit 2
fi

exit 0