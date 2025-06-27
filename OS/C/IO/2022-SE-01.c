#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

uint32_t MAGIC_NUM_DATA = 0x21796F4A;
uint32_t MAGIC1_NUM_COMP = 0xAFBC7A37;
uint16_t MAGIC2_NUM_COMP = 0x1C27;

struct data_header {
    uint32_t magic;
    uint32_t count;
};

struct comp_header {
    uint32_t magic1;
    uint16_t magic2;
    uint16_t reserved;
    uint64_t count;
};

struct comp_data {
    uint16_t type;
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint32_t offset1;
    uint32_t offset2;
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "we need two args");
    }

    const char* data_file = argv[1];
    const char* comp_file = argv[2];

    int fd_d = open(data_file, O_RDWR);
    if (fd_d == -1) {
        err(1, "opening error");
    }

    struct stat st_d;
    if (fstat(fd_d, &st_d) == -1) {
        err(2, "stat error on data file");
    }

    size_t size_d = st_d.st_size;
    if (size_d < sizeof(struct data_header)) {
        close(fd_d);
        errx(2, "data file too small");
    }

    int fd_c = open(comp_file, O_RDONLY);
    if (fd_c == -1) {
        err(1, "opening error");
    }

    struct stat st_c;
    if (fstat(fd_c, &st_c) == -1) {
        close(fd_d);
        close(fd_c);
        err(2, "stat error on comparator file");
    }

    size_t size_c = st_c.st_size;
    if (size_c < sizeof(struct comp_header)) {
        close(fd_d);
        close(fd_c);
        errx(4, "comparator file too small");
    }

    struct data_header d_hdr;

    if (read(fd_d, &d_hdr, sizeof(struct data_header)) != sizeof(struct data_header)) {
        err(5, "reading error");
    }

    if (d_hdr.magic != MAGIC_NUM_DATA) {
        errx(2, "invalid magic in data file");
    }

    if (size_d != sizeof(struct data_header) + d_hdr.count * sizeof(uint64_t)) {
        close(fd_d);
        close(fd_c);
        errx(7, "unexpected size of data file");
    }

    struct comp_header c_hdr;

    if (read(fd_c, &c_hdr, sizeof(struct comp_header)) != sizeof(struct comp_header)) {
        err(5, "reading error");
    }

    if (c_hdr.magic1 != MAGIC1_NUM_COMP || c_hdr.magic2 != MAGIC2_NUM_COMP) {
        close(fd_d);
        close(fd_c);
        errx(4, "invalid magic numbers in comparator file");
    }

    if (size_c != sizeof(struct comp_header) + c_hdr.count * sizeof(struct comp_data)) {
        close(fd_d);
        close(fd_c);
        errx(10, "unexpected size of comparator file");
    }

    for (uint64_t i = 0; i < c_hdr.count; i++) {
        struct comp_data cd;
        if (read(fd_c, &cd, sizeof(cd)) != sizeof(cd)) {
            err(8, "failed to read comparator rule at index %lu", i);
        }

        if (cd.type != 0 && cd.type != 1) {
            errx(9, "invalid type in rule %lu: %u", i, cd.type);
        }

        if (cd.r1 != 0 || cd.r2 != 0 || cd.r3 != 0) {
            errx(10, "non-zero reserved field in rule %lu", i);
        }

        if (cd.offset1 >= d_hdr.count || cd.offset2 >= d_hdr.count) {
            errx(11, "offsets out of range in rule %lu: %u, %u", i, cd.offset1, cd.offset2);
        }

        long pos1 = sizeof(struct data_header) + cd.offset1 * sizeof(uint64_t);
        long pos2 = sizeof(struct data_header) + cd.offset2 * sizeof(uint64_t);

        uint64_t val1;
        uint64_t val2;

        if (lseek(fd_d, pos1, SEEK_SET) == -1 || read(fd_d, &val1, sizeof(val1)) != sizeof(val1)) {
            err(15, "failed to read val1");
        }
        if (lseek(fd_d, pos2, SEEK_SET) == -1 || read(fd_d, &val2, sizeof(val2)) != sizeof(val2)) {
            err(16, "failed to read val2");
        }

        int need_swap = false;
        if (cd.type == 0 && val1 >= val2 && val1 != val2) {
            need_swap = true;
        }
        else if (cd.type == 1 && val1 <= val2 && val1 != val2) {
            need_swap = true;
        }

        if (need_swap) {
            if (lseek(fd_d, pos1, SEEK_SET) == -1 || write(fd_d, &val2, sizeof(val2)) != sizeof(val2)) {
                err(17, "failed to write val2 to pos1");
            }
            if (lseek(fd_d, pos2, SEEK_SET) == -1 || write(fd_d, &val1, sizeof(val1)) != sizeof(val1)) {
                err(18, "failed to write val1 to pos2");
            }
        }
    }

    close(fd_d);
    close(fd_c);
    return 0;
}
