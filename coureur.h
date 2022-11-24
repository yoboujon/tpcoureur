#include <stdio.h>                                  //lib de base 
#include <stdlib.h>                                 //lib de base 
#include <string.h>                                 //lib de base 
#include <stdbool.h>                                //lib de base 

typedef struct{                                     //definition de la structure coureur
    char * nom;                                     
    char * prenom;
    int dossard;
    char * equipe;
    int temps;
} coureur;

//Prototype 
coureur * creerCoureur(char nom[],char prenom[],int dossard, char equipe[],int temps);// Creation d'un coureur en memoire avec recupération de son adrresse avec le parametrage de c'est different champs 
void ajouterTemps(int leTemps,coureur * leCoureur);                                   //Modifier le temps d'un coureur a partir de son adresse et d'une valeur de cumule 
void afficherCoureur(coureur * leCoureur);                                            //Afficher le temps d'un coureur stocker en seconde sous forme d'heures, de minutes et de secondes ( a partir de l'adresse de sa structure de définition)