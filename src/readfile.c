#include "../header/readfile.h"

/**
 * @brief Récupère le nombre de ligne d'un fichier
 * 
 * @param readFile le fichier en question 
 * @return int nombre de ligne
 */
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

/**
 * @brief Converti les caractères d'un fichier dans la liste de coureur.
 * 
 * @param nbLines nombre de ligne du fichier qui va être lu
 * @param size renvoie la taille de la chaîne de caractère
 * @param stepsNb int * renvoi le nombre d'étapes
 * @param teamsNb int * renvoi le nombre d'équipes
 * @return liste de coureurs
 */
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
 * @brief /!\/!\/!\ Debug uniquement /!\/!\/!\ : 
 * récupère une ligne, non optimisé donc inutilisable
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
 * @brief /!\/!\/!\ INUTILISE CAR OBSELETE /!\/!\/!\ :
 * Renvoi une liste à partir d'une chaîne de caractère contenant
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

/**
 * @brief Supprime les retours à la ligne dans les chaînes de caractère.
 * Attention ! les remplace par le caractère signifiant la fin de la chaîne.
 * 
 * @param string chaîne de caractère
 */
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

/**
 * @brief /!\/!\/!\ Debug uniquement /!\/!\/!\ :
 * Permet d'observer les valeurs de chaque caractère.
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