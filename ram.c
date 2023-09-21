/* ram.c - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#include "inc/ram.h"
#include "inc/cpu.h"

uint32_t RAM[RAM_BYTES];

void readRAM() {
    DATA_BUS = RAM[ADDRESS_BUS]; // Set the Data Bus value to the RAM value on current Address
}

void writeRAM() {
    RAM[ADDRESS_BUS] = DATA_BUS; // Set the current Address value on the RAM to the Data Bus value.
}
