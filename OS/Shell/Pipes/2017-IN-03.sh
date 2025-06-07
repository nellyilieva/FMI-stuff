grep "/home/Inf" etc/passwd | cut -d ':' -f 1,5 | cut -d ',' -f1 |  grep "a$" | cut -c3,4 | sort -nr | uniq -c | sort -nr | head -n 1

cat passwd | egrep "/home/Inf/" | awk -F ':' '{print $1 " " $5}' | awk '{print $1 $3}' | egrep ".*a[,]{0,1}$" | sed -E 's/..(..).*/\1/g' | sort -n | uniq -c | sort -nr | head -n 1

# sed -> Replaces the whole line with just those two captured characters.
# unique -c !!!