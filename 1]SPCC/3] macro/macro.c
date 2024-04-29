//3. Two Pass Macro Processor.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct mdt
{
char lab[10];
char opc[10];
char oper[10];
} d[10];

int main()
{
char label[10], opcode[10], operand[10];
char macroname[10];
int i, lines = 0, count = 1;
FILE *f1, *f2, *f3, *f4;
f1 = fopen("MACIN.txt", "r");
f2 = fopen("MACOUT.txt", "w");
f3 = fopen("MDT.txt", "w");
f4 = fopen("MNT.txt", "w");
if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL)
{
perror("Error opening files");
return 1;
}
while (fscanf(f1, "%s %s %s", label, opcode, operand) != EOF)
{
if (strcmp(opcode, "END") == 0)
break;
if (strcmp(opcode, "MACRO") == 0)
{
strcpy(macroname, label);
fprintf(f4, "%s\t%d\n", macroname, count);
lines = 0;
while (fscanf(f1, "%s %s %s", label, opcode, operand) != EOF)
{
if (strcmp(opcode, "MEND") == 0)
break;
fprintf(f3, "%d\t%s\t%s\t%s\n", count, label, opcode, operand);
strcpy(d[lines].lab, label);
strcpy(d[lines].opc, opcode);
strcpy(d[lines].oper, operand);
lines++;
count++;
}
}
else if (strcmp(opcode, macroname) == 0)
{
for (i = 0; i < lines; i++)
fprintf(f2, "%s\t%s\t%s\n", d[i].lab, d[i].opc, d[i].oper);
}
else
{
fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);
}
}
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
printf("FINISHED\n");
return 0;
}