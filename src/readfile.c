/**
 * @file readfile.c
 * @author Yohan Boujon (boujon@insa-toulouse.fr)
 * @author Simon Paris (pari@insa-toulouse.fr)
 * @brief Gère la lecture de fichier
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../header/readfile.h"


int getNbLines(void)
{
    int c,count=0;
    FILE * readFile=fopen ("fichier_coureurs.txt","r");
    if (readFile == NULL)
    {
        printf("Le fichier ne peut pas être ouvert!\n");
        return -1;
    }
    do{
        c=getc(readFile);
        if(c == 0xa)
        {
            count++;
        }
    }while(c!=0xffffffff);
    fclose(readFile);
    return count+1;
}


liste getListFromFile(int nbLines,int * size, int * stepsNb,int * teamsNb)
{
    liste l = initListe();
    FILE * readFile=fopen("fichier_coureurs.txt","r");
    if (readFile == NULL)
    {
        printf("Le fichier ne peut pas être ouvert!\n");
        return l;
    }
    int i,j=0;
    char * team = (char *)(malloc(MAXLINE*sizeof(char)));
    char *temp =(char *)(malloc(MAXLINE*(sizeof(char))));
    *size=0;
    fseek(readFile,0,0);
    for(i=0;i<nbLines;i++)
    {
        char * nom = (char *)(malloc(MAXLINE*sizeof(char)));
        char * prenom = (char *)(malloc(MAXLINE*sizeof(char)));
        int dossard=0;
        fgets(temp,MAXLINE,readFile);
        deleteLineFeed(temp);
        switch(i)
        {
            case 0:
                *stepsNb = atoi(temp);
                break;
            case 1:
                *teamsNb = atoi(temp);
                break;
            default :
                switch(j)
                {
                    case 0:
                        strcpy(team,temp);
                        break;
                    default:
                        //printHexString(temp);
                        string2Coureur(temp,nom,prenom,&dossard);
                        coureur * coureurTemp = creerCoureur(nom,prenom,dossard,team,0);
                        ajoutListe(&l,coureurTemp);
                }
                j++;
                if(j>5)
                {
                    j=0;
                }
                free(nom);
                free(prenom);
        }
        *size+=strlen(temp);
    }
    fclose(readFile);
    return l;
}


int getFileSize(FILE * readFile)
{
    fseek(readFile,0,2);
    int returnValue = ftell(readFile);
    fseek(readFile,0,0);
    return returnValue;
}


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


liste string2Liste(char * string,int nbLines)
{
    int j=0;
    char * team = (char *)(malloc(MAXLINE*sizeof(char)));
    liste l = initListe();
    for(int i=3;i<=nbLines;i++)
    {
        char * nom = (char *)(malloc(MAXLINE*sizeof(char)));
        char * prenom = (char *)(malloc(MAXLINE*sizeof(char)));
        int dossard=0;
        switch(j)
        {
            case 0:
                strcpy(team,getLine(string,i));
                break;
            default:
                string2Coureur(getLine(string,i),nom,prenom,&dossard);
                coureur * coureurTemp = creerCoureur(nom,prenom,dossard,team,0);
                ajoutListe(&l,coureurTemp);
        }
        j++;
        if(j>5)
        {
            j=0;
        }
        free(nom);
        free(prenom);
    }
    return l;
}


void string2Coureur(char * string,char * nom, char * prenom, int * dossard)
{
    int i=0,j=0,k=0;
    char * temp = (char *)(malloc(MAXLINE*sizeof(char)));
    while(string[j]!='\0' && string[j]!='\n'){
        k=0;
        while(string[j] != ',' && string[j]!='\0'){
            temp[k] = string[j];
            j++;
            k++;
        }
        temp[k]='\0';
        j++;
        switch(i)
        {
            case 0:
                *dossard = atoi(temp);
                break;
            case 1:
                strcpy(nom,temp);
                break;
            case 2:
                strcpy(prenom,temp);
                break;
            default:
        }
        i++;
    }
    free(temp);
}


void deleteLineFeed(char * string)
{
    int i=0;
    while(string[i]!='\0')
    {
        if(string[i]=='\n')
        {
            string[i]='\0';
        }
        i++;
    }
}


void printHexString(char * string)
{
    for(int i=0;i<MAXLINE;i++)
    {
        printf("0x%x, ",string[i]);
    }
    printf("\n\n");
}