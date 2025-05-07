#!/bin/bash

# 03-a-0200
# Сортирайте /etc/passwd лексикографски по поле UserID.
sort /etc/passwd -t : -k 3

# 03-a-0201
# Сортирайте /etc/passwd числово по поле UserID.
# (Открийте разликите с лексикографската сортировка)
 sort /etc/passwd -t : -k 1 -n

# 03-a-0210
#  Изведете само 1-ва и 5-та колона на файла /etc/passwd спрямо разделител ":".
 cut /etc/passwd -d : -f 1,5

#  03-a-0211
# Изведете съдържанието на файла /etc/passwd от 2-ри до 6-ти символ.
cut /etc/passwd -c 2-6

# 03-a-0212
# Отпечатайте потребителските имена и техните home директории от /etc/passwd.
cut /etc/passwd -d : -f 1,6

# 03-a-0213
# Отпечатайте втората колона на /etc/passwd, разделена спрямо символ '/'.
cut /etc/passwd -d / -f 2

# 03-a-1500
# Изведете броя на байтовете в /etc/passwd.
# Изведете броя на символите в /etc/passwd.
# Изведете броя на редовете  в /etc/passwd.
wc /etc/passwd -c
wc /etc/passwd -m
wc /etc/passwd -l

# 03-a-2000
# С отделни команди, извадете от файл /etc/passwd:
# - първите 12 реда
# - първите 26 символа
# - всички редове, освен последните 4
# - последните 17 реда
# - 151-я ред (или друг произволен, ако нямате достатъчно редове)
# - последните 4 символа от 13-ти ред (символът за нов ред не е част от реда)
head /etc/passwd -12
head /etc/passwd -c 26
head /etc/passwd -n -4
tail -17 /etc/passwd
head /etc/passwd -n 151 | tail -n 1
head /etc/passwd -n 13 | tail -n 1 | tail -c 5

#03-a-3000
# Запаметете във файл в своята home директория резултатът от командата `df -P`.
# Напишете команда, която извежда на екрана съдържанието на този файл,
# без първия ред (хедъра), сортирано по второ поле (numeric).
df -P > df.file
tail -n +2 df.file | sort -n -k 2

# 03-a-3100
# Запазете само потребителските имена от /etc/passwd във файл users във вашата home директория.
cat /etc/passwd | cut -d: -f1 > users

# 03-a-3500
# Изпишете всички usernames от /etc/passwd с главни букви.
cat /etc/passwd | cut -d: -f1 | tr 'a-z' 'A-Z'

# 03-a-5000
# Изведете реда от /etc/passwd, на който има информация за вашия потребител.
# Изведедете този ред и двата реда преди него.
# Изведете този ред, двата преди него, и трите след него.
# Изведете *само* реда, който се намира 2 реда преди реда, съдържащ информация за вашия потребител.
cat /etc/passwd | grep $(id -u)
cat /etc/passwd | grep $(id -u) -B2
cat /etc/passwd | grep $(id -u) -B2 -A3
cat /etc/passwd | grep $(id -u) -B2 | head -n1

# 03-a-5001
# Изведете колко потребители не изпозват /bin/bash за login shell според /etc/passwd
# (hint: 'man 5 passwd' за информация какъв е форматът на /etc/passwd)
cat /etc/passwd | cut -d : -f7 | grep -E -v '/bin/bash' | wc -l

# 03-a-5002
# Изведете само имената на хората с второ име по-дълго от 6 (>6) символа според /etc/passwd
cat /etc/passwd | cut -d: -f5 | cut -d, -f1 | grep -E '.* .{7,}'

# 03-a-5003

# Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?
cat /etc/passwd | cut -d: -f5 | cut -d, -f1 | grep -E -v ".* .{8,}"
# we do the reverse

# 03-a-5004
# Изведете целите редове от /etc/passwd за хората от 03-a-5003
# so i will avoid using cut and use grep or awk directly
# not mine
cat /etc/passwd | cut -d ':' -f5 | cut -d ',' -f1 | cut -d ' ' -f2 | grep -v -E '.{8,}$' | grep -E '[^a-zA-Z]' | sort | uniq | xargs -I{} grep -w {} /etc/passwd

# 03-a-6000
# Копирайте <РЕПО>/exercises/data/emp.data във вашата home директория.
cp /srv/fmi-os/exercises/data/emp.data .
# Посредством awk, използвайки копирания файл за входнни данни, изведете:

# - общия брой редове
awk 'END{print NR}' emp.data
    #or
awk 'BEGIN{i=0} {i++} END{print i}' emp.data
    #or
cat emp.data | awk 'END{print NR}'
# - третия ред
awk '{if (NR==3) print $0}' emp.data
# - последното поле от всеки ред
awk '{print $3}' emp.data
    # or
awk '{print $NF}' emp.data
# - последното поле на последния ред
awk 'END{print $NF}' emp.data
# - всеки ред, който има повече от 4 полета
awk '{if (NF > 4) print $0}' emp.data
# - всеки ред, чието последно поле е по-голямо от 4
awk '{if ($NF > 4) print $0}' emp.data
# - общия брой полета във всички редове
awk '{print NF}' emp.data 
    # or
awk 'BEGIN{c=0} {c+=NF} END{print c}' emp.data # count total
# - броя редове, в които се среща низът Beth
awk 'BEGIN{c=0} {if(/Beth/) c++} END{print c}' emp.data
# - най-голямото трето поле и редът, който го съдържа
awk 'BEGIN{max=-1; line=" "} {if($3>max){max=$3; line=$0}} END{printf line" "max"\n"}' emp.data
# - всеки ред, който има поне едно поле
awk '{if(NF>=1) printf$0"\n"}' emp.data
# - всеки ред, който има повече от 17 знака
awk '{if(/.{18,}/) printf$0"\n"}' emp.data #-> first thing that came to my mind
    #or
awk '{if(length($0)>17) printf$0"\n"}' emp.data
# - броя на полетата във всеки ред и самият ред
awk '{print NF, $0}' emp.data
# - първите две полета от всеки ред, с разменени места
awk '{print $2, $1}' emp.data
# - всеки ред така, че първите две полета да са с разменени места
awk '{temp = $1; $1=$2; $2=temp;print}' emp.data
# - всеки ред така, че на мястото на първото поле да има номер на реда
 awk '{$1=NR; print}' emp.data
# - всеки ред без второто поле
# we can do this with for loop and check if filed is $2
awk '{$2='\t'; print}' emp.data #or "" -> the problems we will have extra spaces/tabs
# - за всеки ред, сумата от второ и трето поле
awk '{print $2+$3}' emp.data
# - сумата на второ и трето поле от всеки ред
awk 'BEGIN{sum=0} {sum+=$2+$3} END{print sum}' emp.data

# 03-b-0300
# Намерете само Group ID-то си от файлa /etc/passwd.
grep $(id -u) /etc/passwd | cut -d ':' -f4

# 03-b-3400
# Колко коментара има във файла /etc/services ? Коментарите се маркират със символа #, след който всеки символ на реда се счита за коментар.
cat /etc/services |grep -E '^#.*'| wc -l

# 03-b-3500
# Колко файлове в /bin са 'shell script'-oве? (Колко файлове в дадена директория са ASCII text?)
find /bin -type f -exec cat {} \; | grep '#!/bin/' | wc -l
    #or
find /bin | xargs -I{} file {} | grep "ASCII text executable" | wc -l

# 03-b-3600
# Направете списък с директориите на вашата файлова система, до които нямате достъп.
# Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина.
find / -maxdepth 3 -type d >/dev/null 2> sol.txt; cat sol.txt | cut -d ':' -f 2 | tr -d ' ' | cut -c 4- | rev | cut -c 4- | rev; rm sol.txt

# 03-b-4001
# Във file2 (inplace) подменете всички малки букви с главни.
sed -i 's/.*/\U&/' file2
# or something with tr

# 03-b-4002
# Във file3 (inplace) изтрийте всички "1"-ци.
sed -i 's/1//g' file3
    # or
cat file3 | tr -d '1' > file3

# 03-b-4003
# Изведете статистика за най-често срещаните символи в трите файла.
cat file1 file2 file3 | fold -w1 | sort | uniq -c | sort -nr |head
    # or
grep -o '.' file{1,2,3} | sort | uniq -c | sort -nr

# 03-b-5200
# Намерете броя на символите, различни от буквата 'а' във файла /etc/passwd
cat /etc/passwd | sed 's/a//g' | wc -m

# 03-b-5400
# Отпечатайте всички редове на файла /etc/passwd, които не съдържат символния низ 'ов'.
grep -v "ов" /etc/passwd

# 03-b-6900
# Намерете имената на 10-те файла във вашата home директория, чието съдържание е
# редактирано най-скоро. На първо място трябва да бъде най-скоро редактираният
# файл. Намерете 10-те най-скоро достъпени файлове. (hint: Unix time)
find . -printf "%T@ %f\n" | sort -k 1nr -t ' '|cut -d ' ' -f2 | head -n 10
