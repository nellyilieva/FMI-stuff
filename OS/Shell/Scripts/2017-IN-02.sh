#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Needs 1 arg"
    exit 1
fi

if [[ $(id -u) -ne 0 ]]; then
    echo "Must be from root"
    exit 1
fi

if ! id "$1" &>/dev/null; then
    echo "User doesn't exist"
    exit 1
fi

# a
FOO="$1"
fooCount=$(ps -u "$FOO" -o -pid | wc -l) # + pid -> process id

users=$(ps -eo ruser | sort | uniq -c | sort -n -r | awk -v usr="$1" '{ if ( $2 == usr ) exit; else { print $2"("$1")"} }')
# "$1" is the count; then "$2" is the username

# b
aveg=$(ps -eo etimes= | awk ' BEGIN{c=0} {sum+=$1;c++;}  END{ if(c > 0) print sum/c; else print 0 } ')
avgtime=$aveg
hours=$(echo "$aveg / 3600" | bc)
aveg=$(echo "$aveg-$(echo "3600 * $hours" | bc)" | bc)
mins=$(echo "$aveg / 60" | bc)
aveg=$(echo "$aveg-$(echo "60 * $mins" | bc)" | bc)

echo "Average time every current process has been running for: ${hours}:${mins}:${aveg}"
echo ""

# c
pc -u "$FOO" -o pid=,etimes= | while IFS= read -r line; do
    t=$(echo "$line" | awk ' {print $2} ')

    if [[ "$t" -gt $(($avgtime * 2)) ]]; then
        kill $(echo "$line" | awk ' { print $1 } ')
    fi
done