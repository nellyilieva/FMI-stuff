// Реализирайте команда head без опции (т.е. винаги да извежда на стандартния изход
// само първите 10 реда от съдържанието на файл подаден като първи параматър)

#include <unistd.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Args count must be 1");
    }

    const char* file = argv[1];

    int fd_file = open(file, O_RDONLY);

    if (fd_file == -1) {
        err(2, "Couldn't open %s", file);
    }

    char buff = 0;
    int bytes_read = 0;
    int bytes_written = 0;
    int lines = 0;

    while (bytes_read = read(fd_file, &buff, sizeof(buff))) {
        if (bytes_read == -1) {
            close(fd_file);
            err(3, "Error while reading");
        }

        if (buff == '\n') {
            lines++;
        }

        if (lines == 10) {
            break;
        }

        bytes_written = write(1, &buff, sizeof(buff));

        if (bytes_written == -1) {
            close(fd_file);
            err(4, "Error while writting");
        }
    }

    // while (bytes_read = read(fd_file, &buff, sizeof(buff)) == sizeof(buff)) {
    //     if (buff == '\n') {
    //         lines++;
    //     }

    //     if ((write(1, &buff, sizeof(buff))) == -1) {
    //         err(3, "Error while writting");
    //     }

    //     if (lines == 10) {
    //         break;
    //     }
    // }

    close(fd_file);
    return 0;
}