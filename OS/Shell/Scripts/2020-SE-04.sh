#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "args count"
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "First dir"
    exit 2
fi

if [[ -e "$2" ]]; then
    echo "second dir existing"
    exit 3
fi

mkdir "$2"

mkdir -p "$2"/"images"
images="$2"/"images"

mkdir -p "$2"/"by-date"
bydate="$2"/"by-date"

mkdir -p "$2"/"by-album"
byalbum="$2"/"by-album"

mkdir -p "$2"/"by-title"
bytitle="$2"/"by-title"


find "$1" -type f -name "*.jpg" | while read -r f; do
    # name=$(echo "$f" | cut -d '.' -f1)
    filename=$(basename "$f")
    name=$(basename "$f" .jpg)

    title=$(echo "$name" | sed -E 's/\([^)]*\)//g' | xargs | tr -s ' ')
    album=$(echo "$name" | grep -E -o "([^)]*)" | tail -n 1 | sed 's/[()]//g' | xargs | tr -s ' ')  # grep -o print only the matching part
    if [[ -z "$album" ]]; then
        album="misc"
    fi

    date=$(date -r "$f" +"%Y-%m-%d")
    hash=$(sha256sum "$f" | cut -d ' ' -f 1 | cut -c 1-16)

    # cp "$f" "$images/$hash.jpg"
    if [[ ! -f "$2/images/$hash.jpg" ]]; then
        cp "$f" "$2/images/$hash.jpg"
    fi

    mkdir -p "$bydate/$date/by-album/$album/by-title"
    ln -s "../../../../images/$hash.jpg" "$bydate/$date/by-album/$album/by-title/$title.jpg"

    mkdir -p "$bydate/$date/by-title"
    ln -s "../../../images/$hash.jpg" "$bydate/$date/by-title/$title.jpg"

    mkdir -p "$byalbum/$album/by-date/$date/by-title"
    ln -s "../../../../../images/$hash.jpg" "$byalbum/$album/by-date/$date/by-title/$title.jpg"

    mkdir -p "$byalbum/$album/by-title"
    ln -s "../../images/$hash.jpg" "$byalbum/$album/by-title/$title.jpg"

    mkdir -p "$bytitle"
    ln -s "../images/$hash.jpg" "$bytitle/$title.jpg"
done

# ln -s creates a symbolic link (symlink)