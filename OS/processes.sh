#!/bin/bash

# 04-a-5000
# Намерете командите на 10-те най-стари процеси в системата.
ps -eo pid,cmd --sort=etime | tail -n10

# 04-a-6000
# Намерете PID и командата на процеса, който заема най-много виртуална памет в системата.
ps -eo pid,args,vsz --sort=vsz | tail -n1

# 04-a-6300
# Изведете командата на най-стария процес
ps -eo comm= --sort=etimes | tail -n1

# 04-b-5000
# Намерете колко физическа памет заемат всички процеси на потребителската група root.
ps -eo rss= -g root | awk '{sum+=$1} END{print sum}'

# 04-b-6100
# Изведете имената на потребителите, които имат поне 2 процеса, чиято команда е vim (независимо какви са аргументите й)
ps -eo user -C vim | sort | uniq -c |awk '{if($1>=2) print $2}'

# 04-b-6200
# Изведете имената на потребителите, които не са логнати в момента, но имат живи процеси
# not mine
comm -1 -3 <(who | cut -d ' ' -f 1 | sort -u ) <(ps -e -o user= | sort -u)

# 04-b-7000
# Намерете колко физическа памет заемат осреднено всички процеси на потребителската група root.
# Внимавайте, когато групата няма нито един процес.
ps -eo rss= -g root | awk 'BEGIN{sum=0; count=0} {sum+=$1; count++} END{if(count > 0) print sum/count; else print "No processes found for root group"}'

# 04-b-8000
# Намерете всички PID и техните команди (без аргументите), които нямат tty, което ги управлява.
# Изведете списък само с командите без повторения.
ps -eo pid,tty,cmd | awk '{if($2=="?") {print $3}}' | sort -u

# 04-b-9000
# Да се отпечатат PID на всички процеси, които имат повече деца от родителския си процес.
# not mine
ps -eo pid,ppid | awk '{parent[$1]=$2;children[$2]++;} END{for (child in children) {if (children[child] > children[parent[child]]) print child}}'