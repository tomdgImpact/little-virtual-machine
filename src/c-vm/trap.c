#include "opcode.h"
#include "vm.h"
#include "trap.h"
#include <stdint.h>
#include <stdio.h>

void t_puts() {
    uint16_t* chars = memory + reg[R0];
    while(*chars) {
        putc((char)*chars, stdout);
        chars++;
    }
    fflush(stdout);
}

void t_getc()
{
    reg[R0] = (uint16_t)getchar();
    update_flags(R0);
}

void t_out() {
    putc((char)reg[R0], stdout);
    fflush(stdout);
}

void t_in(){
    printf("press your keyboard to enter a letter: ");
    char letter = getchar();
    putc(letter, stdout);
    fflush(stdout);
    reg[R0] = (uint16_t)letter;
    update_flags(R0);
}

void t_putsp(){
    /* print word size char
     * We need to swap back to big endian format 
     */
    uint16_t* to_print = memory + reg[R0];
    while (*to_print){
        char c1 = (*to_print) & 0xFF;
        putc(c1, stdout);
        char c2 = (*to_print) >> 8;
        if (c2)
            putc(c2, stdout);
        to_print++;
    }
    fflush(stdout);
}

uint16_t t_halt() {
    puts("halt program");
    fflush(stdout);
    return 1;
}

uint16_t traps(uint16_t instruction){
    reg[R7] = reg[RPC];
    uint16_t res = 1;
    switch (instruction & 0xFF) {
        case TGETC:
            t_getc();
            break;
        case TOUT:
            t_out();
            break;
        case TPUTS:
            t_puts();
            break;
        case TIN:
            t_in();
            break;
        case TPUTSP:
            t_putsp();
            break;
        case THALT:
            res = t_halt();
            break;
    }
    return res;
}

