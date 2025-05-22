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

static void read_param(char* buff) {
    ssize_t bytes_read = 0;
    char byte = 0;
    int len = 0;

    while ((bytes_read = read(0,&byte,sizeof(byte))) > 0) {
        if(len == 4) {
			errx(3,"Param is longer than 4 chars!");
		}
		else if(byte == 0x20 || byte == 0x0A) {
			break;
		}

		buff[len] = byte;
        len++;
    }

    if (bytes_read == -1) {
        err(2, "Error reading");
    }

    buff[len] = '\0';
}

void execute_cmd(const char* command, const char* param1, const char* param2) {
    pid_t pid = fork();

    if (pid == -1) {
        err(4, "Couldn't fork");
    }

    if (pid == 0) {
        if (*param2 == '\0') {
            if (execlp(command, command, param1, NULL) == -1) {
                err(5, "Couldnt exec single param!");
            }
        }
        else {
            if (execlp(command, command, param1, param2, NULL) == -1) {
                err(5, "Couldnt exec single param!");
            }
        }
    }
}

void run(const char* cmd) {
    char param1[5] = {'\0'};
    char param2[5] = {'\0'};

    while (true) {
        read_param(param1);
        read_param(param2);
        if(*param1 == '\0' && *param2 == '\0') {
			return ;
		}

        execute_cmd(cmd,param1,param2);
    }
}

int main(int argc, char* argv[]) {
    if (argc > 2) {
        errx(1, "Wrong count args");
    }
    else if (argc == 2 && strlen(argv[1]) < 5) {
        run(argv[1]);
    }
    else if (argc == 1) {
        run("echo");
    }

    return 0;
}