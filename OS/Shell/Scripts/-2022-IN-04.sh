# dir Fuga -> foo.pwd и foo.conf
# foo.pwd -> username:password (hash)
# foo.conf -> in dir fuga/cfg and its dirs in parts
# fuga/validate.sh -> takes name of conf file and check it
#   0 -> vaid file; 1 -> not valid; 2 -> error
# if files is not valid -> Line x: invalid line
# pwgen -> случайни пароли;  pwgen [password_length] [number_of_passwords]
# mkpasswd -> по подаден аргумент – парола в чист вид извежда нейният хеш на stdout

# - on stderr (2) -> filename: Line x: invalid line
# - make foo.pwd only from the valid parts
# - провери за всеки валиден малък конфигурационен файл дали потребителят съществува в автентификационния файл
# и ако не – да го добави по подходящия начин, като изведе на stdout
# потребителското име и паролата в чист вид, разделени с двоеточие username:password

#!/bin/bash

if [[ "${#}" -ne 1 ]]; then
    echo "Usage: $0 <fuga_directory>"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "Error: $1 is not a directory"
    exit 1
fi

FUGA_DIR="$1"
PWD_FILE="${FUGA_DIR}/foo.pwd"
CONF_FILE="${FUGA_DIR}/foo.conf"
CFG_DIR="${FUGA_DIR}/cfg"

if [[ ! -d "$CFG_DIR" ]]; then
    echo "Error: Configuration directory ${CFG_DIR} does not exist"
    exit 1
fi

if [[ ! -x "${FUGA_DIR}/validate.sh" ]]; then
    echo "Error: Validation script ${FUGA_DIR}/validate.sh not found or not executable"
    exit 1
fi

# Create empty conf file
> "$CONF_FILE"

if [[ ! -f "$PWD_FILE" ]]; then
    touch "$PWD_FILE"
fi

configs=$(find "${CFG_DIR}" -name "*.cfg" -type f)

if [[ -z "$configs" ]]; then
    echo "Warning: No .cfg files found in ${CFG_DIR}"
    exit 0
fi

echo "$configs" | while read -r config_file; do
    if [[ -z "$config_file" ]]; then
        continue
    fi
    
    basename_file=$(basename "$config_file")
    username="${basename_file%.cfg}"
    
    validation_output=$("${FUGA_DIR}/validate.sh" "$config_file" 2>&1)
    exit_code=$?
    
    if [[ $exit_code -eq 0 ]]; then
        cat "$config_file" >> "$CONF_FILE"

        if ! grep -q "^${username}:" "$PWD_FILE"; then
            password=$(pwgen 12 1)
            hashed_password=$(mkpasswd "$password")
            echo "${username}:${hashed_password}" >> "$PWD_FILE"
            echo "${username}:${password}"
        fi
    elif [[ $exit_code -eq 1 ]]; then
        if [[ -n "$validation_output" ]]; then
            echo "$validation_output" | while IFS= read -r line; do
                echo "${basename_file}:${line}" >&2 
            done
        fi
    fi
done