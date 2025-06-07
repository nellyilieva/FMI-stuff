#!/bin/bash

# Намерете имената на топ 5 файловете в текущата директория с най-много hardlinks.

find . -type f -printf "%f %n\n" | sort -k 2 -n -r | head -5 | cut -d ' ' -f 1

# %n -> for hardlinks
