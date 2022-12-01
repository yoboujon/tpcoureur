/**
 * @file liste.h
 * @author Yohan Boujon (boujon@insa-toulouse.fr)
 * @author Simon Paris (pari@insa-toulouse.fr)
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HEADER_LISTE
#define HEADER_LISTE
#include <time.h>
#include "coureur.h"                                            //inclure le fichier "coureur.h" qui contien les libs et la structure coureur
#define TEMPSMAX 400
#define TEMPSMIN 80
#define TEMPSDOP 70

/**
 * @struct element
 * @brief definition de la structure qui element qui sera encaspule/chaine
 * 
 * @var element::coureurActuel
 * "contient" l'adresse d'une structure coureur
 * @var element::suiv
 * "contient" l'adresse d'une autre strucutre element(chainage)
 */
struct element{
    coureur * coureurActuel;
    struct element * suiv;
};

/**
 * @struct liste
 * @brief definition de la structure liste qui "contient" l'encaspsulation 
 * 
 * @var liste::debut
 * "contient" un element en debut
 * @var liste::courant
 * "contient"element actuel
 * @var liste::fin
 * "contient"element en fin de la liste (NULL)
 */
typedef struct{
    struct element * debut;
    struct element * courant;
    struct element * fin;
} liste;

/**
 * @brief initialise un element en memoire qui encapsule une strucure de coureur au champs vide
 * 
 * @return returnElement retourne un element vierge  
 */
struct element * initElement(void);                             

/**
 * @brief initialise chaque elements de la liste a partir de initElement
 * 
 *  
 * @return l 
 */
liste initListe(void);                                          

/**
 * @brief ajout d'un element contenant un coureur dans liste 
 * fonctionnement :
    -Creation element vierge 
    -l'element vierge recoi le coureur passer en parametre
    -l'element vierge poite sur le premier element 
    -le poiteur du premier element contenu dans liste pointe sur le nouvelle element(vierge)
    -le poiteur courant contenu dans la liste pointe sur le nouvelle element
 * @param listeActuel liste ou l'on rajoute un element
 * @param leCoureur   le coureur qui sera contenu dans l'element rajoutee
 */
void ajoutListe(liste * listeActuel,coureur * leCoureur);       

/**
 * @brief affiche tous les coureurs contenu dans les elements d'une liste
 * fonctionnement :
    -declaration d'un poiteur eCourant egale l'adresse du premiere element (variable temporaire)
    -Tant que eCourant->suiv n'est pas egale a l'adresse du derniere element faire :
    -affichee le coureur dans l'element d'adresse eCourant
    -eCourant devient l'adresse de l'element suivant
    
 * @param l liste a affiche
 */
void printlist(liste l);   

/**
 * @brief Mettre le poiteur courant d'une liste sur le premiere element
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */                                     
void allerDebut(liste * l);                                     

/**
 * @brief Mettre le poiteur courant d'une liste sur le derniee element
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
void allerFin(liste * l);                                       

/**
 * @brief Mettre le poiteur courant sur l'element suivant
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
void avancer(liste * l);              

/**
 * @brief Retourne le coureur encapsulee dans l'element pointer par le pointeur courant
 * 
 * @param l liste ou l'on modifie le poiteur courant
 */
coureur * coureurCourant(liste * l);                

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
    -tant que l'element poitee par eParcours ne contient pas le coureur a supprimer faire :
    -ePrevious pointe sur l'element suivant
    -eParcours pointe sur l'element suivant 
    -l'element avant celui a suprimer pointe sur l'element sur le qu'elle poite l'element a supprimer 
    -supression de l'element

 * @param listeActuel Liste ou l'on suppr un element
 * @param coureurSuppr le coureur qui doit etre dans l'element pour le supprimer 
 */
bool effacerCoureur(liste * listeActuel,coureur * coureurSuppr, bool returnSuiv);

/**
 * @brief Cherche si un coureur existe dans une liste
 * 
 * @param l la liste en question
 * @param c le coureur cherché 
 * @return true / false
 */
bool doesCoureurExist(liste* l,coureur * c);

/**
 * @brief A partir d'une liste source supprime tous les éléments en commun
 * 
 * @param destination liste à modifier
 * @param source liste des éléments à supprimer
 * @return int nombre d'éléments supprimés
 */
int effacerListe(liste * destination, liste * source);

/**
 * @brief Renvoie le nombre d'elements d'une liste
 fonctionnement :
 -initilisation a 0 d'un compteur (int)
 -declaration d'un poiteur elementActuel initialiser au poiteur debut present dans liste qui pointe sur le premier element du chainage
 -tant que elementActuel n'est pas egale a l'adresse du derniere element faire 
 -increment compteur
 -elementActuel pointe sur l'element suivant
 -retourne le compteur

 * 
 * @param l l la liste dont on ve connaitre la taille 
 * @return int le nombre d'element (on compte a partir de 0)
 */
int tailleListe(liste l);                                       

/**
 * @brief retourne le coureur contenu dans l'element nb d'une liste (on considere un element 0)
 * fonctionnement :
    -init elementCourant a l'adresse du premiere element de la liste
    -pour i allant de 0 a nb-1
    -a la fin de la boucle elementcourant pointe sur l'element nb (on considere un element 0)
    -renvoie le coureur encapsulee dans l'element nb
 * @param l la liste ou doit se trouver l'element encapsulant le coureur 
 * @param nb le numero d'element rechercher 
 * @return coureur* 
 */
coureur * getCoureur(liste l,int nb);                           

/**
 * @brief inverse l'element nb et nb+1 dans une liste (on considere un element 0)
 * fonctionnement :
    -declaration d'un poiteur elementCourant initialiser au poiteur debut present dans liste qui pointe sur le premier element du chainage
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
void invertCoureur(liste * l,int nb);                          

/**
 * @brief trie bulle des elements d'une liste a partir du temps contenu dans la structure encapsuler dans l'element
 * fonctionnement :
    -pour i allant du nombre d'element dans la liste a 2 step -1
    -pour j allant de 0 a i-1 step 1
    -si lecoureur taille -i a un temps < au coureur taille-i+1
    -inverser les coureurs j et j+1

 * @param l liste a trier
 * @param taille represente la taille de la liste 
 */
void triListe(liste * l,int taille);                            


/**
 * @brief Initialise un tableau de chaîne de caractères
 * 
 * @param sizeCol taille des colonnes
 * @param sizeLine taille de chaque ligne
 * @return int** Une matrice de caractère
 */
char ** initMatrix(int sizeCol,int sizeLine);

/**
 * @brief Detecte si une chaîne de caractères est présente dans un
 * tableau de chaîne de caractères
 * 
 * @param matrix tableau de chaîne de caractères
 * @param string chaîne de caractère
 * @param size nombre de lignes
 * @return true / false
 */
bool isStringInMatrix(char ** matrix, char * string, int size);

/**
 * @brief Donne le nom de chaque équipe dans un tableau de chaîne de caractères
 * 
 * @param matrix tableau de chaîne de caractère
 * @param sizeCol taille des colonns
 * @param sizeLine taille des lignes
 * @param l la liste composant les noms des équipes
 */
void readTeams(char ** matrix, int sizeCol, int sizeLine, liste l);

/**
 * @brief Compte le nombre de joueur dans chaque équipe et le met dans une liste
 * d'entiers
 * 
 * @param teamNames les noms de chaque équipe
 * @param sizeCol taille de la colonne des noms de chaque équipe
 * @param list la liste que l'ont veut analyser
 * @return int* tableau en commun avec le nom des équipes du nombre de joueur
 */
int * teamsCount(char ** teamNames, int sizeCol, liste list);

/**
 * @brief Elimine une équipe si elle a moins de lessThanCoureurCount
 * 
 * @param teamNames les noms de chaque équipe
 * @param sizeCol taille de la colonne des noms de chaque équipe
 * @param list la liste que l'ont veut analyser
 * @param coureursInTeams nombre de joueur par équipe
 * @param lessThanCoureurCount int
 */
void removeTeam(char ** teamNames, int sizeCol, liste * list, int * coureursInTeams, int lessThanCoureurCount);

/**
 * @brief Récupère l'élément courant de la liste
 * 
 * @param l liste
 * @return struct element* 
 */
struct element * getElementCourant(liste l);

/**
 * @brief Affiche les équipes et le nombre de coureurs
 * 
 * @param teamsNames les noms de chaque équipe
 * @param coureurInTeams nombre de coureur dans chaque équipe
 * @param teamsNB nombre d'équipes
 */
void printTeamsDetails(char ** teamsNames, int * coureurInTeams, int teamsNB);

/**
 * @brief Affiche les équipes composés d'un certain nombre de coureur 
 * 
 * @param num le nombre de coureur auquel l'équipe doit être égale
 * @param teamsNames les noms de chaque équipe
 * @param coureurInTeams nombre de coureur dans chaque équipe
 * @param teamsNB nombre d'équipes
 */
void printTeamsDetailsFor(int num, char ** teamsNames, int * coureurInTeams, int teamsNB);

/**
 * @brief Supprime les coureurs s'il y a plus de maxCoureur
 * 
 * @param maxCoureur nombre de coureur max dans une équipe
 * @param list liste à analyser
 * @param teamNames nom des équipes
 * @param sizeCol taille de la colonne des équipe/nombre d'équipes
 */
int * keepOnlyCoureur(int maxCoureur, liste * list, char ** teamNames, int sizeCol);

/**
 * @brief Tri une liste de int ainsi qu'une liste de chaîne de caractère associé
 * 
 * @param temps liste de int
 * @param taille taille de cette liste
 * @param teams liste de chaîne de caractère (doit être de la même taille)
 */
void triTemps(int * temps, int taille,char ** teams);

/**
 * @brief Affiche le temps ainsi que les équipes
 * 
 * @param temps liste de temps en int
 * @param teams liste de chaîne de caractères, les équipes
 * @param taille taille des deux listes (doivent être égales)
 * @param ignore le chiffre qui doit être ignoré (si vous voulez le désactiver, choisissez un nombre impossible)
 */
void printTeamsTimes(int * temps, char ** teams, int taille, int ignore);

/**
 * @brief Fonction de test
 * 
 * @return int renvoie zéro si réussie
 */
int test(void);
#endif