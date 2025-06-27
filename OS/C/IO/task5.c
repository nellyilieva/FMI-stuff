// cat command with args

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        const char* curr = argv[i];
        int fd_curr = open(curr, O_RDONLY);

        if (fd_curr == -1) {
            err(1, "Couldn't open %s", curr);
        }

        char buff = 0;  // we can use larger buff, char buff [1024]
        int read_bytes = 0;
        int write_bytes = 0;

        while ((read_bytes = read(fd_curr, &buff, sizeof(buff))) > 0) {
            write_bytes = write(1, &buff, sizeof(buff));

            if (write_bytes == -1) {
                close(fd_curr);
                err(3, "Error while writing");
            }

            // if (write(1, &buff, bytesCount) != bytesCount) {
            //     close(fd);
            //     err(2, "Couldn't output the bytes to std::out");
            // }
        }

        if (read_bytes == -1) {
            close(fd_curr);
            err(2, "Error while reading");
        }

        // while(read_bytes = read(fd_curr, &buff, sizeof(buff))) {
        //     if (read_bytes == -1) {
        //         close(fd_curr);
        //         err(2, "Error while reading");
        //     }

        //     write_bytes = write(1, &buff, sizeof(buff));

        //     if (write_bytes == -1) {
        //         close(fd_curr);
        //         err(3, "Error while writting");
        //     }
        // }

        close(fd_curr);
    }
}