#include "../header/readfile.h"

int getNbLines(FILE * readFile)
{
    int c,count=0;
    do{
        c=getc(readFile);
        if(c == 0xa)
        {
            count++;
        }
    }while(c!=0xffffffff);
    return count+1;
}

char * getLines(FILE * readFile,int nbLines)
{
    int i;
    char str[100];
    fseek(readFile,0,0);
    for(i=0;i<nbLines;i++)
    {
        fgets(str,100,readFile);
        printf("%s",str);
    }
}