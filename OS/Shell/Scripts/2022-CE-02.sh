#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Needs 1 arg"
    exit 1
fi

if [[ -z "$1" ]]; then
    echo "Needs name"
    exit 1
fi

echo "${1}" | grep -q -E "^[A-Z0-9]{,4}$"
if [[ ${?} -ne 0 ]] ; then
    echo "Invalid device"
    exit 1
fi

grep -q -E "${1}" /proc/acpi/wakeup
if [[ ${?} -ne 0 ]] ; then
    echo "Invalid device"
    exit 1
fi

status=$(grep -E "^$1\s" /proc/acpi/wakeup | awk ' { print $3 } ' )

if [[ "$status" == "*enabled" ]]; then
    echo "$1" > /proc/acpi/wakeup
fi