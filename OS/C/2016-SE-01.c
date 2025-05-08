// Напишете програма на C, която приема параметър - име на (двоичен) файл с байтове.
// Програмата трябва да сортира файла.


#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <sys/stat.h>

int main(int argc, char* argv []) {
    if (argc != 2) {
        errx(1, "There must be only 1 arg");
    }

    const char* file = argv[1];

    struct stat st;

    if (stat(file, &st) == -1) {
        err(2, "Error while stat file %s", file);
    }

    if (st.st_size == 0) {
        errx(3, "File %s is empty", file);
    }

    if ((st.st_size % sizeof(uint16_t)) != 0) {
        errx(4, "File %s does not contain only uint16_t numbers", file);
    }

    int fd = open(file, O_RDWR);

    if (fd == -1) {
        err(5, "Couldn't open the file");
    }

    // we have raw binary data, so we read uint16_t values (like the check)
    // we use counting sort

    uint32_t count[65536] = {0};

    uint8_t buff = 0;
    int bytes_read = 0;
    int bytes_written = 0;

    while ((bytes_read = read(fd, &buff, sizeof(buff))) > 0) {
        if (bytes_read != sizeof(buff)) {
            close(fd);
            err(6, "Unexpected byte count read from file");
    }
        count[buff]++;
    }

    if (bytes_read == -1) {
        close(fd);
        err(7, "Error while reading");
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
        err(8, "Error while setting the offset");
    }

    for (int i = 0; i < 65536; i++) {
        uint16_t ch = i;

        for (int j = 0; j < count[i]; j++) {
            bytes_written = write(fd, &ch, sizeof(ch));

            if (bytes_written == -1) {
                close(fd);
                err(9, "Error while writting");
            }
        }
    }
    
    close(fd);
    return 0;
}