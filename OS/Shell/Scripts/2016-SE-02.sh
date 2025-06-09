#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Need 1 args"
    exit 1
fi

if [[ ! "${arg}" =~ ^-?[0-9]+$ ]]; then
    echo "It is not a number"
    exit 1
fi

if [[ $(id -u) -ne 0 ]]; then
    echo "Script must be executed by root"
    exit 2
fi

# if [[ "$EUID" -ne 0 ]] ; then
#         echo "This script must be run as root"
#         exit 1
# fi

num="$1"

uids=$(ps -e -o uid= | sort -n | uniq)

for uid in $uids; do
    rss_u=$(ps -e -o uid=,rss= | awk -v u="$uid" '$1==u { sum+=$2 } END { print sum+0 }')  # v is to pass variables

    if [[ "$rss_u" -gt "$num" ]]; then
        echo "User $uid exceeds threshold ($rss_u > $num)"

        pid_to_kill=$(ps -e -o uid=,pid=,rss= | awk -v u="$uid" '$1==u { if ($3 > max) { max=$3; pid=$2 } } END { print pid }')

        kill -TERM "$pid_to_kill"
    fi
done