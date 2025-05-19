// Koпирайте файл /etc/passwd в текущата ви работна директория и променете разделителят на копирания файл от ":", на "?"

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(void) {
    const char* etc = "/etc/passwd";
    const char* copy = "./passwd";

    int fd_o = open(etc, O_RDONLY);

    if (fd_o == -1) {
        err(1, "Couldn't open file");
    }

    int fd_c = open(copy, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd_c == -1) {
        close(fd_o);
        err(2, "Couldn't open file");
    }

    char buff = 0;
    int bytes_read = 0;

    while ((bytes_read = read(fd_o, &buff, sizeof(buff))) > 0) {
        if (buff == ':') {
            buff = '?';
        }

        if ((write(fd_c, &buff, sizeof(buff))) != bytes_read) {
            close(fd_o);
            close(fd_c);
            err(3, "Error while writting");
        }

        if (bytes_read == -1) {
            close(fd_o);
            close(fd_c);
            err(4, "Error while reading");
        }
    }

    close(fd_o);
    close(fd_c);
    return 0;
}