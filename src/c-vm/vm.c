#include "vm.h"
#include "opcode.h"
#include "trap.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint16_t memory[MEMORY_MAX];
uint16_t reg[RCOUNT];

uint16_t swap16(uint16_t val) {
    return (val << 8) | (val >> 8);
}

int read_file(const char* file){
    FILE* f = fopen(file, "rb");
    if (!f)
        return 0;
    uint16_t org;
    fread(&org, sizeof(org), 1, f);
    org = swap16(org);
    uint16_t max = MEMORY_MAX - org;
    uint16_t* text = memory + org;
    size_t r = fread(text, sizeof(uint16_t), max, f);

    /* LC-3 program are big endian but as most of modern computer are
     * little endian, we need to swap to litlle endian for
     * the computer to understand what is going on in the vm
     * */
    while(r-- > 0){
        *text = swap16(*text);
        text++;
    }
    fclose(f);
    return 1;
}

void mem_write(uint16_t addr, uint16_t val) {
    memory[addr] = val;
}

uint16_t mem_read(uint16_t addr) {
    if (addr == KBSR) {
        if (check_key()){
            memory[KBSR] = (1 << 15);
            memory[KBDR] = getchar();
        }
        else {
            memory[KBSR] = 0;
        }
    }
    return memory[addr];
}

/* We need to disable input buffering during the execution of the program
 * and restore it after
 * */
struct termios term;

void disable_input_buffer() {
    tcgetattr(STDIN_FILENO, &term);
    struct termios new_term = term;
    new_term.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void restore_input_buffer() {
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

uint16_t check_key() {
    fd_set read_fd;
    FD_ZERO(&read_fd);
    FD_SET(STDIN_FILENO, &read_fd);
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 0;
    return select(1, &read_fd, NULL, NULL, &time) != 0;
}

void handler(int signal){
    restore_input_buffer();
    printf("\n");
    exit(-2);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("LC-3 file missing\n");
        exit(2);
    }
    signal(SIGINT, handler);
    disable_input_buffer();
    for (int i = 1; i < argc; ++i)
    {
        if (!read_file(argv[i])) {
            printf("failed to load image: %s\n", argv[i]);
            exit(1);
        }
    }
    /* Set up the VM */
    /* We set one condition flag to have one at each time */
    reg[RCOND] = ZRO;

    /* Set the PC to the default starting position 0x3000 */
    const int pc_start = 0x3000;
    reg[RPC] = pc_start;

    int runnning = 1; /* The program begin */
    while (runnning)
    {
        /* Fetch instruction from program counter and read memory */
        uint16_t instruction = mem_read(reg[RPC]++);
        uint16_t opcode = instruction << 12;/* opcode stored in the left 4 bits*/
    switch (opcode) /* To decide what to execute */
    {
    case ADD:
        add(instruction);
        break;
    case AND:
        break;
    case NOT:
        break;
    case BR:
        break;
    case JMP:
        break;
    case JSR:
        break;
    case LD:
        break;
    case LDI:
        ldi(instruction);
        break;
    case LDR:
        break;
    case LEA:
        break;
    case ST:
        break;
    case STI:
        break;
    case STR:
        break;
    case TRAP:
        break;
    case RES:
    case RTI:
    default:
        // bad opcode
        abort();
        break;
    }
    restore_input_buffer();
}
