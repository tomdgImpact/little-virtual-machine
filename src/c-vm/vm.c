#include "vm.h"
#include "opcode.h"
#include "trap.h"

uint16_t memory[MEMORY_MAX];
uint16_t reg[RCOUNT];

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
}
