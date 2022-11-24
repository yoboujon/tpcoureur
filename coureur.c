#include "coureur.h"                                        //inclure le fichier "coureur.h" qui contien les libs, structure et prototypes

// Creation d'un coureur en memoire avec recupération de son adrresse avec le parametrage de c'est different champs 
coureur * creerCoureur(char nom[],char prenom[],int dossard, char equipe[],int temps) 
{
    coureur * leCoureur = malloc(sizeof(coureur));          //initilisation taille memoire taille de structure

    leCoureur->nom = malloc(sizeof(char)*strlen(nom));      //initilisation taille memoire 4oct*tailleChaine
    strcpy(leCoureur->nom,nom);                             //copy de nom(para) dans le champs nom de la structure leCoureur
    leCoureur->prenom = malloc(sizeof(char)*strlen(prenom));//initilisation taille memoire 4oct*tailleChaine
    strcpy(leCoureur->prenom,prenom);                       //copy de prenom(para) dans le champs prenom de la structure leCoureur
    leCoureur->equipe = malloc(sizeof(char)*strlen(equipe));//initilisation taille memoire 4oct*tailleChaine
    strcpy(leCoureur->equipe,equipe);                       //copy de equipe(para) dans le champs equipe de la structure leCoureur

    leCoureur->temps=temps;                                 //ecriture temps(para) dans le champs temps de la structure leCoureur
    leCoureur->dossard=dossard;                             //ecriture dossard un int dans le champs dossard de la structure leCoureur

    return leCoureur;                                       //retour addresse de la structure crée "leCoureur"
}                                                           


//Modifier le temps d'un coureur a partir de son adresse et d'une valeur de cumule 
void ajouterTemps(int leTemps,coureur * leCoureur)          
{                                                           
    leCoureur->temps+=leTemps;                              //Cumul du champ temps appartenant a la structure leCoureur avec leTemp(para) qui est un int
}                                                           
                                                             
//Afficher le temps d'un coureur stocker en seconde sous forme d'heures, de minutes et de secondes ( a partir de l'adresse de sa structure de définition)
void afficherCoureur(coureur * leCoureur)                   
{                                                           
    int heure,minute,seconde;                               //initilisation de 3 variable tampon
    heure = (int)(leCoureur->temps)/3600;                   //calcul d'heures qui renvoie uniquement la partie entier
    minute = (int)((leCoureur->temps-heure*3600)/60);       //calcul de minutes qui renvoie uniquement la partie entier avec la prise en compte des heures soustraite en minutes
    seconde = leCoureur->temps-(heure*3600+minute*60);      //calcul de seconde qui renvoie uniquement la partie entier avec la prise en compte des heures soustraite en secondes et des minutes en secondes
     
    printf("Nom : %s\tPrenom : %s\tDossard : %d\tEquipe : %s\tTemps : %d:%d:%d\n",leCoureur->nom,leCoureur->prenom,leCoureur->dossard,leCoureur->equipe,heure,minute,seconde);
}