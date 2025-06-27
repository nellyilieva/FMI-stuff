#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>
#include <stdint.h>

// obshto vzeto pak imame programa nablydatel
// trqbva da vidim kak si generirame random dannite
// N pyti gi podavame, pravim N deca za tezi N puti
// i sushto taka pravim monitor process da sledi dali nqkoq programa ne e krashnala

#define MAX_INPUT_SIZE 65536  // 2^16

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "args count must be 3");
    }

    char *endptr;
    int N = strtol(argv[2], &endptr, 10);
    if (*argv[2] == '\0' || *endptr != '\0') {
        errx(1, "expected int");
    }
    if (N < 1) {
        errx(1, "wrong N");
    }

    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd == -1) {
        err(1, "cannot open /dev/urandom");
    }

    int res_fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (res_fd == -1) {
        err(1, "cannot open result file");
    }

    char buffer[MAX_INPUT_SIZE];
    for (int i = 0; i < N; i++) {
        uint16_t S;
        if (read(urandom_fd, &S, sizeof(S)) == -1) {
            err(1, "reading input size from /dev/urandom failed");
        }

        ssize_t total = 0;
        while (total < S) {
            ssize_t r = read(urandom_fd, buffer + total, S - total);
            if (r <= 0) {
                err(1, "reading random input failed");
            }
            total += r;
        }

        int pfd[2];
        if (pipe(pfd) == -1) {
            err(1, "pipe error");
        }

        pid_t pid = fork();

        if (pid == -1) {
            err(2, "fork error");
        }
        else if (pid == 0) {
            close(pfd[1]);  //close write
            if (dup2(pfd[0], 0) == -1) {
                err(1, "dup2 stdin failed");
            }
            close(pfd[0]);

            int devnull = open("/dev/null", O_WRONLY);
            if (devnull == -1) {
                err(1, "open /dev/null failed");
            }
            if (dup2(devnull, 1) == -1 || dup2(devnull, 2) == -1) {
                err(1, "dup2 to /dev/null failed");
            }
            close(devnull);

            execl(argv[1], argv[1], (char*)NULL);
            err(1, "exec failed");
        }

        close(pfd[0]);  //close read

        ssize_t written = 0;
        while (written < S) {
            ssize_t w = write(pfd[1], buffer + written, S - written);
            if (w <= 0) {
                err(1, "writing to child stdin failed");
            }
            written += w;
        }
        close(pfd[1]);

        int status;
        if (waitpid(pid, &status, 0) == -1) {
            err(1, "waitpid failed");
        }

        if (WIFSIGNALED(status)) {
            ssize_t out_written = 0;
            while (out_written < S) {
                ssize_t w = write(res_fd, buffer + out_written, S - out_written);
                if (w <= 0) {
                    err(1, "writing to result file failed");
                }
                out_written += w;
            }

            close(urandom_fd);
            close(res_fd);
            exit(42); // crash found
        }
    }

    close(urandom_fd);
    close(res_fd);
    return 0;
}