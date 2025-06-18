// #include <fcntl.h>
// #include <unistd.h>
// #include <err.h>
// #include <stdint.h>
// #include <sys/stat.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <sys/stat.h>
// #include <stdio.h>

// struct entry {
//     char filename[8];
//     uint32_t offset;
//     uint32_t length;
// };

// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         errx(1, "Needs 1 arg");
//     }

//     int fd = open(argv[1], O_RDONLY);
//     if (fd == -1) {
//         err(1, "error opening");
//     }

//     struct stat st;
//     if (fstat(fd, &st) == -1) {
//         err(2, "stat error");
//     }

//     size_t file_size = st.st_size;
//     if (file_size % sizeof(struct entry) != 0) {
//         errx(2, "wrong size");
//     }

//     int count = file_size / sizeof(struct entry);

//     struct entry entries[8];
//     if (read(fd, entries, count * sizeof(struct entry)) == -1) {
//         err(4, "error reading entries");
//     }
//     close(fd);

//     uint16_t res = 0;
//     pid_t pids[8];

//     for (int i = 0; i < count; i++) {
//         pid_t pid = fork();

//         if (pid == -1) {
//             err(3, "fork error");
//         }
//         else if (pid == 0) {
//             struct entry e = entries[i];

//             int file_fd = open(e.filename, O_RDONLY);
//             if (file_fd == -1) {
//                 err(5, "error opening file");
//             }

//             if (lseek(file_fd, e.offset * sizeof(uint16_t), SEEK_SET) == -1) {
//                 err(6, "error lseek");
//             }

//             uint16_t child_result = 0;
//             for (uint32_t j = 0; j < e.length; j++) {
//                 uint16_t value;
//                 if (read(file_fd, &value, sizeof(uint16_t)) != sizeof(uint16_t)) {
//                     err(7, "error reading value");
//                 }
//                 child_result ^= value;
//             }
            
//             close(file_fd);
//             exit(child_result & 0xFF);
//         }
//         else {
//             pids[i] = pid;
//         }
//     }

//     for (int i = 0; i < count; i++) {
//         int status;
//         if (waitpid(pids[i], &status, 0) == -1) {
//             err(8, "wait error");
//         }
//         if (WIFEXITED(status)) {
//             res ^= WEXITSTATUS(status);
//         }
//     }
    
//     printf("result: %04X\n", res);
//     return 0;

// }

#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>

typedef struct IndexEntry {
	char filename[8];
	uint32_t offset;
	uint32_t length;
} IndexEntry;

void xorFile(IndexEntry* entry, int result_fd);

void xorFile(IndexEntry* entry, int result_fd) {
	int file = open(entry->filename, O_RDONLY);
	if(file == -1) { err(2, "open %s", entry->filename); }

	struct stat st;
	if(fstat(file, &st) == -1) { err(2, "stat %s", entry->filename); }

	// XXX: Sample data doesn't actually follow this rule.
	// if(st.st_size % sizeof(uint16_t) != 0) {
	// 	errx(2, "%s: bad file size", entry->filename);
	// }

	if((uint32_t)st.st_size < sizeof(uint16_t) * (entry->offset + entry->length)) {
		errx(2, "%s: offset would go past EOF", entry->filename);
	}

	if(lseek(file, sizeof(uint16_t) * entry->offset, SEEK_SET) == -1) {
		err(2, "lseek");
	}

	uint16_t result = 0;
	ssize_t read_size = 0;
	uint16_t element;

	size_t num_elements = 0;

	while((num_elements < entry->length) && (read_size = read(file, &element, sizeof(element))) > 0) {
		result ^= element;
		num_elements++;
	}

	if(read_size < 0) {
		err(2, "read");
	}

	close(file);

	if(write(result_fd, &result, sizeof(result)) == -1) {
		err(2, "write");
	}
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		errx(1, "not enough args");
	}

	int index = open(argv[1], O_RDONLY);
	if(index == -1) { err(1, "%s", argv[1]); }

	struct stat st;
	if(fstat(index, &st) == -1) { err(1, "%s: stat", argv[1]); }

	if(st.st_size % sizeof(IndexEntry) != 0 || (uint8_t)st.st_size > 8 * sizeof(IndexEntry)) {
        errx(1, "wrong index format");
    }

	int pipe_fd[2];
	if(pipe(pipe_fd) == -1) { err(1, "pipe"); }

	IndexEntry entry;
	ssize_t read_size;

	int child_count = 0;

	while((read_size = read(index, &entry, sizeof(entry))) > 0) {
		child_count++;

		pid_t pid = fork();
		if(pid == -1) { err(1, "fork"); }

		if(pid == 0) {
			// worker process
			close(index);
			close(pipe_fd[0]);

			xorFile(&entry, pipe_fd[1]);

#ifdef DEBUG
			dprintf(2, "child %d handling %s done\n", getpid(), entry.filename);
#endif

			close(pipe_fd[1]);
			exit(0);
		}

#ifdef DEBUG
		dprintf(2, "file name: %s, handled by pid: %d\n", entry.filename, pid);
#endif
	}

	if(read_size < 0) {
		err(1, "read from index");
	}

	// (!): Will deadlock without this. The read() below expects all
	//      write ends of the pipe to be closed.
	close(pipe_fd[1]);

	uint16_t result = 0;
	uint16_t element;

	while((read_size = read(pipe_fd[0], &element, sizeof(element))) > 0) {
		result ^= element;
	}

	if(read_size < 0) {
		err(1, "read from pipes");
	}

	close(pipe_fd[0]);

	int status;

	for(int i = 0; i < child_count; i++) {
		pid_t pid;
		if((pid = wait(&status)) == -1) { err(1, "wait"); }

		if (WIFEXITED(status)) {
#ifdef DEBUG
			dprintf(2, "child %d has exited\n", pid);
#endif

			if(WEXITSTATUS(status) != 0) {
				warnx("child %d exited with code %d", pid, WEXITSTATUS(status));
			}
		} else {
			warnx("child %d was killed", pid);
		}
	}

	dprintf(1, "result: %.4X\n", result);

	close(index);
	return 0;
}