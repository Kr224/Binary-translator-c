#include <stdio.h>
#include "xis.h"
//
// Created by Karishni Gupta on 2024-03-11.
//


//void printPrologue() {
//    printf(".globl test\ntest:\npush %rbp\nmov %rsp, %rbp\n"); // Output prologue
//}
//
////Function to translate X instruction to x86-64 assembly
//void translateInstruction(unsigned int opcode, unsigned int operand) {
//
//    //Array to store x86 register names
//    char *x86_registers[XIS_REGS] = {"%rax","%rbx","%rcx","%rdx","%rsi","%rdi","%r8",
//                                     "%r9","%r10","%r11","%r12","%r13","%r14","%r15","%rbp","%rsp"};
//
//    //Extract first 2 bits of the opcode to check the type
//    //int optype = (opcode & 0x60) >> 5;
//    int optype = opcode & 0x3;
//
//    if (optype == 0x00) { //0-operand instructions
//        //Extract the next 6-bits to match instruction
//        opcode = opcode >> 2; //Right shift by 2 bits
//        int identifier = opcode & 0x3F; //Extraction complete of next 6 bits
//        switch (identifier) {  //match instruction with identifier and print
//            case I_RET:
//                printf("ret\n");
//                break;
//            case I_CLD:
//                printf("cld\n");
//                break;
//            case I_STD:
//                printf("std\n");
//                break;
//            case I_CLI:
//                printf("cli\n");
//                break;
//            case I_STI:
//                printf("sti\n");
//                break;
//            default:
//                printf("Unknown instruction\n");
//                break;
//        }
//
//    } else if (optype == 0x01) { //1-operand instructions
//        opcode = opcode >> 2; //Right shift by 2 bits
//        int thirdBit = opcode & 0x1; //Extract 3rd bit to see if register or immediate value
//        opcode = opcode >> 1; //Shift 1 right
//        int nextFiveBits = opcode & 0x1F; //Extract next 5 bits
//
//            switch (nextFiveBits) {  //match instruction with identifier and print
//                case I_NEG:
//                    printf("neg\n");
//                    break;
//                case I_NOT:
//                    printf("not\n");
//                    break;
//                case I_INC:
//                    printf("inc\n");
//                    break;
//                case I_DEC:
//                    printf("cli\n");
//                    break;
//                case I_PUSH:
//                    printf("push\n");
//                    break;
//                case I_POP:
//                    printf("pop\n");
//                    break;
//                case I_OUT:
//                    printf("push\n");
//                    break;
//                case I_JMPR:
//                    printf("jmpr\n");
//                    break;
//                case I_CALLR:
//                    printf("callr\n");
//                    break;
//                case I_CPUID:
//                    printf("cpuid\n");
//                    break;
//                case I_CPUNUM:
//                    printf("cpunum\n");
//                    break;
//                default:
//                    printf("Unknown instruction\n");
//                    break;
//            }
//
//        opcode = opcode >> 5; //Shift right by 5 to fulfill next conditions
//
//        if (thirdBit == 0) { //If 0 then register
//            // Extract the four most significant bits of the second byte
//            int fourBitsOfSecondByte = opcode & 0xF;
//            printf("%%%s\n", x86_registers[fourBitsOfSecondByte]); //Register operand
//
//        } else if (thirdBit == 1) { //If 1 then immediate value
//            int secondByte = opcode & 0xFF;
//            printf("$%d\n", secondByte & ~XIS_1_IMED);
//        }
//
//    } else if (optype == 0x02) { //2-operand instructions
//        opcode = opcode >> 2; //Right shift by 2 bits
//        int nextSixBits = opcode & 0x3F; //Extraction complete of next 6 bits
//        switch (nextSixBits) {  //match instruction with identifier and print
//            case I_ADD:
//                printf("add\n");
//                break;
//            case I_SUB:
//                printf("sub\n");
//                break;
//            case I_MUL:
//                printf("mul\n");
//                break;
//            case I_DIV:
//                printf("div\n");
//                break;
//            case I_AND:
//                printf("and\n");
//                break;
//            case I_OR:
//                printf("or\n");
//                break;
//            case I_XOR:
//                printf("xor\n");
//                break;
//            case I_TEST:
//                printf("test\n");
//                break;
//            case I_CMP:
//                printf("cmp\n");
//                break;
//            case I_EQU:
//                printf("equ\n");
//                break;
//            case I_MOV:
//                printf("mov\n");
//                break;
//            default:
//                printf("Unknown instruction\n");
//                break;
//        }
//        // Extract register operands
//            opcode = opcode >> 6; //Shift to next byte
//            int reg1 = XIS_REG1(opcode);
//            int reg2 = XIS_REG2(opcode);
//            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
//
//    } else  if (optype == 0x03) { //extended instructions
//        int thirdBit = opcode & 0x20; //Extract 3rd bit to see if register used
//        opcode = opcode >> 1; //Shift 1 right
//        int nextFiveBits = opcode & 0x1F; //Extract next 5 bits
//
//        switch (nextFiveBits) {
//            case I_JMP:
//                printf("jmp\n");
//                break;
//            case I_CALL:
//                printf("call\n");
//                break;
//            case I_LOADI:
//                printf("loadi\n");
//                break;
//            default:
//                printf("Unknown instruction\n");
//                break;
//        }
//
//        if (thirdBit == 0) { //Immediate value
//            int secondByte = opcode & 0xFF;
//            printf("$%d\n", secondByte & ~XIS_1_IMED);
//        } else if (thirdBit == 1) { //Register operand
//            // Extract the four most significant bits of the second byte
//            int fourBitsOfSecondByte = opcode & 0xF;
//            printf("%%%s\n", x86_registers[fourBitsOfSecondByte]); //Register operand
//        }
//    }
//}
//
//void printEpilogue() { // Output epilogue
//    printf("pop %rbp\n");
//    printf("ret");
//}

void printPrologue() {
    printf(".globl test\ntest:\npush %rbp\nmov %rsp, %rbp\n"); // Output prologue
}

//Function to translate X instruction to x86-64 assembly
void translateInstruction(int opcode, int operand) {

    //Array to store x86 register names
    char *x86_registers[XIS_REGS] = {"%rax","%rbx","%rcx","%rdx","%rsi","%rdi","%r8",
                                     "%r9","%r10","%r11","%r12","%r13","%r14","%r15","%rbp","%rsp"};

    //Extract first 2 bits of the opcode to check the type
    //int optype = (opcode & 0x60) >> 5;
    int optype = opcode & 0x3;

    if (optype == 0x00) { //0-operand instructions
        //Extract the next 6-bits to match instruction
        opcode = opcode >> 2; //Right shift by 2 bits
        int identifier = opcode & 0x3F; //Extraction complete of next 6 bits
        switch (identifier) {  //match instruction with identifier and print
            case I_RET:
                printf("ret\n");
                break;
            case I_CLD:
                printf("call debug\n");
                break;
            case I_STD:
                printf("call debug\n");
                break;
            case I_CLI:
                printf("cli\n");
                break;
            case I_STI:
                printf("sti\n");
                break;
            default:
                printf("Unknown instruction\n");
                break;
        }

    } else if (optype == 0x01) { //1-operand instructions
        opcode = opcode >> 2; //Right shift by 2 bits
        int thirdBit = opcode & 0x1; //Extract 3rd bit to see if register or immediate value
        opcode = opcode >> 1; //Shift 1 right
        int nextFiveBits = opcode & 0x1F; //Extract next 5 bits

        switch (nextFiveBits) {  //match instruction with identifier and print
            case I_NEG:
                printf("neg\n");
                break;
            case I_NOT:
                printf("not\n");
                break;
            case I_INC:
                printf("inc\n");
                break;
            case I_DEC:
                printf("cli\n");
                break;
            case I_PUSH:
                printf("push\n");
                break;
            case I_POP:
                printf("pop\n");
                break;
            case I_OUT:
                printf("push\n");
                break;
            case I_JMPR:
                printf("jmpr\n");
                break;
            case I_CALLR:
                printf("callr\n");
                break;
            case I_CPUID:
                printf("cpuid\n");
                break;
            case I_CPUNUM:
                printf("cpunum\n");
                break;
            default:
                printf("Unknown instruction\n");
                break;
        }

        opcode = opcode >> 5; //Shift right by 5 to fulfill next conditions

        if (thirdBit == 0) { //If 0 then register
            // Extract the four most significant bits of the second byte
            int fourBitsOfSecondByte = opcode & 0xF;
            printf("%%%s\n", x86_registers[fourBitsOfSecondByte]); //Register operand

        } else if (thirdBit == 1) { //If 1 then immediate value
            int secondByte = opcode & 0xFF;
            printf("$%d\n", secondByte & ~XIS_1_IMED);
        }

    } else if (optype == 0x02) { //2-operand instructions
        opcode = opcode >> 2; //Right shift by 2 bits
        int nextSixBits = opcode & 0x3F; //Extraction complete of next 6 bits
        switch (nextSixBits) {  //match instruction with identifier and print
            case I_ADD:
                printf("add\n");
                break;
            case I_SUB:
                printf("sub\n");
                break;
            case I_MUL:
                printf("imul\n");
                break;
            case I_DIV:
                printf("div\n");
                break;
            case I_AND:
                printf("and\n");
                break;
            case I_OR:
                printf("or\n");
                break;
            case I_XOR:
                printf("xor\n");
                break;
            case I_TEST:
                printf("test\n");
                break;
            case I_CMP:
                printf("cmp\n");
                break;
            case I_EQU:
                printf("equ\n");
                break;
            case I_MOV:
                printf("mov\n");
                break;
            default:
                printf("Unknown instruction\n");
                break;
        }
        // Extract register operands
        opcode = opcode >> 6; //Shift to next byte
        int reg1 = XIS_REG1(opcode);
        int reg2 = XIS_REG2(opcode);
        printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);

    } else  if (optype == 0x03) { //extended instructions
        int thirdBit = opcode & 0x20; //Extract 3rd bit to see if register used
        opcode = opcode >> 1; //Shift 1 right
        int nextFiveBits = opcode & 0x1F; //Extract next 5 bits

        switch (nextFiveBits) {
            case I_JMP:
                printf("jmp\n");
                break;
            case I_CALL:
                printf("call\n");
                break;
            case I_LOADI:
                printf("mov\n");
                break;
            default:
                printf("Unknown instruction\n");
                break;
        }

        if (thirdBit == 0) { //Immediate value
            int secondByte = opcode & 0xFF;
            printf("$%d\n", secondByte & ~XIS_1_IMED);
        } else if (thirdBit == 1) { //Register operand
            // Extract the four most significant bits of the second byte
            int fourBitsOfSecondByte = opcode & 0xF;
            printf("%%%s\n", x86_registers[fourBitsOfSecondByte]); //Register operand
        }
    }
}

void printEpilogue() { // Output epilogue
    printf("pop %rbp\n");
    printf("ret");
}


