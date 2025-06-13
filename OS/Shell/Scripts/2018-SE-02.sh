#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "2 args"
    exit 1
fi

file="$1"
dir="$2"

if [[ ! -f "$file" || ! -d "$dir" ]]; then
    echo "Not correct args"
    exit 1
fi

all_types=$(find "${dir}" | wc -l)
if [[ "$all_types" -ne 0 ]]; then
    echo "Dir not empty"
    exit 1
fi

# all_types=$(find "${dir}" | wc -l)
# files_count=$(find "${dir}" -type f | wc -l)
# dirs_count=$(find "${dir}" -type d | wc -l)
# if [[ $(( files_count + dirs_count )) -ne ${all_types} ]] ; then
#         echo "Directory should not contain objects"
#         exit 1
# fi

names="$(cat "$file" | cut -d ':' -f 1 | cut -d '(' -f 1 | rev | sed 's/^ *//' | rev | sort | uniq)"
idx=0

touch "$dir"/dict.txt

while read name;do
	idx=$(($idx + 1))
	echo "${name};${idx}" >> "$dir"/dict.txt

	touch $2/${idx}.txt
	echo "$(cat $1| grep "^ *${name}.*:.*")" >> $2/${idx}.txt

done < <(echo "$names")