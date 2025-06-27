#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>
#include <stdio.h>

// we will work byte by byte with while

#define START_BYTE 0x55
#define MAX_MESSAGE_SIZE 255

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "args must be 2");
    }

    const char* stream = argv[1];
    const char* messg = argv[2];

    int fd1 = open(stream, O_RDONLY);
    if (fd1 == -1) {
        err(1, "error opening");
    }

    int fd2 = open(messg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        err(1, "error opening");
    }

    uint8_t buf[MAX_MESSAGE_SIZE];
    uint8_t b;

    while (read(fd1, &b, 1) == 1) {
        if (b != START_BYTE) {
            continue;
        }

        buf[0] = b;

        if (read(fd1, &buf[1], 1) != 1) {  //ako svyrshva sled begin byte-a, so not == -1
            break;
        }

        uint8_t length = buf[1];
        if (length < 3 || length > MAX_MESSAGE_SIZE) {
            continue;
        }

        ssize_t expected = length - 2;
        if (read(fd1, &buf[2], expected) != expected) {
            break;
        }

        uint8_t checksum = 0;
        for (int i = 0; i < length - 1; i++) {
            checksum ^= buf[i];
        }

        if (checksum == buf[length - 1]) {
            if (write(fd2, buf, length) != length) {
                err(3, "Write failed");
            }
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}