// :tabe bar.c (inside Vim)
// Switch between files in Vim	gt, gT

// foo

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Invalid arguments. Usage: %s <file_name>", argv[0]);
    }

    const char* file = argv[1];
    const char* pipe_name = "/tmp/my_pipe";

    if (mkfifo(pipe_name, 0666) == -1) {
        if (errno != EEXIST) {
            err(1, "couldn't make the pipe");
        }
    }
   
    int fd = open(pipe_name, O_WRONLY);

    if (fd == -1) {
        err(2, "Error writting");
    }

    dup2(fd, 1);  // redirect stdout to the pipe
    close(fd);    // close original fd, it's now duplicated

    if (execlp("cat", "cat", argv[1], NULL) == -1) {  // replace currect foo process
        err(3, "Couldn't execlp");
    }
}

// bar

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Invalid arguments. Usage: %s <file_name>", argv[0]);
    }

    const char* cmd = argv[1];
    const char* pipe_name = "/tmp/my_pipe";

    if (mkfifo(pipe_name, 0666) == -1) {
        if (errno != EEXIST) {
            err(1, "couldn't make the pipe");
        }
    }
   
    int fd = open(pipe_name, O_RDONLY);

    if (fd == -1) {
        err(2, "Error writting");
    }

    dup2(fd, 0);  // redirect stdin to the pipe
    close(fd);    // close original fd, it's now duplicated

    if (execlp(cmd, cmd, (char*)NULL) == -1) {
        err(3, "Couldn't execlp");
    }
}