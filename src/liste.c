#include "../header/readfile.h"
#include "../header/liste.h"
#define MAXTEAMATES 3

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

/**
 * @brief initialise un element en memoire qui encapsule une strucure de coureur au champs vide
 * 
 * @return returnElement retourne un element vierge  
 */
struct element * initElement(void)
{
    struct element * returnElement = (struct element *)malloc(sizeof(struct element));
    returnElement->coureurActuel = creerCoureur("","",0,"",0);
    returnElement->suiv = NULL;
    return returnElement;
}

/**
 * @brief initialise chaque element de la liste a partir de initElement
 * 
 *  
 * @return l 
 */
liste initListe(void)
{
    liste l;
    l.debut=initElement();
    l.fin=initElement();
    l.courant=initElement();
    return l;
}

/**
 * @brief ajout d'un element contenant un coureur dans liste 
 * fonctionnement :
    -Creation element vierge 
    -l'element vierge recoi le coureur passer en parametre
    -l'element vierge poite sur le premier element 
    -le poiteur de premiere element contenue dans liste pointe sur le nouvelle element(vierge)
    -le poiteur courant contenue dans la liste pointe sur le nouvelle element
 * @param listeActuel liste ou l'on rajoute un element
 * @param leCoureur   le coureur qui sera contenue dans l'element rajoutee
 */
void ajoutListe(liste * listeActuel,coureur * leCoureur)                                 
{
    struct element * elementActuel = (struct element *)malloc(sizeof(struct element));    
    elementActuel->coureurActuel=leCoureur;                                                                                     
    elementActuel->suiv=listeActuel->courant;                                                                                        
    listeActuel->debut=elementActuel;                                                     
    listeActuel->courant=elementActuel;                                                   
}

/**
 * @brief affiche tous les coureurs contenue dans les elements d'une liste
 * fonctionnement :
    -decleration d'un poiteur eCourant egale l'adresse du premiere element (variable temporaire)
    -Tant que eCourant->suiv n'est pas egale a l'adresse du derniere element faire :
    -affichee le coureur dans l'element d'adresse eCourant
    -eCourant devient l'adresse de l'element suivant
    
 * @param l liste a affiche
 */
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

/**
 * @brief Mettre le poiteur courant d'une liste sur le premiere element
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
void allerDebut(liste * l) 
{
    l->courant = l->debut;
}

/**
 * @brief Mettre le poiteur courant d'une liste sur le derniee element
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
void allerFin(liste * l)
{
    l->courant = l->fin;
}

/**
 * @brief Mettre le poiteur courant sur l'element suivant
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
void avancer(liste * l)
{
    l->courant = l->courant->suiv;
}

/**
 * @brief Retourne le coureur encapsulee dans l'element pointer par le pointeur courant
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
coureur * coureurCourant(liste * l)
{
    return l->courant->coureurActuel;
}

/**
 * @brief suprime un element(a partir de l'adresse d'un coureur) dans la liste sans briser le chainage
 * fonctionnement :
    -declaration d'un poiteur eParcours egale l'adresse du premiere element (variable temporaire)
    -declaration d'un poiteur(ePrevious) qui stockera temporairement l'adresse des elements pendant la reconstruction du chainage
    -si l'element a supprimer est le premiere element de la liste :
    -le poiteur courant pointe sur l'element suivant
    -le poiteur pointant sur le premiere element poite sur le deuxieme
    -si l'element a suppr n'est pas le deuxieme :
    -ePrevious egale l'adresse du premiere element 
    -eParcours egale l'adresse du deuxieme element 
    -tant que l'element poitee par eParcours ne contient pas le courreur a supprimer faire :
    -ePrevious pointe sur l'element suivant
    -eParcours pointe sur l'element suivant 
    -l'element avant celui a suprimer pointe sur l'element sur le qu'elle poite l'element a supprimer 
    -supression de l'element

 * @param listeActuel Liste ou l'on suppr un element
 * @param coureurSuppr le coureur qui doit etre dans l'element pour le supprimer 
 */
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

/**
 * @brief Cherche si un coureur existe dans une liste
 * 
 * @param l la liste en question
 * @param c le coureur cherché 
 * @return true / false
 */
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

/**
 * @brief A partir d'une liste source supprime tous les éléments en commun
 * 
 * @param destination liste à modifier
 * @param source liste des éléments à supprimer
 * @return int nombre d'éléments supprimés
 */
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

/**
 * @brief Renvoie le nombre d'elements d'une liste
 fonctionnement :
 -initilisation a 0 d'un compteur (int)
 -decleration d'un poiteur elementActuel initialisee au poiteur debut present dans liste qui pointe sur le premier element du chainage
 -tant que elementActuel n'est pas egale a l'adresse du derniere element faire 
 -increment compteur
 -elementActuel pointe sur l'element suivant
 -retourne le compteur

 * 
 * @param l l la liste dont on ve connaitre la taille 
 * @return int le nombre d'element (on compte a partir de 0)
 */
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

/**
 * @brief retourne le courreur contenue dans l'element nb d'une liste (on considere un element 0)
 * fonctionnement :
    -init elementCourant a l'adresse du premiere element de la liste
    -pour i allant de 0 a nb-1
    -a la fin de la boucle elementcourant pointe sur l'element nb (on considere un element 0)
    -renvoie le coureur encapsulee dans l'element nb
 * @param l la liste ou doit se trouver l'element encapsulant le coureur 
 * @param nb le numero d'element rechercher 
 * @return coureur* 
 */
coureur * getCoureur(liste l,int nb)                
{
    struct element * elementCourant = l.debut;     
    for(int i=0;i<nb;i++)
    {
        elementCourant=elementCourant->suiv;       
    }
    return elementCourant->coureurActuel;       
}

/**
 * @brief inverse l'element nb et nb+1 dans une liste (on considere un element 0)
 * fonctionnement :
    -decleration d'un poiteur elementCourant initialisee au poiteur debut present dans liste qui pointe sur le premier element du chainage
    -declaration et allocation  en memoire(a l'adresse *elemeentPrecedent) d'une taille de structure element de type element 
    -pour i allant de 0 a nb-1 faire :
    -en fin de boucle elementCourant poite sur l'element nb et elementPrecendent nb-1
    
    -declaration de elementsuivant qui poite sur l'element nb+1
    -elementCourant pointe sur nb+1
    -elementSuivant pointe sur nb
    -si l'element a intervertir est le premier :
    -le poiteur courant pointe sur l'ancien deuxieme element
    -le poiteur debut pointe sur l'ancien deuxieme
    -si l'element a intervertir diff du premier :
    -element nb-1 pointe sur element nb
    -le poiteur courant pointe sur le premier element
 * @param l liste ou l'on inverse les elements
 * @param nb le numero d'element inverser avec nb+1
 */
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

/**
 * @brief trie bulle des element d'une liste a partir du temps contenue dans la structure encapsule dans l'element
 * fonctionnement :
    -pour i allant du nombre d'element dans la liste a 2 step -1
    -pour j allant de 0 a i-1 step 1
    -si leCourreur taille -i a un temps < au coureur taille-i+1
    -inverser les courreurs j et j+1

 * @param l liste a trier
 * @param taille represente la taille de la liste 
 */
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
            //printlist(*l);
        }
        if(tabOrdered)
        {
            return;
        }
    }
}

/**
 * @brief Initialise un tableau de chaîne de caractères
 * 
 * @param sizeCol taille des colonnes
 * @param sizeLine taille de chaque ligne
 * @return int** Une matrice de caractère
 */
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

/**
 * @brief Detecte si une chaîne de caractères est présente dans un
 * tabealu de chaîne de caractères
 * 
 * @param matrix tableau de chaîne de caractères
 * @param string chaîne de caractère
 * @param size nombre de lignes
 * @return true / false
 */
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

/**
 * @brief Donne le nom de chaque équipe dans un tableau de chaîne de caractères
 * 
 * @param matrix tableau de chaîne de caractère
 * @param sizeCol taille des colonns
 * @param sizeLine taille des lignes
 * @param l la liste composant les noms des équipes
 */
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

/**
 * @brief Compte le nombre de joueur dans chaque équipe et le met dans une liste
 * d'entiers
 * 
 * @param teamNames les noms de chaque équipe
 * @param sizeCol taille de la colonne des noms de chaque équipe
 * @param list la liste que l'ont veut analyser
 * @return int* tableau en commun avec le nom des équipes du nombre de joueur
 */
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

/**
 * @brief Elimine une équipe si elle a moins de lessThanCoureurCount
 * 
 * @param teamNames les noms de chaque équipe
 * @param sizeCol taille de la colonne des noms de chaque équipe
 * @param list la liste que l'ont veut analyser
 * @param coureursInTeams nombre de joueur par équipe
 * @param lessThanCoureurCount int
 */
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
                //afficherCoureur(elementCourant->coureurActuel);
                effacerCoureur(list,elementCourant->coureurActuel,false);
                elementCourant=getElementCourant(*list);
            }
        }
        elementCourant=elementCourant->suiv;
    }
}

/**
 * @brief Récupère l'élément courant de la liste
 * 
 * @param l liste
 * @return struct element* 
 */
struct element * getElementCourant(liste l)
{
    return l.courant;
}

/**
 * @brief Affiche les équipes et le nombre de coureurs
 * 
 * @param teamsNames les noms de chaque équipe
 * @param coureurInTeams nombre de coureur dans chaque équipe
 * @param teamsNB nombre d'équipes
 */
void printTeamsDetails(char ** teamsNames, int * coureurInTeams, int teamsNB)
{
    for(int i=0;i<teamsNB;i++)
    {
        printf("Team [%d] : %s\tCoureurs : %d\n",i,teamsNames[i],coureurInTeams[i]);
    }
}

/**
 * @brief Affiche les équipes composés d'un certain nombre de coureur 
 * 
 * @param num le nombre de coureur auquel l'équipe doit être égale
 * @param teamsNames les noms de chaque équipe
 * @param coureurInTeams nombre de coureur dans chaque équipe
 * @param teamsNB nombre d'équipes
 */
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

/**
 * @brief Supprime les coureurs s'il y a plus de maxCoureur
 * 
 * @param maxCoureur nombre de coureur max dans une équipe
 * @param list liste à analyser
 * @param teamNames nom des équipes
 * @param sizeCol taille de la colonne des équipe/nombre d'équipes
 */
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

/**
 * @brief Tri une liste de int ainsi qu'une liste de chaîne de caractère associé
 * 
 * @param temps liste de int
 * @param taille taille de cette liste
 * @param teams liste de chaîne de caractère (doit être de la même taille)
 */
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

/**
 * @brief Affiche le temps ainsi que les équipes
 * 
 * @param temps liste de temps en int
 * @param teams liste de chaîne de caractères, les équipes
 * @param taille taille des deux listes (doivent être égales)
 * @param ignore le chiffre qui doit être ignoré (si vous voulez le désactiver, choisissez un nombre impossible)
 */
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

/**
 * @brief Fonction de test
 * 
 * @return int renvoie zéro si réussie
 */
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