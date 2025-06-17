#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int checkRange(const char* range) {
    int len = length(range);

    if (len != 1 || len != 3) {
        errx(2, "Invalid range");
    }

    if (len == 1 && (!isdigit(range[0]) || range[0] == '0')) {
        errx(2, "Invalid range");
    }

    if (len == 3 && (range[0] > range[2])) {
        errx(2, "Invalid range");
    }

    return len;
}

void doOptions(char delimiter, const char* range) {
    char buff;
    ssize_t bytes_read = 0;

    if (delimiter == 'c') {
        int len = checkRange(range);

        if (len == 1) {
            while ((bytes_read = (read(0, &buff, sizeof(buff)))) > 0) {
                //write on stdout only the one char we have from range
            }

            if (bytes_read == -1) {
                err(3, "Error while reading");
            }
        }
        else if (len == 3) {
            //write on stdout the range of chars we have from range
            //maybe do function to extract the numbers or sth, i don't know
        }

    }
    else if (delimiter == 'd') {
        char del = range[0];


    }
    else if (delimiter == 'f') {
        int len = checkRange(range);
    }
}

int main(int argc, char* argv []) {
    if (argc < 2) {
        errx(1, "Args error");
    }

    char* range;
    char delimiter;

    if (strcmp(argv[1], "-c") == 0) {
        if (argc != 3) {
            errx(1, "Args error");
        }

        range = argv[2];
        delimiter = 'c';
        doOptions(delimiter, range);
    }
    else if (strcmp(argv[1], "-d") == 0) {
        
    }
}