#include <stdio.h>
#include "xis.h"
//
// Created by Karishni Gupta on 2024-03-11.
//

void printPrologue() {
    printf(".text\n.globl _start\n_start:\n"); // Output prologue
}

//Function to translate X instruction to x86-64 assembly
void translateInstruction(unsigned char opcode, unsigned char operand) {

    //Array to store register names
    char *x86_registers[XIS_REGS] = {"%rax","%rbx","%rcx","%rdx","%rsi","%rdi","%r8",
    "%r9","%r10","%r11","%r12","%r13","%r14","%r15","%rbp","%rsp"};

    // Extract the opcode type and instruction identifier
    unsigned char op_type = (opcode >> 6) & 0x03;
    unsigned char op_num = opcode & 0x3F;

    // Switch based on opcode type
    switch (op_type) {
        case 0x00: // 0-operand instructions
            switch (op_num) {
                case I_RET:
                    printf("ret\n");
                    break;
                case I_CLD:
                    printf("cld\n");
                    break;
                case I_STD:
                    printf("std\n");
                    break;
                case I_CLI:
                    printf("cli\n");
                    break;
                case I_STI:
                    printf("sti\n");
                    break;
                case I_TRAP:
                    printf("trap\n");
                    break;
                default:
                    printf("Unknown instruction\n");
                    break;
            }
            break;

        case 0x01: // 1-operand instructions
            switch (op_num) {
                case I_NEG:
                    printf("neg ");
                    break;
                case I_NOT:
                    printf("not ");
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
                case I_OUT:
                    printf("out ");
                    break;
                case I_INC:
                    printf("inc ");
                    break;
                case I_DEC:
                    printf("dec ");
                    break;
                case I_LIT:
                    printf("lit ");
                    break;
                case I_CPUID:
                    printf("cpuid ");
                    break;
                case I_CPUNUM:
                    printf("cpunum ");
                    break;
                default:
                    printf("Unknown instruction\n");
                    break;
            }

            //Check if immediate or register operand
            if (operand & XIS_1_IMED) {
                printf("$%d\n", operand & ~XIS_1_IMED); // Immediate operand
            } else {
                printf("%%%s\n", x86_registers[operand]); // Register operand
            }
            break;

        case 0x02: // 2-operand instructions
            switch (op_num) {
                case I_ADD:
                    printf("add ");
                    break;
                case I_SUB:
                    printf("sub ");
                    break;
                case I_MUL:
                    printf("mul ");
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
                case I_SHR:
                    printf("shr ");
                    break;
                case I_SHL:
                    printf("shl ");
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
                    printf("mov ");
                    break;
                case I_STOR:
                    printf("test ");
                    break;
                case I_STORB:
                    printf("test ");
                    break;
                case I_LOADA:
                    printf("loada ");
                    break;
                case I_STORA:
                    printf("stora ");
                    break;
                case I_TNSET:
                    printf("tnset ");
                    break;
                case I_OUTP:
                    printf("outp ");
                    break;
                case I_INP:
                    printf("inp ");
                    break;
                case I_INPA:
                    printf("inpa ");
                    break;
                case I_SWAP:
                    printf("swap ");
                    break;
                case I_LOADI:
                    printf("loadi ");
                    break;
                default:
                    printf("Unknown instruction\n");
                    break;
            }
            //unsigned char reg1 = (operand >> 4) & 0x0F;
            //unsigned char reg2 = operand & 0x0F;
            // Extract register operands
            unsigned char reg1 = XIS_REG1(operand);
            unsigned char reg2 = XIS_REG2(operand);
            printf("%%%s, %%%s\n", x86_registers[reg1], x86_registers[reg2]);
            break;

        case 0x03: // Extended instructions
            switch (op_num) {
                case I_JMP:
                    printf("jmp ");
                    break;
                case I_CALL:
                    printf("call ");
                    break;
                default:
                    printf("Unknown instruction\n");
                    break;
            }
            //Check for immediate or register operand
            if (operand & XIS_X_REG) {
                printf("%%%s, ", x86_registers[operand & ~XIS_X_REG]); // Register operand
            } else {
                printf("$%d, ", operand); // Immediate operand
            }
//            // Additional operand for extended instructions
//            unsigned char second_operand;
//            fread(&second_operand, 1, 1, stdin);
//            printf("%%%s\n", x86_registers[second_operand]);
//            break;

        default:
            printf("Unknown instruction type\n");
            break;
    }
}

void printEpilogue() { // Output epilogue
    printf("movl $0, %%ebx\n");
    printf("movl $1, %%eax\n");
    printf("int $0x80\n");
}


