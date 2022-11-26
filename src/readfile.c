#include "../header/readfile.h"
#define MAXLINE 50

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

void getStringFromFile(FILE * readFile,int nbLines,char * returnString,int * size)
{
    int i;
    char temp[MAXLINE];
    *size=0;
    strcpy(returnString,"");
    fseek(readFile,0,0);
    for(i=0;i<nbLines;i++)
    {
        fgets(temp,100,readFile);
        *size+=strlen(temp);
        strcat(returnString,temp);
    }
}

int getFileSize(FILE * readFile)
{
    fseek(readFile,0,2);
    int returnValue = ftell(readFile);
    fseek(readFile,0,0);
    return returnValue;
}

/**
 * @brief Debug uniquement : récupère une ligne, non optimisé donc inutilisable
 * 
 * @param string la chaîne de caractère à analyser
 * @param line int la ligne à récupérer
 * @return char* la ligne sous un string
 */
char * getLine(char * string,int line)
{
    int j=0,k=0;
    char * returnString = (char *)(malloc(MAXLINE*sizeof(char)));
    for(int i=0;i<line;i++)
    {
        k=0;
        strcpy(returnString,"");
        while(*(string+j) != '\n')
        {
            *(returnString+k)=*(string+j);
            j++;
            k++;
        }
        j++;
    }
    *(returnString+k)='\0';
    return returnString;
}

void string2Coureur(char * string,int nbLines)
{
    int j=0;
    for(int i=3;i<=nbLines;i++)
    {
        switch(j)
        {
            case 0:
                printf("Nom de l'equipe : %s\n",getLine(string,i));
                break;
            default:
                printf("Coureur : %s\n",getLine(string,i));
        }
        j++;
        if(j>5)
        {
            j=0;
            printf("\n");
        }
    }
}