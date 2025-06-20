#!/bin/bash

# ./occ.sh user:list

locals=$(mktemp)
awk -F ':' '$3 >= 1000 { print $1 }' /etc/passwd | sort > "$locals"

occ_users=$(mktemp)
./occ.sh user:list | cut -d '-' -f2- | cut -d ':' -f1 | sort > "$occ_users"

while read -r user; do
    if ./occ.sh user:info "$user" | grep -qE "^- enabled: false"; then
        ./occ.sh user:enable "$user"
    fi

done < <(comm ${locals} ${occ_users} -12)

while read -r user; do
    if ./occ.sh user:info "$user" | grep -qE "^- enabled: true"; then
        ./occ.sh user:disable "$user"
    fi
done < <(comm "$locals" "$occ_users" -13)

while read -r user; do
    echo "$user"
    # ./occ.sh user:add "$user"
done < <(comm "$locals" "$occ_users" -23)


rm ${localUsers}
rm ${cloudUsers}