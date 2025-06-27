// wc command; lines, words, bytes
// with printf

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Args count must be 1");
    }

    const char* file = argv[1];

    int fd_file = open(file, O_RDONLY);

    if (fd_file == -1) {
        err(2, "File %s couldn't open", file);
    }

    char buff = 0;
    int bytes_read = 0;

    int lines = 0;
    int words = 0;
    int bytes = 0;

    while (bytes_read = read(fd_file, &buff, sizeof(buff))) {  //while ((bytes_read = read(fd_file, &buff, sizeof(buff))) > 0)
        if (bytes_read == -1) {
            close(fd_file);
            err(3, "Error while reading");
        }

        if (buff == '\n') {
            lines++;
            words++;
        }

        if (buff == ' ') {
            words++;
        }

        bytes++;
    }

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Bytes: %d\n", bytes);

    close(fd_file);
    return 0;
}