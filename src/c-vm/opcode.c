#include "vm.h"
#include "opcode.h"
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

void ldi(uint16_t instruction) {
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t addr_value = sign_extension(instruction & 0x1FF, 9);
    /* According to LC-3 architecture, the address of the value is stored
     * in a specific memory chunk which address is calculated by adding
     * to the PC, addr_value
     */
    reg[r0] = mem_read(mem_read(reg[RPC] + addr_value));
    update_flags(r0);
}

void and_op(uint16_t instruction)
{
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t r1 = (instruction >> 6) & 0x7;
    uint16_t imm_flag = (instruction >> 5) & 0x1;

    if (imm_flag) {
        uint16_t immediate = sign_extension(instruction & 0x1F, 5);
        reg[0] = reg[1] & immediate;
    }
    else {
        uint16_t r2 = instruction & 0x7;
        reg[r0] = reg[r1] & reg[r2];
    }
    update_flags(r0);
}

void not_op(uint16_t instruction) {
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t r1 = (instruction >> 6) & 0x7;

    reg[r0] = ~reg[r1];
    update_flags(r0);
}

void branch(uint16_t instruction) {
    uint16_t flag = (instruction >> 9) & 0x7;
    uint16_t offset = sign_extension(instruction & 0x1FF, 9);
    if (flag & reg[RCOND])
        reg[RPC] = offset;
}

void jump(uint16_t instruction) {
    uint16_t r1 = (instruction >> 6) & 0x7;
    reg[RPC] = reg[r1];
}

void jump_register(uint16_t instruction) {
    uint16_t flag = (instruction >> 11) & 1;
    reg[R7] = reg[RPC];
    if (flag) /* JSR */
    {
        uint16_t offset = sign_extension(instruction & 0x1FF, 11);
        reg[RPC] += offset;
    }
    else { /* JSRR */
        uint16_t r1 = (instruction >> 6) & 0x7;
        reg[RPC] = reg[r1];
    }
}

void load(uint16_t instruction) {
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t offset = sign_extension(instruction & 0x1FF, 6);
    reg[r0] = mem_read(reg[RPC] + offset);
    update_flags(r0);
}

void load_register(uint16_t instruction) {
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t r1 = (instruction >> 6) & 0x7;
    uint16_t offset = sign_extension(instruction & 0x3F, 6);
    reg[r0] = mem_read(reg[r1], offset);
    update_flags(r0);
}

void lea(uint16_t instruction) {
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t addr_offset = sign_extension(instruction & 0x1FF, 9);
    reg[r0] = reg[RPC] + addr_offset;
    update_flags(r0);
}

void store(uint16_t instruction){
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t offset = sign_extension(instruction & 0x1FF, 9);
    mem_write(reg[RPC] + offset, reg[r0]);
}

void store_indirect(uint16_t instruction){
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t offset = sign_extension(instruction & 0x1FF, 9);
    mem_write(mem_read(reg[RPC] + offset), reg[r0]);
}

void store_register(uint16_t instruction) {
    uint16_t r0 = (instruction >> 9) & 0x7;
    uint16_t r1 = (instruction >> 6) & 0x7;
    uint16_t offset = sign_extension(instruction & 0x3F, 6);
    mem_write(reg[r1] + offset, reg[r0]);
}
