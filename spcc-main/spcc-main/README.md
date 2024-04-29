# SPCC 2023-2024 Notes

### Pass 1 of 2 pass assembler

1. pass1.c
```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
        FILE *f1,*f2,*f3,*f4;
        int lc,sa,l,op1,o,len;
        char m1[20],la[20],op[20],otp[20];
        f1=fopen("input.txt","r");
        f3=fopen("symtab.txt","w");
        fscanf(f1,"%s%s%d",la,m1,&op1);
        if(strcmp(m1,"START")==0)
        {
                sa=op1;
                lc=sa;
                printf("\t%s\t%s\t%d\n",la,m1,op1);
        }
        else
        {
                lc=0;
        }
        fscanf(f1,"%s%s",la,m1);
        while(!feof(f1))
        {
                fscanf(f1,"%s",op);
                printf("\n%d\t%s\t%s\t%s\n", lc, la, m1, op);
                if(strcmp(la,"-")!=0)
                {
                        fprintf(f3,"\n%d\t%s\n",lc,la);
                }
                f2=fopen("optab.txt","r");
                fscanf(f2,"%s%d",otp,&o);
                while(!feof(f2))
                {
                        if(strcmp(m1,otp)==0)
                        {
                                lc=lc+3;
                                break;
                        }
                        fscanf(f2,"%s%d",otp,&o);
                        }
                        fclose(f2);
                        if(strcmp(m1,"WORD")==0)
                        {
                                lc=lc+3;
                        }
                        else if(strcmp(m1,"RESW")==0)
                        {
                                op1=atoi(op);
                                lc=lc+(3*op1);
                        }
                        else if(strcmp(m1,"BYTE")==0)
                        {
                                if(op[0]=='X')
                                {
                                        lc=lc+1;
                                }
                                else
                                {
                                        len=strlen(op)-2;
                                        lc=lc+len;
                                }
                        }
                        else if(strcmp(m1,"RESB")==0)
                        {
                                op1=atoi(op);
                                lc=lc+op1;
                        }
                        fscanf(f1,"%s%s",la,m1);
                }
                if(strcmp(m1,"END")==0)
                {
                        printf("program length=\n%d",lc-sa);
                }
                fclose(f1);
                fclose(f3);
}
```
2. input.txt
```
**               START     2000
**                LDA      FIVE
**                STA      ALPHA
**                LDCH     CHARZ
**                STCH     C1
ALPHA             RESW     2
FIVE              WORD     5
CHARZ             BYTE     C 'Z'
C1                RESB     1
**                END      **
```
3. optab.txt
```
LDA 03
STA 0f
LDCH 53
STCH 57
END *
```
4. steps to run
```sh
gcc pass1.c -o pass1
```

```sh
pass1.exe
```

### Pass 2 of 2 pass assembler
1. pass2.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    FILE *f1,*f2,*f3,*f4;
    char ch[100],chp[100];
    int addr=1000;
    f1=fopen("input1.txt","r");
    f2=fopen("optab1.txt","r");
    f3=fopen("littab2.txt","w");
    f4=fopen("symtab2.txt","w");
    while (fscanf(f1,"%s",ch) !=EOF)
    {
        if(strcmp(ch,"-")==0)
        {
            addr++;
        }
        if(strcmp(ch,"db")==0)
        {
            fprintf(f4,"%s\t%d\n",chp,addr);
        }
        if(strcmp(chp,"LTORG")==0)
        {
            fprintf(f3,"%s\t%d\n",ch,addr);
        }
        strcpy(chp,ch);
    }
    fclose(f4);
    fclose(f3);
    fclose(f2);
    fclose(f1);
}
```
2. input1.txt
```
** START 2000
2000 ** LDA FIVE
2003 ** STA ALPHA
2006 ** LDCH CHARZ
2009 ** STCH
2012 ALPHA RESW
2018 FIVE WORD
2021 CHARZ BYTE Z
2023 C1 RESB
2024 ** END **
```
3. optab1.txt
```
LDA 03
LDA 0f
LDCH 53
STCH 57
END *
```
4. littab2.txt
```
1 Z 2018
```
5. symtab2.txt
```
2000 **
2003 **
2006 **
2009 **
2012 ALPHA
2018 FIVE
2021 CHARZ
2023 C1
2024 **
```
6. Steps to run
```sh
gcc pass2.c -o pass2
```

```
pass2.exe
```


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

### First() and Follow()
1. ff.c
```c
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int n,m=0,p,i=0,j=0;
char a[10][10],f[10];
void follow(char c);
void first(char c);
int main()
{
    int i,z;
    char c,ch;
    //clrscr();
    printf("Enter the no of productions:\n");
    scanf("%d",&n);
    printf("Enter the productions:\n");
    for(i=0;i<n;i++)
        scanf("%s%c",a[i],&ch);
    do
    {
        m=0;
        printf("Enter the elemets whose fisrt & follow is to be found:");
        scanf("%c",&c);
        first(c);
        printf("First(%c)={",c);
        for(i=0;i<m;i++)
            printf("%c",f[i]);
        printf("}\n");
        strcpy(f," ");
        //flushall();
        m=0;
        follow(c);
        printf("Follow(%c)={",c);
        for(i=0;i<m;i++)
            printf("%c",f[i]);
        printf("}\n");
        printf("Continue(0/1)?");
        scanf("%d%c",&z,&ch);
    }while(z==1);
    return(0);
}
void first(char c)
{
    int k;
    if(!isupper(c))
        f[m++]=c;
    for(k=0;k<n;k++)
    {
        if(a[k][0]==c)
        {
            if(a[k][2]=='$')
                follow(a[k][0]);
            else if(islower(a[k][2]))
                f[m++]=a[k][2];
            else 
                first(a[k][2]);
        }
    }
}
void follow(char c)
{
    if(a[0][0]==c)
        f[m++]='$';
    for(i=0;i<n;i++)
    {
        for(j=2;j<strlen(a[i]);j++)
        {
            if(a[i][j]==c)
            {
                if(a[i][j+1]!='\0')
                    first(a[i][j+1]);
                if(a[i][j+1]=='\0' && c!=a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}
```
2. input while running
```
S=AaBb
A=a
B=g
A=c
B=h
```

3. Steps to run
```sh
gcc ff.c -o ff
```

```
ff.exe
```

### Left factoring
1. leftfact.c
```c
#include<stdio.h>
#include<string.h>
int main()
{
    char gram[20],part1[20],part2[20],modifiedGram[20],newGram[20],tempGram[20];
    int i,j=0,k=0,l=0,pos;
    printf("Enter Production : A->");
    gets(gram);
    for(i=0;gram[i]!='|';i++,j++)
        part1[j]=gram[i];
    part1[j]='\0';
    for(j=++i,i=0;gram[j]!='\0';j++,i++)
        part2[i]=gram[j];
    part2[i]='\0';
    for(i=0;i<strlen(part1)||i<strlen(part2);i++){
        if(part1[i]==part2[i]){
            modifiedGram[k]=part1[i];
            k++;
            pos=i+1;
        }
    }
    for(i=pos,j=0;part1[i]!='\0';i++,j++){
        newGram[j]=part1[i];
    }
    newGram[j++]='|';
    for(i=pos;part2[i]!='\0';i++,j++){
        newGram[j]=part2[i];
    }
    modifiedGram[k]='X';
    modifiedGram[++k]='\0';
    newGram[j]='\0';
    printf("\nGrammar Without Left Factoring : : \n");
    printf(" A->%s",modifiedGram);
    printf("\n X->%s\n",newGram);
}
```

2. Input whilw running
```
aA|bB|aAB
```
3. Steps to run
```sh
gcc leftfact.c -o leftfact 
```

```
leftfact.exe
```

### Operator code precedence

1. opr.c
```c
#include <stdio.h>
#include <string.h>

void main() {
    char stack[20], ip[20], opt[10][10][2], ter[10];
    int i, j, k, n, top = 0, col, row;

    for (i = 0; i < 10; i++) {
        stack[i] = '\0'; // Use '\0' to represent null character
        ip[i] = '\0';
        for (j = 0; j < 10; j++) {
            opt[i][j][0] = '\0';
            opt[i][j][1] = '\0';
        }
    }

    printf("Enter the number of terminals: ");
    scanf("%d", &n);
    printf("\nEnter the terminals: ");
    scanf("%s", ter);

    printf("\nEnter the table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\nOPERATOR PRECEDENCE TABLE:\n");
    for (i = 0; i < n; i++) {
        printf("\t%c", ter[i]);
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++) {
            printf("\t%c", opt[i][j][0]);
        }
        printf("\n");
    }

    stack[top] = '$';
    printf("\nEnter the input string: ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, ip);
    
    while (i <= strlen(ip)) {
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k])
                col = k;
            if (ip[i] == ter[k])
                row = k;
        }

        if ((stack[top] == '$') && (ip[i] == '$')) {
            printf("String is accepted");
            break;
        } else if ((opt[col][row][0] == '<') || (opt[col][row][0] == '=')) {
            stack[++top] = opt[col][row][0];
            stack[++top] = ip[i];
            printf("Shift %c", ip[i]);
            i++;
        } else {
            if (opt[col][row][0] == '>') {
                while (stack[top] != '<') {
                    --top;
                }
                top = top - 1;
                printf("Reduce");
            } else {
                printf("\nString is not accepted");
                break;
            }
        }
        printf("\n");
        for (k = 0; k <= top; k++) {
            printf("%c", stack[k]);
        }
        printf("\t\t\t");
        for (k = i; k < strlen(ip); k++) {
            printf("%c", ip[k]);
        }
        printf("\t\t\t");
    }
}
```

2. Input while running
![alt text](/opr.png)

3. input string
```
i+i*i$
```
4. Steps to run
```sh
gcc opr.c -o opr
```

```sh
opr.exe
```

### Intermediate code generstion
1. icg.c
```c
#include<stdio.h>
#include<conio.h>
#include<string.h>
char op[2],arg1[5],arg2[5],result[5];
void main()
{
  FILE *fp1,*fp2;
  fp1=fopen("input.txt","r");
  fp2=fopen("output.txt","w");
  while(!feof(fp1))
  {

    fscanf(fp1,"%s%s%s%s",op,arg1,arg2,result);
    if(strcmp(op,"+")==0)
    {
      fprintf(fp2,"\nMOV R0,%s",arg1);
      fprintf(fp2,"\nADD R0,%s",arg2);
      fprintf(fp2,"\nMOV %s,R0",result);
    }
     if(strcmp(op,"*")==0)
    {
      fprintf(fp2,"\nMOV R0,%s",arg1);
      fprintf(fp2,"\nMUL R0,%s",arg2);
      fprintf(fp2,"\nMOV %s,R0",result);
    }
    if(strcmp(op,"-")==0)
    {
      fprintf(fp2,"\nMOV R0,%s",arg1);
      fprintf(fp2,"\nSUB R0,%s",arg2);
      fprintf(fp2,"\nMOV %s,R0",result);
    }
    if(strcmp(op,"/")==0)
    {
      fprintf(fp2,"\nMOV R0,%s",arg1);
      fprintf(fp2,"\nDIV R0,%s",arg2);
      fprintf(fp2,"\nMOV %s,R0",result);
    }
    if(strcmp(op,"=")==0)
    {
      fprintf(fp2,"\nMOV R0,%s",arg1);
      fprintf(fp2,"\nMOV %s,R0",result);
    }
    }
    fclose(fp1);
    fclose(fp2);
    // getch();
  }
```

2. input.txt
```
+ a b t1
* c d t2
- t1 t2 t
= t ? x
```
3. Steps to run
```sh
gcc icg.c -o icg
```

```
icg.exe
```

# Congrats! You passed SPCC
