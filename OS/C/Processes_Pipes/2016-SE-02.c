//simple cmd prompt

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

static void execute(const char* cmd) {
    char full_command[256];

    strcpy(full_command, "/bin/");
    strcat(full_command, cmd);

    pid_t pid = fork();
    int status;

    if (pid == -1) {
        err(3, "Couldn't fork");
    }

    if (pid == 0) {
        if (execl(full_command, full_command, (char*)NULL) == -1) {
            err(5, "error executing");
        }
    }
    else if (pid > 0) {
        if (wait(&status) == -1) {
            err(4, "error wait");
        }
        if (!WIFEXITED(status)) {
            errx(6, "Child did not terminate normally.");
        }
    }
}

void run() {
    char buff[128];

    while (true) {
        if (write(1, "> ", 2) == -1) {
            err(1, "Error writting");
        }

        uint8_t i = 0;
        char byte = 0;
        ssize_t bytes_read = 0;

        while ((bytes_read = read(0, &byte, sizeof(byte))) > 0) {
            if (byte == '\n') {
                break;
            }

            buff[i] = byte;
            i++;
        }

        if (bytes_read == -1) {
            err(2, "Error reading");
        }

        buff[i] = '\0';

        if (strcmp(buff, "exit") == 0) {
            break;
        }

        execute(buff);
    }
}

int main(void) {
    run();
    return 0;
}