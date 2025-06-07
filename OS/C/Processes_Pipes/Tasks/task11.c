// Да се напише програма на C, която изпълнява последователно подадените ѝ като параметри команди,
// като реализира следната функционалност постъпково:
// main cmd1 ... cmdN Изпълнява всяка от командите в отделен дъщерен процес.
// ... при което се запазва броя на изпълнените команди, които са дали грешка и броя на завършилите успешно.

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
    size_t successful = 0;
    size_t failed = 0;

    for (int i = 1; i < argc; i++) {
        const char* cmd = argv[i];

        pid_t pid = fork();
        int status;

        if (pid == -1) {
            err(1, "Couldn't fork");
        }

        if (pid == 0) {
            if (execlp(cmd, cmd, (char*)NULL) == -1) {
                err(2, "failed to exec %s", cmd);
            }
        }
        else if (pid > 0) {
            if (wait(&status) == -1) {
                err(3, "wait failed");
            }

            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {   //this with checks
                failed++;
            }
            else {
                successful++;
            }
        }
    }
    return 0;
}