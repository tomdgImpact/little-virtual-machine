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


