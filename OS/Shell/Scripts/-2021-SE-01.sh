#!/bin/bash

if [[ $(whoami) != "oracle" && $(whoami) != "grid" ]]; then
    echo "user must be oracle or grid"
    exit 1
fi

user=$(whoami)

if [[ -z "$ORACLE_HOME" ]]; then
    echo "oracle_home var is not set"
    exit 1
fi

adrci_path="$ORACLE_HOME/bin/adrci"
if [[ ! -x "$adrci_path" ]]; then
    echo "Error: adrci executable not found in $ORACLE_HOME/bin"
    exit 1
fi

diag_dest="/u01/app/$user"

adr_homes=$("$adrci_path" exec="show homes")

if [[ "$adr_homes" == *"No ADR homes are set"* ]]; then
    echo "No ADR homes configured"
    exit 0
fi

cat "$adr_homes" | while IFS= read -r line; do
    if [[ "$line" == "ADR Homes:" || -z "$line" ]]; then
        continue
    fi
    
    home=$(echo "$line" | xargs)
    
    if [[ ! "$home" == diag/* ]]; then
        continue
    fi
    
    absolute_path="$diag_dest/$home"
    
    if [[ ! -d "$absolute_path" ]]; then
        echo "Warning: ADR home $absolute_path does not exist"
        continue
    fi
    
    size_mb=$(du -sm "$absolute_path" | awk '{print $1}')
    
    echo "$size_mb $absolute_path"
    
done

exit 0