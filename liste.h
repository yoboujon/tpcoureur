#include "coureur.h"                                            //inclure le fichier "coureur.h" qui contien les libs et la structure coureur 

struct element{                                                 //definition de la structure qui element qui sera encaspule/chaine
    coureur * coureurActuel;                                    //"contient" l'adresse d'une structure coureur
    struct element * suiv;                                      //"contient" l'adresse d'une autre strucutre element(chainage)
};

typedef struct{                                                 //definition de la structure liste qui "contient" l'encaspsulation 
    struct element * debut;                                     //"contient" un element en debut                *voir init dans liste.c
    struct element * courant;                                   //"contient"element actuel                      *voir init dans liste.c
    struct element * fin;                                       //"contient"element en fin de la liste (NULL)   *voir init dans liste.c
} liste;

//Prototype de fonction 
struct element * initElement(void);                             //initialise un element en memoir qui encapsule une strucure de coureurau champs vide
liste initListe(void);                                          //initialise chaque element de la liste a partir de initElement
void ajoutListe(liste * listeActuel,coureur * leCoureur);       //ajoute un element contenant un courreur dans le chainage d'une liste 
void printlist(liste l);                                        //afficher le coureur dans chaque element d'une liste 
void allerDebut(liste * l);                                     //mettre le poiteur courant sur l'element premier d'une liste
void allerFin(liste * l);                                       //mettre le poiteur courant sur l'element de fin d'une liste 
void avancer(liste * l);                                        //mettre le poiteur courant sur l'element suivant de la liste dans la qu'elle qu'il pointe
coureur * coureurCourant(liste * l);                            //rien a foutre ici
void effacerCoureur(liste * listeActuel,coureur * coureurSuppr);//enleve un element d'une liste a partir de l'adresse d'un courreur, sans briser le chainage
int tailleListe(liste l);                                       //retourne le nombre d'elements chaine d'une liste
coureur * getCoureur(liste l,int nb);                           //
void invertCoureur(liste * l,int nb);                           //
void triListe(liste * l,int taille);                            //trie bulle des element d'une liste a partir du temps contenue dans la structure encapsule dans l'element