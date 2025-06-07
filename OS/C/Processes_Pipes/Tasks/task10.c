// Да се напише програма на C, която получава като параметри от команден ред две команди (без параметри).
// Изпълнява първата. Ако тя е завършила успешно изпълнява втората. Ако не, завършва с код 42.

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Args count wrong");
    }

    const char* cmd1 = argv[1];
    const char* cmd2 = argv[2];

    pid_t pid = fork();
    int status;

    if (pid == -1) {
        err(2, "Couldn't fork");
    }

    if (pid == 0) {
        if (execlp(cmd1, cmd1, (char*)NULL) == -1) {
            err(3, "failed to exec %s", cmd1);
        }
    }
    else if (pid > 0) {
        if (wait(&status) == -1) {
            err(4, "wait failed");
        }

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {   //this with checks
            exit(42);
        }

        execlp(cmd2, cmd2, (char*)NULL);
        err(5, "failed to exec %s", cmd2);
    }
    return 0;
}

//or with 2 forks for each command