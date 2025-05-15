#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const int MAX_SIZE = 16384;
const int MAX_USER = 2048;

struct info {
    uint32_t uid;
    uint16_t s1;
    uint16_t s2;
    uint32_t start;
    uint32_t end;
};

struct userInfo {
    uint32_t uid;
    uint32_t maxDuration;
};

double calc_dispersion(struct info* sessions, size_t count) {
    if (count == 0) {
        return 0;
    }

    double sum = 0;
    double mean = 0; //avg
    double disperssion = 0;

    for (int i = 0; i < count; i++) {
        uint32_t duration = sessions[i].end - sessions[i].start;
        sum += duration;
    }

    mean = sum / count;

    for (size_t i = 0; i < count; i++) {
        uint32_t duration = sessions[i].end - sessions[i].start;
        double diff = (double)duration - mean;
        disperssion += diff * diff;
    }

    return disperssion / count;
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        errx(1, "Arg must be 1");
    }

    const char* file = argv[1];
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        err(2, "Error while opening");
    }

    struct stat st;

    if (fstat(fd, &st) == -1) {
        err(3, "stat error");
    }

    size_t fd_size = st.st_size;

    if (fd_size == 0) {
        errx(4, "Size error");
    }

    if (fd_size % sizeof(struct info) != 0) {
        errx(4, "Size error");
    }

    struct info sessions[MAX_SIZE];

    size_t count = fd_size / sizeof(struct info);

    if (count > MAX_SIZE) {
        close(fd);
        errx(5, "Too many sessions");
    }

    ssize_t read_bytes = read(fd, &sessions, fd_size);

    if (read_bytes == -1) {
        close(fd);
        err(6, "Error while reading");
    }

    double dispersion = calc_dispersion(sessions, count);


    struct userInfo users[MAX_USER];
    int userCount = 0;

    for (int i = 0; i < count; i++) {
        uint32_t uid = sessions[i].uid;
        uint32_t duration = sessions[i].end - sessions[i].start;

        int user_idx = -1;
        for(int j = 0; j < userCount; j++) {
            if (users[j].uid == uid) {
                user_idx = j;
                break;
            }
        }

        if (user_idx == -1) {
            if (userCount >= MAX_USER) {
                close(fd);
                errx(8, "Too many users");
            }
            users[userCount].uid = uid;
            users[userCount].maxDuration = duration;
            userCount++;
        }
        else if (duration > users[user_idx].maxDuration) {
            users[user_idx].maxDuration = duration;
        }
    }

    for (int i = 0; i < userCount; i++) {
        uint64_t durationSq = (uint64_t)users[i].maxDuration * users[i].maxDuration;
        if (durationSq > dispersion) {
            printf("%u %u\n", users[i].uid, users[i].maxDuration);
        }
    }

    close(fd);
    return 0;
}