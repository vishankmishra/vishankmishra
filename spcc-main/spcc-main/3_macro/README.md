### 2 pass macro 

1. twopassmacro.c
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct for Macro Definition Table (MDT)
struct mdt {
    char lab[10];
    char opc[10];
    char oper[10];
};

// Corrected main function
int main() {
    char label[10], opcode[10], operand[10];
    char macroname[10];
    int i, lines = 0, count = 1;
    struct mdt d[10]; // Array of struct to hold macro definitions
    
    // Open files
    FILE *f1 = fopen("MACIN.txt", "r");
    FILE *f2 = fopen("MACOUT.txt", "w");
    FILE *f3 = fopen("MDT.txt", "w");
    FILE *f4 = fopen("MNT.txt", "w");
    
    // Check if files are opened correctly
    if (!f1 || !f2 || !f3 || !f4) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read the first instruction
    fscanf(f1, "%s %s %s", label, opcode, operand);

    // Main loop to process the input
    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "MACRO") == 0) {
            // Start of a macro definition
            strcpy(macroname, label);
            fprintf(f4, "%s\t%d\n", macroname, count);

            fscanf(f1, "%s %s %s", label, opcode, operand); // Move to the next line
            lines = 0;

            // Capture macro definition into MDT
            while (strcmp(opcode, "MEND") != 0) {
                fprintf(f3, "%d\t%s\t%s\t%s\n", count, label, opcode, operand);

                strcpy(d[lines].lab, label);
                strcpy(d[lines].opc, opcode);
                strcpy(d[lines].oper, operand);
                lines++;
                count++;

                fscanf(f1, "%s %s %s", label, opcode, operand); // Next line
            }
        } else if (strcmp(opcode, macroname) == 0) {
            // Macro expansion
            for (i = 0; i < lines; i++) {
                fprintf(f2, "%s\t%s\t%s\n", d[i].lab, d[i].opc, d[i].oper);
            }
        } else {
            fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);
        }

        fscanf(f1, "%s %s %s", label, opcode, operand); // Move to the next line
    }

    // Write the "END" line to the output file
    fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);

    // Close files
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    printf("FINISHED\n");
    
    return 0; // Proper exit code for main
}
```
2. MACIN.txt
```
CALC START 1000
SUM MACRO **
** LDA #5
** ADD #10
** sTa 2000
** MEND **
** LDA LENGTH 
** COMP ZERO
** JEQ LOOP
** SUM **
LENGTH WORD S
ZERO WORD S
LOOP SUM **
** END **
```
3. Steps to run
```sh
gcc twopassmacro.c -o twopassmacro
```

```sh
twopassmacro.exe
```
