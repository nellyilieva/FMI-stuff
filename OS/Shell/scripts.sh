#!/bin/bash
# to change prompt -> PS1=

# 05-b-2000
# Да се напише shell скрипт, който приканва потребителя да въведе низ (име) и изпечатва "Hello, низ".

#!/bin/bash

read -p "Enter name: " name
echo "Hello, ${name}"

# 05-b-2800
# Да се напише shell скрипт, който приема точно един параметър
# и проверява дали подаденият му параметър се състои само от букви и цифри.

#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "It is not exactly 1 parameter"
    exit 1
fi

if [[ ! "${1}" =~ ^[a-zA-Z0-9]+$ ]]; then
    echo "It is not from only letters and numbers"
    exit 2
fi

# 05-b-3100
# Да се напише shell скрипт, който приканва потребителя да въведе низ
# - потребителско име на потребител от системата
# - след което извежда на стандартния изход колко активни сесии има потребителят в момента.

#!/bin/bash

read -p "Enter username: " name

if ! $(grep -q "${name}" /etc/passwd); then
    echo "Wrong username"
    exit 1
fi

echo $(who | grep "${name}" | wc -l)

# 05-b-3200
# Да се напише shell скрипт, който приканва потребителя да въведе пълното име на директория
# и извежда на стандартния изход подходящо съобщение за броя на всички файлове и всички директории в нея.

#!/bin/bash

read -p "Enter directory: " dir

if [[ ! -d "${dir}" ]]; then
    echo "This is not directory"
    exit 1
fi

echo "Files: $(find "${dir}" -mindepth 1 -type f | wc -l)"
echo "Directories: $(find "${dir}" -mindepth 1 -type d | wc -l)"

# 05-b-3300
# Да се напише shell скрипт, който чете от стандартния вход имената на 3 файла,
# обединява редовете на първите два (man paste), подрежда ги по азбучен ред и резултата записва в третия файл.

#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    echo "Not 3 files"
    exit 1
fi

if [[ ! -f "${1}" ]] || [[ ! -f "${2}" ]]; then
    echo "Not files"
    exit 2
fi

paste "${1}" "${2}" | sort > "${3}"
cat "${3}"

# 05-b-3400
# Да се напише shell скрипт, който чете от стандартния вход име на файл и символен низ,
# проверява дали низа се съдържа във файла и извежда на стандартния изход кода
# на завършване на командата с която сте проверили наличието на низа.

# NB! Символният низ може да съдържа интервал (' ') в себе си.

#!/bin/bash

if [[ "${#}" -lt 2 ]]; then
    echo "Not 2 args"
    exit 1
fi

file="${1}"
shift
str="$*"

if [[ ! -f "$file" ]]; then
    echo "Not file"
    exit 2
fi

grep -q "${str}" "${file}"
echo $?

# 05-b-4200
# Имате компилируем (a.k.a няма синтактични грешки) source file на езика C. Напишете shell script,
# който да покaзва колко е дълбоко най-дълбокото nest-ване (влагане).
# Примерен .c файл:

# #include <stdio.h>

# int main(int argc, char *argv[]) {

#   if (argc == 1) {
# 		printf("There is only 1 argument");
# 	} else {
# 		printf("There are more than 1 arguments");
# 	}

# 	return 0;
# }
# Тук влагането е 2, понеже имаме main блок, а вътре в него if блок.

# Примерно извикване на скрипта:

# ./count_nesting sum_c_code.c

# Изход:
# The deepest nesting is 2 levels

#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Not 1 arg"
    exit 1
fi

max=0
curr=0

while read ch; do
    if [[ ${ch} == "{" ]] ; then
            curr=$(( curr + 1 ))
    else
        if [[ max -lt curr ]] ; then
            max=${curr}
        fi

        curr=$(( curr - 1 ))
    fi

done < <( cat "${1}" | grep -E -o '[{}]' )  # пренасочваме while loop-а да "работи" за input файла

echo "Deepest nesting: ${max}"

# grep -E -o '[{}]' "${1}" | while read ch; do
#     ...
# done

# 05-b-4301
# Напишете shell script, който автоматично да попълва файла указател от предната задача по подадени аргументи:
# име на файла указател, пълно име на човека (това, което очакваме да е в /etc/passwd) и избран за него nickname.
# Файлът указател нека да е във формат:
# <nickname, който лесно да запомните> <username в os-server>
# // може да сложите и друг delimiter вместо интервал

# Примерно извикване:
# ./pupulate_address_book myAddressBook "Ben Dover" uncleBen

# Добавя към myAddressBook entry-то:
# uncleBen <username на Ben Dover в os-server>

# ***Бонус: Ако има няколко съвпадения за въведеното име (напр. има 10 човека Ivan Petrov в /etc/passwd),
# всички те да се показват на потребителя, заедно с пореден номер >=1,
# след което той да може да въведе някой от номерата (или 0 ако не си хареса никого), и само избраният да бъде добавен към указателя.

#!/bin/bash

if [[ "${#}" -ne 3 ]]; then
    echo "Not 3 args"
    exit 1
fi

file="${1}"
name="${2}"
nickname="${3}"

# now we search for matches in /etc/passwd; matches with the name
matches=$(grep "${name}" /etc/passwd | awk -F ':' '{print $1}')
match_count=$(echo "$(matches)" | wc -l)

if [[ "${matches}" == "" ]]; then  # -z "${matches}"
    echo "User not find"
    exit 1
fi

if [[ "${match_count}" -eq 1 ]]; then
    username="${matches}"
else
    i=1
    while read -r line; do
        echo "${i}.${line}"
        i=$((i+1))
    done < <(echo "${matches}")   # prenasochvame / <<< "${matches}"
    echo "0.Exit"
    read -p "Choose from 1-${match_count}: " choice

    if [[ ${choice} -lt 0 ]] || [[ ${choice} -gt ${match_count} ]] ; then
        echo "Invalid choice"
        exit 1
    else
        if [[ ${choice} -eq 0 ]] ; then
            exit 0
        else
            username=$(echo "${matches}" | sed -n "${choice}p")  # -n: suppress default output (don’t print everything)
        fi
    fi
fi

echo "${nickname} ${username}" >> "${file}"

# p means print that specific line.
#" ${choice}p" means: print the line number stored in variable ${choice}.
# can be dobe with arr

# 05-b-4400
# Напишете shell script, който да приема параметър име на директория, от която взимаме файлове,
# и опционално експлицитно име на директория, в която ще копираме файлове.
# Скриптът да копира файловете със съдържание, променено преди по-малко от 45 мин,
# от първата директория във втората директория.
# Ако втората директория не е подадена по име, нека да получи такова от днешната дата във формат,
# който ви е удобен. При желание новосъздадената директория да се архивира.

#!/bin/bash

if [[ "${#}" -lt 1 ]]; then
    echo "Need more args"
    exit 1
fi

if [[ "${#}" -gt 2 ]]; then
    echo "No more then 2 args"
    exit 1
fi

if [[ ! -d "${1}" ]]; then
    echo "Needs to be dir"
    exit 1 
fi

destDir="${1}"
OUTPUT=$(date -I)

if [[ "${#}" -eq 2 ]]; then
    OUTPUT=${2}
fi

if [[ ! -d ${OUTPUT} ]] ; then
    mkdir -p ${OUTPUT}
fi

for FILE in $(find ${destDir} -mindepth 1 -maxdepth 1 -type f -mmin -45) ; do
    cp ${FILE} ${OUTPUT}
done
