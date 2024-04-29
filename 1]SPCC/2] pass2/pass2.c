//2. Pass two of Two Pass Assembler.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
FILE *f1, *f2, *f3, *f4;
char ch[100], chp[100];
int addr = 1000;
f1 = fopen("input1.txt", "r");
f2 = fopen("optab1.txt", "r");
f3 = fopen("littab2.txt", "w");
f4 = fopen("symtab2.txt", "w");
while (fscanf(f1, "%s", ch) != EOF)
{
if (strcmp(ch, "-") == 0)
{
addr++;
}
if (strcmp(ch, "db") == 0)
{
fprintf(f4, "%s\t%d\n", chp, 			addr);
}
if (strcmp(chp, "LTORG") == 0)
{
fprintf(f3, "%s\t%d\n", ch, 			addr);
}
strcpy(chp, ch);
}
fclose(f4);
fclose(f3);
fclose(f2);
fclose(f1);
}