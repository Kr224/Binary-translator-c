#include <stdio.h>
#include "xis.h"
#include <stdbool.h>

///Function to translate X instruction to x86-64 assembly
void translateInstruction(FILE *inputFile) {
    //Array to store x86 register names
    char *x86_registers[XIS_REGS] = {"rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8",
                                     "r9", "r10", "r11", "r12", "r13", "r14", "r15", "rbp", "rsp"};
    unsigned short length;
    unsigned int opcode = 0;
    unsigned int registers = 0;
    bool debug = false;
    do {
        if (debug) {
            printf("  call debug\n");
        }

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
                            debug = false;
                            break;
                        case I_STD:
                            debug = true;
                            break;
                        case I_CLI:
                            printf("cli\n");
                            break;
                        case I_STI:
                            printf("sti\n");
                            break;
                    }

                } else if (optype == 0x01) { //1-operand instructions
                    int thirdBit = (opcode & 0x20) >> 6; //Extract 3rd bit to see if register or immediate value

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
                        case I_JMPR:
                            printf("jmpr ");
                            break;
                        case I_CALLR:
                            printf("callr ");
                            break;
                        case I_BR: //test and jne
                            printf("jne ");
                            break;
                        case I_JR: //add 2 to label
                            printf("j ");
                            break;
                        case I_OUT:
                            printf("call outchar\n");
                            break;
                    }

                    if (thirdBit == 0) { //If 0 then register
                        int fourBitsOfSecondByte = (registers & 0xF0) >> 4; // Extract the four most significant bits of the second byte
                        printf("%%%s\n", x86_registers[fourBitsOfSecondByte]); //Register operand
                    } else { //If 1 then immediate value
                        int secondByte = opcode & 0xFF;
                        printf("$%d\n", secondByte & ~XIS_1_IMED);
                    }

                } else if (optype == 0x02) { //2-operand instructions
                    int reg1 = XIS_REG1(registers);
                    int reg2 = XIS_REG2(registers);

                    switch (opcode) {  //match instruction with identifier and print
                        case I_ADD:
                            printf("  add ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_SUB:
                            printf("sub ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_MUL:
                            printf("  imul ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_DIV:
                            printf("div ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_AND:
                            printf("and ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_OR:
                            printf("or ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_XOR:
                            printf("xor ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_MOV:
                            printf("  mov ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_LOADB:
                            printf("movzx ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_STORB:
                            printf("mov ");
                            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            break;
                        case I_TEST:
                            printf("test %%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            printf("setnz %%r15b\n");
                            break;
                        case I_CMP:
                            printf("cmp %%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            printf("setg %%r15b\n");
                            break;
                        case I_EQU:
                            printf("cmp %%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
                            printf("setz %%r15b\n");
                            break;
                    }

                } else if (optype == 0x03) { //extended instructions
                    int thirdBit = opcode & 0x20; //Extract 3rd bit to see if register used
                    int immediateValue = 0;
                    bool isLabel; //To check if label is needed

                    switch (opcode) {
                        case I_JMP: //add 4
                            isLabel = true;
                            printf("jmp ");
                            fread(&immediateValue, 1, 1, inputFile);
                            immediateValue = immediateValue << 8;
                            fread(&immediateValue, 1, 1, inputFile);
                            break;
                        case I_CALL:
                            isLabel = true;
                            printf("call ");
                            fread(&immediateValue, 2, 1, inputFile);
                            break;
                        case I_LOADI:
                            isLabel = false;
                            printf("  mov ");
                            fread(&immediateValue, 1, 1, inputFile);
                            immediateValue = immediateValue << 8;
                            fread(&immediateValue, 1, 1, inputFile);
                            break;
                        case I_LOADB:
                            isLabel = false;
                            printf("movzx ");
                            break;
                        case I_STORB:
                            isLabel = false;
                            printf("mov ");
                            break;
                    }

                    if (isLabel == true) { //To print labels
                        printf(".L00%d\n", immediateValue);
                    } else {
                        if (thirdBit == 0) { //To print Immediate value
                            printf("$%d\n", immediateValue & XIS_1_IMED);
                        } else {
                            int fourBitsOfSecondByte = (registers & 0xF0) >> 4; // Extract the four most significant bits of the second byte
                            printf("$%d, %%%s\n",immediateValue, x86_registers[fourBitsOfSecondByte]); //Register operand
                        }
                    }
                }
            } else {
                printf("Error reading opcode\n");
                break;
            }
            fflush(stdout);
        }
    } while ((opcode|registers)!= 0); //stopping condition
}









