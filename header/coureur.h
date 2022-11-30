#ifndef HEADER_COUREUR
#define HEADER_COUREUR
#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h>                                

typedef struct{                                     //definition de la structure coureur
    char * nom;                                     
    char * prenom;
    int dossard;
    char * equipe;
    int temps;
} coureur;

//Prototype 
coureur * creerCoureur(char nom[],char prenom[],int dossard, char equipe[],int temps);//Creation d'un coureur en memoire avec recupération de son adrresse avec le parametrage de c'est different champs 
void ajouterTemps(int leTemps,coureur * leCoureur);                                   //Modifier le temps d'un coureur a partir de son adresse et d'une valeur de cumule 
void afficherCoureur(coureur * leCoureur);                                            //Afficher le temps d'un coureur stocker en seconde sous forme d'heures, de minutes et de secondes ( a partir de l'adresse de sa structure de définition)
void formatSecond(int secondsIN, int* hour, int* minute, int* second);
#endif