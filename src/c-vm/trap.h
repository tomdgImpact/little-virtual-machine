#ifndef TRAP_H_
#define TRAP_H_
#include <stdint.h>

/* LC-3 architecture provides directly some common subroutine to have basics
 * I/O. They are called trap routines
 * Each routines has its own code
 * Trap code uses specific address near 0x0 so that's why the program start
 * is at 0x3000 and not 0x0. Lower addresses are left for trap codes.
 */

enum
{
    TGETC = 0x20, /* get character from keyboard */
    TOUT = 0x21, /* output character */
    TPUTS = 0x22, // puts a word string into terminal
    TIN = 0x23, // get and echo char from keyboard to terminal
    TPUTSP = 0x24, // output byte string
    THALT = 0x25,
};

uint16_t traps(uint16_t instruction);
#endif
