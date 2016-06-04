/* --------------------------- c402.c --------------------------------------- */
/* T�ma: Nerekurzivn� implementace operac� nad BVS 
**                           Implementace: Petr P�ikryl, prosinec 1994
**                                 �pravy: Petr P�ikryl, listopad 1997
**                                         Petr P�ikryl, kv�ten 1998
**               P�epracovan� do jazyku c: Martin Tu�ek, srpen 2005
**
** S vyu�it�m dynamick�ho p�id�lov�n� pam�ti, implementujte
** n�sleduj�c� operace nad bin�rn�m vyhled�vac�m stromem -- v�e NEREKURZIVN�.
** (BT znamen� Binary Tree; Tato p�edpona je u procedur uvedena kv�li mo�n�
** kolizi jmen v ostatn�ch p��kladech):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivn� vlo�en� nov�ho uzlu do stromu
**     BTPreorder ...... nerekurzivn� pr�chod typu pre-order
**     BTInorder ....... nerekurzivn� pr�chod typu in-order
**     BTPostorder ..... nerekurzivn� pr�chod typu post-order
**     BTDisposeTree ... zru� v�echny uzly stromu
**
** U v�ech procedur, kter� vyu��vaj� n�kter� z pr�chod� stromem, deklarujte
** lok�ln� proceduru nazvanou Leftmost -- nalezen� nejlev�j��ho uzlu
** v podstromu (viz p�edn�ky, kde se tato procedura jmenovala Nejlev).
**
** Definice typ� naleznete v souboru c402.h; uzel stromu je typu tBTNode,
** ukazatel na n�j je typu tBTNodePtr, uzel obsahuje polo�ku int Cont
** (obsah) a ukazatele LPtr a RPtr.
**
** P��klad slou�� zejm�na k procvi�en� nerekurzivn�ch z�pis� algoritm�
** nad stromy. Ne� za�nete tento p��klad �e�it, prostudujte si d�kladn�
** principy p�evodu rekurzivn�ch algoritm� na nerekurzivn�. Programov�n�
** je p�edev��m in�en�rsk� discipl�na, kde op�tn� objevov�n� Ameriky nem�
** m�sto. Pokud se v�m zd�, �e by n�co �lo zapsat optim�ln�ji, promyslete
** si v�echny detaily va�eho �e�en�. Pov�imn�te si typick�ho um�st�n� akc�
** pro r�zn� typy pr�chod�. Zamyslete se nad modifikac� �e�en�ch algoritm�
** pro v�po�et po�tu uzl� stromu, po�tu list� stromu, v��ky stromu a pro
** vytvo�en� zrcadlov�ho obrazu stromu (pouze pop�ehazov�n� ukazatel� bez
** vytv��en� nov�ch uzl� a ru�en� star�ch).
**
** P�i pr�chodech stromem pou�ijte ke zpracov�n� uzlu proceduru BTWorkOut().
** Pro pr�ci se z�sobn�ky pou�ijte rovn� p�edem p�ipraven� procedury
** a funkce. K dispozici m�te z�sobn�ky pro hodnoty typu boolean
** a tBTNodePtr (SInit*, SPush*, STopPop*, SEmpty*, kde m�sto '*' pou�ijete
** 'P' pro z�sobn�k s ukazateli nebo 'B' pro z�sobn�k s boolovsk�mi hodnotami.
**
** !Upozorn�n�! Je t�eba, abyste spravn� rozli�ovali, kdy pou�it dereferen�n� 
** oper�tor * na samotn� ukazatel a kdy budeme pracovat pouze se samotn�m 
** ukazatelem (prohledavaci fce). V techto �loh�ch pozn�te tuto skute�nost 
** predev��m pomoc� prototypu t�chto funkc�. V situaci, kdy pracujeme s 
** ukazatelem na ukazatel, je t�eba pou��t dereferenci.
*/
#include "c402.h"
int solved;
int errflg;

void BTWorkOut (tBTNodePtr Ptr) {
/* Pomocn� procedura pou��van� p�i pr�chodech stromem.
** Zpracuje uzel, na kter� ukazuje Ptr. 
** Nemodifikovat!
*/

  if (Ptr == NULL) 
    printf("NULL\n");
  else 
    printf("Vypis hodnoty daneho uzlu> %d\n", Ptr->Cont);
}
  
/* -------------------------------------------------------------------------- */
/* Implementace z�sobn�k� je velmi zjednodu�ena. Zdrojov� text je form�tov�n
** s ohledem na �sporu m�sta a nen� p��li� komentov�n (neberte si z toho
** p��klad -- kdy�, tak odstra�uj�c�). Definice datovych struktur, viz. 
** hlavickovy soubor. 
*/

/* *********************** OPERACE SE Z�SOBN�KEM **************************** */

/* ----------------------- Z�sobn�k ukazatel�: ------------------------------ */
void SInitP (tStackP *S) {
/* inicializace z�sobn�ku ukazatel� */
  S->top = 0;  
}

void SPushP (tStackP *S, tBTNodePtr ptr) {
/* vlo�� hodnotu na vrchol z�sobn�ku */
  if (S->top==MAXSTACK) 
    printf("P�ete�en� z�sobn�ku s ukazateli!\n");
  else {  
    S->top++;  
    S->a[S->top] = ptr;  
  }
}

tBTNodePtr STopPopP (tStackP *S) {
/* vrac� odstran�nou hodnotu */
  if (S->top == 0)  {
    printf("Podte�en� z�sobn�ku s ukazateli!\n");
    return(NULL);  
  }
  else {
    return (S->a[S->top--]);
  }
}

bool SEmptyP (tStackP *S) {
/* test na pr�zdnost z�sobn�ku */
  if (S->top == 0)
    return(true);
  else
    return(false);
}


/* ----------------------- Z�sobn�k boolovsk�ch hodnot: --------------------- */
void SInitB (tStackB *S) {
/* inicializace z�sobn�ku */
  S->top = 0;  
}

void SPushB (tStackB *S,bool val) {
/* vlo�� hodnotu na vrchol z�sobn�ku */
  if (S->top == MAXSTACK) 
    printf("P�ete�en� z�sobn�ku pro boolean!\n");
  else {
    S->top++;  
    S->a[S->top] = val;
  }
}

bool STopPopB (tStackB *S) {
/* vrac� odstran�nou hodnotu */
  if (S->top == 0) {
    printf("Podte�en� z�sobn�ku pro boolean!\n");
    return(NULL);  
  } 
  else {
    return(S->a[S->top--]); 
  }
}

bool SEmptyB (tStackB *S) {
  if (S->top == 0)
    return(true);
  else 
    return(false);  
}

/* ---------------------------------- INIT ---------------------------------- */
void BTInit (tBTNodePtr *RootPtr) {
/* Inicializace stromu. Sm� se volat pouze p�ed prvn�m pou�it�m
** konkr�tn�ho bin�rn�ho stromu, proto�e neuvol�uje uzly nepr�zdn�ho
** stromu (ani to d�lat nem��e). K ru�en� nepr�zdn�ho stromu slou��
** procedura BTDisposeTree (viz d�le).
**
** V�imn�te si, �e zde se poprv� v hlavi�ce objevuje typ ukazatel na ukazatel,
** proto je t�eba p�i pr�ci s RootPtr(p�i�azen�) pou��t dereferen�n� operator.
** Ten bude je�t� t�eba pou��t v procedur�ch BTInsert() a BTDisposeTree().
*/

  *RootPtr = NULL;

}


void BTInsert (tBTNodePtr *RootPtr, int Content) {
/* Vlo�� do stromu nov� uzel s hodnotou 'Content'. Z pohledu vkl�d�n�
** ch�pejte vytv��en� strom jako bin�rn� vyhled�vac� strom (BVS = BST),
** kde uzly s hodnotou men�� ne� m� otec le�� v lev�m podstromu, uzly v�t��
** le�� vpravo. Pokud vkl�dan� uzel ji� existuje, neprov�d� se nic (hodnota
** se ve stromu vyskytuje maxim�ln� jedenkr�t). Pokud se vytv��� nov� uzel,
** vznik� v�dy jako list stromu. �e�te nerekurzivn�.
*/
  tBTNodePtr fptr;  /* ukazatel na otcovsk� uzel F */
  tBTNodePtr ptr;   /* pomocn� ukazatel */
  bool myend;       /* p��znak ukon�en� cyklu */

/* V p��pad�, kdy strom nen� pr�zdn�, mus�me vyhledat m�sto, kam by se nov� 
** hodnota m�la vlo�it. Pokud uzel se zadanou hodnotou ji� existuje, ned�l�me 
** nic. Pokud se bude uzel vytv��et, mus�me si pamatovat ukazatel na otce, 
** na kter�ho bude nov� uzel p�ipojen.
*/

  if(*RootPtr == NULL) {
    if(!(*RootPtr = malloc(sizeof(struct tBTNode)))) {
      printf("M�lo pam�ti!\n");
    }
    else {
      (*RootPtr)->Cont = Content;
      (*RootPtr)->LPtr = NULL;
      (*RootPtr)->RPtr = NULL;
    }
  }
  else {
    fptr = *RootPtr;
    myend = true;
  
    while(myend) {
      if(fptr->Cont > Content) {
        if(fptr->LPtr == NULL) {
          ptr = malloc(sizeof(struct tBTNode));
          ptr->Cont = Content;
          ptr->LPtr = NULL;
          ptr->RPtr = NULL;
          fptr->LPtr = ptr;
          myend = false;
        }
        else {
          fptr = fptr->LPtr;
        }
      }
      else if(fptr->Cont < Content) {
        if(fptr->RPtr == NULL) {
          ptr = malloc(sizeof(struct tBTNode));
          ptr->Cont = Content;
          ptr->LPtr = NULL;
          ptr->RPtr = NULL;
          fptr->RPtr = ptr;
          myend = false;
        }
        else {
          fptr = fptr->RPtr;
        }
      }
      else {
        myend = false;
      }
    }
  }

}

/* Nyn� n�sleduje sekce jednotliv�ch pr�chod� stromem, p�ed tvorbou Leftmost
�t�te v�dy i popisek nasleduj�ci procedury = implikace �e�en� dan�ho Leftmost */

/* ------------------------------ PREORDER ---------------------------------- */
void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack) {
/* Lok�ln� procedura BTPreorder -- funkce viz p�edn�ky.
** Pohybuje se po lev� v�tvi podstromu, a� naraz� na jeho nejlev�j�� uzel.
** Ukazatele na v�echny nav�t�ven� uzly ukl�d� do z�sobn�ku. Proto�e jde
** o pr�chod typu preorder, je nav�t�ven� uzel sou�asn� zpracov�n, pou�ijte
** BTWorkOut(). 
*/

  while(ptr != NULL) {
    BTWorkOut(ptr);
    SPushP(Stack, ptr);
    ptr = ptr->LPtr;
  }

}

void BTPreorder (tBTNodePtr RootPtr) {
/* Samotn� nerekurzivn� pr�chod typu pre-order, pou�ijte dan� Leftmost_Preorder
** dle predn�ek. 
*/
  tStackP Stack ;  /* z�sobn�k ukazatel� */
  tBTNodePtr ptr;  /* pomocn� ukazatel na uzel */

  SInitP(&Stack);
  ptr = NULL;

  if(RootPtr != NULL) {
    Leftmost_Preorder(RootPtr, &Stack);
  
    while(!SEmptyP(&Stack)) {
      ptr = STopPopP(&Stack);
      Leftmost_Preorder(ptr->RPtr, &Stack);
    }
  }
}


/* ------------------------------ IN ORDER ---------------------------------- */
void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack) {
/* Lok�ln� procedura BTInorder -- funkce viz p�edn�ky.
** Pohybuje se po lev� v�tvi podstromu, a� naraz� na jeho nejlev�j�� uzel.
** Ukazatele na v�echny nav�t�ven� uzly ukl�d� do z�sobn�ku. 
*/

  while(ptr != NULL) {
    SPushP(Stack, ptr);
    ptr = ptr->LPtr;
  }
}


void BTInorder (tBTNodePtr RootPtr) {
/* Nerekurzivn� pr�chod typu in-order. Pro zpracov�n� uzlu volejte
** proceduru BTWorkOut a pracujte s LeftMost_Inorder.
*/
  tStackP Stack;  /* z�sobn�k ukazatel� */
  tBTNodePtr ptr; /* pomocn� ukazatel na uzel */

  SInitP(&Stack);
  ptr = NULL;

  if(RootPtr != NULL) {
    Leftmost_Inorder(RootPtr, &Stack);
  
    while(!SEmptyP(&Stack)) {
      ptr = STopPopP(&Stack);
      BTWorkOut(ptr);
      Leftmost_Inorder(ptr->RPtr, &Stack);
    }
  }
}


/* ------------------------------ POST ORDER -------------------------------- */
void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/* Lok�ln� procedura pro Postorder -- funkce viz p�edn�ky.
** Pohybuje se po lev� v�tvi podstromu, a� naraz� na jeho nejlev�j�� uzel.
** Ukazatele na v�echny nav�t�ven� uzly ukl�d� do z�sobn�ku. Proto�e jde
** o pr�chod typu postorder, je sou�asn� do boolovsk�ho z�sobn�ku ukl�d�na
** hodnota, kter� ��k�, �e uzel byl nav�t�ven poprv� (p�i pr�chodu do
** lev�ho podstromu) a �e se tedy je�t� nem� zpracov�vat.
*/

  while(ptr != NULL) {
    SPushP(StackP, ptr);
    SPushB(StackB, true);
    ptr = ptr->LPtr;
  }

}


void BTPostorder (tBTNodePtr RootPtr) {
/* Nerekurzivn� pr�chod typu post-order. Pro zpracov�n� uzlu volejte
** proceduru BTWorkOut.
*/
  tStackP StackP;  /* z�sobn�k ukazatel� */
  tBTNodePtr ptr;  /* pomocn� ukazatel na uzel */
  tStackB StackB;  /* z�sobn�k boolovsk�ch hodnot */

  SInitP(&StackP);
  SInitB(&StackB);
  ptr = NULL;

  if(RootPtr != NULL) {
    Leftmost_Postorder(RootPtr, &StackP, &StackB);
  
    while(!SEmptyP(&StackP)) {
      if(STopPopB(&StackB)){
        ptr = STopPopP(&StackP);
        SPushP(&StackP, ptr);
        SPushB(&StackB, false);
        Leftmost_Postorder(ptr->RPtr, &StackP, &StackB);
      }
      else {
        ptr = STopPopP(&StackP);
        BTWorkOut(ptr);
      }
    }
  }
}

/* ------------------------------ DISPOSE ----------------------------------- */
void BTDisposeTree (tBTNodePtr *RootPtr)  {
/* Zru�� v�echny uzly stromu -- uvoln� jimi zab�ran� prostor vol�n�m
** standardn� funkce free.
**
** Pozn.: p�i ru�en� uzl� stromu nen� d�le�it�, v jak�m po�ad� se budou ru�it,
** proto m��ete uva�ovat i jin� varianty, ne� klasick� typy pr�chodu stromem.
*/
  tStackP S;       /* z�sobn�k ukazatel� */
  tBTNodePtr ptr;  /* pomocn� ukazatel na uzel */
  
  SInitP(&S);
  ptr = *RootPtr;

  while(ptr != NULL) {
    if(ptr->LPtr != NULL)
      SPushP(&S, ptr->LPtr);
      
    if(ptr->RPtr != NULL)
      SPushP(&S, ptr->RPtr);
      
    free(ptr);
      
    if(!SEmptyP(&S))
      ptr = STopPopP(&S);
    else
      ptr = NULL;
  }
  
  *RootPtr = NULL;
}

/* ----------------------------- konec c402.c ------------------------------- */
