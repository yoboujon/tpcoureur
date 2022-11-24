#include "liste.h"

int main(void)
{
    coureur * c1 = creerCoureur("Paris","Simon",15,"TRAUFORE",50000);               //creation coureur
    coureur * c2 = creerCoureur("Bougeont","Yoann",65,"MEILLEUR",99994);            //creation coureur
    coureur * c3 = creerCoureur("Barakai","Obama",120,"AMERICA",372);               //creation coureur
    coureur * c4 = creerCoureur("Boujon","Yohan",56,"MAISYEUR",49999);              //creation coureur
    coureur * c5 = creerCoureur("Runner","Tedi",1,"JUDOOOKA",120);                  //creation coureur
    coureur * c6 = creerCoureur("Fatigue","Jean",69,"DODODODO",11554751);           //creation coureur
    printf(" -- COUREUR -- \n");                                
    afficherCoureur(c1);                                                            //Afficher les champs de la structure coureur c1
    ajouterTemps(50,c1);                                                            //Ajoutee 50 seconde dans le champ temp de c1
    afficherCoureur(c1);                                                            //Afficher les champs de la structure coureur c1
    liste l1 = initListe();                                                         //declaration de la liste l1 et initialisation
    ajoutListe(&l1,c1);                                                             //ajout d'un element contenat c1 dans liste l1(a partir de son adresse modfication a la maniere d'une variable global)
    ajoutListe(&l1,c2);                                                             //ajout d'un element contenat c2 dans liste l1(a partir de son adresse modfication a la maniere d'une variable global)
    ajoutListe(&l1,c3);                                                             //ajout d'un element contenat c3 dans liste l1(a partir de son adresse modfication a la maniere d'une variable global)
    ajoutListe(&l1,c4);                                                             //ajout d'un element contenat c4 dans liste l1(a partir de son adresse modfication a la maniere d'une variable global)
    ajoutListe(&l1,c5);                                                             //ajout d'un element contenat c5 dans liste l1(a partir de son adresse modfication a la maniere d'une variable global)
    ajoutListe(&l1,c6);                                                             //ajout d'un element contenat c6 dans liste l1(a partir de son adresse modfication a la maniere d'une variable global)
    printf(" -- AJOUT LISTE, taille =%d -- \n",tailleListe(l1));                    //affichee le nombre d'element dans la liste 
    printlist(l1);                                                                  //affiche tous les coureurs contenue dans les elements d'une liste 
    effacerCoureur(&l1,c2);                                                         //
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
    liste l;printlist
    l.debut=initElement();
    l.fin=initElement();
    l.courant=initElement();
    return l;
}

void ajoutListe(liste * listeActuel,coureur * leCoureur)                                  //avec "leCoureur" le coureur a rajouter 
{
    struct element * elementActuel = (struct element *)malloc(sizeof(struct element));    //declaration et allocation  en memoire(a l'adresse *elementActuel) d'une taille de structure element de type element (Creation element vierge de taille element)
    elementActuel->coureurActuel=leCoureur;                                               //dans la variable elementActuel le champ coureurActuel devient  leCourreur                                           (l'element vierge est remplie avec le coureur a rajoute)
    elementActuel->suiv=listeActuel->courant;                                             //dans la variable elementActuel le champ suiv devient le poiteur courant                                             (l'element vierge poite sur le debut le poiteur courant (le premier element)chainage)
    listeActuel->debut=elementActuel;                                                     //le poiteur de premiere element contenue dans liste pointe sur le nouvelle element
    listeActuel->courant=elementActuel;                                                   //le poiteur courant contenue dans la liste pointe sur le nouvelle element
}

void printlist(liste l)                                                                   //avec l la liste a affichée
{
    struct element * eCourant = l.courant;                                                //decleration d'un poiteur eCourant egale au poiteur courant (variable temporaire)

    while(eCourant->suiv != l.fin)                                                        //Tant que eCourant n'est pas égale a l'adresse du derniere element faire :
    {
        afficherCoureur(eCourant->coureurActuel);                                         //affichee le coureur dans l'element d'adresse eCourant
        eCourant=eCourant->suiv;                                                          //eCourant devient l'adresse de l'element suivant
    }
    printf("NULL \n");                                                                    //affiche la valeur du dernier element 
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

coureur * coureurCourant(liste * l)//------------------------------------------------------------------------Artefacte
{
    return l->courant->coureurActuel;
}

void effacerCoureur(liste * listeActuel,coureur * coureurSuppr)
{
    struct element * eParcours = listeActuel->courant;
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

int tailleListe(liste l)
{
    int returnValue=0;
    struct element * elementActuel = l.courant;
    while(elementActuel->suiv != l.fin->suiv)
    {
        returnValue++;
        elementActuel=elementActuel->suiv;
    };
    return returnValue;
}

coureur * getCoureur(liste l,int nb)
{
    struct element * elementCourant = l.courant;
    for(int i=0;i<nb;i++)
    {
        elementCourant=elementCourant->suiv;
    }
    return elementCourant->coureurActuel;
}

void invertCoureur(liste * l,int nb)
{
    struct element * elementCourant = l->courant;
    struct element * elementPrecedent = (struct element *)(malloc(sizeof(struct element)));
    for(int i=0;i<nb;i++)
    {
        elementPrecedent = elementCourant;
        elementCourant=elementCourant->suiv;
    }
    struct element * elementSuivant = elementCourant->suiv;
    elementCourant->suiv=elementSuivant->suiv;
    elementSuivant->suiv=elementCourant;
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
            printlist(*l);
        }
        if(tabOrdered)
        {
            return;
        }
    }
}