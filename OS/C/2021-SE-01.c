#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <err.h>

static uint16_t encode(uint8_t byte) {
	uint8_t MASK = 128;
	uint16_t result = 0;

	while(MASK != 0) {
		if(MASK & byte) {
			result = (result << 2) | 2;
		}
		else{
			result = (result << 2) | 1;
		}

		MASK = MASK >> 1;
	}

	return result;
}

int main(int argc, char* argv []) {
    if (argc != 3) {
        errx(1, "Args count must be 2");
    }

    const char* input = argv[1];
    const char* output = argv[2];

    int fd_i = open(input, O_RDONLY);
    if (fd_i == -1) {
        err(2, "Error opening");
    }

    int fd_o = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_o == -1) {
        err(2, "Error opening");
    }

    ssize_t read_bytes = 0;
    uint8_t byte;
    size_t total_written = 0;

    while (read_bytes = (read(fd_i, &byte, sizeof(byte))) > 0) {
        uint16_t encoded = encode(byte);

        if (write(fd_o, &encoded, sizeof(encoded)) == -1) {
            close(fd_i);
            close(fd_o);
            err(4, "Error while writing");
        }

        total_written += sizeof(encoded);
    }

    if (read_bytes == -1) {
        err(3, "Error while reading");
    }

    if (total_written % 2 != 0) {
        errx(5,"File length isnt correct!");
    }

    close(fd_i);
    close(fd_o);
    return 0;
}