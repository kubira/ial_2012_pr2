

/* Hlavi�kov� soubor pro c401.c - rekurz�vn� implementace operaci nad BVS,
obsahuje jednak nutn� knihovny a extern� prom�nn�, ale rovn� 
definici datov�ch typ�, se kter�mi se pracuje v p��slu�n�ch 
�loh�ch. Nemodifikovat! */

/* ********************** SOUBOR S HLAVI�KOU ********************** */
/* ********************** ------------------ ********************** */

/*  vytvo�il: Martin Tu�ek
    p�edm�t: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologi�)
    hlavicka pro soubor: c401.c
    datum: z��� 2005                                                 */
/* ***************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#define TRUE 1
#define FALSE 0

extern int solved; 			/* glob�ln� prom�nn� nazna�uj�c�, zda bylo �e�eno �i nikoliv */
extern int errflg;

typedef struct tBSTNode {
	char Key;			/* podle tohoto kl��e se vyhled�v� */
	int BSTNodeCont;
	struct tBSTNode * LPtr;
	struct tBSTNode * RPtr;
} *tBSTNodePtr;	

/* prototypes */

void BSTInit   (tBSTNodePtr *);
int BSTSearch  (tBSTNodePtr ,char , int *);
void BSTInsert (tBSTNodePtr *, char, int );
void BSTDelete (tBSTNodePtr *, char );
void BSTDispose(tBSTNodePtr *);

