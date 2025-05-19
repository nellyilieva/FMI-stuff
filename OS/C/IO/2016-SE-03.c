#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

int compareUint32_t(const void* a, const void* b) {
    uint32_t x = *(const uint32_t*)a;
    uint32_t y = *(const uint32_t*)b;
    return (x > y) - (x < y);
}

void writeSafe(int fd, uint32_t value, const char* fname) {
    if (write(fd, &value, sizeof(value)) != sizeof(value)) {
        err(99, "write error to file %s", fname);
    }
}

void merge(const char* temp1, const char* temp2, size_t n1, size_t n2, const char* out_file) {
    int fd1 = open(temp1, O_RDONLY);
    if (fd1 == -1) err(11, "Error opening %s", temp1);

    int fd2 = open(temp2, O_RDONLY);
    if (fd2 == -1) err(11, "Error opening %s", temp2);

    int fd_out = open(out_file, O_WRONLY | O_TRUNC);
    if (fd_out == -1) err(11, "Error opening %s", out_file);

    uint32_t a, b;
    ssize_t ra = read(fd1, &a, sizeof(a));
    ssize_t rb = read(fd2, &b, sizeof(b));

    while (ra == sizeof(a) && rb == sizeof(b)) {
        if (a <= b) {
            writeSafe(fd_out, a, out_file);
            ra = read(fd1, &a, sizeof(a));
        } else {
            writeSafe(fd_out, b, out_file);
            rb = read(fd2, &b, sizeof(b));
        }
    }

    while (ra == sizeof(a)) {
        writeSafe(fd_out, a, out_file);
        ra = read(fd1, &a, sizeof(a));
    }

    while (rb == sizeof(b)) {
        writeSafe(fd_out, b, out_file);
        rb = read(fd2, &b, sizeof(b));
    }

    close(fd1);
    close(fd2);
    close(fd_out);
}

void split(size_t count, int fd, const char* temp_file, const char* src) {
    uint32_t num;
    uint32_t* half = malloc(count * sizeof(uint32_t));
    if (!half) errx(7, "Memory alloc error");

    ssize_t bytes_read;
    size_t i = 0;
    while (i < count && (bytes_read = read(fd, &num, sizeof(num))) == sizeof(num)) {
        half[i++] = num;
    }

    if (bytes_read == -1) err(8, "Read error from %s", src);

    qsort(half, count, sizeof(uint32_t), compareUint32_t);

    int fd1 = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) err(9, "Error opening %s", temp_file);

    for (size_t j = 0; j < count; j++) {
        writeSafe(fd1, half[j], temp_file);
    }

    close(fd1);
    free(half);
}

int main(int argc, char* argv []) {
    if (argc != 2) {
        errx(1, "Usage: %s <binary_file>", argv[0]);
    }

    const char* file_name = argv[1];

    int fd = open(file_name, O_RDWR);
    if (fd == -1) {
        err(2, "Couldn't open %s", file_name);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        close(fd);
        err(3, "stat error");
    }

    if (st.st_size == 0) {
        close(fd);
        errx(4, "Empty file");
    }

    if (st.st_size % sizeof(uint32_t) != 0) {
        close(fd);
        errx(5, "File does not contain only uint32_t values");
    }

    size_t total_numbers = st.st_size / sizeof(uint32_t);
    if (total_numbers > 100000000) {
        close(fd);
        errx(6, "Too many numbers");
    }

    char temp1[] = "temp1XXXXXX";
    char temp2[] = "temp2XXXXXX";
    int tmp_fd1 = mkstemp(temp1);
    int tmp_fd2 = mkstemp(temp2);

    if (tmp_fd1 == -1 || tmp_fd2 == -1) {
        close(fd);
        err(7, "mkstemp failed");
    }

    close(tmp_fd1);
    close(tmp_fd2);

    size_t half = total_numbers / 2;
    size_t rest = total_numbers - half;

    split(half, fd, temp1, file_name);
    split(rest, fd, temp2, file_name);

    close(fd);

    merge(temp1, temp2, half, rest, file_name);

    if (unlink(temp1) == -1 || unlink(temp2) == -1) {
        err(10, "Couldn't unlink");
    }

    return 0;
}   