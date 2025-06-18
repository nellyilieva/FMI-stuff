#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// so in child -> Q; parent -> P; Parent waits for Q to finish
// now it's like we are in P

int main(int agrc, char* argv[]) {
    if (argc < 3) {
        errx(1, "Args count wrong");
    }

    int seconds = atoi(argv[1]);
    char* Q = argv[2];
    char** q_args = &argv[2];

    int fd = open("run.log", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd == -1) {
        err(2, "error opening");
    }

    bool has_previous = false;
    int prev_exit_code = 0;
    time_t prev_duration = 0;

    while (true) {
        time_t start_time = time(NULL);

        pid_t pid = fork();
        if (pid == -1) {
            err(3, "fork error");
        }

        if (pid == 0) {
            execvp(Q, q_args);
            err(4, "exec failed");
        }

        int status;
        if (wait(&status) == -1) {
            err(4, "error wait");
        }

        time_t end_time = time(NULL);
        time_t duration = end_time - start_time;

        int exit_code;
        if (WIFEXITED(status)) {
            exit_code = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status)) {
            exit_code = 129;
        }
        else {
            exit_code = -1;
        }

        write(fd, &start_time, sizeof(time_t));  // here do them in if == -1
        write(fd, " ", 1);
        write(fd, &end_time, sizeof(time_t));
        write(fd, " ", 1);
        write(fd, &exit_code, sizeof(int));
        write(fd, "\n", 1);

        if (has_previous && exit_code != 0 && duration < seconds && prev_exit_code != 0 && prev_duration < seconds) {
            break;
        }
        
        prev_exit_code = exit_code;
        prev_duration = duration;
        has_previous = true;
    }

    close(fd);
    return 0;
}