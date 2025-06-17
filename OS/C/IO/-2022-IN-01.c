// task.c

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>
#include <stdio.h>

const uint16_t MAGIC_NUM = 0x5A4D;

struct header {
    uint16_t magic;
    uint16_t file_type; // 1: list, 2: data, 3: output
    uint32_t count;
};

int read_header(int fd, struct header* h, uint16_t expected_type) {
    if (read(fd, h, sizeof(struct header)) != sizeof(struct header)) {
        return -1;
    }
    if (h->magic != MAGIC_NUM) {
        return -2;
    }
    if (h->file_type != expected_type) {
        return -3;
    }
    return 0;
}

uint32_t find_max_output_offset(int fd_l, uint32_t list_count) {
    uint32_t max_offset = 0;
    uint16_t list_element;

    for (uint32_t i = 0; i < list_count; i++) {
        if (read(fd_l, &list_element, sizeof(uint16_t)) != sizeof(uint16_t)) {
            err(1, "Error reading list element");
        }
        if (list_element > max_offset) {
            max_offset = list_element;
        }
    }

    if (lseek(fd_l, sizeof(struct header), SEEK_SET) == -1) {
        err(1, "Error seeking in list file");
    }

    return max_offset;
}

int write_header(int fd, struct header* h) {
    return write(fd, h, sizeof(struct header)) == sizeof(struct header) ? 0 : -1;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Usage: %s list.bin data.bin out.bin", argv[0]);
    }

    const char* list_file = argv[1];
    const char* data_file = argv[2];
    const char* output = argv[3];

    int fd_l = open(list_file, O_RDONLY);
    if (fd_l == -1) err(2, "Cannot open %s", list_file);

    int fd_d = open(data_file, O_RDONLY);
    if (fd_d == -1) {
        close(fd_l);
        err(2, "Cannot open %s", data_file);
    }

    struct stat list_st, data_st;
    if (fstat(fd_l, &list_st) == -1 || fstat(fd_d, &data_st) == -1) {
        close(fd_l); close(fd_d);
        err(3, "fstat error");
    }

    if (list_st.st_size < sizeof(struct header) || data_st.st_size < sizeof(struct header)) {
        close(fd_l); close(fd_d);
        errx(1, "Input file too small (no header)");
    }

    size_t list_data_size = list_st.st_size - sizeof(struct header);
    size_t data_data_size = data_st.st_size - sizeof(struct header);

    if (list_data_size % sizeof(uint16_t) != 0 || data_data_size % sizeof(uint32_t) != 0) {
        close(fd_l); close(fd_d);
        errx(1, "Invalid element size in input files");
    }

    struct header list_header, data_header;
    if (read_header(fd_l, &list_header, 1) != 0 ||
        read_header(fd_d, &data_header, 2) != 0) {
        close(fd_l); close(fd_d);
        errx(1, "Invalid header(s)");
    }

    if (list_header.count != list_data_size / sizeof(uint16_t) ||
        data_header.count != data_data_size / sizeof(uint32_t)) {
        close(fd_l); close(fd_d);
        errx(1, "Header count doesn't match file size");
    }

    uint32_t out_count = find_max_output_offset(fd_l, list_header.count) + 1;

    int out_fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd == -1) {
        close(fd_l); close(fd_d);
        err(1, "Cannot open output file %s", output);
    }

    struct header out_header = {
        .magic = MAGIC_NUM,
        .file_type = 3,
        .count = out_count
    };
    if (write_header(out_fd, &out_header) != 0) {
        close(fd_l); close(fd_d); close(out_fd);
        err(1, "Failed writing output header");
    }

    uint64_t zero = 0;
    for (uint32_t i = 0; i < out_count; i++) {
        if (write(out_fd, &zero, sizeof(uint64_t)) != sizeof(uint64_t)) {
            close(fd_l); close(fd_d); close(out_fd);
            err(1, "Error initializing output file");
        }
    }

    for (uint32_t i = 0; i < list_header.count; i++) {
        uint16_t list_element;
        if (read(fd_l, &list_element, sizeof(uint16_t)) != sizeof(uint16_t)) {
            err(1, "Error reading list element %u", i);
        }

        if (i >= data_header.count || list_element >= out_count) {
            continue;
        }

        off_t data_pos = sizeof(struct header) + i * sizeof(uint32_t);
        if (lseek(fd_d, data_pos, SEEK_SET) == -1) err(1, "Seek data");

        uint32_t data_value;
        if (read(fd_d, &data_value, sizeof(uint32_t)) != sizeof(uint32_t)) {
            err(1, "Read data");
        }

        off_t out_pos = sizeof(struct header) + list_element * sizeof(uint64_t);
        if (lseek(out_fd, out_pos, SEEK_SET) == -1) err(1, "Seek output");

        uint64_t result = (uint64_t)data_value;
        if (write(out_fd, &result, sizeof(uint64_t)) != sizeof(uint64_t)) {
            err(1, "Write output");
        }
    }

    close(fd_l);
    close(fd_d);
    close(out_fd);

    return 0;
}
