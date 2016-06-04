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

  *RootPtr = NULL;  //Inicializace stromu - nastavení na NULL

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

  if(*RootPtr == NULL) {  //Pokud je strom prázdný,
    if(!(*RootPtr = malloc(sizeof(struct tBTNode)))) {
    //alokuji jeho koøenu pamì»,
      printf("Málo pamìti!\n");  //pokud se nepodaøí pamì» alokovat - Chyba
      errflg = TRUE;
    }
    else {  //Pokud se pamì» podaøilo pøidìlit,
      (*RootPtr)->Cont = Content;  //nastavím obsah uzlu na hodnotu Content,
      (*RootPtr)->LPtr = NULL;  //nastavím levého potomka na NULL
      (*RootPtr)->RPtr = NULL;  //a nastavím pravého potomka na NULL
    }
  }
  else {  //Pokud strom není prázdný,
    fptr = *RootPtr;  //ulo¾ím si do pomocného ukazatele adresu koøene stromu
    myend = true;  //a nastavím podmínku cyklu na true
  
    while(myend) {  //Pokud se je¹tì nepodaøilo ulo¾it nový prvek do stromu,
      if(fptr->Cont > Content) {  //kdy¾ je obsah otcovského uzlu vet¹í
        if(fptr->LPtr == NULL) {  //a pokud nemá levého potomka,
          if((ptr = malloc(sizeof(struct tBTNode)))) {
            //alokuji pamì» nového uzlu a kdy¾ se alokace podaøí,
            ptr->Cont = Content;  //nastavím mu jeho obsah,
            ptr->LPtr = NULL;  //nastavím levého potomka na NULL,
            ptr->RPtr = NULL; //nastavím pravého potomka na NULL,
            fptr->LPtr = ptr;  //nový prvek se stane levým potomkem otcovského uzlu 
            myend = false;  //a ukonèím cyklus nastavením myend na false
          }
          else {
            printf("Málo pamìti!\n");  //pokud se nepodaøí pamì» alokovat - Chyba
            errflg = TRUE;
          }
        }
        else {  //pokud má levého potomka,
          fptr = fptr->LPtr;  //tak se stane otcovským uzlem tento levý potomek
        }
      }
      else if(fptr->Cont < Content) {  //kdy¾ je obsah otcovkého uzlu men¹í
        if(fptr->RPtr == NULL) {  //a pokud nemá pravého potomka,
          if((ptr = malloc(sizeof(struct tBTNode)))) {
            //alokuji pamì» nového uzlu a kdy¾ se alokace podaøí,
            ptr->Cont = Content;  //nastavím mu jeho obsah,
            ptr->LPtr = NULL;  //nastavím levého potomka na NULL,
            ptr->RPtr = NULL; //nastavím pravého potomka na NULL,
            fptr->RPtr = ptr;  //nový prvek se stane pravým potomkem otcovského uzlu 
            myend = false;  //a ukonèím cyklus nastavením myend na false
          }
          else {
            printf("Málo pamìti!\n");  //pokud se nepodaøí pamì» alokovat - Chyba
            errflg = TRUE;
          }
        }
        else {  //a pokud má pravého potomka,
          fptr = fptr->RPtr;  //tak se stane otcovským uzlem tento pravý potomek
        }
      }
      else {  //pokud ji¾ uzel se stejným obsahem existuje,
        myend = false;  //ukonèí se cyklus a nedìlá se nic
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

  while(ptr != NULL) {  //Dokud nejsem v nejlevìj¹ím uzlu stromu,
    BTWorkOut(ptr);  //zpracuji tento uzel,
    SPushP(Stack, ptr);  //ulo¾ím ho na zásobník,
    ptr = ptr->LPtr;  //a nastavím ukazatel na jeho levého potomka
  }

}

void BTPreorder (tBTNodePtr RootPtr) {
/* Samotný nerekurzivní prùchod typu pre-order, pou¾ijte dané Leftmost_Preorder
** dle predná¹ek. 
*/
  tStackP Stack ;  /* zásobník ukazatelù */
  tBTNodePtr ptr;  /* pomocný ukazatel na uzel */

  SInitP(&Stack);  //Inicializace zásobníku ukazatelù
  ptr = NULL;  //Inicializace pomocného ukazatele

  if(RootPtr != NULL) {  //Pokud není strom prázdný,
    Leftmost_Preorder(RootPtr, &Stack);  //volám funkci na koøen stromu
  
    while(!SEmptyP(&Stack)) {  //Dokud není zásobník prázdný,
      ptr = STopPopP(&Stack);  //ukládám do ptr ukazatel z vrcholu zásobníku
      Leftmost_Preorder(ptr->RPtr, &Stack);  //a volám funkci na jeho pravý uzel
    }
  }
}


/* ------------------------------ IN ORDER ---------------------------------- */
void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack) {
/* Lokální procedura BTInorder -- funkce viz pøedná¹ky.
** Pohybuje se po levé vìtvi podstromu, a¾ narazí na jeho nejlevìj¹í uzel.
** Ukazatele na v¹echny nav¹tívené uzly ukládá do zásobníku. 
*/

  while(ptr != NULL) {  //Dokud nejsem v nejlevìj¹ím uzlu stromu,
    SPushP(Stack, ptr);  //ukládám uzel na zásobník
    ptr = ptr->LPtr;  //a nastavím ukazatel na jeho levého potomka
  }
}


void BTInorder (tBTNodePtr RootPtr) {
/* Nerekurzivní prùchod typu in-order. Pro zpracování uzlu volejte
** proceduru BTWorkOut a pracujte s LeftMost_Inorder.
*/
  tStackP Stack;  /* zásobník ukazatelù */
  tBTNodePtr ptr; /* pomocný ukazatel na uzel */

  SInitP(&Stack);  //Inicializace zásobníku ukazatelù
  ptr = NULL;  //Inicializace pomocného ukazatele

  if(RootPtr != NULL) {  //Pokud není strom prázdný,
    Leftmost_Inorder(RootPtr, &Stack);  //volám funkci na jeho koøen
  
    while(!SEmptyP(&Stack)) {  //Dokud není zásobník prázdný,
      ptr = STopPopP(&Stack);  //ukládám do ptr ukazatel z vrcholu zásobníku,
      BTWorkOut(ptr);  //tento uzel zpracuji
      Leftmost_Inorder(ptr->RPtr, &Stack);  //a volám funkci na jeho pravý uzel
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

  while(ptr != NULL) {  //Dokud nejsem v nejlevìj¹ím uzlu stromu,
    SPushP(StackP, ptr);  //ukládám uzel na zásobník ukazatelù,
    SPushB(StackB, true);  //do zásobníku bool hodnot ukládám true
    ptr = ptr->LPtr;  //a nastavím ukazatel na levého potomka uzlu
  }

}


void BTPostorder (tBTNodePtr RootPtr) {
/* Nerekurzivní prùchod typu post-order. Pro zpracování uzlu volejte
** proceduru BTWorkOut.
*/
  tStackP StackP;  /* zásobník ukazatelù */
  tBTNodePtr ptr;  /* pomocný ukazatel na uzel */
  tStackB StackB;  /* zásobník boolovských hodnot */

  SInitP(&StackP);  //Inicializace zásobníku ukazatelù
  SInitB(&StackB);  //Inicializace zásobníku bool hodnot
  ptr = NULL;  //Inicializace pomocného ukazatele ptr na NULL

  if(RootPtr != NULL) {  //Pokud není strom prázdný,
    Leftmost_Postorder(RootPtr, &StackP, &StackB);  //volám funkci na jeho koøen
  
    while(!SEmptyP(&StackP)) {  //Dokud není zásobník ukazatelù prázdný,
      if(STopPopB(&StackB)){  //pokud je na vrcholu bool zásobníku true,
        ptr = STopPopP(&StackP);  //ulo¾ím do ptr ukazatel z vrcholu zásobníku,
        SPushP(&StackP, ptr);  //vlo¾ím ho zpìt na zásobník
        SPushB(&StackB, false);  //vlo¾ím do bool zásobníku false,
        Leftmost_Postorder(ptr->RPtr, &StackP, &StackB);
        //volám funkci na pravého potomka uzlu na vrcholu zásobníku
      }
      else {  //pokud není na vrcholu bool zásobníku true,
        ptr = STopPopP(&StackP);  //vyberu ukazatel z vrcholu zásobníku ukazatelù
        BTWorkOut(ptr);  //a zpracuji ho
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
  
  SInitP(&S);  //Inicializace zásobníku ukazatelù
  ptr = *RootPtr;  //Nastavím pomocný ukazatel na koøen stromu

  while(ptr != NULL) {  //Dokud není pomocný ukazatel nastaven na NULL,
    if(ptr->LPtr != NULL) {  //Pokud není levý potomek uzlu ptr nulový,
      SPushP(&S, ptr->LPtr);  //ulo¾ím jej na zásobník
    }
      
    if(ptr->RPtr != NULL) {  //Pokud není pravý potomek uzlu ptr nulový,
      SPushP(&S, ptr->RPtr);  //ulo¾ím jej na zásobník
    }
      
    free(ptr);  //Uvolním pamì» po uzlu v ptr
      
    if(!SEmptyP(&S)) {  //Pokud není zásobník prázdný,
      ptr = STopPopP(&S);  //ulo¾ím jeho vrchol do ukazatele ptr
    }
    else {  //Pokud je zásobník prázdný,
      ptr = NULL;  //ulo¾ím do ptr hodnotu NULL, aby cyklus skonèil
    }
  }
  
  *RootPtr = NULL;  //Nastavím koøen stromu na NULL - stav po inicializaci
}

/* ----------------------------- konec c402.c ------------------------------- */
