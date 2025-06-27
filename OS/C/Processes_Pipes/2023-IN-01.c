#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <sys/wait.h>

// again semaohores; we use signal in every process to tell the next one it is done
// we do it with pipes; we use pipe between evry 2 processes; NC + 1 pipes; max -> 8
// чете от pipe[i], пише в pipe[i+1]
// the processes write and read from the pipes the index and with that the signal each other that they are finished

const char* list[3] = {"tic ","tac ","toe\n"};
const int MAX_PROCESSES = 8;

void init_pipes(int NC, int pipes[MAX_PROCESSES][2]) {
    for (int i = 0; i < NC + 1; i++) {
        if (pipe(pipes[i]) == -1) {
            err(3, "pipe error");
        }
    }
}

void close_unused_pipes(int NC, int pipes[MAX_PROCESSES][2], int in, int out) {
    for (int i = 0; i < NC + 1; i++) {
        if (i != in && i != out) {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
    }
}

void run_loop(int in, int out, int pipes[MAX_PROCESSES][2], int WC) {
    int index;
    while (read(pipes[in][0], &index, sizeof(index)) > 0) {
        if (index == WC) {
            break;
        }
        dprintf(1, "%s", list[index % 3]);
        index++;
        if (write(pipes[out][1], &index, sizeof(index)) == -1) {
            err(5, "child write failed");
        }
    }
}

void spawn_worker(int id, int NC, int WC, int pipes[MAX_PROCESSES][2]) {
    pid_t pid = fork();
    if (pid == -1) {
        err(4, "fork failed");
    }

    if (pid == 0) {
        close(pipes[id][1]);
        close(pipes[id + 1][0]);
        close_unused_pipes(NC, pipes, id, id + 1);
        run_loop(id, id + 1, pipes, WC);
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "args count must be 2");
    }

    char* endptr;

    int NC = strtol(argv[1], &endptr, 10);
    if (*argv[1] == '\0' || *endptr != '\0') {
        errx(1, "expected int");
    }
    if (NC < 1 || NC > 7) {
        errx(1, "N >= 1");
    }

    int WC = strtol(argv[2], &endptr, 10);
    if (*argv[2] == '\0' || *endptr != '\0') {
        errx(1, "expected int");
    }
    if (WC < 1 || WC > 35) {
        err(1, "D >= 0");
    }

    int pipes[MAX_PROCESSES][2];
    init_pipes(NC, pipes);

    int index = 0;
    dprintf(1, "%s", list[index % 3]);  // to stdout
    index++;

    for (int i = 0; i < NC; i++) {
        spawn_worker(i, NC, WC, pipes);
    }

    close(pipes[NC][1]);
    close(pipes[0][0]);
    close_unused_pipes(NC, pipes, NC, 0);

    if (write(pipes[0][1], &index, sizeof(index)) == -1) {
        err(5, "parent write failed");
    }

    run_loop(NC, 0, pipes, WC);

    for (int i = 0; i < NC; i++) {
        wait(NULL);
    }
    return 0;
}