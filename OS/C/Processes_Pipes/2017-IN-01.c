#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <err.h>

// cut -d: -f7 /etc/passwd | sort | uniq -c | sort -n
// we have 4 processes, connected with 3 pipes
// for every command -> fork
// we have 1 parent process and many children processes

int main(void) {
    int fd1[2];
    int fd2[2];
    int fd3[2];

    if (pipe(fd1) == -1) {
        err(1, "error piep");
    }

    if (pipe(fd2) == -1) {
        err(1, "error piep");
    }

    if (pipe(fd3) == -1) {
        err(1, "error piep");
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        err(2, "error fork");
    }
    
    if (pid1 == 0) {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);

        close(fd2[0]); close(fd2[1]);
        close(fd3[0]); close(fd3[1]);

        execlp("cut", "cut", "-d:", "-f7", "/etc/passwd", NULL);
        err(1, "execlp cut failed");
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        err(2, "error fork");
    }

    if (pid2 == 0) {
        close(fd1[1]);
        dup2(fd1[0], 0);
        close(fd1[0]);

        close(fd2[0]);
        dup2(fd2[1], 1);
        close(fd2[1]);

        close(fd3[0]); close(fd3[1]);

        execlp("sort", "sort", NULL);
        err(2, "execlp sort failed");
    }

    pid_t pid3 = fork();

    if (pid3 == -1) {
        err(2, "error fork");
    }

    if (pid3 == 0) {
        close(fd2[1]);
        dup2(fd2[0], 0);
        close(fd2[0]);

        close(fd3[0]);
        dup2(fd3[1], 1);
        close(fd3[1]);

        close(fd1[0]); close(fd1[1]);

        execlp("uniq", "uniq", "-c", NULL);
        err(3, "execlp uniq failed");
    }

    pid_t pid4 = fork();

    if (pid4 == -1) {
        err(2, "error fork");
    }

    if (pid4 == 0) {
        close(fd3[1]);
        dup2(fd3[0], 0);
        close(fd3[0]);

        close(fd1[0]); close(fd1[1]);
        close(fd2[0]); close(fd2[1]);
        
        execlp("sort", "sort", "-n", NULL);
        err(4, "execlp sort -n failed");
    }

    close(fd1[0]); close(fd1[1]);
    close(fd2[0]); close(fd2[1]);
    close(fd3[0]); close(fd3[1]);
    
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    
    return 0;
}

// we can have only 3 proccesses, the last sort in the parent
// but this way the child proccesses will become zombies, because we don't do wait()