#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <err.h>
#include <sys/stat.h>

struct diff {
    uint16_t offset;
    uint8_t pos_o;
    uint8_t pos_n;
};

int main(int argc, char* argv []) {
    if (argc != 4) {
        errx(1, "Args must be 3");
    }

    const char* f1 = argv[1];
    const char* f2 = argv[2];
    const char* patch = argv[3];

    int fd1 = open(f1, O_RDONLY);

    if (fd1 == -1) {
        err(2, "Error while opening");
    }

    int fd2 = open(f2, O_RDONLY);

    if (fd2 == -1) {
        close(fd1);
        err(2, "Error while opening");
    }

    int fd3 = open(patch, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd3 == -1) {
        close(fd1);
        close(fd2);
        err(2, "Error while opening");
    }

    struct stat st;

    if (fstat(fd1, &st) == -1) {
        err(3, "stat");
    }

    size_t f1_s = st.st_size;

    if (fstat(fd2, &st) == -1) {
        err(3, "stat");
    }

    size_t f2_s = st.st_size;

    if (f1_s != f2_s) {
        errx(4, "Not equal size");
    }

    if(f1_s > UINT16_MAX) {
        errx(5, "files too big");
    }

    for (size_t i = 0; i < f1_s; i++) {
        uint8_t original;

        if ((read(fd1, &original, sizeof(original))) == -1) {
            err(6, "Error while reading");
        }

        uint8_t new;

        if ((read(fd2, &new, sizeof(new))) == -1) {
            err(6, "Error while reading");
        }

        if (original != new) {
            struct diff d;
            d.offset = i;
            d.pos_o = original;
            d.pos_n = new;

            if ((write(fd3, &d, sizeof(d))) == -1) {
                err(7, "Error while writting");
            }
        }
    }

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}