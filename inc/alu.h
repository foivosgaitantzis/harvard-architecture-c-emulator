/* alu.h - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#ifndef ALU_H
#define ALU_H

#include <stdio.h>
#include <stdint.h>
#include "opcodes.h"

/* ALU Input & Output Variables */
extern int32_t ALU_A ;
extern int32_t ALU_B ;
extern OPCODES ALU_CS;

extern int32_t ALU_Result ;

/* ALU Flags */
extern uint8_t Positive_Flag ;
extern uint8_t Zero_Flag ;

/* ALU Functions */
void runALU();
void setFlags();

#endif // ALU_H

