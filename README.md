# Harvard Architecture 32-Bit Computer Emulator in C

## General

Welcome to the **Harvard Architecture C 32-bit Emulator** repository. This project provides a C-based 32-bit Harvard Architecture Computer Emulator with CPU and RAM emulation, assembly code support, sample programs, a user-friendly interface, and memory access logging.

**Original Authors**: Foivos Gaitantzis & Simas Stankus

<img src="https://avatars.githubusercontent.com/u/47535153?v=4" width="20%" height="20%" alt="Global Recruits Logo">

## Project Description

This emulator is designed to replicate the behavior of a 32-bit Harvard Architecture computer. It emulates two key hardware components: the CPU and RAM, allowing for the execution of assembly code instructions using a decoder and an Arithmetic Logic Unit (ALU). Three sample programs are included for testing the accuracy of the hardware emulation:

1. **Increment Program:** This program increments a previous value stored in memory.
2. **Square Calculation Program:** It calculates the squares of all integers between 0 and a preset value, N.
3. **Prime Number Calculation Program:** This program calculates all prime numbers from 0 to N.

A simple console interface is provided for program selection, and a basic debug function logs all memory accesses into a log file.

## Usage

### Emulator Design

The emulator follows the Harvard architecture, with separate instruction and data memory. It supports two types of instructions:

- **R-Type Instruction:**
  - 4-bit OpCode
  - 12-bit Address ARG0
  - 12-bit Address ARG1

- **L-Type Instruction:**
  - 4-bit OpCode
  - 12-bit Address ARG0

The data flow diagram is shown below:

<img src="demo/cycle.png?raw=true" alt="Data Flow Cycle Diagram">

### Compilation and Execution

To compile the emulator, open a Command Prompt or Terminal window and run the following command:

```bash
gcc main.c cpu.c alu.c ram.c -o main
```

After successfully compiling the code, you can run the emulator using:
```bash
./main
```

## Repository Contents

This repository includes the source code and necessary files for the C-based 32-bit Harvard Architecture Computer Emulator. The key components and features of the emulator are described in the repository's main page.

## Disclaimer
This repository serves as a learning resource and reference for studying the architecture and components of the Harvard Architecture C 32-bit Emulator. It is not intended for production use, and no support or updates will be provided. Please use this repository responsibly and in compliance with any relevant legal and ethical considerations.

## Demo

<h3 align="center">Console Entry Point</h3>
<p align="center"><img src="demo/entrypoint.png?raw=true" alt="Entry Point"></p>

<h3 align="center">Debug File</h3>

```
Timestamp: 2.871000
OPCODE: JMP
PRESNT State: DECODE | NEXT State: FETCH
DATA Bus: 1073905664 | ADDRESS Bus: 0x0000
PC: 0x0000 | IR: 0x40028000 | AC: 0


Timestamp: 2.871000
OPCODE: READ
PRESNT State: EXECUTE | NEXT State: FETCH
DATA Bus: 200 | ADDRESS Bus: 0x0019
PC: 0x0005 | IR: 0x300C8000 | AC: 200


Timestamp: 2.871000
OPCODE: WRITE
PRESNT State: EXECUTE | NEXT State: FETCH
DATA Bus: 200 | ADDRESS Bus: 0x0001
PC: 0x0006 | IR: 0x38008000 | AC: 200


Timestamp: 2.871000
OPCODE: BNP
PRESNT State: DECODE | NEXT State: FETCH
DATA Bus: 200 | ADDRESS Bus: 0x0001
PC: 0x0007 | IR: 0x50008070 | AC: 200


Timestamp: 2.871000
OPCODE: BIZ
PRESNT State: DECODE | NEXT State: FETCH
DATA Bus: 200 | ADDRESS Bus: 0x0001
PC: 0x0008 | IR: 0x48008060 | AC: 200


Timestamp: 2.871000
OPCODE: SUB
PRESNT State: EXECUTE | NEXT State: FETCH
DATA Bus: 198 | ADDRESS Bus: 0x0002
PC: 0x0009 | IR: 0x10008010 | AC: 198


Timestamp: 2.871000
OPCODE: WRITE
PRESNT State: EXECUTE | NEXT State: FETCH
DATA Bus: 198 | ADDRESS Bus: 0x0001
PC: 0x000A | IR: 0x38008000 | AC: 198


Timestamp: 2.871000
OPCODE: JMP
PRESNT State: DECODE | NEXT State: FETCH
DATA Bus: 1073971200 | ADDRESS Bus: 0x000B
PC: 0x000B | IR: 0x40038000 | AC: 198

...
```