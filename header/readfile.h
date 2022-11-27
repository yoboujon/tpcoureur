#ifndef HEADER_READFILE
#define HEADER_READFILE
#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h>
#include "liste.h"

int getNbLines(FILE * readFile);
int getFileSize(FILE * readFile);
void getStringFromFile(FILE * readFile,int nbLines,char * returnString,int * size);
char * getLine(char * string,int line);
liste string2Liste(char * string,int nbLines);
void string2Coureur(char * string,char * nom, char * prenom, int * dossard);
void printHexString(char * string);
#endif