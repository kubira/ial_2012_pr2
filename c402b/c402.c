/* --------------------------- c402.c --------------------------------------- */
/* Téma: Nerekurzivní implementace operací nad BVS 
**                           Implementace: Petr Pøikryl, prosinec 1994
**                                 Úpravy: Petr Pøikryl, listopad 1997
**                                         Petr Pøikryl, kvìten 1998
**               Pøepracované do jazyku c: Martin Tuèek, srpen 2005
**
** S vyu¾itím dynamického pøidìlování pamìti, implementujte
** následující operace nad binárním vyhledávacím stromem -- v¹e NEREKURZIVNÌ.
** (BT znamená Binary Tree; Tato pøedpona je u procedur uvedena kvùli mo¾né
** kolizi jmen v ostatních pøíkladech):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivní vlo¾ení nového uzlu do stromu
**     BTPreorder ...... nerekurzivní prùchod typu pre-order
**     BTInorder ....... nerekurzivní prùchod typu in-order
**     BTPostorder ..... nerekurzivní prùchod typu post-order
**     BTDisposeTree ... zru¹ v¹echny uzly stromu
**
** U v¹ech procedur, které vyu¾ívají nìkterý z prùchodù stromem, deklarujte
** lokální proceduru nazvanou Leftmost -- nalezení nejlevìj¹ího uzlu
** v podstromu (viz pøedná¹ky, kde se tato procedura jmenovala Nejlev).
**
** Definice typù naleznete v souboru c402.h; uzel stromu je typu tBTNode,
** ukazatel na nìj je typu tBTNodePtr, uzel obsahuje polo¾ku int Cont
** (obsah) a ukazatele LPtr a RPtr.
**
** Pøíklad slou¾í zejména k procvièení nerekurzivních zápisù algoritmù
** nad stromy. Ne¾ zaènete tento pøíklad øe¹it, prostudujte si dùkladnì
** principy pøevodu rekurzivních algoritmù na nerekurzivní. Programování
** je pøedev¹ím in¾enýrská disciplína, kde opìtné objevování Ameriky nemá
** místo. Pokud se vám zdá, ¾e by nìco ¹lo zapsat optimálnìji, promyslete
** si v¹echny detaily va¹eho øe¹ení. Pov¹imnìte si typického umístìní akcí
** pro rùzné typy prùchodù. Zamyslete se nad modifikací øe¹ených algoritmù
** pro výpoèet poètu uzlù stromu, poètu listù stromu, vý¹ky stromu a pro
** vytvoøení zrcadlového obrazu stromu (pouze popøehazování ukazatelù bez
** vytváøení nových uzlù a ru¹ení starých).
**
** Pøi prùchodech stromem pou¾ijte ke zpracování uzlu proceduru BTWorkOut().
** Pro práci se zásobníky pou¾ijte rovnì¾ pøedem pøipravené procedury
** a funkce. K dispozici máte zásobníky pro hodnoty typu boolean
** a tBTNodePtr (SInit*, SPush*, STopPop*, SEmpty*, kde místo '*' pou¾ijete
** 'P' pro zásobník s ukazateli nebo 'B' pro zásobník s boolovskými hodnotami.
**
** !Upozornìní! Je tøeba, abyste spravnì rozli¹ovali, kdy pou¾it dereferenèní 
** operátor * na samotný ukazatel a kdy budeme pracovat pouze se samotným 
** ukazatelem (prohledavaci fce). V techto úlohách poznáte tuto skuteènost 
** predev¹ím pomocí prototypu tìchto funkcí. V situaci, kdy pracujeme s 
** ukazatelem na ukazatel, je tøeba pou¾ít dereferenci.
*/
#include "c402.h"
int solved;
int errflg;

void BTWorkOut (tBTNodePtr Ptr) {
/* Pomocná procedura pou¾ívaná pøi prùchodech stromem.
** Zpracuje uzel, na který ukazuje Ptr. 
** Nemodifikovat!
*/

  if (Ptr == NULL) 
    printf("NULL\n");
  else 
    printf("Vypis hodnoty daneho uzlu> %d\n", Ptr->Cont);
}
  
/* -------------------------------------------------------------------------- */
/* Implementace zásobníkù je velmi zjednodu¹ena. Zdrojový text je formátován
** s ohledem na úsporu místa a není pøíli¹ komentován (neberte si z toho
** pøíklad -- kdy¾, tak odstra¹ující). Definice datovych struktur, viz. 
** hlavickovy soubor. 
*/

/* *********************** OPERACE SE ZÁSOBNÍKEM **************************** */

/* ----------------------- Zásobník ukazatelù: ------------------------------ */
void SInitP (tStackP *S) {
/* inicializace zásobníku ukazatelù */
  S->top = 0;  
}

void SPushP (tStackP *S, tBTNodePtr ptr) {
/* vlo¾í hodnotu na vrchol zásobníku */
  if (S->top==MAXSTACK) 
    printf("Pøeteèení zásobníku s ukazateli!\n");
  else {  
    S->top++;  
    S->a[S->top] = ptr;  
  }
}

tBTNodePtr STopPopP (tStackP *S) {
/* vrací odstranìnou hodnotu */
  if (S->top == 0)  {
    printf("Podteèení zásobníku s ukazateli!\n");
    return(NULL);  
  }
  else {
    return (S->a[S->top--]);
  }
}

bool SEmptyP (tStackP *S) {
/* test na prázdnost zásobníku */
  if (S->top == 0)
    return(true);
  else
    return(false);
}


/* ----------------------- Zásobník boolovských hodnot: --------------------- */
void SInitB (tStackB *S) {
/* inicializace zásobníku */
  S->top = 0;  
}

void SPushB (tStackB *S,bool val) {
/* vlo¾í hodnotu na vrchol zásobníku */
  if (S->top == MAXSTACK) 
    printf("Pøeteèení zásobníku pro boolean!\n");
  else {
    S->top++;  
    S->a[S->top] = val;
  }
}

bool STopPopB (tStackB *S) {
/* vrací odstranìnou hodnotu */
  if (S->top == 0) {
    printf("Podteèení zásobníku pro boolean!\n");
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
/* Inicializace stromu. Smí se volat pouze pøed prvním pou¾itím
** konkrétního binárního stromu, proto¾e neuvolòuje uzly neprázdného
** stromu (ani to dìlat nemù¾e). K ru¹ení neprázdného stromu slou¾í
** procedura BTDisposeTree (viz dále).
**
** V¹imnìte si, ¾e zde se poprvé v hlavièce objevuje typ ukazatel na ukazatel,
** proto je tøeba pøi práci s RootPtr(pøiøazení) pou¾ít dereferenèní operator.
** Ten bude je¹tì tøeba pou¾ít v procedurách BTInsert() a BTDisposeTree().
*/

  *RootPtr = NULL;

}


void BTInsert (tBTNodePtr *RootPtr, int Content) {
/* Vlo¾í do stromu nový uzel s hodnotou 'Content'. Z pohledu vkládání
** chápejte vytváøený strom jako binární vyhledávací strom (BVS = BST),
** kde uzly s hodnotou men¹í ne¾ má otec le¾í v levém podstromu, uzly vìt¹í
** le¾í vpravo. Pokud vkládaný uzel ji¾ existuje, neprovádí se nic (hodnota
** se ve stromu vyskytuje maximálnì jedenkrát). Pokud se vytváøí nový uzel,
** vzniká v¾dy jako list stromu. Øe¹te nerekurzivnì.
*/
  tBTNodePtr fptr;  /* ukazatel na otcovský uzel F */
  tBTNodePtr ptr;   /* pomocný ukazatel */
  bool myend;       /* pøíznak ukonèení cyklu */

/* V pøípadì, kdy strom není prázdný, musíme vyhledat místo, kam by se nová 
** hodnota mìla vlo¾it. Pokud uzel se zadanou hodnotou ji¾ existuje, nedìláme 
** nic. Pokud se bude uzel vytváøet, musíme si pamatovat ukazatel na otce, 
** na kterého bude nový uzel pøipojen.
*/

  if(*RootPtr == NULL) {
    if(!(*RootPtr = malloc(sizeof(struct tBTNode)))) {
      printf("Málo pamìti!\n");
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

/* Nyní následuje sekce jednotlivých prùchodù stromem, pøed tvorbou Leftmost
ètìte v¾dy i popisek nasledujíci procedury = implikace øe¹ení daného Leftmost */

/* ------------------------------ PREORDER ---------------------------------- */
void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack) {
/* Lokální procedura BTPreorder -- funkce viz pøedná¹ky.
** Pohybuje se po levé vìtvi podstromu, a¾ narazí na jeho nejlevìj¹í uzel.
** Ukazatele na v¹echny nav¹tívené uzly ukládá do zásobníku. Proto¾e jde
** o prùchod typu preorder, je nav¹tívený uzel souèasnì zpracován, pou¾ijte
** BTWorkOut(). 
*/

  while(ptr != NULL) {
    BTWorkOut(ptr);
    SPushP(Stack, ptr);
    ptr = ptr->LPtr;
  }

}

void BTPreorder (tBTNodePtr RootPtr) {
/* Samotný nerekurzivní prùchod typu pre-order, pou¾ijte dané Leftmost_Preorder
** dle predná¹ek. 
*/
  tStackP Stack ;  /* zásobník ukazatelù */
  tBTNodePtr ptr;  /* pomocný ukazatel na uzel */

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
/* Lokální procedura BTInorder -- funkce viz pøedná¹ky.
** Pohybuje se po levé vìtvi podstromu, a¾ narazí na jeho nejlevìj¹í uzel.
** Ukazatele na v¹echny nav¹tívené uzly ukládá do zásobníku. 
*/

  while(ptr != NULL) {
    SPushP(Stack, ptr);
    ptr = ptr->LPtr;
  }
}


void BTInorder (tBTNodePtr RootPtr) {
/* Nerekurzivní prùchod typu in-order. Pro zpracování uzlu volejte
** proceduru BTWorkOut a pracujte s LeftMost_Inorder.
*/
  tStackP Stack;  /* zásobník ukazatelù */
  tBTNodePtr ptr; /* pomocný ukazatel na uzel */

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
/* Lokální procedura pro Postorder -- funkce viz pøedná¹ky.
** Pohybuje se po levé vìtvi podstromu, a¾ narazí na jeho nejlevìj¹í uzel.
** Ukazatele na v¹echny nav¹tívené uzly ukládá do zásobníku. Proto¾e jde
** o prùchod typu postorder, je souèasnì do boolovského zásobníku ukládána
** hodnota, která øíká, ¾e uzel byl nav¹tíven poprvé (pøi prùchodu do
** levého podstromu) a ¾e se tedy je¹tì nemá zpracovávat.
*/

  while(ptr != NULL) {
    SPushP(StackP, ptr);
    SPushB(StackB, true);
    ptr = ptr->LPtr;
  }

}


void BTPostorder (tBTNodePtr RootPtr) {
/* Nerekurzivní prùchod typu post-order. Pro zpracování uzlu volejte
** proceduru BTWorkOut.
*/
  tStackP StackP;  /* zásobník ukazatelù */
  tBTNodePtr ptr;  /* pomocný ukazatel na uzel */
  tStackB StackB;  /* zásobník boolovských hodnot */

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
/* Zru¹í v¹echny uzly stromu -- uvolní jimi zabíraný prostor voláním
** standardní funkce free.
**
** Pozn.: pøi ru¹ení uzlù stromu není dùle¾ité, v jakém poøadí se budou ru¹it,
** proto mù¾ete uva¾ovat i jiné varianty, ne¾ klasické typy prùchodu stromem.
*/
  tStackP S;       /* zásobník ukazatelù */
  tBTNodePtr ptr;  /* pomocný ukazatel na uzel */
  
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
