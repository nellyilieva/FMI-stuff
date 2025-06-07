# Напишете серия от команди, които изтриват:
# а) всички файлове в текущата директория и нейните поддиректории, които са с нулева дължина.
# б) 5-е най-големи файла в home директорията на текущия потребител и нейните поддиректории.

find . -type f -size 0 -delete  # works with recursion to delete in the subdirs

find ~ -type f -exec du -b {} \; | sort -nr | head -n 5 | cut -f2 | xargs -d '\n' rm -f

# exec runs command on each found file/dir/...
# {} -> placeholder
# xargs -> builds and runs commands from input; when we want to apply command on list of items