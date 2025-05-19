// Реализирайте команда swap, разменяща съдържанието на два файла, подадени като входни параметри.

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Args count must be 2");
    }

    const char* first = argv[1];
    const char* second = argv[2];

    int fd_f = open(first, O_RDWR);
    int fd_s = open(second, O_RDWR);

    if (fd_f == -1) {
        err(2, "File %s couldn't open", first);
    }

    if (fd_s == -1) {
        close(fd_f);
        err(3, "File %s couldn't open", second);
    }

    int fd_temp = open("tmp", O_RDWR | O_CREAT, 0644); //this to be made with mktemp command

    if (fd_temp == -1) {
        close(fd_f);
        close(fd_s);
        err(4, "File temp couldn't open");
    }

    char buff = 0;
    int bytes_read = 0;
    int bytes_written = 0;

    while (bytes_read = read(fd_f, &buff, sizeof(buff))) {
        if (bytes_read == -1) {
            err(5, "Error while reading");
        }

        bytes_written = write(fd_temp, &buff, sizeof(buff));

        if (bytes_written == -1) {
            err(6, "Error while writting");
        }
    }

    if (lseek(fd_f, 0, SEEK_SET) == -1) {
        close(fd_f);
        close(fd_s);
        close(fd_temp);
        err(7, "Could not move the offset");
    }

    if (lseek(fd_temp, 0, SEEK_SET) == -1) {
        close(fd_f);
        close(fd_s);
        close(fd_temp);
        err(8, "Could not move the offset");
    }

    while (bytes_read = read(fd_s, &buff, sizeof(buff))) {
        if (bytes_read == -1) {
            err(9, "Error while reading");
        }

        bytes_written = write(fd_f, &buff, sizeof(buff));

        if (bytes_written == -1) {
            err(10, "Error while writting");
        }
    }

    if (lseek(fd_s, 0, SEEK_SET) == -1) {
        err(11, "Could not move the offset");
    }

    while (bytes_read = read(fd_temp, &buff, sizeof(buff))) {
        if (bytes_read == -1) {
            err(12, "Error while reading");
        }

        bytes_written = write(fd_s, &buff, sizeof(buff));

        if (bytes_written == -1) {
            err(13, "Error while writting");
        }
    }

    close(fd_f);
    close(fd_s);
    close(fd_temp);
    unlink("tmp");
    return 0;
}