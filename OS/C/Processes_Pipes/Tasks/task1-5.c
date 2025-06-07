#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <sys/types.h>

// T1 - Да се напише програма на C, която изпълнява команда date.
// int main (void) {
//     if (execl("/bin/date", "date", (char*)NULL) == -1) {  //or just NULL
//         err(1, "err executing");
//     }

//     return 0;
// }

// T2 - Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         errx(1, "Wrong count of args");
//     }

//     if (execl("/bin/ls", "ls", argv[1], NULL) == -1) {
//         err(2, "error executing");
//     }
//     return 0;
// }

// T3 - Да се напише програма на C, която изпълнява команда sleep (за 60 секунди).
// int main(void) {
//     if (execlp("sleep", "sleep","60", NULL) == -1) {
//          err(1, "err executing");
//     }
//     return 0;
// }

// T4 - Да се напише програма на C, която създава процес дете и демонстрира принцина на конкурентност при процесите.
// int main(void) {
//     int n = 10;

//     pid_t pid = fork();

//     if (pid == 0) {
//         for (int i = 0; i < n; i++) {
//             write(1, "C", 1);
//         }
//     }
//     else if (pid > 0) {
//         for (int i = 0; i < n; i++) {
//             write(1, "P", 1);
//         }
//     }
//     else if (pid == -1) {
//         err(1, "BOO");
//     }
//     return 0;
// }

// T5 - Да се напише програма на C, която е аналогична на горния пример, но принуждава бащата да изчака сина си да завърши.
int main(void) {
    int n = 10;
    int status;  //stores the child's exit info

    pid_t pid = fork();

    if (pid == 0) {
        for (int i = 0; i < n; i++) {
            write(1, "C", 1);
        }
    }
    else if (pid > 0) {
        wait(&status);  //causes the parent process to pause execution until one of its children exits
        for (int i = 0; i < n; i++) {
            write(1, "P", 1);
        }
    }
    else if (pid == -1) {
        err(1, "BOO");
    }
    return 0;
}

// The child process cannot directly wait for the parent using wait(); return -1
// We can do it with pipes or sleep()
// wait() check if it has child porcesses; the child in most cases do not
// if parent dies first, the child gets adopted by the init process