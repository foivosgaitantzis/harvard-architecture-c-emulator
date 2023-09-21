/* opcodes.h - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#ifndef OPCODES_H
#define OPCODES_H


#include <stdio.h>


typedef enum OPCODES {
	ADD = 1, // Add (RAM[ARG0]+RAM[ARG1])
	SUB, // Subtract (RAM[ARG0]-RAM[ARG1])
	AND, // And (RAM[ARG0]&RAM[ARG1])
	LSHIFT, // Left-Shift (RAM[ARG0] << ARG1)
	ADDI, // Add (RAM[ARG0]+ARG1)
	READ, // Read from RAM (ARG0)
	WRITE, // Write to RAM (ARG0)
	JMP, // Jumps Address (ARG0)
	BIZ, // Branch-If-Zero (if (ARG0 == 0) { JMP (ARG1) };)
	BNP, // Branch-Not-Positive (if (ARG0 < 0) { JMP (ARG1) };)
	HALT // Halt the CPU (Inactive State)
} OPCODES;

#endif // OPCODES_H
