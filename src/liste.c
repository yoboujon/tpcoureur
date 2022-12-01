/**
 * @file liste.c
 * @author Yohan Boujon (boujon@insa-toulouse.fr)
 * @author Simon Paris (pari@insa-toulouse.fr)
 * @brief Gère les listes
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../header/readfile.h"
#include "../header/liste.h"
#define MAXTEAMATES 3

/*! \mainpage TP Coureur par Simon Paris et Yohan Boujon
# TP Langage C
## Introduction
Le programme tpcoureur fonctionne de manière aléatoire.

A chaque lancement du programme les coureurs sont lu à partir du fichier
[fichier_coureur.txt](fichier_coureurs.txt). Ces derniers vont être ensuite mis dans une liste, dans le même ordre que donné par le fichier. Ce fichier possède une convention particulière, soit :
> `1` Nombre d'étapes

> `1` Nombre d'équipe

> `x` Nom de l'équipe *x*

>   `5x` n° du dossard, Nom, `d'un coureur de l'équipe x`

>    ...

Les variables définies 
> `TEMPSMAX` Temps maximum qu'un coureur peut avoir\
`TEMPSMIN` Temps minimum qu'un coureur peut avoir\
`TEMPSDOP` Temps pour les joueurs dopés *(Inférieur à `TEMPSMIN`)*\

Chaque calcul de temps est randomisé selon ces variables. Elles peuvent être changées pour avoir des temps finaux différents. Mais surtout change la chance qu'un joueur soit dopé.

Le programme va tout d'abord supprimer les coureurs dopés et trier avec l'algorithme du [tri bulle][bullewiki] dans l'ordre croissant. Il va ensuite afficher les équipes éliminées : une équipe est éliminée si elle possède moins de `3 joueurs`. Et enfin elle affiche le classement final des **équipes uniquement**, seuls les temps des 3 meilleurs coureurs sont comptés.

En premier lieu les différents participants sont affichés :

![coureurs](img/coureurs.png)

Différents classements sont affichés. Tout d'abord le general :

![general](img/general.png)

Ensuite les différentes personnes dopées ainsi que les équipe éliminées :

![general](img/elimine.png)

Et enfin le classement final :

![final](img/final.png)

## Installation

Le [Makefile](/Makefile) permet de compiler et lancer le programme. Il permet aussi de nettoyer les résidus de la compilation. Pour cela il est possible de faire différentes commandes :
```
make
```
*Compile et lance le programme*
```
make clean
```
*Supprime les fichiers d'output ainsi que l'executable*
```
./main
```
*Lance le programme s'il est déjà compilé*

A noter que sur windows Le Makefile produit une erreur 127. Cela n'est produit qu'en compilation et non à l'execution.

[bullewiki]: https://fr.wikipedia.org/wiki/Tri_%C3%A0_bulles
 */

int main(void)
{
    int size, stepsNb, teamsNb, listeTaille, dopageCount;
    srand(time(NULL));
    int fileLines = getNbLines();
    liste l = getListFromFile(fileLines,&size,&stepsNb,&teamsNb);
    liste dopageList = initListe();
    listeTaille = tailleListe(l);

    printf("Nombre d'etapes : %d\t Nombre d'equipes :%d\n",stepsNb,teamsNb);
    for(int i=0; i<stepsNb ; i++)
    {
        for(int j=0; j<listeTaille ; j++)
        {
            int temptemps = (rand()%(TEMPSMAX-TEMPSDOP+1))+TEMPSDOP;
            coureur * coureurTemp = l.courant->coureurActuel;
            ajouterTemps(temptemps,coureurTemp);
            avancer(&l);
            if(temptemps < TEMPSMIN)
            {
                ajoutListe(&dopageList,coureurTemp);
            }
        }
        allerDebut(&l);
    }
    allerDebut(&l);
    printf("\n --- LISTE DES PARTICIPANTS --- \n");
    printlist(l);
    char ** tabTeam = initMatrix(teamsNb,MAXLINE);
    readTeams(tabTeam,teamsNb,MAXLINE,l);
    dopageCount=effacerListe(&l,&dopageList);
    int * teamCount = teamsCount(tabTeam,teamsNb,l);
    printf("\n --- CLASSEMENT GENERAL : ---\n");
    triListe(&l,tailleListe(l));
    printlist(l);
    printf("\n --- NOMBRE DE PERSONNES DOPEES : %d ---\n",dopageCount);
    printf("\n --- ELIMINATION DES EQUIPES --- : \n");
    removeTeam(tabTeam,teamsNb,&l,teamCount,MAXTEAMATES);
    teamCount = teamsCount(tabTeam,teamsNb,l);
    printTeamsDetailsFor(0,tabTeam,teamCount,teamsNb);
    printf("\n --- CLASSEMENT FINAL : --- : \n");
    int * timeTeam = keepOnlyCoureur(MAXTEAMATES,&l,tabTeam,teamsNb);
    triTemps(timeTeam,teamsNb,tabTeam);
    printTeamsTimes(timeTeam,tabTeam,teamsNb,0);
    return 0;
}

struct element * initElement(void)
{
    struct element * returnElement = (struct element *)malloc(sizeof(struct element));
    returnElement->coureurActuel = creerCoureur("","",0,"",0);
    returnElement->suiv = NULL;
    return returnElement;
}

liste initListe(void)
{
    liste l;
    l.debut=initElement();
    l.fin=initElement();
    l.courant=initElement();
    return l;
}

void ajoutListe(liste * listeActuel,coureur * leCoureur)                                 
{
    struct element * elementActuel = (struct element *)malloc(sizeof(struct element));    
    elementActuel->coureurActuel=leCoureur;                                                                                     
    elementActuel->suiv=listeActuel->courant;                                                                                        
    listeActuel->debut=elementActuel;                                                     
    listeActuel->courant=elementActuel;                                                   
}

void printlist(liste l)                                                                   
{
    struct element * eCourant = l.debut;                                                  
    while(eCourant->suiv != l.fin->suiv)                                                  
    {
        afficherCoureur(eCourant->coureurActuel);                                         
        eCourant=eCourant->suiv;                                                         
    }
    printf("NULL \n");                                                                   
}

void allerDebut(liste * l) 
{
    l->courant = l->debut;
}

void allerFin(liste * l)
{
    l->courant = l->fin;
}

void avancer(liste * l)
{
    l->courant = l->courant->suiv;
}

coureur * coureurCourant(liste * l)
{
    return l->courant->coureurActuel;
}

bool effacerCoureur(liste * listeActuel,coureur * coureurSuppr, bool returnSuiv) 
{
    if(!doesCoureurExist(listeActuel,coureurSuppr))
    {
        return false;
    }
    struct element *eParcours =listeActuel->debut;       
    struct element * ePrevious;                          
    if(eParcours->coureurActuel == coureurSuppr)         
    {
        listeActuel->courant=eParcours->suiv;            
        listeActuel->debut=eParcours->suiv;            
    }
    else{                                               
        ePrevious=eParcours;                             
        eParcours=eParcours->suiv;                       
        while(eParcours->coureurActuel != coureurSuppr){ 
            ePrevious=ePrevious->suiv;                   
            eParcours=eParcours->suiv;                   
        }
        ePrevious->suiv=eParcours->suiv;                 
        free(eParcours);
        if(returnSuiv)
        {
            listeActuel->courant=ePrevious;
        }                         
    }
    return true;
}

bool doesCoureurExist(liste* l,coureur * c)
{
    struct element * eDebut = l->debut;                                                  
    while(eDebut->suiv != l->fin->suiv)                                                  
    {
        if(eDebut->coureurActuel == c)
        {
            return true;
        }                                    
        eDebut=eDebut->suiv;                                                         
    }
    return false; 
}

int effacerListe(liste * destination, liste * source)
{
    int returnValue=0;
    struct element * eCourant = source->debut;                                                  
    while(eCourant->suiv != source->fin->suiv)
    {
        if(effacerCoureur(destination,eCourant->coureurActuel,false))
        {
            returnValue++; 
        }                            
        eCourant=eCourant->suiv;
    }
    return returnValue;
}

int tailleListe(liste l)                            
{
    int returnValue=0;                              
    struct element * elementActuel = l.debut;       
    while(elementActuel->suiv != l.fin->suiv)       
    {
        returnValue++;                              
        elementActuel=elementActuel->suiv;          
    };
    return returnValue;
    allerDebut(&l);                  
}

coureur * getCoureur(liste l,int nb)                
{
    struct element * elementCourant = l.debut;     
    for(int i=0;i<nb;i++)
    {
        elementCourant=elementCourant->suiv;       
    }
    return elementCourant->coureurActuel;       
}

void invertCoureur(liste * l,int nb)
{
    struct element * elementDebut = l->debut;                                            
    struct element * elementPrecedent = (struct element *)(malloc(sizeof(struct element)));
    for(int i=0;i<nb;i++)                                                                  
    {
        elementPrecedent = elementDebut;                                                 
        elementDebut=elementDebut->suiv;                        
    }
    struct element * elementSuivant = elementDebut->suiv;                               
    elementDebut->suiv=elementSuivant->suiv;                                             
    elementSuivant->suiv=elementDebut;                                                   
    if(nb==0)                                                                              
    {
        l->courant=elementSuivant;                                                         
        l->debut=l->courant;                                                               
    }
    else{                                                                                  
        elementPrecedent->suiv = elementSuivant;                                           
        l->courant=l->debut;                                                               
    }
}

void triListe(liste * l,int taille)
{
    bool tabOrdered = true;
    for(int i=taille-1;i>1;i--)                                    
    {
        for(int j=0;j<=i-1;j++)                                    
        {
            if(getCoureur(*l,j+1)->temps < getCoureur(*l,j)->temps)
            {
                invertCoureur(l,j);                                
                tabOrdered = false;
            }
            
        }
        if(tabOrdered)
        {
            return;
        }
    }
}

char ** initMatrix(int sizeCol,int sizeLine)
{
    char ** matrix;
    matrix = (char **)(malloc(sizeLine*sizeof(char *)));
    for(int i=0;i<sizeLine;i++)
    {
        *(matrix+i) = (char *)(malloc(sizeCol*sizeof(char)));
    }
    return matrix;
}

bool isStringInMatrix(char ** matrix, char * string, int size)
{
    for(int i=0;i<size;i++)
    {
        if(strcmp(matrix[i],string) == 0)
        {
            return true;
        }
    }
    return false;
}

void readTeams(char ** matrix, int sizeCol, int sizeLine, liste l)
{
    int i=0;
    struct element * elementCourant = l.courant;
    struct element * elementFin = l.fin;
    while(elementCourant->suiv != elementFin->suiv)
    {
        if(!isStringInMatrix(matrix,elementCourant->coureurActuel->equipe,sizeCol))
        {
            matrix[i]=elementCourant->coureurActuel->equipe;
            i++;
        }
        elementCourant=elementCourant->suiv;
    }
}

int * teamsCount(char ** teamNames, int sizeCol, liste list)
{
    int * teamCount = (int *)(malloc(sizeCol*sizeof(int)));
    memset(teamCount, 0, sizeCol*sizeof(int));
    struct element * elementCourant = list.courant;
    struct element * elementFin = list.fin;
    while(elementCourant->suiv != elementFin->suiv)
    {
        for(int i=0;i<sizeCol;i++)
        {
            if(strcmp(teamNames[i],elementCourant->coureurActuel->equipe) == 0)
            {
                teamCount[i]++;
            }
        }
        elementCourant=elementCourant->suiv;
    }
    return teamCount;
}

void removeTeam(char ** teamNames, int sizeCol, liste * list, int * coureursInTeams, int lessThanCoureurCount)
{
    struct element * elementCourant = list->courant;
    struct element * elementFin = list->fin;
    while(elementCourant->suiv != elementFin->suiv)
    {
        for(int i=0;i<sizeCol;i++)
        {
            if((strcmp(teamNames[i],elementCourant->coureurActuel->equipe)) == 0 && (coureursInTeams[i]<lessThanCoureurCount))
            {
                
                effacerCoureur(list,elementCourant->coureurActuel,false);
                elementCourant=getElementCourant(*list);
            }
        }
        elementCourant=elementCourant->suiv;
    }
}

struct element * getElementCourant(liste l)
{
    return l.courant;
}

void printTeamsDetails(char ** teamsNames, int * coureurInTeams, int teamsNB)
{
    for(int i=0;i<teamsNB;i++)
    {
        printf("Team [%d] : %s\tCoureurs : %d\n",i,teamsNames[i],coureurInTeams[i]);
    }
}

void printTeamsDetailsFor(int num, char ** teamsNames, int * coureurInTeams, int teamsNB)
{
    for(int i=0;i<teamsNB;i++)
    {
        if(coureurInTeams[i] == num)
        {
            printf("Team [%d] : %s\n",i,teamsNames[i]);
        }
    }
}

int * keepOnlyCoureur(int maxCoureur, liste * list, char ** teamNames, int sizeCol)
{
    int * teamsCount = (int *)(malloc(sizeCol*sizeof(int)));
    int * secondsPerTeam = (int *)(malloc(sizeCol*sizeof(int)));
    memset(teamsCount, 0, sizeCol*sizeof(int));
    memset(secondsPerTeam, 0, sizeCol*sizeof(int));
    struct element * elementCourant = list->courant;
    struct element * elementFin = list->fin;
    for(int i=0;i<sizeCol;i++)
    {
        while(elementCourant->suiv != elementFin->suiv)
        {
            if(strcmp(teamNames[i],elementCourant->coureurActuel->equipe) == 0)
            {
                if(teamsCount[i]>=maxCoureur)
                {
                    effacerCoureur(list,elementCourant->coureurActuel,true);
                    elementCourant=getElementCourant(*list);
                }
                else
                {
                    secondsPerTeam[i]+=elementCourant->coureurActuel->temps;
                }
                teamsCount[i]+=1;
            }
            elementCourant=elementCourant->suiv;
        }
        elementCourant=list->debut;
    }
    allerDebut(list);
    return secondsPerTeam;
}

void triTemps(int * temps, int taille,char ** teams)
{
    int tabTemp;
    char * stringTemp = (char *)(malloc(MAXLINE*sizeof(char)));
    bool tabOrdered = true;
    for(int i=taille-1;i>1;i--)                                    
    {
        for(int j=0;j<=i-1;j++)                                    
        {
            if(temps[j+1] < temps[j])
            {
                tabTemp = temps[j+1];
                stringTemp = teams[j+1];
                temps[j+1] = temps[j];
                teams[j+1] = teams[j];
                temps[j] = tabTemp;    
                teams[j] = stringTemp;
                tabOrdered = false;
            }
        }
        if(tabOrdered)
        {
            return;
        }
    }
}

void printTeamsTimes(int * temps, char ** teams, int taille, int ignore)
{
    for(int i=0;i<taille;i++)
    {
        if(temps[i] != ignore)
        {
            int heures,minutes,secondes;
            formatSecond(temps[i],&heures,&minutes,&secondes);
            printf("Temps : %d:%02d:%02d\t Equipe : %s\n",heures,minutes,secondes,teams[i]);
        }
    }
}

int test(void)
{
    coureur * c1 = creerCoureur("Paris","Simon",15,"TRAUFORE",50000);
    coureur * c2 = creerCoureur("Bougeont","Yoann",65,"MEILLEUR",99994);
    coureur * c3 = creerCoureur("Barakai","Obama",120,"AMERICA",372);
    coureur * c4 = creerCoureur("Boujon","Yohan",56,"MAISYEUR",49999);
    coureur * c5 = creerCoureur("Runner","Tedi",1,"JUDOOOKA",120);
    coureur * c6 = creerCoureur("Fatigue","Jean",69,"DODODODO",11554751);
    coureur * c7 = creerCoureur("MISSINGO","No way",42,"dontexist",2);
    printf(" -- COUREUR -- \n");                                
    afficherCoureur(c1);
    ajouterTemps(50,c1);
    afficherCoureur(c1);
    liste l1 = initListe();
    ajoutListe(&l1,c1);
    ajoutListe(&l1,c2);
    ajoutListe(&l1,c3);
    ajoutListe(&l1,c4);                                                             
    ajoutListe(&l1,c5);                                                             
    ajoutListe(&l1,c6);                                                             
    printf(" -- AJOUT LISTE, taille =%d -- \n",tailleListe(l1));
    printlist(l1);
    effacerCoureur(&l1,c2,false);
    printf(" -- SUPR LISTE, taille =%d -- \n",tailleListe(l1));
    printlist(l1);
    printf(" -- INTERVERTI COUREUR 1 ET 2 DE LA LISTE -- \n");
    invertCoureur(&l1,1);
    printlist(l1);
    printf(" -- INTERVERTI COUREUR 0 ET 1 DE LA LISTE -- \n");
    invertCoureur(&l1,0);
    printlist(l1);
    printf(" -- COUREUR 2 DE LA LISTE -- \n");
    afficherCoureur(getCoureur(l1,2));
    printf(" -- TRI LISTE -- \n");
    triListe(&l1,tailleListe(l1));
    printlist(l1);
    printf(" -- SUPPRIME UN COUREUR N'EXISTANT PAS -- \n");
    effacerCoureur(&l1,c7,false);
    effacerCoureur(&l1,c3,false);
    effacerCoureur(&l1,c4,false);
    printf("Does c3 exists : %d\tand c4 ? : %d\n",doesCoureurExist(&l1,c3),doesCoureurExist(&l1,c4));
    printlist(l1);
    return 0;
}