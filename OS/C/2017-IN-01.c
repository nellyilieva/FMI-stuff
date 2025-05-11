#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>
#include <stdint.h>
#include <unistd.h>

struct pos {
    uint16_t offset;
    uint8_t length;
    uint8_t saved;
};

int main(int argc, char* argv []) {
    if (argc != 5) {
        errx(1, "Args must be 4");
    }

    const char* first_dat = argv[1];
    const char* first_idx = argv[2];
    const char* second_dat = argv[3];
    const char* second_idx = argv[4];

    int fd_1d = open(first_dat, O_RDONLY);

    if (fd_1d == -1) {
        err(2, "Error while opening");
    }

    int fd_1i = open(first_idx, O_RDONLY);

    if (fd_1i == -1) {
        close(fd_1d);
        err(2, "Error while opening");
    }

    struct stat st;

    if (fstat(fd_1d, &st) == -1) {
        err(3, "stat error");
    }

    size_t s_fd = st.st_size;

    if (s_fd == 0) {
        errx(4, "Empty file");
    }

    if (s_fd % sizeof(uint8_t) != 0) {
        close(fd);
        errx(5, "File does not contain only uint8_t values");
    }

    if (fstat(fd_1i, &st) == -1) {
        err(3, "stat error");
    }

    size_t s_fi = st.st_size;

    if (s_fi == 0) {
        errx(4, "Empty file");
    }

    if (s_fi % sizeof(struct pos) != 0) {
        errx(5, "Not alingning with struct error");
    }

    int fd_2d = open(second_dat, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (fd_2d == -1) {
        close(fd_1d);
        close(fd_1i);
        err(2, "Error while opening");
    }

    int fd_2i = open(second_idx, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (fd_1i == -1) {
        close(fd_1d);
        close(fd_1i);
        close(fd_2d);
        err(2, "Error while opening");
    }

    struct pos p;
    ssize_t bytes_read = 0;
    ssize_t bytes_write = 0;
    uint16_t offs = 0;

    while ((bytes_read = read(fd_1i, &p, sizeof(struct pos))) > 0) {
        if (p.offset + p.length > s_fd) {
            err(6, "Inconsistent");
        }

        if (lseek(fd_1d, p.offset, SEEK_SET) == -1) {
            err(7, "lseek failed");
        }

        // if (bytes_read == -1) {
        //     err(8, "Error while reading");
        // }

        uint8_t buff[255];

        if (read(fd_1d, &buff, p.length) == -1) {
            err(8, "Error while reading");
        }

        if (buff[0] < 0x41 || buff[0] > 0x5A) {
            continue;
        }

        if (write(fd_2d, &buff, p.length) == -1) {
            err(9, "Error while writting");
        }

        struct pos out;
        out.offset = offs;
        out.length = pos.length;    
        out.saved = 0;

        if (write(fd_2i, &out, sizeof(out)) == -1) {
            err(9, "Error while wrtting");
        }

        offs += pos.length;

    }

    if (bytes_read == -1) {
            err(8, "Error while reading");
    }

    close(fd_1d);
    close(fd_1i);
    close(fd_2d);
    close(fd_2i);
    return 0;
}