type=$(tail -n +2 planets.txt | sort -t ';' -k3 -n | tail -n 1 | cut -d ';' -f2)
tail -n +2 planets.txt | grep ";$type;" | sort -t ';' -k3 -n | head -n 1 | awk -F ';' '{print $1 "\t" $4}'


tail -n +2 planets.txt | grep ";$(tail -n +2 planets.txt | sort -t ';' -k3 -n | tail -1 | cut -d ';' -f2);" | sort -t ';' -k3 -n | head -1 | awk -F ';' '{print $1 "\t" $4}'

