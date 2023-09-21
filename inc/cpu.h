/* cpu.h - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>

extern clock_t begin;

FILE *LogFile;

extern uint8_t enable_debug;

/* Debug Logging Function */
void fileLog();

/* Enumerate States */
typedef enum CPU_States {
	FETCH, // Fetch instruction from memory.
	DECODE,  // Decode instruction.
	EXECUTE,  // Execute Instructions & Update Program Counter (PC).
	HALT_CPU
} CPU_States;

extern CPU_States Present_State; //Present State
extern CPU_States Next_State;    //Next state.

/* Register Definitions */
extern uint32_t PC ;
extern uint32_t IR ;
extern int32_t AC ;

/* Bus Definitions */
extern int32_t DATA_BUS ;
extern uint32_t ADDRESS_BUS ;

/* CPU Functions */
void fetch();
void decode();
void execute();

/* Clock Functions */
void clockTick();

#endif // CPU_H
