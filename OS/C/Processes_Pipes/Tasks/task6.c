// Да се напише програма на С, която получава като параметър команда (без параметри)
// и при успешното ѝ изпълнение, извежда на стандартния изход името на командата.

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Wrong args count");
    }

    const char* cmd = argv[1];
    int status;

    pid_t pid = fork();

    if (pid == 0) {
        if (execlp(cmd, cmd, (char*)NULL) == -1) {
            err(2, "err executing");
        }
    }
    else if (pid > 0) {
        if (wait(&status) == -1) {
            err(4, "wait failed");
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            write(1, cmd, strlen(cmd));
            write(1, "\n", 1);
        }
        else {
            errx(4, "not correct execution");
        }
    }
    else if (pid == -1) {
        err(3, "Error fork");
    }
}

//  if (!(WIFEXITED(child_exit_status))) {
//         errx(5, "child did not terminate normally");
//     }

//     if(WEXITSTATUS(child_exit_status)) {
//         errx(6, "child exit code not 0");
//     }