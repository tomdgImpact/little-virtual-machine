#ifndef OPCODE_H_
#define OPCODE_H_

#include <stdint.h>
uint16_t sign_extension(uint16_t x, int bit_count);
void update_flags(uint16_t n_fl);
void add(uint16_t instruction);
void ldi(uint16_t instruction);
void and_op(uint16_t instruction);
void not_op(uint16_t instruction);
void branch(uint16_t instruction);
void jump(uint16_t instruction);
void jump_register(uint16_t instruction);
void load(uint16_t instruction);
void load_register(uint16_t instruction);
void lea(uint16_t instruction);
void store(uint16_t instruction);
void store_indirect(uint16_t instruction);
void store_register(uint16_t instruction);

#endif
