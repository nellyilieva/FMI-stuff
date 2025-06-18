#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <err.h>

// find dir -type f -printf "%T@ %p\n" | sort -n | tail -1 | awk '{print $2}'
int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Usage: %s <directory>", argv[0]);
    }
    
    const char* dir = argv[1];
    int fd1[2], fd2[2], fd3[2];

    if (pipe(fd1) == -1) {
        err(1, "error pipe fd1");
    }
    if (pipe(fd2) == -1) {
        err(1, "error pipe fd2");
    }
    if (pipe(fd3) == -1) {
        err(1, "error pipe fd3");
    }
    
    pid_t pid1 = fork();
    if (pid1 == -1) {
        err(1, "error fork pid1");
    }
    
    if (pid1 == 0) {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);
        
        close(fd2[0]); close(fd2[1]);
        close(fd3[0]); close(fd3[1]);
        
        execlp("find", "find", dir, "-type", "f", "-printf", "%T@ %p\n", NULL);
        err(1, "execlp find failed");
    }
    
    pid_t pid2 = fork();
    if (pid2 == -1) {
        err(1, "error fork pid2");
    }
    
    if (pid2 == 0) {
        close(fd1[1]);
        dup2(fd1[0], 0);
        close(fd1[0]);
        
        close(fd2[0]);
        dup2(fd2[1], 1);
        close(fd2[1]);
        
        close(fd3[0]); close(fd3[1]);
        
        execlp("sort", "sort", "-n", NULL);
        err(1, "execlp sort failed");
    }
    
    pid_t pid3 = fork();
    if (pid3 == -1) {
        err(1, "error fork pid3");
    }
    
    if (pid3 == 0) {
        close(fd2[1]);
        dup2(fd2[0], 0);
        close(fd2[0]);
        
        close(fd3[0]);
        dup2(fd3[1], 1);
        close(fd3[1]);
        
        close(fd1[0]); close(fd1[1]);
        
        execlp("tail", "tail", "-1", NULL);
        err(1, "execlp tail failed");
    }
    
    pid_t pid4 = fork();
    if (pid4 == -1) {
        err(1, "error fork pid4");
    }
    
    if (pid4 == 0) {
        close(fd3[1]);
        dup2(fd3[0], 0);
        close(fd3[0]);
        
        close(fd1[0]); close(fd1[1]);
        close(fd2[0]); close(fd2[1]);
        
        execlp("awk", "awk", "{print $2}", NULL);
        err(1, "execlp awk failed");
    }
    
    close(fd1[0]); close(fd1[1]);
    close(fd2[0]); close(fd2[1]);
    close(fd3[0]); close(fd3[1]);
    
    int status;

    if (wait(&status) == -1) {
        err(1, "wait for child 1 failed");
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        errx(1, "find command failed with exit code %d", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
        errx(1, "find command terminated by signal %d", WTERMSIG(status));
    }
    
    if (wait(&status) == -1) {
        err(1, "wait for child 2 failed");
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        errx(1, "sort command failed with exit code %d", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
        errx(1, "sort command terminated by signal %d", WTERMSIG(status));
    }
    
    if (wait(&status) == -1) {
        err(1, "wait for child 3 failed");
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        errx(1, "tail command failed with exit code %d", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
        errx(1, "tail command terminated by signal %d", WTERMSIG(status));
    }
    
    if (wait(&status) == -1) {
        err(1, "wait for child 4 failed");
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        errx(1, "awk command failed with exit code %d", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
        errx(1, "awk command terminated by signal %d", WTERMSIG(status));
    }
    
    return 0;
}