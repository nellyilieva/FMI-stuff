#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/wait.h>

void findFiles(int pfd[2], const char* dir) {
    pid_t pid = fork();

    if (pid == -1) {
        err(2, "fork error");
    }
    else if (pid == 0) {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);

        char cmd[1024] = "";
        strcat(cmd, "find ");
        strcat(cmd, dir);
        strcat(cmd, " -type f -not -name '*.hash'");

        execlp("/bin/sh", "sh", "-c", cmd, NULL);
        err(1, "execlp error");
    }
    else {
        close(pfd[1]);
    }
}

// simple line reader
void readLine(int fd, char* buf, size_t size, char sep) {
    size_t i = 0;
    char c;
    ssize_t r;

    while ((r = read(fd, &c, 1)) == 1 && i < size - 1) {
        if (c == sep) break;
        buf[i++] = c;
    }

    if (r == -1) {
        err(1, "read error");
    }

    buf[i] = '\0';
}

void createHashFile(const char* filename) {
    char outname[2048];
    outname[0] = '\0';

    // Copy original filename into outname
    strcpy(outname, filename);

    // Append ".hash" manually
    strcat(outname, ".hash");

    int fd = open(outname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        err(1, "couldn't open output file");
    }

    pid_t pid = fork();
    if (pid == -1) {
        err(1, "fork error");
    }

    if (pid == 0) {
        dup2(fd, 1); // redirect stdout to file
        close(fd);
        execlp("md5sum", "md5sum", filename, NULL);
        err(1, "md5sum error");
    } else {
        close(fd);
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            err(1, "md5sum child failed");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "args count must be 1");
    }

    int pfd[2];
    if (pipe(pfd) == -1) {
        err(1, "pipe error");
    }

    findFiles(pfd, argv[1]);

    char buf[1024];
    int childCount = 0;

    while (true) {
        readLine(pfd[0], buf, sizeof(buf), '\n');
        if (strlen(buf) == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == -1) {
            err(3, "fork error");
        }
        else if (pid == 0) {
            close(pfd[0]);
            createHashFile(buf);
            exit(0);
        }

        childCount++;
    }

    close(pfd[0]);

    // Wait for all children
    for (int i = 0; i < childCount + 1; i++) {  !!!!!!
        int status;
        wait(&status);
    }

    return 0;
}
