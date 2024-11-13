/*
Adwaith Raj
S5 CS
Roll No.5
Experiment No. 4

                             PASS 1 of PASS 2 ASSEMBLER
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[3];
    int locctr, start, length;
    FILE *fp1, *fp2, *fp3, *fp4;
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtbl.txt", "w");
    fp4 = fopen("output.txt", "w");
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL) {
        printf("Error opening file(s)\n");
        exit(1);
    }
    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = strtoul(operand, NULL, 16);
        locctr = start;
        fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }
    while (strcmp(opcode, "END") != 0) {
        fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%X\n", label, locctr);
        }
        int found = 0;
        rewind(fp2);
        while (fscanf(fp2, "%s\t%s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += (3 * atoi(operand));
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'X')
                    locctr += (strlen(operand) - 3) / 2;
                else if (operand[0] == 'C')
                    locctr += strlen(operand) - 3;
            }
        }
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(fp4, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;
    printf("Length of the code: %d\n", length);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}
