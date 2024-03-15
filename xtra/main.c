//#include <stdio.h>
//int main(int argc, char **argv) {
//
//    if (argc < 2) {
//        printf("No files specified\n");
//        return 1;
//    }
//
//    for (int i = 0; i < argc; i++) {
//        FILE *inputFile = fopen(argv[i], "rb");
//        if (inputFile == NULL) {
//            printf("Input file could not be opened: %s\n", argv[i]);
//            continue;
//        }
//
//        unsigned long length;
//        char buffer [100];
//        do {
//            length = fread(buffer,1,100,inputFile);
//            for (int j = 0; j < length; j++) {
//                putc(buffer[j],stdout);
//            }
//        } while (length == 100);
//        fclose(inputFile);
//    }
//
//    return 0;
//}
#include <stdio.h>
#include "xis.h"

void translateInstruction(unsigned char opcode, unsigned char operand);

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
        unsigned char opcode = 0;
        unsigned char operand = 0; //Storing opcode and operand
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
        } while (length == 100);

        fclose(inputFile);

    return 0;
}
