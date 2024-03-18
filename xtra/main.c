#include <stdio.h>
#include "xis.h"

void translateInstruction(unsigned char opcode, unsigned char operand);
void printPrologue();
void printEpilogue();

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("No files specified\n");
        return 1;
    }

        FILE *inputFile = fopen(argv[1], "rb");
        if (inputFile == NULL) {
            printf("Input file could not be opened: %s\n", argv[1]);
            return 1;
        }

        unsigned short length;
    //Storing opcode and operand
        unsigned char opcode = 0;
        unsigned char operand = 0;
        unsigned short stoppingCondition;
        printPrologue();
        do {
            //To Read opcode and operand from file
            length = fread(&opcode, 1, 1, inputFile);
            if (length == 1) {
                length = fread(&operand, 1, 1, inputFile);
                if (length == 1) {
                    translateInstruction(opcode, operand); //Calling function
                } else {
                    printf("Error reading operand\n");
                    break;
                }
            } else {
                printf("Error reading opcode\n");
                break;
            }
            stoppingCondition = (opcode|operand);
            fflush(stdout);
        } while (stoppingCondition != 0);

        fclose(inputFile);
        printEpilogue();

    return 0;
}
