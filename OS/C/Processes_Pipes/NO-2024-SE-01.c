#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/wait.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "wrong args");
    }

    char* endptr;
    int N = strtol(argv[2], &endptr, 10);

    if(*argv[2] == '\0' || *endptr != '\0') {
        errx(1, "N must be an int");
    }

    if(N < 0 || N >= 256) {
        errx(1, "N must be in range [0, 256)");
    }

    int urandom = open("/dev/urandom", O_RDONLY);
    if(urandom == -1) { err(1, "/dev/urandom"); }

    int null = open("/dev/null", O_WRONLY);  
    if(null == -1) { err(1, "/dev/null"); }

    char buf[UINT16_MAX];

    for (int i = 0; i < N; i++) {
        int pfd[2];
        if(pipe(pfd) == -1) { err(1, "pipe"); }

        pid_t pid = fork();
        if(pid == -1) { err(1, "fork"); }

        if(pid == 0) {
            close(urandom);
            close(pfd[1]);

            dup2(pfd[0], 0);
            close(pfd[0]);

            dup2(null, 1);
            dup2(null, 2);
            close(null);

            execl(argv[1], argv[1], (char*)NULL);
            err(1, "exec");
        }

        close(pfd[0]);

        int out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(out == -1) { err(1, "%s", argv[3]); }

        uint16_t to_write;
        if(read(urandom, &to_write, sizeof(to_write)) == -1) { 
            err(1, "read from /dev/urandom"); 
        }

        
    }

}