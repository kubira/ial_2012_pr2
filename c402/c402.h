
/* Hlavi�kov� soubor pro c402.c - nerekurz�vn� implementace operac� nad BVS,
obsahuje jednak nutn� knihovny a extern� prom�nn�, ale rovn� 
definici datov�ch typ�, se kter�mi se pracuje v p��slu�n�ch 
�loh�ch. Nemodifikovat! */

/* ********************** SOUBOR S HLAVI�KOU ********************** */
/* ********************** ------------------ ********************** */

/*  vytvo�il: Martin Tu�ek
    p�edm�t: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologi�)
    hlavicka pro soubor: c402.c
    datum: z��� 2005                                                 */
/* ***************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<stdbool.h>

#define FALSE 0
#define TRUE 1
#define MAXSTACK 30 			/* maxim�ln� po�et prvk� v z�sobn�ku */

extern int solved; 			/* glob�ln� prom�nn� nazna�uj�c�, zda bylo �e�eno �i nikoliv */
extern int errflg;			/* p��znak o�et�en� chyby */


typedef struct tBTNode	{		/* uzel stromu */
    int Cont;      			/* obsah uzlu  */
    struct tBTNode * LPtr;   		/* ukazatel na lev� podstrom  */
    struct tBTNode * RPtr; 	  	/* ukazatel na prav� podstrom */
} *tBTNodePtr;				/* typ ukazatel na uzel */

/* datove struktury pro praci se zasobniky */

typedef struct	{ 			/* Z�sobn�k na hodnoty typu tBTNodePtr */
    tBTNodePtr a[MAXSTACK];
    int top;
} tStackP;

typedef struct {  		    	/* Z�sobn�k na boolovsk� hodnoty. */
    bool a[MAXSTACK];
    int top;
} tStackB;


/***prototypes***/
void BTInit (tBTNodePtr * );
void BTInsert (tBTNodePtr *, int );

void Leftmost_Preorder(tBTNodePtr, tStackP *);
void BTPreorder(tBTNodePtr );

void Leftmost_Inorder(tBTNodePtr, tStackP *);
void BTInorder(tBTNodePtr );

void Leftmost_Postorder(tBTNodePtr, tStackP *, tStackB *);
void BTPostorder(tBTNodePtr );

void BTDisposeTree(tBTNodePtr *);
/********end of prototypes******/

