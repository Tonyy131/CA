Spicy Von Neumann Fillet with Extra Shifts
Project Overview
This project involves simulating a fictional processor design and architecture using C. The chosen package for this project is "Spicy Von Neumann Fillet with Extra Shifts".

Memory Architecture
Architecture: Von Neumann
Memory Size: 2048 * 32
Memory Addressing:
Addresses: 0 to 2047
Instruction Memory: Addresses 0 to 1023
Data Memory: Addresses 1024 to 2048
Word Addressable: Each memory block contains 1 word (32 bits or 4 bytes)
Registers
Total Registers: 33
General-Purpose Registers (GPRS): 31 (R1 to R31)
Zero Register: 1 (R0, hard-wired to 0)
Program Counter: 1 (PC)
Instruction Set Architecture
Instruction Size
32 bits
Instruction Types
3 types
Instruction Count
12 instructions with opcodes ranging from 0 to 11
Data Path
Stages
Instruction Fetch (IF): Fetches the next instruction from main memory using the PC and increments the PC.
Instruction Decode (ID): Decodes the instruction and reads operands from the register file.
Execute (EX): Executes the instruction and performs ALU operations.
Memory (MEM): Performs memory access operations for loads and stores.
Write Back (WB): Writes results back to the register file.
Pipeline
Maximum of 4 instructions running in parallel.
Instruction Fetch (IF) and Memory (MEM) cannot operate in parallel due to shared memory access.
Clock Cycles: 7 + ((n - 1) * 2), where n = number of instructions.
Example: For 7 instructions, the number of clock cycles is 19.
