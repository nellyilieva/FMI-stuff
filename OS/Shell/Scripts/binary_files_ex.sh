#!/bin/bash

# 2021-SE-03

# Convert binary float32 data to C array
# Input: binary file with little-endian float32 values
# Output: header with const float arr[] and size

xxd -p -c 4 input.bin | while read -r HEX; do
    # Convert hex to float representation
    echo "$HEX" | xxd -r -p | od -tf4 -An
done > output.h

# fuller C header
echo "const float arr[] = {" > output.h
xxd -p -c 4 input.bin | while read -r HEX; do
    echo "$HEX" | xxd -r -p | od -tf4 -An | xargs | tr ' ' ','
done | sed 's/^/    /' >> output.h
echo "};" >> output.h
echo "const size_t arr_size = $(wc -c < input.bin)/4;" >> output.h

# od (octal dump) -t specifies the output format


# Convert binary uint64_t (little-endian) to header
# Requires handling 8-byte swaps

xxd -p -c 8 input.bin | while read -r HEX; do
    # Reverse byte order for 64-bit values
    echo "$HEX" | grep -o .. | tac | tr -d '\n'
done > output.h


# Convert binary file with mixed uint16_t and uint32_t
# First 2 bytes = count (uint16_t), remaining = uint32_t values

COUNT=$(xxd -p -l 2 input.bin | sed 's/\(..\)\(..\)/\2\1/')
echo "uint32_t arr[$COUNT] = {" > output.h
xxd -p -s 2 -c 4 input.bin | while read -r HEX; do
    echo "$HEX" | grep -o .. | tac | tr -d '\n'
done >> output.h
echo "};" >> output.h


# Convert network packet capture to protocol constants
# Extracts specific fields from binary packets

OFFSET=24  # Example field offset
LENGTH=4
echo "const uint32_t PACKET_HEADERS[] = {" > protocols.h
tcpdump -r capture.pcap -xx | grep -o '0x....' | 
    while read -r HEX; do
        echo "$HEX," >> protocols.h
    done
echo "};" >> protocols.h


# Convert firmware image to flashable C array
# Adds checksum validation

CHECKSUM=$(sha256sum firmware.bin | cut -d' ' -f1)
echo "const unsigned char firmware[] = {" > firmware.h
xxd -i < firmware.bin >> firmware.h
echo "};" >> firmware.h
echo "const char *firmware_checksum = \"$CHECKSUM\";" >> firmware.h