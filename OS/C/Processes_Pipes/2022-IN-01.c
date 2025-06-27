#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

// One pipe to send signals from parent to child.
// One pipe to send signals from child to parent.
// => 1 child process
// bukvalno semafori, procesite se izpylnqvat i si signalizirat koi koga e priklychil

const char* DING = "DING ";
const char* DONG = "DONG\n";

void doParent(int N, int D, int toChild, int fromChild) {
    for(int i = 0; i < N; i++) {
        if(write(1, DING, strlen(DING)) == -1) { err(1, "write"); }

        // signal child
        char signal = 0;
        if(write(toChild, &signal, sizeof(signal)) == -1) { err(2, "write"); }

        // wait for child
        if(read(fromChild, &signal, sizeof(signal)) == -1) { err(2, "read"); }

        sleep(D);
    }
}

void doChild(int N, int toParent, int fromParent) {
    for(int i = 0; i < N; i++) {
        char signal;

        // wait for parent
        if(read(fromParent, &signal, sizeof(signal)) == -1) { err(2, "read"); }

        if(write(1, DONG, strlen(DONG)) == -1) { err(2, "write"); }

        // signal parent
        if(write(toParent, &signal, sizeof(signal)) == -1) { err(2, "write"); }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        errx(1, "arg count");
    }

    char* endptr;

    int N = strtol(argv[1], &endptr, 10);
    if(*argv[1] == '\0' || *endptr != '\0') {
        errx(1, "expected int");
    }
    if(N < 1) { errx(1, "N >= 1"); }

    int D = strtol(argv[2], &endptr, 10);
    if(*argv[2] == '\0' || *endptr != '\0') {
        errx(1, "expected int");
    }
    if(D < 0) { err(1, "D >= 0"); }

    int parent_to_child[2];
    if(pipe(parent_to_child) == -1) { err(1, "pipe"); }

    int child_to_parent[2];
    if(pipe(child_to_parent) == -1) { err(2, "pipe"); }

    pid_t pid = fork();
    if(pid == -1) { err(1, "fork"); }

    if(pid == 0) {
        // child

        close(parent_to_child[1]);  //close write
        close(child_to_parent[0]);  //close read

        doChild(N, child_to_parent[1], parent_to_child[0]);

        close(parent_to_child[0]);
        close(child_to_parent[1]);

        exit(0);
    }

    // parent

    close(parent_to_child[0]);
    close(child_to_parent[1]);

    doParent(N, D, parent_to_child[1], child_to_parent[0]);

    close(parent_to_child[1]);
    close(child_to_parent[0]);

    int status;
    wait(&status);

    if(!WIFEXITED(status)) {
        warnx("child was killed");
    }

    return 0;
}
   
    // for (int i = 0; i < N; i++) {
    //     write(1, "DING ", 5);

    //     pid_t child = fork();
    //     if (child == -1) {
    //         err(4, "fork failed");
    //     }
        
    //     if (child == 0) {
    //         write(1, "DONG\n", 5);
    //         exit(0);
    //     } else {
    //         wait(NULL);
    //         sleep(D);
    //     }
    // }