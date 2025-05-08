// Copy content of one file in other

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Args count must be 2");
    }

    const char* src = argv[1];
    const char* dest = argv[2];

    int fd_source = open(src, O_RDONLY);
    int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd_source == -1) {
        err(2, "Couldn't open the file for reading");
    }

    if (fd_dest == -1) {
        close(fd_source);
        err(3, "Couldn't open the file for writting");
    }

    uint8_t buff = 0;
    int bytes_read = 0;
    int bytes_written = 0;

    // while ((bytes_read = read(fd_source, &buff, sizeof(buff))) == sizeof(buff)) {
    //     if ((write(fd_dest, &buff, sizeof(buff))) != sizeof(buff)) {
    //         close(fd_source);
    //         close(fd_dest);
    //         err(4, "Error while writting to destination");
    //     }
    // }

    // if (bytes_read == -1) {
    //         close(fd_source);
    //         close(fd_dest);
    //         err(5, "Error while reading from source");
    // }

    while (bytes_read = read(fd_source, &buff, sizeof(buff))) {  //reads 1 byte at a time
        if (bytes_read == -1) {
            close(fd_source);
            close(fd_dest);
            err(4, "Error while reading from source");
        }

        bytes_written = write(fd_dest, &buff, sizeof(buff));

        if (bytes_written == -1) {
            close(fd_source);
            close(fd_dest);
            err(5, "Error while writting to destination");
        }
    }

    close(fd_source);
    close(fd_dest);

    return 0;
}