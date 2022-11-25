#include "../header/liste.h"
#include "../header/readfile.h"

int main(void)
{
    FILE * f=fopen ("fichier_coureurs.txt","r");
    //printf("Number of lines : %d\n",getNbLines(f));
    getLines(f,getNbLines(f));
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



void allerDebut(liste * l)// car demandee dans le TP zero reference 
{
    l->courant = l->debut;
}

void allerFin(liste * l)// car demandee dans le TP zero reference 
{
    l->courant = l->fin;
}

void avancer(liste * l) // car demandee dans le TP zero reference 
{
    l->courant = l->courant->suiv;
}

coureur * coureurCourant(liste * l)// car demandee dans le TP zero reference 
{
    return l->courant->coureurActuel;
}


/**
 * @brief suprime un element(a partir de l'adresse d'un coureur) dans la liste sans briser le chainage
 * fonctionnement :
    -declaration d'un poiteur eParcours egale l'adresse du premiere element (variable temporaire)
    -declaration d'un poiteur(ePrevious) qui stockera temporairement l'adresse des elements pendant la reconstruction du chainage
    -
 * @param listeActuel 
 * @param coureurSuppr 
 */
void effacerCoureur(liste * listeActuel,coureur * coureurSuppr) 
{
    struct element *eParcours =listeActuel->debut;       
    struct element * ePrevious;                          
    if(eParcours->coureurActuel == coureurSuppr)         //si l'element a supprimer est le premiere element de la liste :
    {
        listeActuel->courant=eParcours->suiv;            //le poiteur courant pointe sur l'element suivant
        listeActuel->debut=eParcours->suiv;              //le poiteur pointant sur le premiere element poite sur le deuxieme
    }
    else{                                                //si l'element a suppr n'est pas le deuxieme
        ePrevious=eParcours;                             //ePrevious egale l'adresse du premiere element 
        eParcours=eParcours->suiv;                       //eParcours egale l'adresse du deuxieme element 
        while(eParcours->coureurActuel != coureurSuppr){ //tant que l'element poitee par eParcours ne contient pas le courreur a supprimer faire :
            ePrevious=ePrevious->suiv;                   //ePrevious pointe sur l'element suivant
            eParcours=eParcours->suiv;                   //eParcours pointe sur l'element suivant 
        }
        ePrevious->suiv=eParcours->suiv;                 //l'element avant celui a suprimer pointe sur l'element sur le qu'elle poite l'element a supprimer 
        free(eParcours);                                 //supression de l'element 
    }
}

int tailleListe(liste l)                            
{
    int returnValue=0;                              //initilisation a 0 d'un compteur (int)
    struct element * elementActuel = l.debut;       //decleration d'un poiteur elementActuel initialisee au poiteur debut present dans liste qui pointe sur le premier element du chainage
    while(elementActuel->suiv != l.fin->suiv)       //tant que elementActuel n'est pas egale a l'adresse du derniere element faire :
    {
        returnValue++;                              //increment compteur
        elementActuel=elementActuel->suiv;          //elementActuel pointe sur l'element suivant
    };
    return returnValue;                             //retourne le compteur
}

coureur * getCoureur(liste l,int nb)                
{
    struct element * elementCourant = l.debut;     //init elementCourant a l'adresse du premiere element de la liste
    for(int i=0;i<nb;i++)
    {
        elementCourant=elementCourant->suiv;       //a la fin de la boucle elementcourant pointe sur l'element nb (on considere un element 0)
    }
    return elementCourant->coureurActuel;          //renvoie le coureur encapsulee dans l'element nb
}


void invertCoureur(liste * l,int nb)
{
    struct element * elementDebut = l->debut;                                            //decleration d'un poiteur elementCourant initialisee au poiteur debut present dans liste qui pointe sur le premier element du chainage
    struct element * elementPrecedent = (struct element *)(malloc(sizeof(struct element)));//declaration et allocation  en memoire(a l'adresse *elemeentPrecedent) d'une taille de structure element de type element 
    for(int i=0;i<nb;i++)                                                                  //pour i allant de 0 a nb-1
    {
        elementPrecedent = elementDebut;                                                 //en fin de boucle elementCourant poite sur l'element nb et elementPrecendent nb-1
        elementDebut=elementDebut->suiv;                        
    }
    struct element * elementSuivant = elementDebut->suiv;                                //declaration de elementsuivant qui poite sur l'element nb+1
    elementDebut->suiv=elementSuivant->suiv;                                             //elementCourant pointe sur nb+1
    elementSuivant->suiv=elementDebut;                                                   //elementSuivant pointe sur nb
    if(nb==0)                                                                              //si l'element a intervertir est le premier :
    {
        l->courant=elementSuivant;                                                         //le poiteur courant pointe sur l'ancien deuxieme element
        l->debut=l->courant;                                                               //le poiteur debut pointe sur l'ancien deuxieme
    }
    else{                                                                                  //si l'element a intervertir diff du premier :
        elementPrecedent->suiv = elementSuivant;                                           //element nb-1 pointe sur element nb
        l->courant=l->debut;                                                               //le poiteur courant pointe sur le premier element
    }
}

    void triListe(liste * l,int taille)
    {
        bool tabOrdered = true;
        for(int i=taille-1;i>1;i--)                                    //pour i allant du nombre d'element dans la liste a 2 step -1
        {
            for(int j=0;j<=i-1;j++)                                    //pour j allant de 0 a i-1 step 1
            {
                if(getCoureur(*l,j+1)->temps < getCoureur(*l,j)->temps)//si leCourreur taille -i a un temps < au coureur taille-i+1
                {
                    invertCoureur(l,j);                                //inverser les courreurs
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

