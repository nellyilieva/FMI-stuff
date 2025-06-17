#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

const int MAX_COUNT = 524288;

void print(int fd, const char* message) {
    int written = write(fd, message, strlen(message));
    if(written < 0) {
        err(1, "Couldn't write");
    }
    if(written != (int)strlen(message)) {
        errx(1, "Couldn't write whole message");
    }
}

void printUint32(int fd, uint32_t num) {
    char buf[12];  // достатъчно за uint32_t
    snprintf(buf, sizeof(buf), "%u", num); // конвертира числото в string (десетично представяне)
    print(fd, buf);
}

void printUint16(int fd, uint16_t num) {
    char buf[8];   // достатъчно за uint16_t
    snprintf(buf, sizeof(buf), "%u", num);
    print(fd, buf);
}

void printData(int fd_from, int fd_to, size_t count) {
    uint16_t cur;
    for(size_t i = 0; i < count; i++) {
        int bytes = read(fd_from, &cur, sizeof(cur));
        if(bytes != sizeof(cur)) {
            if(bytes < 0) {
                err(1, "Couldn't read");
            } else {
                errx(1, "Couldn't read all data");
            }
        }
        
        printUint16(fd_to, cur);
        
        if(i < count - 1) {
            print(fd_to, ", ");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        errx(1, "Needs 3 args");
    }

    const char* input = argv[1];
    const char* output = argv[2];

    int fd_in = open(input, O_RDONLY);

    if (fd_in == -1) {
        err(2, "Error while opening");
    }

    struct stat st;
    if (fstat(fd_in, &st) == -1) {
        err(3, "stat error");
    }

    size_t in_size = st.st_size;

    if (in_size == 0) {
        errx(4, "Size error");
    }

    if (in_size % sizeof(uint16_t) != 0) {
        errx(4, "Size error");
    }

    size_t count = in_size / sizeof(uint16_t);

    if (count > MAX_COUNT) {
        errx(4, "Size error");
    }

    int fd_out = open(output, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (fd_out == -1) {
        close(fd_in);
        err(2, "Error while opening");
    }

    const char header[] = "#include <stdint.h>\n\n";
    const char arr_start[] = "const uint16_t arr[] = { ";
    const char arr_end[] = " };\n";
    const char arrN_start[] = "const uint32_t arrN = ";
    const char arrN_end[] = ";\n";

    print(fd_out, header);
    
    print(fd_out, arr_start);
    printData(fd_in, fd_out, count);
    print(fd_out, arr_end);
    
    print(fd_out, arrN_start);
    printUint32(fd_out, (uint32_t)count);
    print(fd_out, arrN_end);

    close(fd_in);
    close(fd_out);

    return 0;

}