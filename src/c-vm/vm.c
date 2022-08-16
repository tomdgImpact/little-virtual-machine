#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#define MEMORY_MAX (1 << 16) // 2 power 16
uint16_t memory[MEMORY_MAX]; // init a memory range address with 65 536 locations
enum /* Registers*/
{
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    RPC, // program counter
    RCOND, // condition branching
    RCOUNT,
};

uint16_t reg[RCOUNT];

enum // Opcodes
{
    BR,
    ADD,
    LD,
    ST,
    JSR,
    AND,
    LDR,
    STR,
    RTI,
    NOT,
    LDI,
    STI,
    JMP,
    RES,
    LEA,
    TRAP // execute trap
};

/* condition flag */
enum
{
    POS = 1 << 0, // P
    ZRO = 1 << 1, // Z
    NEG = 1 << 2 // N
};

uint16_t sign_extension(uint16_t x, int bit_count) {
    if ((x >> (bit_count - 1)) & 1) {
        x |= 0xFFFF << bit_count; /* 0xFFF is -1 in hexa, we do the inverse of x*/
    }
    return x;
}

void update_flags(uint16_t n_fl) {
    if (reg[n_fl] == 0)
        reg[RCOND] = ZRO;
    else if (reg[n_fl] >> 15) /* a 1 in the left most bit incates negatives */
        reg[RCOND] = NEG;
    else
        reg[RCOND] = POS;
}

void add(uint16_t instruction)
{
    /* destination register (DR) */
    uint16_t r0 = (instruction >> 9) & 0x7; /* 0x7 filter the 3 bits of the register */
    /* first operande */
    uint16_t r1 = (instruction >> 6) & 0x7;
    /* immediate mode check */
    uint16_t im_fl = (instruction >> 5) & 0x1;

    if (im_fl) {
        uint16_t imm = sign_extension(instruction & 0x1F, 5);
        reg[r0] = reg[r1] + imm;
    }
    else {
        uint16_t r2 = instruction & 0x7;
        reg[r0] = reg[r1] + reg[r2];
    }
    update_flags(r0);
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("LC-3 file ....\n");
        exit(2);
    }
    for (int i = 1; i < argc; ++i)
    {
        if (!read_image(argv[i])) {
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
        break;
    }
}
