/**
 * @file readfile.h
 * @author Yohan Boujon (boujon@insa-toulouse.fr)
 * @author Simon Paris (pari@insa-toulouse.fr)
 * @version 1.0
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HEADER_READFILE
#define HEADER_READFILE
#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h>
#include "liste.h"
#define MAXLINE 50

/**
 * @brief Récupère le nombre de ligne d'un fichier
 * 
 * @param readFile le fichier en question 
 * @return int nombre de ligne
 */
int getNbLines(void);

/**
 * @brief Converti les caractères d'un fichier dans la liste de coureur.
 * 
 * @param nbLines nombre de ligne du fichier qui va être lu
 * @param size renvoie la taille de la chaîne de caractère
 * @param stepsNb int * renvoi le nombre d'étapes
 * @param teamsNb int * renvoi le nombre d'équipes
 * @return liste de coureurs
 */
int getFileSize(FILE * readFile);

/**
 * @brief récupère la taille du fichier, est assez grossier et ne sert qu'à
 * initialiser les tableaux pour ne pas avoir une taille à prédéfinir.
 * 
 * @param readFile fichier en question
 * @return int taille du fichier
 */
liste getListFromFile(int nbLines,int * size, int * stepsNb,int * teamsNb);

/**
 * @brief /!\/!\/!\ Debug uniquement /!\/!\/!\ : 
 * récupère une ligne, non optimisé donc inutilisable
 * 
 * @param string la chaîne de caractère à analyser
 * @param line int la ligne à récupérer
 * @return char* la ligne sous un string
 */
char * getLine(char * string,int line);

/**
 * @brief /!\/!\/!\ INUTILISE CAR OBSELETE /!\/!\/!\ :
 * Renvoi une liste à partir d'une chaîne de caractère contenant
 * les équipes ainsi que les coureurs avec leur nom, leur prénom et numéro de dossard
 * 
 * @param string chaîne de caractère
 * @param nbLines nombre de ligne max de la chaîne de caractère
 * @return liste des coureurs
 */
liste string2Liste(char * string,int nbLines);

/**
 * @brief A partir d'une ligne récupère les informations sur le coureur,
 * Notamment son numéro de dossard, son nom et son prénom
 * 
 * @param string    char * ligne textuel
 * @param nom       char * renvoi le nom du coureur, doit être vide
 * @param prenom    char * renvoi le nom du coureur, doit être vide
 * @param dossard   int * renvoi le numéro du dossard
 */
void string2Coureur(char * string,char * nom, char * prenom, int * dossard);

/**
 * @brief Supprime les retours à la ligne dans les chaînes de caractère.
 * Attention ! les remplace par le caractère signifiant la fin de la chaîne.
 * 
 * @param string chaîne de caractère
 */
void deleteLineFeed(char * string);

/**
 * @brief /!\/!\/!\ Debug uniquement /!\/!\/!\ :
 * Permet d'observer les valeurs de chaque caractère.
 * la taille n'est pas demandée pour observer au delà de l'espace mémoire donné
 * 
 * @param string un tableau de caractère
 */
void printHexString(char * string);
#endif