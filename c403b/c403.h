
/* Hlavi�kov� soubor pro c403.c - Vyhled�vac� tabulka v nese�azen�m 
poli se zar. (optimalizace), obsahuje jednak nutn� includes a 
externovan� prom�nn�, ale rovne� definici datov�ch typ�, se kter�mi 
se pracuje v p��slu�n�ch �loh�ch. Nemodifikovat! */

/* ********************** SOUBOR S HLAVI�KOU ********************** */
/* ********************** ------------------ ********************** */

/*  vytvo�il: Martin Tu�ek
    p�edm�t: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologi�)
    hlavicka pro soubor: c403.c
    datum: z��� 2005                                                 */
/* ***************************************************************** */


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#define ASMaxSize 50        /* Maxim�ln� velikost pole pro implementaci
			       vyhled�vac� tabulky. �e�en� procedury v�ak
			       vyu��vaj� pouze ASSize prvk� pole (viz
			       deklarace t�to prom�nn�). */
#define FALSE 0
#define TRUE 1

extern int solved;
extern int errflg;
extern int ASCompNum;       /* Prom�nn�, kter� bude uchov�vat po�et porovn�n� */

typedef struct { 
/* datov� z�znam */
        int Cont;                /* zde se bude ukl�dat obsah  */
        int Key;     	         /* a zde kl�� */
} tASData;

typedef struct  {
/* tabulka implementovan� polem */
   tASData arr[ASMaxSize];  /* pole pro datov� polo�ky */
   int last;                /* index posledn� vyu�it� polo�ky pole */
} tASTable;

int ASSize;          /* Pro ��ely testov�n� je vhodn� m�t mo�nost
                        volby velikosti pole, kter�m je vyhled�vac�
                        tabulka implementov�na. Fyzicky je
                        deklarov�no pole o rozm�ru ASMaxSize, ale
                        p�i implementaci va�ich procedur uva�ujte
                        velikost ASSize! */


/****prototypes*****/
void ASInit   (tASTable *);
int  ASSearch (tASTable *, int , int* );
void ASInsert (tASTable *, int, int );
/*******end of prototypes**************/

