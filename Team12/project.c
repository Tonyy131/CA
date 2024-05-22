#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"


int registerFile [32];
int instructionMemory[2048];
int NumberofInstructions = sizeof(instructionMemory)/sizeof(int);
int pc = 0;
int zeroFlag = 0;
int flush = 0;
int pcOLD = -1;


// Binary int format in c is 0b00000000000000000000000000000000 (32 bits)
int RetrieveInstruction(){
    FILE *file;
    char line[10000];
    char instruction[5];
    char operand1[5];
    char operand2[5];
    char operand3[5];
    int value;
    int count = 0;
    unsigned int result;

    // Open the file in read mode
    file = fopen("test.txt", "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    // Read line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line
        
        
        if(sscanf(line, "%s %s %s %s", instruction, operand1, operand2, operand3)>= 1){

            // Check if the instruction is "ADD"
            if (strcasecmp(instruction, "ADD") == 0) {

                result = 0b0000;
                // Check if operands are in the format "R<number>"
                if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                    value = atoi(&operand1[1]); // Extract the number
                    if (value >= 0 && value <= 31) {
                        value = value & 0x1F;
                        // Concatenate with another value
                        result = (result << 5) | value;
                    } else {
                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                    }
                }
                if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                    value = atoi(&operand2[1]);
                    if (value >= 0 && value <= 31) {
                        value = value & 0x1F;
                        // Concatenate with another value
                        result = (result << 5) | value;
                    } else {
                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                    }
                }
                if ((operand3[0] == 'R' || operand3[0] == 'r') && isdigit(operand3[1])) {
                    value = atoi(&operand3[1]);
                    if (value >= 0 && value <= 31) {
                        value = value & 0x1F;
                        // Concatenate with another value
                        result = (result << 5) | value;
                         
                    } else {
                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                    }
                }
                result = (result << 13) | 0b0000000000000;
            } else{ if (strcasecmp(instruction, "SUB") == 0) {

                result = 0b0001;
                // Check if operands are in the format "R<number>"
                if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                    value = atoi(&operand1[1]); // Extract the number
                    if (value >= 0 && value <= 31) {
                        value = value & 0x1F;
                        // Concatenate with another value
                        result = (result << 5) | value;
                         
                    } else {
                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                    }
                }
                if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                    value = atoi(&operand2[1]);
                    if (value >= 0 && value <= 31) {
                        value = value & 0x1F;
                        // Concatenate with another value
                        result = (result << 5) | value;
                         
                    } else {
                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                    }
                }
                if ((operand3[0] == 'R' || operand3[0] == 'r') && isdigit(operand3[1])) {
                    value = atoi(&operand3[1]);
                    if (value >= 0 && value <= 31) {
                        value = value & 0x1F;
                        // Concatenate with another value
                        result = (result << 5) | value;
                         
                    } else {
                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                    }
                }
                result = (result << 13) | 0b0000000000000;
            }else{
                if (strcasecmp(instruction, "MULI") == 0) {
                    result = 0b0010;
                    // Check if operands are in the format "R<number>"
                    if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                        value = atoi(&operand1[1]); // Extract the number
                        if (value >= 0 && value <= 31) {
                            value = value & 0x1F;
                            // Concatenate with another value
                            result = (result << 5) | value;
                             
                        } else {
                            printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                        }
                    }
                    if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                        value = atoi(&operand2[1]);
                        if (value >= 0 && value <= 31) {
                            value = value & 0x1F;
                            // Concatenate with another value
                            result = (result << 5) | value;
                             
                        } else {
                            printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                        }
                    }
                    // Check if the third operand exists and is an integer
                    if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                        char* endptr;
                        value = strtol(operand3, &endptr, 10);
                        // Check if conversion was successful and if it's within the desired range
                        if (endptr != operand3 && value >= -131072 && value <= 131071) {
                            value &= 0x3FFFF;
                            result = (result << 18) | value;
                            // Further processing here
                        } else {
                            printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                        }
                    }
                }else{
                    if (strcasecmp(instruction, "ADDI") == 0) {
                        result = 0b0011;
                        // Check if operands are in the format "R<number>"
                        if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                            value = atoi(&operand1[1]); // Extract the number
                            if (value >= 0 && value <= 31) {
                                value = value & 0x1F;
                                // Concatenate with another value
                                result = (result << 5) | value;
                                 
                            } else {
                                printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                            }
                        }
                        if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                            value = atoi(&operand2[1]);
                            if (value >= 0 && value <= 31) {
                                value = value & 0x1F;
                                // Concatenate with another value
                                result = (result << 5) | value;
                                 
                            } else {
                                printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                            }
                        }
                        // Check if the third operand exists and is an integer
                        if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                            char* endptr;
                            value = strtol(operand3, &endptr, 10);

                            // Check if conversion was successful and if it's within the desired range
                            if (endptr != operand3 && value >= -131072 && value <= 131071) {
                                value &= 0x3FFFF;
                                result = (result << 18) | value;
                                // Further processing here
                            } else {
                                printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                            }
                        }
                    }else{
                        if (strcasecmp(instruction, "BNE") == 0) {
                            result = 0b0100;
                            // Check if operands are in the format "R<number>"
                            if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                value = atoi(&operand1[1]); // Extract the number
                                if (value >= 0 && value <= 31) {
                                    value = value & 0x1F;
                                    // Concatenate with another value
                                    result = (result << 5) | value;
                                     
                                } else {
                                    printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                }
                            }
                            if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                value = atoi(&operand2[1]);
                                if (value >= 0 && value <= 31) {
                                    value = value & 0x1F;
                                    // Concatenate with another value
                                    result = (result << 5) | value;
                                     
                                } else {
                                    printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                }
                            }
                            // Check if the third operand exists and is an integer
                            if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                                char* endptr;
                                value = strtol(operand3, &endptr, 10);

                                // Check if conversion was successful and if it's within the desired range
                                if (endptr != operand3 && value >= -131072 && value <= 131071) {
                                    value &= 0x3FFFF;
                                    result = (result << 18) | value;
                                    // Further processing here
                                } else {
                                    printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                                }
                            }
                        }else{
                            if (strcasecmp(instruction, "ANDI") == 0) {
                                result = 0b0101;
                                // Check if operands are in the format "R<number>"
                                if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                    value = atoi(&operand1[1]); // Extract the number
                                    if (value >= 0 && value <= 31) {
                                        value = value & 0x1F;
                                        // Concatenate with another value
                                        result = (result << 5) | value;
                                         
                                    } else {
                                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                    }
                                }
                                if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                    value = atoi(&operand2[1]);
                                    if (value >= 0 && value <= 31) {
                                        value = value & 0x1F;
                                        // Concatenate with another value
                                        result = (result << 5) | value;
                                         
                                    } else {
                                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                    }
                                }
                                // Check if the third operand exists and is an integer
                                if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                                    char* endptr;
                                    value = strtol(operand3, &endptr, 10);

                                    // Check if conversion was successful and if it's within the desired range
                                    if (endptr != operand3 && value >= -131072 && value <= 131071) {
                                        value &= 0x3FFFF;
                                        result = (result << 18) | value;
                                        // Further processing here
                                    } else {
                                        printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                                    }
                                }
                            }else{
                                if (strcasecmp(instruction, "ORI") == 0) {
                                    result = 0b0110;
                                    // Check if operands are in the format "R<number>"
                                    if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                        value = atoi(&operand1[1]); // Extract the number
                                        if (value >= 0 && value <= 31) {
                                            value = value & 0x1F;
                                            // Concatenate with another value
                                            result = (result << 5) | value;
                                             
                                        } else {
                                            printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                        }
                                    }
                                    if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                        value = atoi(&operand2[1]);
                                        if (value >= 0 && value <= 31) {
                                            value = value & 0x1F;
                                            // Concatenate with another value
                                            result = (result << 5) | value;
                                             
                                        } else {
                                            printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                        }
                                    }
                                    // Check if the third operand exists and is an integer
                                    if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                                        char* endptr;
                                        value = strtol(operand3, &endptr, 10);

                                        // Check if conversion was successful and if it's within the desired range
                                        if (endptr != operand3 && value >= -131072 && value <= 131071) {
                                            value &= 0x3FFFF;
                                            result = (result << 18) | value;
                                            // Further processing here
                                        } else {
                                            printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                                        }
                                    }
                                }else{
                                    if(strcasecmp(instruction, "J") == 0){
                                        result = 0b0111;
                                        if (operand1[0] != '\0' && isdigit(operand1[0])) {
                                            value = atoi(operand1);
                                            if (value >= 0 && value <= 268435455) {
                                                value = value & 0xFFFFFFF;

                                                result = (result << 28) | value;
                                                                  } else {
                                                printf("Error: Target address must be within 28-bit range (0 to 268435455).\n");
                                            }
                                        }
                                    }else{
                                        if(strcasecmp(instruction, "SLL") == 0){
                                            result = 0b1000;
                                            if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                                value = atoi(&operand1[1]); // Extract the number
                                                if (value >= 0 && value <= 31) {
                                                    value = value & 0x1F;
                                                    // Concatenate with another value
                                                    result = (result << 5) | value;
                                                     
                                                } else {
                                                    printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                }
                                            }
                                            if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                                value = atoi(&operand2[1]);
                                                if (value >= 0 && value <= 31) {
                                                    value = value & 0x1F;
                                                    // Concatenate with another value
                                                    result = (result << 5) | value;
                                                     
                                                } else {
                                                    printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                }
                                            }
                                            result = (result << 5) | 0b00000;
                                            if (operand3[0] != '\0' && isdigit(operand3[0])) {
                                                value = atoi(operand3);
                                                if (value >= 0 && value <= 8191) {
                                                    value = value & 0x1FFF;
                                                    result = (result << 13) | value;
                                                                          } else {
                                                    printf("Error: Target address must be within 18-bit range (0 to 262143).\n");
                                                }
                                            }
                                            
                                        }else{
                                            if(strcasecmp(instruction, "SRL") == 0){
                                                result = 0b1001;
                                                if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                                    value = atoi(&operand1[1]); // Extract the number
                                                    if (value >= 0 && value <= 31) {
                                                        value = value & 0x1F;
                                                        // Concatenate with another value
                                                        result = (result << 5) | value;
                                                         
                                                    } else {
                                                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                    }
                                                }
                                                if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                                    value = atoi(&operand2[1]);
                                                    if (value >= 0 && value <= 31) {
                                                        value = value & 0x1F;
                                                        // Concatenate with another value
                                                        result = (result << 5) | value;
                                                         
                                                    } else {
                                                        printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                    }
                                                }
                                                result = (result << 5) | 0b00000;
                                                if (operand3[0] != '\0' && isdigit(operand3[0])) {
                                                    value = atoi(operand3);
                                                    if (value >= 0 && value <= 8191) {
                                                        value = value & 0x1FFF;
                                                        result = (result << 13) | value;
                                                                                  } else {
                                                        printf("Error: Target address must be within 18-bit range (0 to 262143).\n");
                                                    }
                                                }
                                            }else{
                                                if (strcasecmp(instruction, "LW") == 0) {
                                                    result = 0b1010;
                                                    // Check if operands are in the format "R<number>"
                                                    if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                                        value = atoi(&operand1[1]); // Extract the number
                                                        if (value >= 0 && value <= 31) {
                                                            value = value & 0x1F;
                                                            // Concatenate with another value
                                                            result = (result << 5) | value;
                                                             
                                                        } else {
                                                            printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                        }
                                                    }
                                                    if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                                        value = atoi(&operand2[1]);
                                                        if (value >= 0 && value <= 31) {
                                                            value = value & 0x1F;
                                                            // Concatenate with another value
                                                            result = (result << 5) | value;
                                                             
                                                        } else {
                                                            printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                        }
                                                    }
                                                    // Check if the third operand exists and is an integer
                                                    if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                                                        char* endptr;
                                                        value = strtol(operand3, &endptr, 10);

                                                        // Check if conversion was successful and if it's within the desired range
                                                        if (endptr != operand3 && value >= -131072 && value <= 131071) {
                                                            value &= 0x3FFFF;
                                                            result = (result << 18) | value;
                                                            // Further processing here
                                                        } else {
                                                            printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                                                        }
                                                    }
                                                }else{
                                                    if (strcasecmp(instruction, "SW") == 0) {
                                                        result = 0b1011;
                                                        // Check if operands are in the format "R<number>"
                                                        if ((operand1[0] == 'R' || operand1[0] == 'r') && isdigit(operand1[1])) {
                                                            value = atoi(&operand1[1]); // Extract the number
                                                            if (value >= 0 && value <= 31) {
                                                                value = value & 0x1F;
                                                                // Concatenate with another value
                                                                result = (result << 5) | value;
                                                                 
                                                            } else {
                                                                printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                            }
                                                        }
                                                        if ((operand2[0] == 'R' || operand2[0] == 'r') && isdigit(operand2[1])) {
                                                            value = atoi(&operand2[1]);
                                                            if (value >= 0 && value <= 31) {
                                                                value = value & 0x1F;
                                                                // Concatenate with another value
                                                                result = (result << 5) | value;
                                                                 
                                                            } else {
                                                                printf("Error: Immediate value must be within 5-bit range (0 to 31).\n");
                                                            }
                                                        }
                                                        // Check if the third operand exists and is an integer
                                                        if (operand3[0] != '\0' && isdigit(operand3[0]) || operand3[0] == '-') {
                                                            char* endptr;
                                                            value = strtol(operand3, &endptr, 10);

                                                            // Check if conversion was successful and if it's within the desired range
                                                            if (endptr != operand3 && value >= -131072 && value <= 131071) {
                                                                value &= 0x3FFFF;
                                                                result = (result << 18) | value;
                                                                // Further processing here
                                                            } else {
                                                                printf("Error: Target address must be within 18-bit range (-131072 to 131071).\n");
                                                            }
                                                        }
                                                    }else{
                                                        printf("Invalid instruction!");
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            }
            printf(RED"MEM[%d] ="BLUE" %d. "RESET,count, result);
            instructionMemory[count] = result;
        }
        count = count + 1;
        if(count > 1024){
            break;
        }
    }
    printf("\n \n");
    // Close the file
    fclose(file);

    return count; // return the total number of instructions
}


int* fetch() {
        int* arr = malloc(2 * sizeof(int32_t));
        int32_t instruction = 0;
        instruction = instructionMemory[pc];
        pc = pc + 1;
        arr[0] = instruction;
        arr[1] = pc; // this is the instruction number that will be used in all methods
        return arr;
        
}

int* decode(int* arr) {
        int32_t instruction = arr[0];
        int N = arr[1];
        unsigned int opcode = 0;  
        int r1 = 0;      
        int r2 = 0;      
        int r3 = 0;      
        int shamt = 0;   
        int imm = 0;     
        int address = 0; 
        int *alu = malloc(8 * sizeof(int));

        opcode = instruction & 0b11110000000000000000000000000000;
        opcode = opcode >> 28;
        r1 = instruction & 0b00001111100000000000000000000000;
        r1 = r1 >> 23;
        alu[0] = r1;
        r2 = instruction & 0b00000000011111000000000000000000;
        r2 = r2 >> 18;
        alu[1] = r2;
        r3 = instruction & 0b00000000000000111110000000000000;
        r3 = r3 >> 13;
        alu[2] = r3;
        shamt = instruction & 0b00000000000000000001111111111111;
        alu[3] = shamt;
        imm = instruction & 0b00000000000000111111111111111111;
        int sign = imm & 0b00000000000000100000000000000000;
        sign = sign >> 17;
        if (sign == 1) {
            imm = (imm | 0xFFFFC000) & 0xFFFFFFFF; //sign extension
        }
        alu[4] = imm;
        address = instruction & 0b00001111111111111111111111111111;
        alu[5] = address;
        alu[6] = opcode;
        alu[7] = N;
        
       return alu;
        
        
             
}

int* Execute(int* alu){
    int opcode = alu[6];  
    int R1 = alu[0];      
    int R2 = alu[1];      
    int R3 = alu[2];      
    int shamt = alu[3];   
    int imm = alu[4];     
    int address = alu[5]; 
    int N = alu[7];
    int result = 0;
    int* final = malloc(4 * sizeof(int));
    switch (opcode)
    {
        case 0 : result = registerFile[R2] + registerFile[R3]; break;
        case 1 : result = registerFile[R2] - registerFile[R3];  break;
        case 2 : result = registerFile[R2] * imm;  break;
        case 3 : result = registerFile[R2] + imm;  break;
        case 4 : if(registerFile[R1]!= registerFile[R2]){
            int temp = pc;
            result = temp + imm;
            if(instructionMemory[result] != 0){
                flush = 1; //flag to flush decode and fetch if BNEQ is successful
                if(pcOLD == -1){
                    pcOLD = pc;
                }
                pc = result;
            }
        }; break;
        case 5 : result = registerFile[R2] & imm;  break;
        case 6 : result = registerFile[R2] | imm;  break;
        case 7 : int temp = pc;
                int newX = temp & 0b11110000000000000000000000000000;
                newX = newX >> 28;
                result = newX | address;
                if(instructionMemory[result] != 0){
                    flush = 1;          //flag to flush decode and fetch if Jump is successful    
                    if(pcOLD == -1){
                        pcOLD = pc;
                    } 
                    pc = result;
                }
                 break; 
        case 8 : result = registerFile[R2] << shamt;  break;
        case 9 : result = registerFile[R2] >> shamt;  break;
        case 10: result = registerFile[R2] + imm ;break;
        case 11: result = registerFile[R2] + imm; break;
        default: break;
    }
    final[0] = result;
    final[1] = R1;
    final[2] = opcode;
    final[3] = N;
    return final;
    
}

int* MEM(int* final){
    int x = 0;
    int opcode = final[2];  
    int R1 = final[1];
    int result = final[0];
    int N = final[3];
    int* final2 = malloc(4* sizeof(int));
    switch (opcode)
    {
    case 10:
        x = instructionMemory[result+1024]; //we ADD 1024 as first 1024 places are for instructions only while the rest is for data
        result = x;break;
    case 11:
        instructionMemory[result+1024] = registerFile[R1]; 
        printf(RED"CHANGE: Mem[%d] = %d \n"RESET, result, registerFile[R1]);break;
    default:
        break;
    }
    final2[0] = result;
    final2[1] = R1;
    final2[2] = opcode;
    final2[3] = N;
    return final2;
}

int WB(int* final2){
    int opcode = final2[2];  
    int R1 = final2[1];
    int result = final2[0];
    int N = final2[3];
    if(opcode == 4 || opcode == 7 || opcode == 11 || R1 == 0){ //we make sure that R0 is always 0
        return N;
    }else{
        registerFile[R1] = result;
        printf(RED"CHANGE: R%d = %d \n"RESET, R1, result);
        return N;
    }
}


int main() {
    int clkCycle = 1;   //initialize clock cycles
    int numberInstructions = RetrieveInstruction(); //we call the first method to read text file and put instructions in memmory
    int cycles = 7 + ((numberInstructions - 1) * 2); //for reference only, it is never used
    int* arr = malloc(2 * sizeof(int32_t)); //fecth output
    memset(arr, 0, 2 * sizeof(int32_t));
    int d = 1;
    int x = 1;
    int* alu = malloc(8 * sizeof(int));     //decode output
    memset(alu, -1, 8 * sizeof(int));
    int R1 = 0;
    int result = -10110;    
    int opcode = 0;
    int* final = malloc(4 * sizeof(int));   // execute output
    final[0] = -10110;
    int* final2 = malloc(4 * sizeof(int));  // MEM output
    final2[0] = -10110;
    int instN = 0;  //variable to know when to stop fetching
    int ExN = 0;    //variable to know when to stop executing
    int DeN = 0;    //variable to know when to stop decoding

    while(1){
        printf(GREEN"Cycle %d \n"RESET, clkCycle);
        if(flush == 1){
            printf(RED"There is a flush and new PC is %d.\n"RESET, pc);
            arr[0] = 0;
            d = 1;
            x = 1;
            flush = 0;
        }
        /*if(pcOLD!= -1){
            printf("there is a flush and new PC is %d:\n", pc);
            pcOLD = -1;
            flush = 1;
        }*/
        if(clkCycle % 2 == 1){
            if(final2[0]!= -10110){ //we check if mem output is initialized as if there is something to writeBack
                int N = WB(final2);
                printf(BLUE"WriteBack(Instructon %d):"RESET" IN (Opcode = %d, Register = R%d , value = %d) \n",N, final2[2], final2[1], final2[0]);
                if(N == numberInstructions){
                    break;
                }
            }
        }else{
            if(final[0]!= -10110){
                final2 = MEM(final);
                printf(BLUE"MEM(Instruction %d):"RESET" IN (Opcode = %d, Register = R%d, Location = %d), OUT(Opcode = %d, Register = R%d, Retrieved value = R%d) \n",final2[3], final[2], final[1], final[0], final2[2],final2[1],final2[0]);
            }
        }
        if(alu[0]!= -1 && ExN < numberInstructions){ //we check if we executed all instructions and should stop executing
            if(x == 2){
                final = Execute(alu);
                printf(BLUE"Execute(Instruction %d):"RESET" OUT (result = %d, Flush flag = %d), IN (R1 = %d, R2 = %d, R3 = %d, shamt = %d, immediate = %d, address = %d, and opcode = %d) \n",final[3], final[0],flush, alu[0], alu[1], alu[2], alu[3], alu[4], alu[5], alu[6]);
                ExN = final[3];
                x = 1;
            }else{
                x = x + 1;
                printf(BLUE"Execute(Instruction %d):"RESET" IN (R1 = %d, R2 = %d, R3 = %d, shamt = %d, immediate = %d, address = %d, and opcode = %d) \n",alu[7], alu[0], alu[1], alu[2], alu[3], alu[4], alu[5], alu[6]);
            }
        }
        if(arr[0]!= 0 && DeN < numberInstructions){
            if(flush == 1){ //we check if the flush flag is true we make decode input = 0
                arr[0] = 0b00000000000000000000000000000000;
            }
            if(d == 2){ //we check if this is the second cycle of decoding as it takes 2 cycles
                alu = decode(arr);
                DeN = alu[7];
                printf(BLUE"Decode(Instruction %d):"RESET" IN (instruction = %d), OUT (R1 = %d, R2 = %d, R3 = %d, shamt = %d, immediate = %d, address = %d, and opcode = %d) \n",alu[7], arr[0], alu[0], alu[1], alu[2], alu[3], alu[4], alu[5], alu[6]);
                d = 1;
            }else{
                d = d + 1;
                printf(BLUE"Decode(Instruction %d):"RESET" IN (instruction = %d) \n",arr[1], arr[0]);

            }
        }
        if(clkCycle % 2 == 1 && instN < numberInstructions){
            if(flush == 0){ //we check flush flag if it is true (1) we skip fetching
                arr = fetch();
                instN = arr[1];
            }
            printf(BLUE"Fetch(Instruction %d):"RESET" OUT (Instruction = %d) \n",arr[1], arr[0]);
        }

        clkCycle = clkCycle + 1;
    }

    for (int i = 0; i < 32; i++) //we print all registers
    {
        printf("R%d = %d \n", i, registerFile[i]);
    }
    
    printf("PC = %d \n", pc);
    
    return 0;
}