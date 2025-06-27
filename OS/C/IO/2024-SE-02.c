#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const uint32_t MAGIC = 0x21494D46;

struct header {
    uint32_t magic;
    uint32_t packet_count;
    uint64_t original_size;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "need 2 args");
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        err(1, "error opening");
    }

    struct stat st;
    if (fstat(fd1, &st) == -1) {
        err(2, "stat error");
    }

    size_t file_size = st.st_size;
    if (file_size < sizeof(struct header)) {
        errx(3, "wrong size file");
    }

    struct header hd;
    if (read(fd1, &hd, sizeof(hd)) != sizeof(struct header)) {
        err(3, "error reading");
    }

    if (hd.magic != MAGIC) {
        errx(4, "wrong file");
    }

    int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd2 == -1) {
        err(1, "error opening");
    }

    uint64_t written = 0;
    for (uint32_t i = 0; i < hd.packet_count; i++) {
        uint8_t byte;
        if (read(fd1, &byte, sizeof(byte)) != 1) {   // can be == -1, but with != 1 we also check if it is unexpected EOF
            err(4, "error reading");
        }

        uint8_t t = byte >> 7;
        uint8_t N = byte & 0x7F;

        if (t == 0) {
            uint8_t buf[128];
            if (read(fd1, buf, N + 1) != N + 1) {
                err(6, "Failed to read normal packet data");
            }

            if (write(fd2, buf, N + 1) != N + 1) {
                err(7, "Failed to write normal packet data");
            }

            written += N + 1;
        }
        else if (t == 1) {
            uint8_t byte;
            if (read(fd1, &byte, 1) != 1) {
                err(8, "Failed to read repeated byte");
            }

            for (int j = 0; j < N + 1; j++) {
                if (write(fd2, &byte, 1) != 1) {
                    err(9, "Failed to write repeated byte");
                }
            }
            written += N + 1;
        }
    }

    if (written != hd.original_size) {
        errx(10, "Mismatch: expected %lu bytes, wrote %lu", hd.original_size, written);
    }

    close(fd1);
    close(fd2);
    return 0;
}