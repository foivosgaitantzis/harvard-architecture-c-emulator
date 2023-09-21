/* cpu.c - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus 
*/

#include <stdio.h>
#include <stdlib.h>

#include "inc/cpu.h"
#include "inc/ram.h"
#include "inc/opcodes.h"
#include "inc/alu.h"

// String Arrays used for Logging
char *CPU_States_String[] = {
	"FETCH",
	"DECODE",
	"EXECUTE",
	"HALT CPU",
};

char *OPCODES_String[] = {
	"",
	"ADD",
	"SUB",
	"AND",
	"LSHIFT",
	"ADDI",
	"READ",
	"WRITE",
	"JMP",
	"BIZ",
	"BNP",
	"HALT",
};

uint8_t enable_debug = 0; // Enable debug script variable initially set to 0.

// Declare the States
CPU_States Present_State;
CPU_States Next_State;

// Declare the Registers
uint32_t PC;
uint32_t IR;
int32_t AC; 

// Declare the Bus
int32_t DATA_BUS ;
uint32_t ADDRESS_BUS;


// Log-to-File Function
void fileLog() {
	if (enable_debug) { // Store only if debug is enabled
		if (LogFile == NULL) {
			printf("Unable to Open the LogFile. \n"); 
			return;
		}
		clock_t end = clock(); // Final clock when a reading is taken
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // Get the run time (final - initial)
		fprintf(LogFile, "Timestamp: %f\n", time_spent); // Store OPCode
		fprintf(LogFile, "OPCODE: %s\n", OPCODES_String[(uint32_t) (IR & 0x78000000) >> 27]); // Store OPCode
		fprintf(LogFile, "PRESNT State: %s | NEXT State: %s\n",  CPU_States_String[(uint32_t) Present_State], CPU_States_String[(uint32_t) Next_State]); // Store Present and Next States
		fprintf(LogFile, "DATA Bus: %d | ADDRESS Bus: 0x%04X\n", DATA_BUS, ADDRESS_BUS); // Store the current values on Data & Address Bus 
		fprintf(LogFile, "PC: 0x%04X | IR: 0x%04X | AC: %d\r\n", PC, IR, AC); // Store Register Values
		fprintf(LogFile, "\r");
	}
}

// Fetch State function
void fetch() {
    ADDRESS_BUS = PC; // Set Address Bus to current Program Counter
    readRAM(); 
    IR = DATA_BUS; // Store the read instruction on the Data Bus.
}

// decode State function
void decode() {
    OPCODES OP = (IR & 0x78000000) >> 27; // ... 0000 1111 if OPCode is 1111
    uint16_t ARG0 = (IR & 0x7FFF000) >> 15; // ... 0000 1111 1111 1111 if ARG0 is 1111 1111 1111
    uint16_t ARG1 = (IR & 0x7FF8) >> 3; // ... 0000 1111 1111 1111 if ARG1 is 1111 1111 1111
    switch (OP) {
		/* ADD - ADDI (5 Functions) - Run through ALU */
        case (ADD):
        case (SUB):
        case (AND):
        case (LSHIFT):
            /* Set ALU Control Signal */
            DATA_BUS = OP;
            ALU_CS = DATA_BUS;

            /* Read ARG0 from Memory and set ALU Input Signal A */
            ADDRESS_BUS = ARG0;
            readRAM();
            ALU_A = DATA_BUS;

            /* Read ARG1 from Memory and set ALU Input Signal B */
            ADDRESS_BUS = ARG1;
            readRAM();
            ALU_B = DATA_BUS;

            Next_State = EXECUTE;
            break;
        case (ADDI):
            /* Set ALU Control Signal */
            DATA_BUS = ADD;
            ALU_CS = DATA_BUS;

            /* Read ARG0 from Memory and set ALU Input Signal A */
            ADDRESS_BUS = ARG0;
            readRAM();
            ALU_A = DATA_BUS;
			
            /* Set ALU Input Signal B to Value */
            ALU_B = ARG1;

            Next_State = EXECUTE;
            break;
        case (READ):
            ADDRESS_BUS = ARG0; // Set Address Bus to ARG0
            
            Next_State = EXECUTE;
            break;
        case (WRITE):
            DATA_BUS = AC; // Set the Data Bus value to the accumulator value
            ADDRESS_BUS = ARG0; // Set the Address Bus to ARG0

            Next_State = EXECUTE;
            break;
        case (JMP):
		    Next_State = FETCH;
			
			fileLog(); // Log before execute state, as JMP never reaches execute
			
            PC = ARG0; // Set the Program Counter Address to ARG0
            break;
		case (BIZ):
			ADDRESS_BUS = ARG0; // Set the Address Bus to ARG0
			readRAM(); 
			AC = DATA_BUS; // Set the Read Value to the Data Bus
			
			Next_State = FETCH;
			
			fileLog(); // Log before execute state, as BIZ never reaches execute
			
			if (AC==0) { // If the value is equal to zero
				PC = ARG1; // JMP to ARG1
			} else {
				PC++; // If not, increment the Program Counter
			}			
			break;
		case (BNP):
            ADDRESS_BUS = ARG0; // Set the Address Bus to ARG0
            readRAM();
            AC = DATA_BUS; // Set the Read Value to the Data Bus
			
            Next_State = FETCH; 
			
			fileLog(); // Log before execute state, as BNP never reaches execute
			
			if (AC < 0) { // If the value is less than zero
                PC = ARG1; // JMP to ARG1
            } else {
                PC++; // If not, increment the Program Counter
            }
            break;
        case (HALT):
			Next_State = HALT_CPU;
			
			fileLog(); // Log before execute state, as HALT never reaches execute
            break;
    }
}

void execute() {
    uint8_t OP = (IR & 0x78000000) >> 27; //... 0000 1111 if OPCode is 1111
    switch (OP) {
		/* ADD - ADDI (5 Functions) - Run through ALU */
        case (ADD):
        case (SUB):
        case (AND):
        case (LSHIFT):
        case (ADDI):
            runALU(); // Compute ALU Result & Raise Flags
            DATA_BUS = ALU_Result; // Set the Data Bus to the ALU Result
            AC = DATA_BUS; // Update the Accumulator Value
            break;
        case (READ):
            readRAM();
            AC = DATA_BUS; // Set the Accumulator value to the Read Data Value
            break;
        case (WRITE):
            writeRAM(); // Write the Data Bus value to the RAM Module
            break;
    }
	Next_State = FETCH;
	fileLog(); // Log to File
    PC++; //Increment the Program Counter
}

void clockTick() {
    Present_State = Next_State;
    switch (Present_State) {
        case (FETCH):
            fetch();
            Next_State = DECODE;;
            break;
        case (DECODE):
            decode();
            break;
        case (EXECUTE):
            execute();
            break;
		case (HALT_CPU):
			break;
    }
}
