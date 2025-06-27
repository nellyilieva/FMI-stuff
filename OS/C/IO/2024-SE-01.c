#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    uint64_t next;
    uint8_t userData[504];
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "need 1 arg");
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        err(1, "opening error");
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        err(2, "stat error");
    }

    size_t file_size = st.st_size;

    if (file_size % sizeof(struct Node) != 0) {
        errx(2, "wrong size");
    }

    int count = file_size / sizeof(struct Node);

    // Поддържаме таблица кои индекси са посетени
    // Понеже не можем да ползваме динамична памет, ще използваме временен файл
    // с bitmap: по 1 байт на запис, 0 или 1 (ако е достъпен)
    // nqkvo bfs pravim brat

    char tmp_name[] = "tmp_bitmap_XXXXXX";
    int tmp_fd = mkstemp(tmp_name);
    if (tmp_fd == -1) {
        err(3, "Error creating temp");
    }

    for (uint64_t i = 0; i < count; i++) {
        char zero = 0;
        if (write(tmp_fd, &zero, 1) != 1) {    //If write() fails or writes fewer than 1 byte
            errx(6, "Invalid next index");
        }
    }

    uint64_t curr = 0;

    while(true) {
        if (curr >= count) {
            errx(4, "incorrect next node index");
        }

        if (lseek(fd, curr * sizeof(struct Node), SEEK_SET) == -1) {
            err(4, "error lseek");
        }

        struct Node node;
        if (read(fd, &node, sizeof(node)) != sizeof(node)) {
            close(fd);
            close(tmp_fd);
            err(8, "Failed to read record");
        }

        // Маркиране в bitmap
        if (lseek(tmp_fd, curr, SEEK_SET) == -1 || write(tmp_fd, "\x01", 1) != 1) {
            close(fd);
            close(tmp_fd);
            err(9, "Failed to mark bitmap");
        }

        if (node.next == 0) break;

        curr = node.next;
    }

    struct Node zero_node;
    zero_node.next = 0;
    for (int i = 0; i < 504; i++) { 
        zero_node.userData[i] = 0;
    }

    for (uint64_t i = 0; i < count; i++) {
        if (lseek(tmp_fd, i, SEEK_SET) == -1) {
            close(fd);
            close(tmp_fd);
            err(10, "lseek bitmap");
        }

        char flag;
        if (read(tmp_fd, &flag, 1) != 1) {
            close(fd);
            close(tmp_fd);
            err(11, "read bitmap");
        }

        if (flag == 0) {
            if (lseek(fd, i * sizeof(struct Node), SEEK_SET) == -1 || write(fd, &zero_node, sizeof(zero_node)) != sizeof(zero_node)) {
                close(fd);
                close(tmp_fd);
                err(12, "Failed to zero unused record");
            }
        }
    }

    close(fd);
    close(tmp_fd);
    unlink(tmp_name);

    return 0;
}