#!/bin/bash

if [[ $(id -u) -ne 0 ]]; then
    echo "Must be from the root"
    exit 1
fi

# a
info=$(ps -eo user=,rss=,pid= |
awk ' {count[$1]++; total_rss[$1]+=$2;} END{for (u in count) printf "%s -> %d | %d KB\n", u, count[u], rss[u] } ' )

# b
ps -eo user=,rss=,pid= |
awk '
{
    user=$1; rss=$2; pid=$3
    count[user]++; sum[user]+=rss
    rss_list[user,pid]=rss
    pid_list[user,pid]=pid
}
END {
    for (key in rss_list) {
        split(key, parts, SUBSEP)
        user = parts[1]
        pid = parts[2]
        avg = sum[user] / count[user]
        if (rss_list[key] > 2 * avg) {
            system("kill -9 " pid)
        }
    }
}'