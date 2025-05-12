#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv []) {
    if (argc != 3) {
        errx(1, "Args must be 2");
    }

    // we first find the mode
    int mode = 0; // 0 = replace, 1 = delete, 2 = squeeze
    const char* f1;
    const char* f2 = NULL;

    if (strcmp(argv[1], "-d") == 0) {
        mode = 1;
        f1 = argv[2];
    }
    else if (strcmp(argv[1], "-s") == 0) {
        mode = 2;
        f1 = argv[2];
    }
    else {
        f1 = argv[1];
        f2 = argv[2];

        if (strlen(f1) != strlen(f2)) {
            errx(2, "not same size");
        }
    }

    // now we read from stdin

    char buff;
    ssize_t bytes_read = 0;

    
    if (mode == 1) {
        char contain[256] = {0};
        for (int i = 0; i < strlen(f1); i++) {
            contain[(unsigned char)f1[i]] = 1;
        }

        while ((bytes_read = read(0, &buff, sizeof(buff))) > 0) {
            if (!contain[(unsigned char)buff]) {
                if (write(1, &buff, sizeof(buff)) == -1) {
                    err(4, "Error while wrtting");
                }
            }
        }
        if (bytes_read == -1) {
            err(3, "Error while reading");
        }
    }
    else if (mode == 2) {
        char prev = '\0';
        bool is_first = true;

        while ((bytes_read = read(0, &buff, sizeof(buff))) > 0) {
            bool in_set = false;
            for (int i = 0; i < strlen(f1); i++) {
                if (buff == f1[i]) {
                    in_set = true;
                    break;
                }
            }
            if (!in_set || buff != prev || is_first) {
                if (write(1, &buff, sizeof(buff)) == -1) {
                    err(4, "Error while wrtting");
                }
                is_first = false;
            }
            prev = buff;
        }
        if (bytes_read == -1) {
            err(3, "Error while reading");
        }
    }
    else if (mode == 0) {
        while ((bytes_read = read(0, &buff, sizeof(buff))) > 0) {
            bool replaced = false;
            for (int i = 0; i < strlen(f1); i++) {
                if (buff == f1[i]) {
                    buff = f2[i];
                    replaced = true;
                    break;
                }
            }

            if (write(1, &buff, sizeof(buff)) == -1) {
                err(4, "Error while wrtting");
            }
        }
        if (bytes_read == -1) {
            err(3, "Error while reading");
        }
    }

    return 0;
}