# Converts a binary file containing little-endian uint16_t values into a C header file with:
# - const uint32_t array containing all values converted to big-endian
# - arrN variable storing the array size
# - proper header guards and includes

# xxd -> binary as hex
# cut extracts the 16-bit values
# sed swaps byte order (little-to-big endian)
# sed -E 's/^(..)(..)$/\2\1/'-> Swaps byte order (little-endian to big-endian)
# ^(..)(..)$ captures 4 hex digits as two pairs
# \2\1 reverses them

#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "2 args"
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "not file"
    exit 1
fi

touch "$2"

echo "#include <stdint.h>" > "$2"

ARR=""

for UINT16 in $(xxd "$1" | cut -d ' ' -f2-9); do
        UINT16=$(echo "${UINT16}" | sed -E 's/^(..)(..)$/\2\1/' )
        ARR="${ARR}0x${UINT16},"  # 0x5555,
done

ARR=$(echo "${ARR}" | sed -E "s/,$//")

echo "uint32_t arr[] = { ${ARR} };" > "$2"

# 00000000: 5555 5655 5955 5a55 6555 6655 6955 6a55  UUVUYUZUeUfUiUjU
# 00000010: 9555 9655 9955 9a55 a555 a655 a955 aa55  .U.U.U.U.U.U.U.U