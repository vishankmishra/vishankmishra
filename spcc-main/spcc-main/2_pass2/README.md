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

