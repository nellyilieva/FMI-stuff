// Да се напише програма на C, която която създава файл в текущата директория и генерира два процесa,
// които записват низовете foo и bar в създадения файл.
// Програмата не гарантира последователното записване на низове.
// Променете програмата така, че да записва низовете последователно, като първия е foo.

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
    int fd = open("f.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        err(1, "Error opening");
    }

    pid_t pid = fork();
    if (pid == -1) {
        err(2, "Couldn't fork");
    }

    int status;

    if (pid == 0) {
        if (write(fd, "foo", 3) == -1) {
            err(3, "Error while writting");
        }
        close(fd);
    }
    else if (pid > 0) {
        if (wait(&status) == -1) {
            err(4, "Wait error");
        }

        if (write(fd, "bar", 3) == -1) {
            err(3, "Error while writting");
        }
    }
    
    close(fd);
    return 0;
}