#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        errx(1, "Needs 3 args");
    }

    const char* word = argv[1];
    const char* file = argv[2];
    const char* idx = argv[3];

    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        err(2, "Error opening");
    }

    int fdi = open(idx, O_RDONLY);
    if (fdi == -1) {
        err(2, "Error opening");
    }

    struct stat st;

    if (fstat(fdi, &st) == -1){
        err(3, "stat error");
    }

    size_t i_size = st.st_size;

    if (i_size == 0) {
        errx(4, "empty file");
    }

    if (i_size % sizeof(uint32_t) != 0) {
        errx(5, "wrong size");
    }

    int count = i_size / sizeof(uint32_t);

    int s = 0;
    int e = count - 1;

    bool found = false;

    while (s < e) {
        int mid = s + (e - s) / 2;

        if(lseek(fdi, mid * sizeof(uint32_t), SEEK_SET) == -1) {
			err(6, "can't lseek idx");
		}

        uint32_t index = 0;
        if (read(fdi, &index, sizeof(index)) == -1) {
            err(7, "Error reading");
        }

        if(lseek(fd, index + 1, SEEK_SET) == -1) {  // + 1 for the zero bytes
		    err(3, "can't lseek");
		}

        char w[64];
        ssize_t read_bytes = 0;

        for (int i = 0; i < 64; i++) {
            if ((read_bytes = read(fd, &w[i], sizeof(char))) == -1) {
                err(7, "Error reading");
            }

            if(read_bytes == 0) {
				errx(4, "malformed dic - reached unexpected EOF");
			}

            if(w[i] == '\n') {
				w[i] = '\0';
				break;
			}
        }

        int diff = strcmp(word, w);

        if (diff < 0) {
            e = mid - 1;
        }
        else if (diff > 0) {
            s = mid + 1;
        }
        else {
            // everything until the next \0 is the description

            char c;

            while (read_bytes = (read(fd, &c, sizeof(c))) > 0) {
                if (c == '\0') {
                    break;
                }

                if (write(1, &c, sizeof(c)) == -1) {
                    err(8, "error writting");
                }
            }

            if (read_bytes == -1) {
                err(7, "Error reading");
            }

            c = '\n';

            if (write(1, &c, sizeof(c)) == -1) {
				err(8, "error writting");
			}

			found = true;
			break;
        }
    }
    if(!found) {
		errx(1, "%s not found", argv[1]);
	}

	close(fd);
	close(fdi);

	return 0;
}