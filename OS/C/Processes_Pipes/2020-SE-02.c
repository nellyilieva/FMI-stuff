#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <sys/wait.h>

// byte 0x55, when no signal
// 0x00, 0xFF, 0x55 and 0x7D -> XOR with 0x20
// 0x7D -> escape char
// child -> cat file and data to pipe
// parent -> read from pipe and decode and writes bytes to output

// > 0 - number of bytes successfully read (1 in our case)
// 0 - end of file (EOF) - no more data
// < 0 - error occurred

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "need 2 args");
    }

    const char* in_file = argv[1];
    const char* out_file = argv[2];

    int pfd[2];

    if (pipe(pfd) < 0) {
        err(2, "pipe error");
    }

    pid_t pid = fork();

    if (pid == -1) {
        err(3, "fork error");
    }
    else if (pid == 0) {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);

        if (execl("/bin/cat", "cat", in_file, (char*)NULL) < 0) {
            err(4, "error execute");
        }
    }
    else if (pid > 0) {
        close(pfd[1]);

        int fd_o = open(out_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);

        if (fd_o == -1) {
            err(5, "Error opening");
        }

        unsigned char byte;
        ssize_t read_bytes = 0;

        while ((read_bytes = read(pfd[0], &byte, 1)) > 0) {
            if (byte == 0x7D) {
                if ((read_bytes = read(pfd[0], &byte, 1)) <= 0) {
                    err(6, "incomplete escape sequence");
                }

                byte ^= 0x20;
                if (write(fd_o, &byte, 1) < 0) {
                    err(7, "write error");
                }
            }
            else if (byte == 0x55) {
                continue;
            }
            else {
                if (write(fd_o, &byte, 1) < 0) {
                    err(8, "write error");
                }
            }
        }

        if (read_bytes == -1) {
            err(10, "read error");
        }
        close(pfd[0]);
        close(fd_o);

        int status;
        if (wait(&status) < 0) {
            err(9, "wait error");
        }

        if(!WIFEXITED(status)) {
            errx(1, "Child couldn't exit normally");
        }
    }
}