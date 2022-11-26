#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h>

int getNbLines(FILE * readFile);
int getFileSize(FILE * readFile);
void getStringFromFile(FILE * readFile,int nbLines,char * returnString,int * size);
char * getLine(char * string,int line);
void string2Coureur(char * string,int nbLines);