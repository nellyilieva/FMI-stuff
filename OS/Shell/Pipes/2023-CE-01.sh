# Напишете серия от команди, която извежда пътищата до всички файлове (из цялата файлова система),
# чиито собственик е текущият потребител и имат име, завършващо на .blend<число>.

find / -type f -user "$USER" -regex '.*\.blend[0-9]+' 2>/dev/null

# / -> in the whole directory
