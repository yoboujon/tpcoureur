/**
 * @file coureur.c
 * @author Yohan Boujon (boujon@insa-toulouse.fr)
 * @author Simon Paris (pari@insa-toulouse.fr)
 * @brief Gère les coureurs
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../header/coureur.h"                                        


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


void ajouterTemps(int leTemps,coureur * leCoureur)          
{                                                           
    leCoureur->temps+=leTemps;                              
}                                                           

void afficherCoureur(coureur * leCoureur)                   
{                                                           
    int heure,minute,seconde;
    formatSecond(leCoureur->temps, &heure, &minute, &seconde);   
     
    printf("Nom : %s\tPrenom : %s\tDossard : %d\tEquipe : %s\tTemps : %d:%d:%d\n",leCoureur->nom,leCoureur->prenom,leCoureur->dossard,leCoureur->equipe,heure,minute,seconde);
}


void formatSecond(int secondsIN, int* hour, int* minute, int* second)
{
    *hour = (int)(secondsIN)/3600;                   
    *minute = (int)((secondsIN-(*hour)*3600)/60);       
    *second = secondsIN-((*hour)*3600+(*minute)*60);
}