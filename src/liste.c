#include "../header/liste.h"
#include "../header/readfile.h"

int main(void)
{
    int size;
    FILE * f=fopen ("fichier_coureurs.txt","r");
    char * fileString = (char *)(malloc(getFileSize(f)*sizeof(char)));
    int fileLines = getNbLines(f);
    getStringFromFile(f,fileLines,fileString,&size);
    int stepsNb = atoi(getLine(fileString,1));
    int teamsNb = atoi(getLine(fileString,2));
    printf("Nombre d'etapes : %d\t Nombre d'equipes :%d\n",stepsNb,teamsNb);
    liste l = string2Liste(fileString,fileLines);
    printlist(l);
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
void effacerCoureur(liste * listeActuel,coureur * coureurSuppr) 
{
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
    }
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
            printlist(*l);
        }
        if(tabOrdered)
        {
            return;
        }
    }
}