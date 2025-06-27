#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>

#define MAX_REGISTERS 32
#define MAX_RAM 512
#define MAX_INSTRUCTIONS 1024
#define ENTRY_SIZE 12

typedef struct {
    uint8_t opcode;
    uint8_t op1;
    uint8_t op2;
    uint8_t op3;
} Instruction;

void execute_instruction(uint8_t* reg, uint8_t* ram, Instruction* inst, int* pc, int reg_count, int ram_size) {
    switch (inst->opcode) {
        case 0: // AND
            reg[inst->op1] = reg[inst->op2] & reg[inst->op3];
            break;
        case 1: // OR
            reg[inst->op1] = reg[inst->op2] | reg[inst->op3];
            break;
        case 2: // ADD
            reg[inst->op1] = reg[inst->op2] + reg[inst->op3];
            break;
        case 3: // MULTIPLY
            reg[inst->op1] = reg[inst->op2] * reg[inst->op3];
            break;
        case 4: // XOR
            reg[inst->op1] = reg[inst->op2] ^ reg[inst->op3];
            break;
        case 5: // PRINT
            printf("%d\n", reg[inst->op1]);
            break;
        case 6: // SLEEP
            sleep(reg[inst->op1]);
            break;
        case 7: // LOAD
            if (reg[inst->op2] < ram_size)
                reg[inst->op1] = ram[reg[inst->op2]];
            break;
        case 8: // STORE
            if (reg[inst->op1] < ram_size)
                ram[reg[inst->op1]] = reg[inst->op2];
            break;
        case 9: // JNE
            if (reg[inst->op1] != reg[inst->op2])
                *pc += inst->op3;
            break;
        case 10: // LOADI
            reg[inst->op1] = inst->op2;
            break;
        case 11: // STOREI
            if (inst->op1 < ram_size)
                ram[inst->op1] = inst->op2;
            break;
        default:
            break;
    }
}

void simulate_processor(uint16_t ram_size, uint16_t reg_count, const char* filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) err(1, "cannot open processor file");

    uint8_t registers[MAX_REGISTERS] = {0};
    uint8_t ram[MAX_RAM] = {0};
    Instruction instructions[MAX_INSTRUCTIONS];
    ssize_t total_read;

    // Read registers
    if (read(fd, registers, reg_count) != reg_count)
        err(2, "cannot read registers");

    // Read RAM
    if (read(fd, ram, ram_size) != ram_size)
        err(3, "cannot read RAM");

    // Read instructions
    int inst_count = 0;
    while ((total_read = read(fd, &instructions[inst_count], sizeof(Instruction))) == sizeof(Instruction)) {
        inst_count++;
        if (inst_count >= MAX_INSTRUCTIONS) break;
    }

    // Execute instructions
    for (int pc = 0; pc < inst_count; pc++) {
        execute_instruction(registers, ram, &instructions[pc], &pc, reg_count, ram_size);
    }

    // Rewrite file (registers + RAM only)
    lseek(fd, 0, SEEK_SET);
    if (write(fd, registers, reg_count) != reg_count)
        err(4, "cannot write registers");
    if (write(fd, ram, ram_size) != ram_size)
        err(5, "cannot write RAM");
    close(fd);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        errx(1, "Usage: %s input.bin", argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) err(2, "Cannot open %s", argv[1]);

    while (1) {
        uint16_t ram_size, reg_count;
        char filename[9] = {0};

        ssize_t r = read(fd, &ram_size, 2);
        if (r == 0) break; // EOF
        if (r != 2 || read(fd, &reg_count, 2) != 2 || read(fd, filename, 8) != 8)
            errx(3, "Corrupted input.bin");

        pid_t pid = fork();
        if (pid == -1) err(4, "fork failed");
        if (pid == 0) {
            simulate_processor(ram_size, reg_count, filename);
            exit(0);
        }
    }

    while (wait(NULL) > 0);
    close(fd);
    return 0;
}
