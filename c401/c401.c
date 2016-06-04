/* ------------------------------ c401.c ------------------------------------ */
/* Téma: Rekurzivní implementace operací nad BVS (Dynamické pridel.pam.)
**                           Vytvoøil: Petr Pøikryl, listopad 1994
**                           Úpravy:   Andrea Nìmcová, prosinec 1995
**                                     Petr Pøikryl, duben 1996
**                                     Petr Pøikryl, listopad 1997
**           Pøepracované do jazyku c: Martin Tuèek, rijen 2005
**
** Implementujte rekurzivním zpùsobem operace nad binárním vyhledávacím
** stromem (BVS; v angliètinì BST -- Binary Search Tree).
**
** Klíèem uzlu stromu je jeden znak (obecnì jím mù¾e být cokoliv, podle
** èeho se vyhledává). U¾iteèným (vyhledávaným) obsahem je zde integer.
** Uzly s men¹ím klíèem le¾í vlevo, uzly s vìt¹ím klíèem le¾í ve stromu
** vpravo. Vyu¾ijte dynamického pøidìlování pamìti.
** Rekurzivním zpùsobem øe¹te následující procedury a funkce:
**
**   BSTInit ...... inicializace vyhledávacího stromu
**   BSTSearch .... vyhledávání hodnoty uzlu zadaného klíèem
**   BSTInsert .... vkládání nové hodnoty
**   BSTDelete .... ru¹ení uzlu se zadaným klíèem
**   BSTDispose ... ru¹ení celého stromu
**
** Pøesnou definici typù naleznete v souboru c401.h; pro pøehled --
** ADT BVS je reprezentováno koøenovým ukazatelem stromu typu tBSTNodePtr.
** Uzel stromu (struktura typu tBSTNode) obsahuje ukazatele LPtr a RPtr na levý
** a pravý podstrom, slo¾ku char KEY -- klíè, podle kterého se vyhledává,
** a int BSTNodeCont -- obsah uzlu (demonstrativne integer).
**
** !Upozorneni! Je treba, abyste spravne rozlisovali, kdy pouzit dereferencni 
** operator * na samotny ukazatel (tj. kdyz budeme chtit zapsat urcitou hodnotu 
** do tohoto pointeru, typicky modifikacni operace) a kdy budeme pracovat pouze 
** se samotnym ukazatelem (vyhledavaci fce). V techto ulohach poznate tuto
** skutecnost predevsim pomoci prototypu techto fci. V situaci, kdy pracujeme 
** s ukazatelem na ukazatel, je treba pouzit dereferenci.
**
** Poznámka: nepou¾ívejte nestandardní pøíkazy (exit(),...) a operace.
*/

#include "c401.h"
int solved;
int errflg;

void BSTInit (tBSTNodePtr *RootPtr) {
/* Poèáteèní inicializace stromu pøed prvním pou¾itím datové struktury.
** Poèáteèní testování ukazatele není mo¾né, proto¾e obsahuje nedefinovanou
** (tj. libovolnou) hodnotu, která ov¹em neodrá¾í reálný stav.
** 
** V¹imnìte si, ze zde se poprvé v hlavièce objevuje typ ukazatel na ukazatel,
** proto je treba pri práci s RootPtr(pøiøazení) pou¾ít dereferenèní operátor.
** Ten bude je¹tì tøeba pou¾ít v procedurách BSTDelete, BSTInsert a BSTDispose.
**/

  *RootPtr = NULL;  //Inicializace koøene stromu na NULL

}


int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content) {
/* Vyhledávání uzlu v BVS podle zadaného klíèe K. Pokud je nalezen, vrací
** funkce hodnotu TRUE a v promìnné Content se vrací obsah pøíslu¹ného uzlu.
** Pokud pøíslu¹ný uzel není nalezen, vrací funkce hodnotu FALSE a obsah
** promìnné Content není definován (to znamená, ¾e do ní nebudete nic
** pøiøazovat). Pøi vyhledávání v binárním stromu bychom typicky pou¾ili
** cyklus ukonèený testem zahrnujícím stav dosa¾ení listu nebo nalezení
** uzlu s klíèem. V tomto pøípadì ov¹em test nepou¾ijte a problém øe¹te
** rekurzivním volání této funkce (nedeklarujte ¾ádnou pomocnou proceduru
** nebo funkci).
**/

  if(!RootPtr){  //Pokud je aktuální uzel prázdný,
    return FALSE;  //tak vracím FALSE - uzel nenalezen
  }
  else if(RootPtr->Key > K) {  //Pokud je klíè aktuálního uzlu vìt¹í ne¾ hledám,
    return BSTSearch(RootPtr->LPtr, K, Content);  //volám rekurzí levý podstrom
  }
  else if(RootPtr->Key < K) {  //Pokud je klíè aktuálního uzlu men¹í ne¾ hledám,
    return BSTSearch(RootPtr->RPtr, K, Content);  //volám rekurzí pravý podstrom
  }
  else {  //Pokud nenastala ¾ádná situace vý¹e, na¹el jsem hledaný uzel
    *Content = RootPtr->BSTNodeCont;  //a jeho hodnotu ulo¾ím do Content
    return TRUE;  //Vracím TRUE - uzel nalezen
  }
}


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content) {
/* Vlo¾í do stromu hodnotu Content s klíèem K. Pokud ji¾ uzel
** se zadaným klíèem existuje, nahradí se obsah uzlu novou hodnotou.
** Novì vytvoøený uzel nech» je v¾dy listem stromu. Øe¹te rekurzivnì.
**
** Tato rekurzivní implementace je ponìkud neefektivní, proto¾e se pøi
** ka¾dém rekurzivním zanoøení musí kopírovat celý integer "Content" (obecnì
** obsah uzlu). V praxi by se tento problém øe¹il napøíklad jedním
** z tìcho zpùsobù:
**  - pøedáváním promìnné "Content" odkazem (v tom pøípadì je nutné dosazovat
**    pøi volání promìnnou a není mo¾né pøímo zapsat hodnotu);
**  - deklarací vnitøní procedury, které by se parametr pøedal odkazem;
**    vnìj¹í procedura by slou¾ila jen jako obal (nevolala by se
**    rekurzivnì);
**  - pøi vyu¾ití pøedchozí varianty by se do rekurzivní procedury pøedával
**    pøedem naplnìný nový uzel, který by se na závìr zru¹il v pøípadì,
**    ¾e se uzel nepodaøilo zaøadit (pokud u¾ uzel s tímto klíèem existoval,
**    pøepsal by se jen obsah, pøípadnì by se uzly vymìnily a ke zru¹ení
**    by se pøedal starý uzel);
**
** Nerekurzivní varianta by v tomto pøípadì byla efektivnìj¹í jak z hlediska
** rychlosti, tak z hlediska pamì»ových nárokù. Zde v¹ak jde o ¹kolní
** pøíklad. Nedeklarujte ¾ádnou pomocnou proceduru nebo funkci, problém
** øe¹te rekurzivním voláním procedury samé.
**
** POZOR: Vzhledem k jisté slo¾itosti rekurzívního volání této fce zde uvádím
** pøíklad jak funkci zavolat (kdy¾ jsme pøijali RootPtr jako ukazatel na 
** ukazatel). Správné zavolání napø. na levý podstrom:
** BSTInsert(&((*RootPtr)->LPtr), K, Content)
*/

  if(*RootPtr == NULL){  //Pokud je aktuální uzel prázdný,
    if(!(*RootPtr = malloc(sizeof(struct tBSTNode)))){  //pøidìlím mu pamì»,
      printf("Není pamì»!\n");  //pokud se nepodaøilo pamì» alokovat, oznámím
      errflg = TRUE;
    }
    else {  //Pokud alokování pamìti probìhlo v poøádku,
      (*RootPtr)->Key = K;  //nastavím klíè uzlu,
      (*RootPtr)->BSTNodeCont = Content;  //nastavím obsah uzlu,
      (*RootPtr)->LPtr = NULL;  //levý potomek zatím neexistuje,
      (*RootPtr)->RPtr = NULL;  //pravý potomek také zatím neexistuje
    }
  }
  else {  //Pokud není aktuální uzel prázdný,
    if((*RootPtr)->Key < K) {  //tak kdy¾ je jeho klíè men¹í ne¾ vkládaný,
      BSTInsert(&((*RootPtr)->RPtr), K, Content);  //volám rekurzí pravý podstrom
    }
    else if((*RootPtr)->Key > K) {  //kdy¾ je jeho klíè vìt¹í ne¾ vkládaný,
      BSTInsert(&((*RootPtr)->LPtr), K, Content);  //volám rekurzí levý podstrom
    }
    else {  //pokud nenastala ¾ádná situace vý¹e, tak uzel s klíèem K existuje
      (*RootPtr)->BSTNodeCont = Content;  //a nastavím mu novou hodnotu
    }
  }

}


/* POZOR NASLEDUJÍCÍ PROCEDURA BUDE POU®ITA DÁLE, 
** PREÈTÌTE SI PROTO PODROBNÌ NEJPRVE KOMENTÁØ K PROCEDUØE BSTDELETE(),
** NE® ZAÈNETE VYTVÁØET REPLACEBYRIGHTMOST().
*/
void ReplaceByRightmost (tBSTNodePtr PtrReplaced,tBSTNodePtr *RootPtr) {
/* Pomocná procedura pro vyhledání, pøestìhování a uvolnìní nejpravìj¹ího
** uzlu v podstromu urèeném ukazatelem RootPtr. Na vstupu se pøedpokládá
** hodnota ukazatele RootPtr rùzná od NULL (zajistìte to testováním pøed
** volání procedury). Dále se pøedpokládá, ¾e pomocný ukazatel PtrReplaced
** ukazuje na uzel, který se má naplnit hodnotami vyhledaného uzlu.
*/
  tBSTNodePtr ptr; /* pou¾ívejte tento pomocný ukazatel */
  ptr = NULL;
  
  if(*RootPtr){  //Pokud není aktuální uzel prázdný,
    if((*RootPtr)->RPtr != NULL) {  //tak pokud má pravý podstrom,
      //zavolám na pravý podstrom funkci ReplaceByRightMost
      ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr));
    }
    else if((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL) {
    //kdy¾ nemá pravý podstrom ,ale zároveò má levý podstrom
      PtrReplaced->Key = (*RootPtr)->Key;
      //nastavím ru¹ený klíè na aktuální klíè,
      PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
      //nastavím ru¹ený obsah na aktuální obsah,
      ptr = PtrReplaced->LPtr;
      //ulo¾ím si levého potomka ru¹eného uzlu do pomocného ukazatele,
      PtrReplaced->LPtr = (*RootPtr)->LPtr;
      //nastavím levého potomka ru¹eného uzlu na levého potomka souèasného uzlu,
      free(ptr);  //uvolním pamì» po zru¹eném uzlu
    }
    else {  //Pokud nenastala ¾ádná situace vý¹e, aktuální prvek nemá potomky,
      ptr = (*RootPtr);  //ulo¾ím si ho do pomocného ukazatele pro zru¹ení,
      PtrReplaced->Key = (*RootPtr)->Key;
      //nastavím klíè ru¹eného uzlu na klíè aktuálního uzlu,
      PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
      //nastavím obsah ru¹eného uzlu na obsah aktuálního uzlu,
      free(ptr);  //uvolním pamì» po zru¹eném uzlu
      *RootPtr = NULL;  //a nastavím aktuální uzel na NULL
    }
  }  

}


void BSTDelete (tBSTNodePtr *RootPtr, char K) {
/* Zru¹í uzel stromu, který obsahuje klíè K. Pokud uzel se zadaným klíèem
** neexistuje, nedìlá nic. Ve¹keré manipulace øe¹te rekurzivnì.
**
** Pokud má ru¹ený uzel jen jeden podstrom, pak jej zdìdí otec. Pokud má
** oba podstromy, pak je ru¹ený uzel nahrazen nejpravìj¹ím uzlem levého
** podstromu. Pozor! Nejpravìj¹í uzel nemusí být listem. Pro tuto operaci
** jsme deklarovali proceduru ReplaceByRightmost -- viz. její komentáø
** uveden vý¹e.
** POZOR: Vzhledem k jisté slo¾itosti rekurzívního volání této fce zde uvádím
** pøíklad jak funkci zavolat (kdy¾ jsme pøijali RootPtr jako ukazatel na 
** ukazatel). Správné zavolání napø. na levý podstrom:
** BSTDelete(&((*RootPtr)->LPtr), K).
** Podobnì je tomu tak i u ReplaceByRightMost().  
** Napøíklad: ReplaceByRightmost(*RootPtr, (&((*RootPtr)->LPtr)))
*/
  tBSTNodePtr ptr;  /* pou¾ívejte tento pomocný ukazatel */
  ptr=NULL;

  if(*RootPtr){  //Pokud není aktuální uzel prázdný,
    if((*RootPtr)->Key < K) {  //kdy¾ je klíè aktuálního uzlu men¹í ne¾ ru¹eného,
      BSTDelete(&((*RootPtr)->RPtr), K);  //volám rekurzi na pravý podstrom
    }
    else if((*RootPtr)->Key > K) {  //kdy¾ je klíè aktuálního uzlu vìt¹í,
      BSTDelete(&((*RootPtr)->LPtr), K);  //volám rekurzi na levý podstrom
    }
    else if((*RootPtr)->Key == K) {  //kdy¾ jsem na¹el uzel s ru¹eným klíèem,
      if((*RootPtr)->LPtr == NULL && (*RootPtr)->RPtr != NULL){
      //tak pokud nemá levý podstrom, ale zároveò má pravý podstrom,
        ptr = (*RootPtr);  //ulo¾ím si aktuální uzel pro zru¹ení,
        (*RootPtr) = (*RootPtr)->RPtr;  //nahradím aktuální uzel pravým podstromem
        free(ptr);  //a uvolním pamì» po ru¹eném uzlu
      }
      else if((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL){
      //pokud nemá pravý podstrom, ale zároveò má levý podstrom,
        ptr = (*RootPtr);  //ulo¾ím si aktuální uzel pro zru¹ení,
        (*RootPtr) = (*RootPtr)->LPtr;  //nahradím aktuální uzel levým podstromem
        free(ptr);  //a uvolním pamì» po ru¹eném uzlu
      }
      else if ((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr == NULL){
      //pokud nemá aktuální ru¹ený uzel ¾ádné potomky,
        free((*RootPtr));  //uvolním po nìm pamì»
        *RootPtr = NULL;  //a nastavím ho na NULL
      }
      else {  //kdy¾ nenastala ¾ádná situace vý¹e,
        ReplaceByRightmost(*RootPtr, (&((*RootPtr)->LPtr)));
        //zavolám funkci ReplaceByRightmost na levý podstrom
      }
    }
  }
} 


void BSTDispose (tBSTNodePtr *RootPtr) {
/* Korektnì zru¹í celý binární vyhledávací strom. Zvolte nejvýhodnìj¹í
** druh rekurzívního prùchodu stromem. Nedeklarujte ¾ádné pomocné procedury
** nebo funkce.
** POZOR: Vzhledem k jisté slo¾itosti rekurzívního volání této fce zde uvádím
** pøíklad jak funkci zavolat (kdy¾ jsme pøijali RootPtr jako ukazatel na 
** ukazatel). Správné zavolání napø. na levý podstrom:
** BSTDispose(&(*RootPtr)->LPtr).
*/

  if((*RootPtr)){  //Pokud není aktuální uzel prázdný,
    BSTDispose(&(*RootPtr)->LPtr);  //zavolám funkci rekurzivnì na levý podstrom
    BSTDispose(&(*RootPtr)->RPtr);  //zavolám funkci rekurzivnì na pravý podstrom
    free(*RootPtr);  //uvolním pamì» po aktuálním uzlu
    *RootPtr = NULL; //a nastavím jej na NULL
  }

}

/* --------------------------- konec c401.c -------------------------------- */
