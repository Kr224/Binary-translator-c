//
// Created by Karishni Gupta on 2024-03-11.
//
#include <stdio.h>
#include "xis.h"

///Function to translate X instruction to x86-64 assembly
void translateInstruction(FILE *inputFile) {
    //Array to store x86 register names
    char *x86_registers[XIS_REGS] = {"rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8",
                                     "r9", "r10", "r11", "r12", "r13", "r14", "r15", "rbp", "rsp"};
    unsigned short length;
    unsigned int opcode = 0;
    unsigned int registers = 0;
    do {
        //To Read opcode from file
        length = fread(&opcode, 1, 1, inputFile);
        if (length == 1) {
            length = fread(&registers, 1, 1, inputFile);
            if (length == 1) {
                //Extract first 2 bits of the opcode to check the type
                int optype = (opcode & 0xC0) >> 6;
                printf("  ");

                if (optype == 0x00) { //0-operand instructions
                    switch (opcode) {  //match instruction with identifier and print
                        case I_RET:
                            printf("ret\n");
                            break;
                        case I_CLD:
                            printf("call debug\n");
                            break;
                        case I_STD:
                            printf("  call debug\n");
                            break;
                        case I_CLI:
                            printf("cli\n");
                            break;
                        case I_STI:
                            printf("sti\n");
                            break;
                        default:
                            //printf("Unknown instruction\n");
                            break;
                    }

                } else if (optype == 0x01) { //1-operand instructions
                    int thirdBit = (opcode & 0x20)>>6; //Extract 3rd bit to see if register or immediate value

                    switch (opcode) {  //match instruction with identifier and print
                        case I_NEG:
                            printf("  neg ");
                            break;
                        case I_NOT:
                            printf("not ");
                            break;
                        case I_INC:
                            printf("  inc ");
                            break;
                        case I_DEC:
                            printf("dec ");
                            break;
                        case I_PUSH:
                            printf("push ");
                            break;
                        case I_POP:
                            printf("pop ");
                            break;
                        case I_OUT:
                            printf("out ");
                            break;
                        case I_JMPR:
                            printf("jmpr ");
                            break;
                        case I_CALLR:
                            printf("callr ");
                            break;
                        case I_CPUID:
                            printf("cpuid ");
                            break;
                        case I_CPUNUM:
                            printf("cpunum ");
                            break;
                        default:
                            printf("Unknown instruction ");
                            break;
                    }

                    //opcode = opcode >> 5; //Shift right by 5 to fulfill next conditions

                    if (thirdBit == 0) { //If 0 then register
                        // Extract the four most significant bits of the second byte
                        int fourBitsOfSecondByte = (registers & 0xF0)>>4;
                        printf("%%%s\n", x86_registers[fourBitsOfSecondByte]); //Register operand

                    } else { //If 1 then immediate value
                        int secondByte = opcode & 0xFF;
                        printf("$%d\n", secondByte & ~XIS_1_IMED);
                    }

                } else if (optype == 0x02) { //2-operand instructions

                    switch (opcode) {  //match instruction with identifier and print
                        case I_ADD:
                            printf("  add ");
                            break;
                        case I_SUB:
                            printf("sub ");
                            break;
                        case I_MUL:
                            printf("  imul ");
                            break;
                        case I_DIV:
                            printf("div ");
                            break;
                        case I_AND:
                            printf("and ");
                            break;
                        case I_OR:
                            printf("or ");
                            break;
                        case I_XOR:
                            printf("xor ");
                            break;
                        case I_TEST:
                            printf("test ");
                            break;
                        case I_CMP:
                            printf("cmp ");
                            break;
                        case I_EQU:
                            printf("equ ");
                            break;
                        case I_MOV:
                            printf("  mov ");
                            break;
                        default:
                            printf("Unknown instruction ");
                            break;
                    }
                    // Extract register operands
                    //opcode = opcode >> 8; //Shift to next byte
                    int reg1 = XIS_REG1(registers);
                    int reg2 = XIS_REG2(registers);
                    printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);

                } else if (optype == 0x03) { //extended instructions
                    int thirdBit = opcode & 0x20; //Extract 3rd bit to see if register used
                    int immediateValue = 0;

                    switch (opcode) {
                        case I_JMP:
                            printf("jmp ");
                            fread(&immediateValue, 2, 1, inputFile);
                            break;
                        case I_CALL:
                            printf("call ");
                            fread(&immediateValue, 2, 1, inputFile);
                            break;
                        case I_LOADI:
                            printf("  mov ");
                            fread(&immediateValue, 1, 1, inputFile);
                            immediateValue = immediateValue << 8;
                            fread(&immediateValue, 1, 1, inputFile);
                            break;
                        default:
                            printf("Unknown instruction ");
                            break;
                    }

                    if (thirdBit == 0) { //Immediate value
                        int secondByte = opcode & 0xFF;
                        printf("$%d\n", immediateValue & XIS_1_IMED);
                    } else { //Register operand
                        // Extract the four most significant bits of the second byte
                        int fourBitsOfSecondByte = (registers & 0xF0)>>4;
                        printf("$%d, %%%s\n",immediateValue, x86_registers[fourBitsOfSecondByte]); //Register operand
                    }
                }
            } else {
                printf("Error reading opcode\n");
                break;
            }
            fflush(stdout);
        }
    } while ((opcode|registers)!= 0);
}







