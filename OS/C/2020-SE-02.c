#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>

int main(int argc, char* argv []) {
    // reads byte by byte; 1 byte -> 8 bits, for each reads element from sdl, check if the bit is 1 and writes it
    if (argc != 3) {
        errx(1, "Args count must be 2");
    }

    const char* scl = argv[1];
    const char* sdl = argv[2];
    const char* res = "res.txt";

    int fd_scl = open(scl, O_RDONLY);
    if (fd_scl == -1) {
        err(2, "Error opening");
    }

    int fd_sdl = open(sdl, O_RDONLY);
    if (fd_sdl == -1) {
        err(2, "Error opening");
    }

    int fd_res = open(res, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_res == -1) {
        err(2, "Error opening");
    }

    struct stat st;
    if (fstat(fd_scl, &st) == -1) {
        err(3, "stat error");
    }

    size_t scl_size = st.st_size;

    if (fstat(fd_sdl, &st) == -1) {
        err(3, "stat error");
    }

    size_t sdl_size = st.st_size;

    if (sdl_size % sizeof(uint16_t) != 0) {
         errx(4, "Incorrect size");
    }

    if (scl_size * 8 != sdl_size / 2) {
        errx(4, "Incorrect size");
    }

    ssize_t read_bytes = 0;
    uint8_t bytes;

    while ((read_bytes = read(fd_scl, &bytes, sizeof(bytes))) > 0) {
        for (int i = 0; i < 8; i++) {
            uint16_t sdlEl;
            int readSdl = read(fd_sdl, &sdlEl, sizeof(sdlEl));

            if (readSdl == -1) {
                err(5, "Error while reading");
            }

            if ((bytes >> i) & 1) {
                int write_bytes = write(fd_res, &sdlEl, sizeof(sdlEl));

                if (write_bytes == -1) {
                    err(6, "Error while writting");
                }
            }
        }
    }
    if (read_bytes == -1) {
        err(5, "Error while reading");
    }
    
    close(fd_scl);
    close(fd_sdl);
    close(fd_res);
    return 0;
}