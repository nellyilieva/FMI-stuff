#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>

struct Header {
    uint32_t magic;
    uint8_t headerVersion;
    uint8_t dataVersion;
    uint16_t count;
    uint32_t res1;
    uint32_t res2;
};

struct Data1 {
    uint16_t offset;
    uint8_t original;
    uint8_t new;
};

struct Data2 {
    uint32_t offset;
    uint16_t original;
    uint16_t new;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Args must be 3");
    }

    const char* patch = argv[1];
    const char* f1 = argv[2];
    const char* f2 = argv[3];

    int fd_p = open(patch, O_RDONLY);
    if (fd_p == -1) {
        err(2, "Error while opening");
    }

    int fd1 = open(f1, O_RDONLY);
    if (fd1 == -1) {
        close(fd_p);
        err(2, "Error while opening");
    }

    int fd2 = open(f2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if (fd2 == -1) {
        close(fd_p);
        close(fd1);
        err(2, "Error while opening");
    }

    struct stat st;

    if (fstat(fd_p, &st) == -1) {
        err(3, "stat error");
    }

    // we can validate the total size of the patch file after we read the headere to get data version

    struct Header h;

    ssize_t read_bytes = 0;
    if ((read_bytes = read(fd_p, &h, sizeof(struct Header))) == -1) {
        close(fd_p);
        close(fd1);
        close(fd2);
        err(4, "Error while reading");
    }

    if (h.magic != 0xEFBEADDE) {
        errx(5, "invalid magic");
    }

    if (h.headerVersion != 0x01) {
        errx(6, "wrong version");
    }

    if (h.dataVersion != 0x00 && h.dataVersion != 0x01) {
        errx(7, "wrong data version");
    }

    uint64_t expected_size = sizeof(struct Header);

    if (h.dataVersion == 0x00) {
        expected_size += h.count * sizeof(struct Data1);
    }
    else if (h.dataVersion == 0x01) {
       expected_size += h.count * sizeof(struct Data2);
    }
    else {
        errx(7, "wrong data version");
    }

    if (st.st_size != expected_size) {
        errx(8, "Patch file size does not match expected size");
    }

    ssize_t bytes_read = 0;

    if (h.dataVersion == 0x00) {
        Data1 d;
        uint8_t byte;

        while ((bytes_read = read(fd1, &byte, sizeof(byte))) > 0) {
            if (write(fd2, &byte, sizeof(byte)) == -1) {
                //close files
                err(10, "Error while writting");
            }
        }
        if (bytes_read == -1) {
            //close files
            err(9, "Error while reading");
        }

        while ((bytes_read = read(fd_p, &d, sizeof(struct Data1))) > 0) {
            if (lseek(fd2, d.offset, SEEK_SET) == -1) {
                err(11, "lseek errror");
            }
            if (read(fd2, &byte, sizeof(byte)) == -1) {
                err(9, "Error while rading");
            }

            if (byte != d.original) {
                err(11, "Invalid content");
            }

            if (lseek(fd2, d.offset, SEEK_SET) == -1) {
                err(11, "lseek error");
            }

            if (write(fd2, &d.new, sizeof(d.new)) == -1) {
                err(10, "Error while writting");
            }

        }

        if (bytes_read == -1) {
            err(9, "Error while reading");
        }

    }
    else if (h.dataVersion == 0x01) {
        //kinda the same thing
    }

}