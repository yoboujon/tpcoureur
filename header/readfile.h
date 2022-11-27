#ifndef HEADER_READFILE
#define HEADER_READFILE
#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h>
#include "liste.h"

int getNbLines(void);
int getFileSize(FILE * readFile);
liste getStringFromFile(int nbLines,int * size, int * stepsNb,int * teamsNb);
char * getLine(char * string,int line);
liste string2Liste(char * string,int nbLines);
void string2Coureur(char * string,char * nom, char * prenom, int * dossard);
void deleteLineFeed(char * string);
void printHexString(char * string);
#endif