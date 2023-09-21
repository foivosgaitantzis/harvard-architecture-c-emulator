/* ram.h - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdint.h>

/* Set RAM Capacity (4096Bytes = 4kB) */
#define RAM_BYTES 4096

/* RAM Definition (Ideal RAM: No Read/Write Delay) */
extern uint32_t RAM[RAM_BYTES];

/* RAM Functions */
void readRAM();
void writeRAM();

#endif // RAM_H


