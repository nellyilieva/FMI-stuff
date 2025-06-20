#!/bin/bash

if [[ "${#}" -lt 2 ]]; then
    echo "wrong args"
    exit 1
fi

if [[ ! "$1" =~ ^-?[0-9]+$ ]]; then
    echo "It is not a number"
    exit 1
fi

# if [[ ! ${1} =~ ^[1-9]+[0-9]* ]]; then
#     echo "first arg is not number"
#     exit 2
# fi

sec="$1"
shift 1

cmd="$*"

start_time=$(date +%s.%N) # curr time in second.nanoseconds
count=0
total_time=0

while true; do
    iter_start=$(date +%s.%N)

    "$@"  # execut the command with args

    iter_end=$(date +%s.%N)

    iter_time=$(echo "scale=6; $iter_end - $iter_start" | bc)
    total_time=$(echo "scale=6; $total_time + $iter_time" | bc)

    count=$((count + 1))

    now=$(date +%s.%N)
    elapsed=$(echo "$now - $start_time" | bc)

    comp=$(echo "$elapsed >= $sec" | bc)
    if [[ $comp -eq 1 ]]; then
        break
    fi
done

total_runtime_fmt=$(printf "%.2f" "$total_time")
avg_runtime=$(echo "scale=4; $total_time / $count" | bc)
avg_runtime_fmt=$(printf "%.2f" "$avg_runtime")

echo "Ran the command '$cmd' $count times for $total_runtime_fmt seconds."
echo "Average runtime: $avg_runtime_fmt seconds."