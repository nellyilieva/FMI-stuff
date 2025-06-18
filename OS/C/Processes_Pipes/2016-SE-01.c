#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <sys/wait.h>

// 2 process -> 1 pipe; cat file.txt | sort

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "needs 2 args");
    }

    int pfd[2];
    if (pipe(pfd) < 0) {
        err(1, "pipe error");
    }

    pid_t pid = fork();

    if (pid == -1) {
        err(2, "fork error");
    }
    else if (pid == 0) {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);

        execlp("cat", "cat", argv[1], NULL);
        errx(3, "can't cat");
    }
    else if (pid > 0) {
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);

        execlp("sort", "sort", NULL);
        errx(4, "can't sort");
    }
}