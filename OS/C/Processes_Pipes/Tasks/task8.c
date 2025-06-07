// Да се напише програма на С, която получава като параметър име на файл.
// Създава процес син, който записва стринга foobar във файла
// (ако не съществува, го създава, в противен случай го занулява),
// след което процеса родител прочита записаното във файла съдържание
// и го извежда на стандартния изход, добавяйки по един интервал между всеки два символа.

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Wrong args count");
    }

    const char* file = argv[1];
    const char* content = "foobar";

    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        err(2, "Error opening");
    }

    pid_t pid = fork();
    int status;
    if (pid == -1) {
        err(3, "Couldn't fork");
    }

    if (pid == 0) {
        if (write(fd, content, strlen(content)) == -1) {
            err(4, "Error writting");
        }
    }
    else if (pid > 0) {
        if (wait(&status) == -1) {
            err(5, "Wait error");
        }

        if (!WIFEXITED(status)) {
             errx(6, "Did not terminated normally");
        }

        if (WEXITSTATUS(status)) {
            errx(7, "child exit code not 0");
        }

        if (lseek(fd, 0, SEEK_SET) == -1) {
            err(8, "lseek error");
        }

        ssize_t read_bytes = 0;
        char ch[2];
        while ((read_bytes = read(fd, &ch, sizeof(ch))) > 0) {
            if (write(1, &ch, sizeof(ch)) == -1) {
                err(4, "Error writting");
            }
            if (write(1, " ", 1) == -1) {
                err(4, "Error writting");
            }
        }

        if (read_bytes == -1) {
            err(9, "Error while reading");
        }
    }

    close(fd);
    return 0;
}
