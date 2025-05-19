#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

void read_fd(int fd, int count_lines) {
    uint8_t buff;
    ssize_t bytes_read = 0;
    int line = 1;

    if (count_lines) {
        printf(1, "%d: ", line);
    }

    while ((bytes_read = read(fd, &buff, sizeof(buff))) > 0) {
        if (write(1, &buff, sizeof(buff)) == -1) {
            err(2, "Error while writing");
        }

        if (buff == '\n') {
            if (count_lines) {
                line++;
                printf(1, "%d: ", line);
            }
        }
    }

    if (bytes_read == -1) {
        err(1, "Error while reading");
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        read_fd(0, 0);
    }
    else {
        int count_lines = 0;
        int idx = 1;  // idx for arg in argv
        if (strcmp(argv[1], "-n") == 0) {
            count_lines = 1;
            idx = 2;
        }

        for (int i = idx; i < argc; i++) {
            int fd;
            if (strcmp(argv[i], "-") == 0) {
                fd = 0;
            }
            else {
                fd = open(argv[i], O_RDONLY);
                if (fd == -1) {
                    err(3, "Error while opening");
                }
            }

            read_fd(fd, count_lines);

            if (fd != 0) {
                close(fd);
            }
        }
    }

    return 0;
}