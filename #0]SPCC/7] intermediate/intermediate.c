//7. Intermediate code Generator.✔️
#include <stdio.h>
#include <string.h>

char op[2], arg1[5], arg2[5], result[5];

int main() {
FILE *fp1, *fp2;
fp1 = fopen("input.txt", "r");
if (fp1 == NULL) {
printf("Error opening input file.\n");
return 1;
}
fp2 = fopen("output.txt", "w");
if (fp2 == NULL) {
printf("Error opening output file.\n");
fclose(fp1);
return 1;
}

printf("Intermediate Code Generation started...\n");

while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) == 4) {
if (strcmp(op, "+") == 0) {
fprintf(fp2, "MOV R0, %s\n", arg1);
fprintf(fp2, "ADD R0, %s\n", arg2);
fprintf(fp2, "MOV %s, R0\n", result);
} else if (strcmp(op, "*") == 0) {
fprintf(fp2, "MOV R0, %s\n", arg1);
fprintf(fp2, "MUL R0, %s\n", arg2);
fprintf(fp2, "MOV %s, R0\n", result);
} else if (strcmp(op, "-") == 0) {
fprintf(fp2, "MOV R0, %s\n", arg1);
fprintf(fp2, "SUB R0, %s\n", arg2);
fprintf(fp2, "MOV %s, R0\n", result);
} else if (strcmp(op, "/") == 0) {
fprintf(fp2, "MOV R0, %s\n", arg1);
fprintf(fp2, "DIV R0, %s\n", arg2);
fprintf(fp2, "MOV %s, R0\n", result);
} else if (strcmp(op, "=") == 0) {
fprintf(fp2, "MOV R0, %s\n", arg1);
fprintf(fp2, "MOV %s, R0\n", result);
} else {
printf("Invalid operation: %s\n", op);
}
}

printf("Intermediate Code Generation completed.\n");

fclose(fp1);
fclose(fp2);
return 0;
}