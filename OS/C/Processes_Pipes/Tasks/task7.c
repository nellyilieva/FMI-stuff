// Да се напише програма на С, която получава като параметри три команди (без параметри),
// изпълнява ги последователно, като изчаква края на всяка и извежда на стандартния изход
// номера на завършилия процес, както и неговия код на завършване.

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void runCmd(const char* cmd) {
    int status;
    pid_t pid = fork();

    if (pid == -1) {
        err(2, "Couldn't fork");
    }

    if (pid == 0) {
        if (execlp(cmd, cmd, (char*)NULL) == -1) {
            err(3, "Error executing");
        }
    }
    else if (pid > 0) {
        if (wait(&status) == -1) {
            err(4, "Wait error");
        }
        if(!WIFEXITED(status)) {
            errx(5, "%s did not terminated normally", cmd);
        }

        int exit_code = WEXITSTATUS(status);
        dprintf(1, "Command: %s | PID: %d | Exit Code: %d\n", cmd, pid, exit_code);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Wrong args count");
    }

    const char* cmd1 = argv[1];
    const char* cmd2 = argv[2];
    const char* cmd3 = argv[3];

    runCmd(cmd1);
    runCmd(cmd2);
    runCmd(cmd3);

    return 0;
}