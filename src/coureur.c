#include "../header/coureur.h"                                        //inclure le fichier "coureur.h" qui contien les libs, structure et prototypes

/**
 * @brief Creation d'un coureur en memoire avec recupération de son adrresse avec le parametrage de c'est different champs
    fonctionnement :
    -strcpy pour remplir les champs
    -strlen renvoie taille d'une chaine pour une allocation exacte
 * 
 * @param nom 
 * @param prenom 
 * @param dossard 
 * @param equipe 
 * @param temps 
 * @return coureur* l'adresse qui pointe sur la structure cree 
 */
coureur * creerCoureur(char nom[],char prenom[],int dossard, char equipe[],int temps) 
{
    coureur * leCoureur = malloc(sizeof(coureur));          

    leCoureur->nom = malloc(sizeof(char)*strlen(nom));      
    strcpy(leCoureur->nom,nom);                             
    leCoureur->prenom = malloc(sizeof(char)*strlen(prenom));
    strcpy(leCoureur->prenom,prenom);                       
    leCoureur->equipe = malloc(sizeof(char)*strlen(equipe));
    strcpy(leCoureur->equipe,equipe);                       

    leCoureur->temps=temps;                                 
    leCoureur->dossard=dossard;                             

    return leCoureur;                                       
}                                                           

/**
 * @brief Modifier le temps d'un coureur a partir de son adresse et d'une valeur de cumule
 * 
 * @param leTemps Temps que l'on souhaite cumulee au temps actuel d'un coureur 
 * @param leCoureur Represente le coureur dont on modifie le temps 
 */
void ajouterTemps(int leTemps,coureur * leCoureur)          
{                                                           
    leCoureur->temps+=leTemps;                              
}                                                           

/**
 * @brief Afficher le temps d'un coureur stocker en seconde sous forme d'heures, de minutes et de secondes ( a partir de l'adresse de sa structure):
    -initilisation de 3 variable tampon
    -calcul d'heures qui renvoie uniquement la partie entier
    -calcul de minutes qui renvoie uniquement la partie entier avec la prise en compte des heures soustraite en minutes
    -calcul de seconde qui renvoie uniquement la partie entier avec la prise en compte des heures soustraite en secondes et des minutes en secondes
 
 * @param leCoureur Represente le coureur dont on souhaite affichée le temps 
 */
void afficherCoureur(coureur * leCoureur)                   
{                                                           
    int heure,minute,seconde;                               
    heure = (int)(leCoureur->temps)/3600;                   
    minute = (int)((leCoureur->temps-heure*3600)/60);       
    seconde = leCoureur->temps-(heure*3600+minute*60);      
     
    printf("Nom : %s\tPrenom : %s\tDossard : %d\tEquipe : %s\tTemps : %d:%d:%d\n",leCoureur->nom,leCoureur->prenom,leCoureur->dossard,leCoureur->equipe,heure,minute,seconde);
}