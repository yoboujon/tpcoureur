/**
 * @file coureur.h
 * @author Yohan Boujon (boujon@insa-toulouse.fr)
 * @author Simon Paris (pari@insa-toulouse.fr)
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HEADER_COUREUR
#define HEADER_COUREUR
#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h>                                

/**
 * @struct coureur
 * @brief definition de la structure d'un coureur
 * 
 * @var coureur::nom
 * Nom du coureur
 * @var coureur::prenom
 * Prénom du coureur
 * @var coureur::dossard
 * Numéro de dossard du coureur
 * @var coureur::equipe
 * Nom de l'équipe du coureur
 * @var coureur::temps
 * Son temps en seconde
 */
typedef struct{
    char * nom;                                     
    char * prenom;
    int dossard;
    char * equipe;
    int temps;
} coureur;

/**
 * @brief Creation d'un coureur en memoire avec recupération de son adresse avec le parametrage de ses differents champs
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
coureur * creerCoureur(char nom[],char prenom[],int dossard, char equipe[],int temps);

/**
 * @brief Modifier le temps d'un coureur a partir de son adresse et d'une valeur de cumule
 * 
 * @param leTemps Temps que l'on souhaite cumulee au temps actuel d'un coureur 
 * @param leCoureur Represente le coureur dont on modifie le temps 
 */
void ajouterTemps(int leTemps,coureur * leCoureur);                                   

/**
 * @brief Afficher le temps d'un coureur stocker en seconde sous forme d'heures, de minutes et de secondes ( a partir de l'adresse de sa structure):
 *  Affiche egalement le contenue des autres champs 
 * @param leCoureur Represente le coureur dont on souhaite affichée le temps 
 */
void afficherCoureur(coureur * leCoureur);                                            

/**
 * @brief Convertion des secondes à un format heures,minutes et secondes
 * -calcul d'heures qui renvoie uniquement la partie entier
 * -calcul de minutes qui renvoie uniquement la partie entier avec la prise en compte des heures soustraite en minutes
 * -calcul de seconde qui renvoie uniquement la partie entier avec la prise en compte des heures soustraite en secondes et des minutes en secondes
 * 
 * @param secondsIN les secondes à rentrer
 * @param hour les heures en sortie
 * @param minute les minutes en sortie
 * @param second les secondes en sortie
 */
void formatSecond(int secondsIN, int* hour, int* minute, int* second);
#endif