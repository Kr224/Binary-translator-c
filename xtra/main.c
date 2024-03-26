#include <stdio.h>
#include "xis.h"

void translateInstruction(FILE *inputFile);
void printPrologue() {
    printf(".globl test\ntest:\n    push %rbp\n    mov %rsp, %rbp\n");

}
void printEpilogue() {
    printf("  pop %rbp\n    ret\n");
}

int main(int argc, char **argv) {
    printPrologue();

    if (argc < 2) {
        printf("No files specified\n");
        return 1;
    }
    FILE *inputFile = fopen(argv[1], "rb");
    if (inputFile == NULL) {
        printf("Input file could not be opened: %s\n", argv[1]);
        return 1;
    }
    translateInstruction(inputFile);

    fclose(inputFile);
    printEpilogue();

    return 0;
}

