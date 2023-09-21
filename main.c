/* main.c - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "inc/ram.h"
#include "inc/opcodes.h"
#include "inc/cpu.h"

clock_t begin = 0;

/* Refer to Appendix A on the word document for a more detailed description of the assembly code */

/* Increment a value stored in memory. */
int32_t Example1[RAM_BYTES] = {
    (JMP << 27) | (2 << 15),
    0,
    (ADDI << 27) | (1 << 15) | (1 << 3),
    (WRITE << 27) | (1 << 15),
    (JMP << 27) | (2 << 15)
};

/* Calculate the squares of all integers between 0 and pre-set value N */
int32_t Example2[RAM_BYTES] = {
    (JMP << 27) | (5 << 15),
    0,
	0,
	0,
	1,
    (BIZ << 27) | (2 << 15) | (11 << 3),
	(ADD << 27) | (1 << 15) | (3 << 3),
	(WRITE << 27) | (3 << 15),
	(SUB << 27) | (2 << 15) | (4 << 3),	
    (WRITE << 27) | (2 << 15),
    (JMP << 27) | (5 << 15),	
	(ADDI << 27) | (1 << 15) | (1 << 3),
	(WRITE << 27) | (1 << 15),
	(WRITE << 27) | (2 << 15),
	(READ << 27) | (3 << 15),
	(WRITE << 27) | (19 << 15),
	(READ << 27) | (20 << 15),
	(WRITE << 27) | (3 << 15),
    (JMP << 27) | (22 << 15),
	0,
	0,
	99,
	(BIZ << 27) | (21 << 15) | (26 << 3),
	(SUB << 27) | (21 << 15) | (4 << 3),
	(WRITE << 27) | (21 << 15),
	(JMP << 27) | (5 << 15),
	(HALT << 27),
};

/* Gather the prime numbers between 0 and pre-set value N */
int32_t Example3[RAM_BYTES] = {
    (JMP << 27) | (5 << 15),
    0,
    2,
    2,
    1,
    (READ << 27) | (25 << 15),
    (WRITE << 27) | (1 << 15),
    (BNP << 27) | (1 << 15) | (14 << 3), 
    (BIZ << 27) | (1 << 15) | (12 << 3),
    (SUB << 27) | (1 << 15) | (2 << 3),
    (WRITE << 27) | (1 << 15),
    (JMP << 27) | (7 << 15),
    (JMP << 27) | (28 << 15),                    
    0,
    (SUB << 27) | (25 << 15) | (2 << 3), 
    (WRITE << 27) | (23 << 15),
    (SUB << 27) | (23 << 15) | (3 << 3), 
    (WRITE << 27) | (23 << 15),
    (BIZ << 27) | (23 << 15) | (37 << 3),
    (BNP << 27) | (23 << 15) | (37 << 3),
    (ADD << 27) | (2 << 15) | (4 << 3),
    (WRITE << 27) | (2 << 15),
    (JMP << 27) | (5 << 15),
    0,
    0,
    150,
    1, 
    0, 
    (SUB << 27) | (25 << 15) | (4 << 3),
    (WRITE << 27) | (41 << 15), 
    (BIZ << 27) | (41 << 15) | (36 << 3),
    (SUB << 27) | (25 << 15) | (4 << 3),
    (WRITE << 27) | (25 << 15),
    (READ << 27) | (3 << 15),
    (WRITE << 27) | (2 << 15),
    (JMP << 27) | (5 << 15), 
    (JMP << 27) | (42 << 15),
    (READ << 27) | (25 << 15), 
    (WRITE << 27) | (40 << 15),
    (JMP << 27) | (28 << 15),
    0,
    0, 
	(ADD << 27) | (25 << 15) | (4 << 3),
	(WRITE << 27) | (40 << 15),
	(HALT << 27)
};

int32_t * EXAMPLES[] = {Example1, Example2, Example3}; // Store the examples in a "common" array

int main() {
	/* Reset Values on initialization */
	PC = 0;
	AC = 0;
	IR = 0;
    Next_State = FETCH;

	
	/* User Interface */
	int i, prev_value, program, attribute = 0;
	printf("Enable Debug File (1=Y, 0=N)\n");
	scanf("%d", &enable_debug);
	printf("Select Program: \n");
	printf("[1] - Counter Program \n");
	printf("[2] - Squared Numbers \n");
	printf("[3] - Prime Numbers \n");
	scanf("%d", &program);
	
	if (enable_debug) { // Store only if debug is enabled
		/* Reset the Log File */
		LogFile = fopen("debug.log", "w");
	}
	
	begin = clock(); // Initial clock on program execution
	
	/* Hard Write Programs into Memory */
	for(i=0; i<=RAM_BYTES; i++){
		RAM[i] = EXAMPLES[program-1][i];
	}
	if (program != 1) {
		printf("Enter Limit: \n");
		scanf("%d", &attribute);
		if (program == 2) {
			RAM[21] = attribute;
		}
		if (program == 3) {
			RAM[25] = attribute;
		}
	}
	
    while (1) {
		clockTick(); // Start the State Cycle
		
		/* Choose the correct memory addresses to output for every program */
		if (program == 1) {
			if (RAM[1]!=prev_value) {
				printf("Counter Value: %d\n", RAM[1]);
				prev_value = RAM[1];
			}
		}
		if (program == 2) {
			if (RAM[19]!=prev_value) {
				printf("Squared Numbers (%d): %d\n", (int32_t)(RAM[1] - 1) < 0 ? RAM[1] : RAM[1] - 1 , RAM[19]);
				prev_value = RAM[19];
			}
		} else if (program == 3) {
			if (RAM[40]!=prev_value & RAM[40]!=1) {
				printf("Prime Numbers: %d\n", RAM[40]);
				prev_value = RAM[40];
			}
		}
		
		/* When the CPU is Halted */
		if (Present_State == HALT_CPU) {
			clock_t end = clock(); // Final clock when program is finished
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // Get the execution time (final - initial)
			printf("Execution Time: %f\n", time_spent);
			if (enable_debug) { // Store only if debug is enabled
				/* Reset the Log File */
				fclose(LogFile);
			}
			return 0;
		}
    }  
    return 0;
}
  