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

  *RootPtr = NULL;  //Inicializace stromu - nastaven� na NULL

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

  if(*RootPtr == NULL) {  //Pokud je strom pr�zdn�,
    if(!(*RootPtr = malloc(sizeof(struct tBTNode)))) {
    //alokuji jeho ko�enu pam�,
      printf("M�lo pam�ti!\n");  //pokud se nepoda�� pam� alokovat - Chyba
      errflg = TRUE;
    }
    else {  //Pokud se pam� poda�ilo p�id�lit,
      (*RootPtr)->Cont = Content;  //nastav�m obsah uzlu na hodnotu Content,
      (*RootPtr)->LPtr = NULL;  //nastav�m lev�ho potomka na NULL
      (*RootPtr)->RPtr = NULL;  //a nastav�m prav�ho potomka na NULL
    }
  }
  else {  //Pokud strom nen� pr�zdn�,
    fptr = *RootPtr;  //ulo��m si do pomocn�ho ukazatele adresu ko�ene stromu
    myend = true;  //a nastav�m podm�nku cyklu na true
  
    while(myend) {  //Pokud se je�t� nepoda�ilo ulo�it nov� prvek do stromu,
      if(fptr->Cont > Content) {  //kdy� je obsah otcovsk�ho uzlu vet��
        if(fptr->LPtr == NULL) {  //a pokud nem� lev�ho potomka,
          if((ptr = malloc(sizeof(struct tBTNode)))) {
            //alokuji pam� nov�ho uzlu a kdy� se alokace poda��,
            ptr->Cont = Content;  //nastav�m mu jeho obsah,
            ptr->LPtr = NULL;  //nastav�m lev�ho potomka na NULL,
            ptr->RPtr = NULL; //nastav�m prav�ho potomka na NULL,
            fptr->LPtr = ptr;  //nov� prvek se stane lev�m potomkem otcovsk�ho uzlu 
            myend = false;  //a ukon��m cyklus nastaven�m myend na false
          }
          else {
            printf("M�lo pam�ti!\n");  //pokud se nepoda�� pam� alokovat - Chyba
            errflg = TRUE;
          }
        }
        else {  //pokud m� lev�ho potomka,
          fptr = fptr->LPtr;  //tak se stane otcovsk�m uzlem tento lev� potomek
        }
      }
      else if(fptr->Cont < Content) {  //kdy� je obsah otcovk�ho uzlu men��
        if(fptr->RPtr == NULL) {  //a pokud nem� prav�ho potomka,
          if((ptr = malloc(sizeof(struct tBTNode)))) {
            //alokuji pam� nov�ho uzlu a kdy� se alokace poda��,
            ptr->Cont = Content;  //nastav�m mu jeho obsah,
            ptr->LPtr = NULL;  //nastav�m lev�ho potomka na NULL,
            ptr->RPtr = NULL; //nastav�m prav�ho potomka na NULL,
            fptr->RPtr = ptr;  //nov� prvek se stane prav�m potomkem otcovsk�ho uzlu 
            myend = false;  //a ukon��m cyklus nastaven�m myend na false
          }
          else {
            printf("M�lo pam�ti!\n");  //pokud se nepoda�� pam� alokovat - Chyba
            errflg = TRUE;
          }
        }
        else {  //a pokud m� prav�ho potomka,
          fptr = fptr->RPtr;  //tak se stane otcovsk�m uzlem tento prav� potomek
        }
      }
      else {  //pokud ji� uzel se stejn�m obsahem existuje,
        myend = false;  //ukon�� se cyklus a ned�l� se nic
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

  while(ptr != NULL) {  //Dokud nejsem v nejlev�j��m uzlu stromu,
    BTWorkOut(ptr);  //zpracuji tento uzel,
    SPushP(Stack, ptr);  //ulo��m ho na z�sobn�k,
    ptr = ptr->LPtr;  //a nastav�m ukazatel na jeho lev�ho potomka
  }

}

void BTPreorder (tBTNodePtr RootPtr) {
/* Samotn� nerekurzivn� pr�chod typu pre-order, pou�ijte dan� Leftmost_Preorder
** dle predn�ek. 
*/
  tStackP Stack ;  /* z�sobn�k ukazatel� */
  tBTNodePtr ptr;  /* pomocn� ukazatel na uzel */

  SInitP(&Stack);  //Inicializace z�sobn�ku ukazatel�
  ptr = NULL;  //Inicializace pomocn�ho ukazatele

  if(RootPtr != NULL) {  //Pokud nen� strom pr�zdn�,
    Leftmost_Preorder(RootPtr, &Stack);  //vol�m funkci na ko�en stromu
  
    while(!SEmptyP(&Stack)) {  //Dokud nen� z�sobn�k pr�zdn�,
      ptr = STopPopP(&Stack);  //ukl�d�m do ptr ukazatel z vrcholu z�sobn�ku
      Leftmost_Preorder(ptr->RPtr, &Stack);  //a vol�m funkci na jeho prav� uzel
    }
  }
}


/* ------------------------------ IN ORDER ---------------------------------- */
void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack) {
/* Lok�ln� procedura BTInorder -- funkce viz p�edn�ky.
** Pohybuje se po lev� v�tvi podstromu, a� naraz� na jeho nejlev�j�� uzel.
** Ukazatele na v�echny nav�t�ven� uzly ukl�d� do z�sobn�ku. 
*/

  while(ptr != NULL) {  //Dokud nejsem v nejlev�j��m uzlu stromu,
    SPushP(Stack, ptr);  //ukl�d�m uzel na z�sobn�k
    ptr = ptr->LPtr;  //a nastav�m ukazatel na jeho lev�ho potomka
  }
}


void BTInorder (tBTNodePtr RootPtr) {
/* Nerekurzivn� pr�chod typu in-order. Pro zpracov�n� uzlu volejte
** proceduru BTWorkOut a pracujte s LeftMost_Inorder.
*/
  tStackP Stack;  /* z�sobn�k ukazatel� */
  tBTNodePtr ptr; /* pomocn� ukazatel na uzel */

  SInitP(&Stack);  //Inicializace z�sobn�ku ukazatel�
  ptr = NULL;  //Inicializace pomocn�ho ukazatele

  if(RootPtr != NULL) {  //Pokud nen� strom pr�zdn�,
    Leftmost_Inorder(RootPtr, &Stack);  //vol�m funkci na jeho ko�en
  
    while(!SEmptyP(&Stack)) {  //Dokud nen� z�sobn�k pr�zdn�,
      ptr = STopPopP(&Stack);  //ukl�d�m do ptr ukazatel z vrcholu z�sobn�ku,
      BTWorkOut(ptr);  //tento uzel zpracuji
      Leftmost_Inorder(ptr->RPtr, &Stack);  //a vol�m funkci na jeho prav� uzel
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

  while(ptr != NULL) {  //Dokud nejsem v nejlev�j��m uzlu stromu,
    SPushP(StackP, ptr);  //ukl�d�m uzel na z�sobn�k ukazatel�,
    SPushB(StackB, true);  //do z�sobn�ku bool hodnot ukl�d�m true
    ptr = ptr->LPtr;  //a nastav�m ukazatel na lev�ho potomka uzlu
  }

}


void BTPostorder (tBTNodePtr RootPtr) {
/* Nerekurzivn� pr�chod typu post-order. Pro zpracov�n� uzlu volejte
** proceduru BTWorkOut.
*/
  tStackP StackP;  /* z�sobn�k ukazatel� */
  tBTNodePtr ptr;  /* pomocn� ukazatel na uzel */
  tStackB StackB;  /* z�sobn�k boolovsk�ch hodnot */

  SInitP(&StackP);  //Inicializace z�sobn�ku ukazatel�
  SInitB(&StackB);  //Inicializace z�sobn�ku bool hodnot
  ptr = NULL;  //Inicializace pomocn�ho ukazatele ptr na NULL

  if(RootPtr != NULL) {  //Pokud nen� strom pr�zdn�,
    Leftmost_Postorder(RootPtr, &StackP, &StackB);  //vol�m funkci na jeho ko�en
  
    while(!SEmptyP(&StackP)) {  //Dokud nen� z�sobn�k ukazatel� pr�zdn�,
      if(STopPopB(&StackB)){  //pokud je na vrcholu bool z�sobn�ku true,
        ptr = STopPopP(&StackP);  //ulo��m do ptr ukazatel z vrcholu z�sobn�ku,
        SPushP(&StackP, ptr);  //vlo��m ho zp�t na z�sobn�k
        SPushB(&StackB, false);  //vlo��m do bool z�sobn�ku false,
        Leftmost_Postorder(ptr->RPtr, &StackP, &StackB);
        //vol�m funkci na prav�ho potomka uzlu na vrcholu z�sobn�ku
      }
      else {  //pokud nen� na vrcholu bool z�sobn�ku true,
        ptr = STopPopP(&StackP);  //vyberu ukazatel z vrcholu z�sobn�ku ukazatel�
        BTWorkOut(ptr);  //a zpracuji ho
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
  
  SInitP(&S);  //Inicializace z�sobn�ku ukazatel�
  ptr = *RootPtr;  //Nastav�m pomocn� ukazatel na ko�en stromu

  while(ptr != NULL) {  //Dokud nen� pomocn� ukazatel nastaven na NULL,
    if(ptr->LPtr != NULL) {  //Pokud nen� lev� potomek uzlu ptr nulov�,
      SPushP(&S, ptr->LPtr);  //ulo��m jej na z�sobn�k
    }
      
    if(ptr->RPtr != NULL) {  //Pokud nen� prav� potomek uzlu ptr nulov�,
      SPushP(&S, ptr->RPtr);  //ulo��m jej na z�sobn�k
    }
      
    free(ptr);  //Uvoln�m pam� po uzlu v ptr
      
    if(!SEmptyP(&S)) {  //Pokud nen� z�sobn�k pr�zdn�,
      ptr = STopPopP(&S);  //ulo��m jeho vrchol do ukazatele ptr
    }
    else {  //Pokud je z�sobn�k pr�zdn�,
      ptr = NULL;  //ulo��m do ptr hodnotu NULL, aby cyklus skon�il
    }
  }
  
  *RootPtr = NULL;  //Nastav�m ko�en stromu na NULL - stav po inicializaci
}

/* ----------------------------- konec c402.c ------------------------------- */
