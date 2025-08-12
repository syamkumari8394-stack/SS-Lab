#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char opcode[32], operand[64], label[64], code[32];
    int locctr = 0, start = 0, length = 0;

    FILE *inp = NULL, *symtab = NULL, *optab = NULL, *inter = NULL, *leng = NULL;

    // Open all necessary files for reading or writing
    inp = fopen("input.txt", "r");
    symtab = fopen("symtab.txt", "w");
    optab = fopen("optab.txt", "r");
    inter = fopen("intermediate.txt", "w");
    leng = fopen("length.txt", "w");

    if (!inp || !symtab || !optab || !inter || !leng) {
        fprintf(stderr, "Error: Could not open one or more files.\n");
        if (inp) fclose(inp);
        if (symtab) fclose(symtab);
        if (optab) fclose(optab);
        if (inter) fclose(inter);
        if (leng) fclose(leng);
        return 1;
    }

    // Read first line from input file
    if (fscanf(inp, "%63s %31s %63s", label, opcode, operand) != 3) {
        fprintf(stderr, "Error: input.txt is empty or malformed.\n");
        goto cleanup;
    }

    // Check if program starts with START directive
    if (strcmp(opcode, "START") == 0) {
        locctr = (int)strtol(operand, NULL, 0); // Set starting address
        start = locctr;
        fprintf(inter, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // Read next source line after START
        if (fscanf(inp, "%63s %31s %63s", label, opcode, operand) != 3) {
            fprintf(stderr, "Error: No program after START.\n");
            goto cleanup;
        }
    } else {
        // No START directive, start locctr at 0
        start = 0;
        locctr = 0;
    }

    // Process each line until END directive is found
    while (strcmp(opcode, "END") != 0) {
        fprintf(inter, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // If label is not "~", add it to symbol table with current locctr
        if (strcmp(label, "~") != 0) {
            fprintf(symtab, "%s\t%d\n", label, locctr);
        }

        // Search opcode in optab to find instruction size
        rewind(optab);
        int found = 0;
        while (fscanf(optab, "%31s", code) == 1) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3; // Instruction size assumed to be 3 bytes
                found = 1;
                break;
            }
            // Skip the rest of the line in optab
            int c;
            while ((c = fgetc(optab)) != '\n' && c != EOF) { }
        }

        // If opcode not found in optab, handle assembler directives
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                // Calculate byte length for C'...' or X'...'
                if (operand[0] == 'C' && operand[1] == '\'') {
                    size_t len = strlen(operand);
                    if (len >= 3) locctr += (int)(len - 3);
                } else if (operand[0] == 'X' && operand[1] == '\'') {
                    size_t len = strlen(operand);
                    if (len >= 3) locctr += (int)((len - 3 + 1) / 2);
                } else {
                    locctr += 1; // Default 1 byte if format unknown
                }
            }
            // Unknown opcodes are ignored for locctr increment
        }

        // Read next line from input file
        if (fscanf(inp, "%63s %31s %63s", label, opcode, operand) != 3) {
            fprintf(stderr, "Error: Unexpected end of file or malformed line in input.txt\n");
            goto cleanup;
        }
    }

    // Write END line to intermediate file
    fprintf(inter, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    // Calculate program length and write to file and console
    length = locctr - start;
    printf("\nProgram size: %d\n", length);
    fprintf(leng, "%d\n", length);

cleanup:
    fclose(leng);
    fclose(inp);
    fclose(optab);
    fclose(symtab);
    fclose(inter);

    return 0;
}
