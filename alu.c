/* alu.c - Foivos Gaitantzis (29182913)
   R-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> <- 12 bit Address ARG1 ->
   L-Type Instruction <- 4 bit OPCode -> <- 12 bit Address ARG0 -> 
   Emulator Design Idea Inspired with Simas Stankus
*/

#include "inc/alu.h"

int32_t ALU_A ;
int32_t ALU_B ;
OPCODES ALU_CS;

uint8_t Positive_Flag ;
uint8_t Zero_Flag;

int32_t ALU_Result; 
   
void runALU() {
    switch (ALU_CS) {
        case (ADD):
            ALU_Result = ALU_A + ALU_B;
            break;
        case (SUB):
            ALU_Result = ALU_A - ALU_B;
            break;
        case (AND):
            ALU_Result = (ALU_A & ALU_B);
            break;
        case (LSHIFT):
            ALU_Result = ALU_A << ALU_B;
            break;

    }
    setFlags();
}

void setFlags() {
    if (ALU_Result >= 0) {
        Positive_Flag = 1;
    } else {
        Positive_Flag = 0;
    }
    if (ALU_Result == 0) {
        Zero_Flag = 1;
    } else {
        Zero_Flag = 0;
    }
}
