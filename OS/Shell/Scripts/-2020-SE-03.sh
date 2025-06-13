#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 args"
    exit 1
fi

if [[ -z "$1" ]]; then
    echo "empty string"
    exit 1
fi

if [[ -z "$2" ]]; then
    echo "empty string"
    exit 1
fi

repo="$1"
pkg="$2"

if [[ ! -d "$repo" || ! -f "$repo/db" || ! -d "$repo/packages" ]]; then
    echo "Error: Repository structure is invalid"
    exit 2
fi

if [[ ! -d "$pkg" || ! -f "$pkg/version" || ! -d "$pkg/tree" ]]; then
    echo "Error: Package structure is invalid"
    exit 3
fi

pkgname=$(basename "$pkg")
version=$(< "$pkg/version")
pkg_id="${pkgname}-${version}"

tmpdir=$(mktemp -d)
tmparchive="$tmpdir/${pkg_id}.tar"
xzarchive="$tmpdir/${pkg_id}.tar.xz"

tar -cf "$tmparchive" -C "$pkg/tree" .
xz -z "$tmparchive"

checksum=$(sha256sum "$xzarchive" | awk '{print $1}')
final_archive="$repo/packages/$checksum.tar.xz"

cp "$xzarchive" "$final_archive"

tmpdb=$(mktemp)
grep -v "^${pkg_id} " "$repo/db" > "$tmpdb" || true
echo "${pkg_id} ${checksum}" >> "$tmpdb"
sort "$tmpdb" > "$repo/db"
rm -r "$tmpdir" "$tmpdb"