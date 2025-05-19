#include <stdint.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct pair {
    uint32_t x;
    uint32_t y;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Arguments must be 3");
    }

    const char* f1 = argv[1];
    const char* f2 = argv[2];
    const char* f3 = argv[3];

    int fd_1 = open(f1, O_RDONLY);

    if (fd_1 == -1) {
        err(2, "f1");
    }

    int fd_2 = open(f2, O_RDONLY);

    if (fd_2 == -1) {
        close(fd_1);
        err(3, "f2");
    }

    int fd_3 = open(f3, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd_3 == -1) {
        close(fd_1);
        close(fd_2);
        err(4, "f3");
    }

    struct stat st;

    if (fstat(fd_1, &st) == -1) {
        err(5, "stat");
    }

    size_t f1_s = st.st_size;

    if (f1_s == 0) {
        errx(6, "Empty file");
    }

    if (fstat(fd_2, &st) == -1) {
        err(5, "stat");
    }

    size_t f2_s = st.st_size;

    if (f2_s == 0) {
        errx(6, "Empty file");
    }

    // the files need to be closed but who has time for this

    if (f1_s % sizeof(struct pair) != 0) {
        errx(7, "Invalid f1 size");
    }

    struct pair p;

    ssize_t bytes_read = 0;

    while ((bytes_read = read(fd_1, &p, sizeof(p))) > 0) {
        if ((p.x +p.y) * sizeof(uint32_t) > f2_s) {
            errx(8, "invalid pair");
        }

        if (lseek(fd_2, p.x * sizeof(uint32_t), SEEK_SET) == -1) {
            err(10, "lseek error");
        }

        if (bytes_read == -1) {
            err(9, "Error while reading");
        }

        uint32_t num = 0;

        for (unsigned int i = 0; i < p.y; i++) {
            if (read(fd_2, &num, sizeof(num)) == -1) {
                err(9, "Error while reading");
            }

            if (write(fd_3, &num, sizeof(num)) == -1) {
                err(11, "Error while writting");
            }
        }

    }

    close(fd_1);
    close(fd_2);
    close(fd_3);

    return 0;
}