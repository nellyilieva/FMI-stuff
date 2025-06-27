#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/wait.h>

// so for every cmd i get as parametar i do fork and execl it in the child process
// i will redirect with pipe stdout in the pipe[1] to check in the text out
// if it is “found it!” i will stop the processes with SIGTERM
// then exit with the needed code
// i don't know maybe the child processes needs to be paralel i am not sure if i do that by having child process dor evry command
// i would need to monitor evry child's stdout, so i will create another fork and child process to read from the pipe 
// For each command:
// Fork 1: child to run the command
// Fork 2: child to read its output
// The main parent:
// Forks these pairs
// Watches the monitor children with wait()

#define MAX_CMDS 256
#define LINE_MAX 1024

pid_t cmd_pids[MAX_CMDS];
int n_cmds;

void kill_all() {
    for (int i = 0; i < n_cmds; i++) {
        if (cmd_pids[i] > 0) {
            kill(cmd_pids[i], SIGTERM);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        errx(26, "need at leat 1 arg");
    }

   n_cmds = argc - 1;
   int pipes[MAX_CMDS][2];

    for (int i = 0; i < n_cmds; i++) {
        if (pipe(pipes[i]) == -1) {
            err(26, "error pipe");
        }

        pid_t pid = fork();

        if (pid == -1) {
            err(26, "fork error");
        }
        else if (pid == 0) {
            close(pipes[i][0]);
            dup2(pipes[i][1], 1);
            close(pipes[i][1]);

            if (execlp(argv[i + 1], argv[i + 1], (char*)NULL) == -1) {
                err(26, "exec error");
            }
        }

        cmd_pids[i] = pid;  //for later to SIGTERM
        close(pipes[i][1]);
    }

    // to monitor the output of every command

    for (int i = 0; i < n_cmds; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            err(26, "fork error");
        }
        else if (pid == 0) {
            char line[LINE_MAX];
            int pos = 0;
            char c;
            while (read(pipes[i][0], &c, 1) == 1) {
                if (c == '\n' || pos >= LINE_MAX - 1) {
                    line[pos] = '\0';
                    if (strcmp(line, "found it!") == 0) {
                        kill_all();
                        _exit(0);
                    }
                    pos = 0; // Reset line
                } else {
                    line[pos++] = c;
                }
            }
            _exit(1);
        }
        close(pipes[i][0]);
    }

    int status;
    int found = 0;
    for (int i = 0; i < n_cmds; i++) {
        if (wait(&status) == -1) {
            err(26, "wait");
        }

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            found = 1;
        }
    }

    for (int i = 0; i < n_cmds; i++) {
        waitpid(cmd_pids[i], NULL, 0);
    }

    return found ? 0 : 1;
}