# TD4 Langage C
Pour executer ce code il suffit de le compiler à l'aide de gcc
>gcc -Wall td4.c -o td4

>./td4

Normalement les valeurs retournées devraient être les suivants :
![capture](capture.png)

Les structures sont définies comme suivant :
### Element
- **int** : Valeur
- **struct element \*** : Element suivant
### Liste
- **struct element \*** : Premier élément dans la liste, dernier ajouté
- **struct element \*** : Dernier élément, doit être NULL
