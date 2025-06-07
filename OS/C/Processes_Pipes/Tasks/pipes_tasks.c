// Да се напише програма на C, която приема аргумент - име на файл. Програмата да:

// записва във файла 'fo'
// създава child процес, който записва 'bar\n'
// parent-а, след като изчака child процеса, записва 'o\n'

#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// const char *str1 = "fo";
// const char *str2 = "bar\n";
// const char *str3 = "o\n";

// int main (int argc, char* argv []) {
//     if (argc != 2) {
//         errx(1, "Need 1 file");
//     }

//     const char* file = argv[1];
//     int fd = open (file, O_RDWR | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1) {
//         err(2, "Error opening");
//     }

//     int bytes_write = write(fd, str1, strlen(str1));

//     if (bytes_write == -1) {
//         close(fd);
//         err(3, "Error writting");
//     }

//     int status;
//     pid_t pid = fork();

//     if (pid == -1) {
//         err(4, "Error while fork");
//     }

//     if (pid == 0) {
//         int bytes_write = write(fd, str2, strlen(str2));

//         if (bytes_write == -1) {
//             close(fd);
//             err(3, "Error writting");
//         }
//     }
//     else if (pid > 0) {
//         if(!WIFEXITED(status)) {
//             close(fd);
//             err(5, "Child process did not terminate normally");
//         }

//         if(WEXITSTATUS(status) != 0) {
//             close(fd);
//             err(6, "Child process exited with status != 0");
//         }

//         int bytes_write = write(fd, str3, strlen(str3));

//         if (bytes_write == -1) {
//             close(fd);
//             err(3, "Error writting");
//         }
//     }
//     return 0;
// }

// Напишете програма на C, която демонстрира комуникация през pipe между parent и child процеси.
// Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а,
// който да го отпечатва на стандартния изход.

int main (int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Need 1 file");
    }

    int pf[2];

    if (pipe(pf) == -1) {
        err(2, "Could not create pipe");
    }

    const char* str = argv[1];

    pid_t pid = fork();   //both child and parent have access to the pipe
    if (pid == -1) {
        err(3, "Error while fork");
    }

    if (pid == 0) {
        close(pf[1]);  //close write end; child only reads from pf[0] char by char and writes it to stdout
        char buf;

        ssize_t bytes_read = 0;

        while((bytes_read = read(pf[0], &buf, sizeof(buf))) > 0) {
            if (write(1, &buf, sizeof(buf)) == -1) {
                err(4, "Error while writing to stdin");
            }
        }
        if (bytes_read == -1) {
            err(5, "Error reading");
        }

        close(pf[0]);
        return 0;
    }
    else if (pid > 0) {
        close(pf[0]);  //close read end; parent only writes into pf[1]

        if (write(pf[1], str, strlen(str)) == -1) {
            close(pf[1]);
            err(4, "Error writting");
        }

        close(pf[1]);  //done wrtting
        wait(NULL);   //wait for the child to finish; makes the parent pause
    }
    return 0;
}