#include "../header/readfile.h"
#define MAXLINE 50

/**
 * @brief Récupère le nombre de ligne d'un fichier
 * 
 * @param readFile le fichier en question 
 * @return int nombre de ligne
 */
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

/**
 * @brief Converti les caractères d'un fichier dans un string pour pouvoir
 * le manipuler plus simplement
 * 
 * @param readFile le fichier à lire
 * @param nbLines son nombre de ligne
 * @param returnString une chaîne de caractère vide à modifier
 * @param size renvoie la taille de la chaîne de caractère
 */
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

/**
 * @brief récupère la taille du fichier, est assez grossier et ne sert qu'à
 * initialiser les tableaux pour ne pas avoir une taille à prédéfinir.
 * 
 * @param readFile fichier en question
 * @return int taille du fichier
 */
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

/**
 * @brief Renvoi une liste à partir d'une chaîne de caractère contenant
 * les équipes ainsi que les coureurs avec leur nom, leur prénom et numéro de dossard
 * 
 * @param string chaîne de caractère
 * @param nbLines nombre de ligne max de la chaîne de caractère
 * @return liste des coureurs
 */
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

/**
 * @brief A partir d'une ligne récupère les informations sur le coureur,
 * Notamment son numéro de dossard, son nom et son prénom
 * 
 * @param string    char * ligne textuel
 * @param nom       char * renvoi le nom du coureur, doit être vide
 * @param prenom    char * renvoi le nom du coureur, doit être vide
 * @param dossard   int * renvoi le numéro du dossard
 */
void string2Coureur(char * string,char * nom, char * prenom, int * dossard)
{
    int i=0,j=0,k=0;
    char * temp = (char *)(malloc(MAXLINE*sizeof(char)));
    while(string[j]!='\0'){
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

/**
 * @brief Debug uniquement, permet d'observer les valeurs de chaque caractère.
 * la taille n'est pas demandée pour observer au delà de l'espace mémoire donné
 * 
 * @param string un tableau de caractère
 */
void printHexString(char * string)
{
    for(int i=0;i<MAXLINE;i++)
    {
        printf("0x%x, ",string[i]);
    }
    printf("\n\n");
}