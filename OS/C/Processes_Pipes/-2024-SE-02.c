#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// syshtoto, imame parent, koito e nablydatel
// otdelni child da izpylnqvat programite
// status 0 -> priklychila
// status ne 0 -> otnovo
// ubit proces -> kill(pid, SIGTERM); status -> num program

typedef struct program {
    const char *path;
    pid_t current_pid;
    bool done;
} program;

void startProgram(program *prg) {
    pid_t pid = fork();
    if (pid == -1) {
        err(1, "can't fork");
    }

    if (pid == 0) {
        execl(prg->path, prg->path, (char *)NULL);
        err(1, "can't exec");
    }

    prg->current_pid = pid;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        errx(1, "bad args");
    }

    program programs[10];
    int count = argc - 1;

    // Initialize and start all programs
    for (int i = 0; i < count; i++) {
        programs[i].path = argv[i + 1];     // store the program name
        programs[i].current_pid = 0;        // no PID yet
        programs[i].done = false;           // not yet done
        startProgram(&programs[i]);         // start the program
    }

    int countDone = 0;

    while (countDone < count) {
        int result;
        pid_t pid = wait(&result);          // wait for *any* child process to finish

        if (pid == -1) {
            err(1, "wait");
        }

        // Find which program this pid belongs to
        program *prg = NULL;
        int i;
        for (i = 0; i < count; i++) {
            if (!programs[i].done && programs[i].current_pid == pid) {
                prg = &programs[i];
                break;
            }
        }

        if (prg == NULL) {
            errx(1, "logic error");
        }

        // Process finished -> check its exit status
        if (WIFEXITED(result)) {
            if (WEXITSTATUS(result) == 0) {
                prg->done = true;
                countDone++;
            } else {
                // If not successful, restart the program
                startProgram(prg);
            }
        } else {
            // Process was killed by signal (e.g. segfault)
            prg->done = true;

            // Stop all other running programs
            for (int i = 0; i < count; i++) {
                if (!programs[i].done) {
                    kill(programs[i].current_pid, SIGTERM);
                }
            }

            // Wait for all terminated programs
            while (wait(NULL) > 0);

            // Exit with number of the program that was killed (1-indexed)
            exit(i + 1);
        }
    }

    return 0;
}

// wait(&status)	Waits for any child to finish. Returns its PID.
// waitpid(pid, &status, 0)	Waits for a specific child with pid.
// WIFEXITED(status) -> returns true if the child exited normally (via return or exit()).
// WIFSIGNALED(status) -> returns true if the child was killed by a signal (e.g., segfault).