/* ------------------------------ c401.c ------------------------------------ */
/* T�ma: Rekurzivn� implementace operac� nad BVS (Dynamick� pridel.pam.)
**                           Vytvo�il: Petr P�ikryl, listopad 1994
**                           �pravy:   Andrea N�mcov�, prosinec 1995
**                                     Petr P�ikryl, duben 1996
**                                     Petr P�ikryl, listopad 1997
**           P�epracovan� do jazyku c: Martin Tu�ek, rijen 2005
**
** Implementujte rekurzivn�m zp�sobem operace nad bin�rn�m vyhled�vac�m
** stromem (BVS; v angli�tin� BST -- Binary Search Tree).
**
** Kl��em uzlu stromu je jeden znak (obecn� j�m m��e b�t cokoliv, podle
** �eho se vyhled�v�). U�ite�n�m (vyhled�van�m) obsahem je zde integer.
** Uzly s men��m kl��em le�� vlevo, uzly s v�t��m kl��em le�� ve stromu
** vpravo. Vyu�ijte dynamick�ho p�id�lov�n� pam�ti.
** Rekurzivn�m zp�sobem �e�te n�sleduj�c� procedury a funkce:
**
**   BSTInit ...... inicializace vyhled�vac�ho stromu
**   BSTSearch .... vyhled�v�n� hodnoty uzlu zadan�ho kl��em
**   BSTInsert .... vkl�d�n� nov� hodnoty
**   BSTDelete .... ru�en� uzlu se zadan�m kl��em
**   BSTDispose ... ru�en� cel�ho stromu
**
** P�esnou definici typ� naleznete v souboru c401.h; pro p�ehled --
** ADT BVS je reprezentov�no ko�enov�m ukazatelem stromu typu tBSTNodePtr.
** Uzel stromu (struktura typu tBSTNode) obsahuje ukazatele LPtr a RPtr na lev�
** a prav� podstrom, slo�ku char KEY -- kl��, podle kter�ho se vyhled�v�,
** a int BSTNodeCont -- obsah uzlu (demonstrativne integer).
**
** !Upozorneni! Je treba, abyste spravne rozlisovali, kdy pouzit dereferencni 
** operator * na samotny ukazatel (tj. kdyz budeme chtit zapsat urcitou hodnotu 
** do tohoto pointeru, typicky modifikacni operace) a kdy budeme pracovat pouze 
** se samotnym ukazatelem (vyhledavaci fce). V techto ulohach poznate tuto
** skutecnost predevsim pomoci prototypu techto fci. V situaci, kdy pracujeme 
** s ukazatelem na ukazatel, je treba pouzit dereferenci.
**
** Pozn�mka: nepou��vejte nestandardn� p��kazy (exit(),...) a operace.
*/

#include "c401.h"
int solved;
int errflg;

void BSTInit (tBSTNodePtr *RootPtr) {
/* Po��te�n� inicializace stromu p�ed prvn�m pou�it�m datov� struktury.
** Po��te�n� testov�n� ukazatele nen� mo�n�, proto�e obsahuje nedefinovanou
** (tj. libovolnou) hodnotu, kter� ov�em neodr�� re�ln� stav.
** 
** V�imn�te si, ze zde se poprv� v hlavi�ce objevuje typ ukazatel na ukazatel,
** proto je treba pri pr�ci s RootPtr(p�i�azen�) pou��t dereferen�n� oper�tor.
** Ten bude je�t� t�eba pou��t v procedur�ch BSTDelete, BSTInsert a BSTDispose.
**/

  *RootPtr = NULL;

}


int BSTSearch (tBSTNodePtr RootPtr, char K, int *Content) {
/* Vyhled�v�n� uzlu v BVS podle zadan�ho kl��e K. Pokud je nalezen, vrac�
** funkce hodnotu TRUE a v prom�nn� Content se vrac� obsah p��slu�n�ho uzlu.
** Pokud p��slu�n� uzel nen� nalezen, vrac� funkce hodnotu FALSE a obsah
** prom�nn� Content nen� definov�n (to znamen�, �e do n� nebudete nic
** p�i�azovat). P�i vyhled�v�n� v bin�rn�m stromu bychom typicky pou�ili
** cyklus ukon�en� testem zahrnuj�c�m stav dosa�en� listu nebo nalezen�
** uzlu s kl��em. V tomto p��pad� ov�em test nepou�ijte a probl�m �e�te
** rekurzivn�m vol�n� t�to funkce (nedeklarujte ��dnou pomocnou proceduru
** nebo funkci).
**/

  if(!RootPtr){
    return FALSE;
  }
  else if(RootPtr->Key > K) {
    return BSTSearch(RootPtr->LPtr, K, Content);
  }
  else if(RootPtr->Key < K) {
    return BSTSearch(RootPtr->RPtr, K, Content);
  }
  else {
    *Content = RootPtr->BSTNodeCont;
    return TRUE;    
  }
}


void BSTInsert (tBSTNodePtr* RootPtr, char K, int Content) {
/* Vlo�� do stromu hodnotu Content s kl��em K. Pokud ji� uzel
** se zadan�m kl��em existuje, nahrad� se obsah uzlu novou hodnotou.
** Nov� vytvo�en� uzel nech� je v�dy listem stromu. �e�te rekurzivn�.
**
** Tato rekurzivn� implementace je pon�kud neefektivn�, proto�e se p�i
** ka�d�m rekurzivn�m zano�en� mus� kop�rovat cel� integer "Content" (obecn�
** obsah uzlu). V praxi by se tento probl�m �e�il nap��klad jedn�m
** z t�cho zp�sob�:
**  - p�ed�v�n�m prom�nn� "Content" odkazem (v tom p��pad� je nutn� dosazovat
**    p�i vol�n� prom�nnou a nen� mo�n� p��mo zapsat hodnotu);
**  - deklarac� vnit�n� procedury, kter� by se parametr p�edal odkazem;
**    vn�j�� procedura by slou�ila jen jako obal (nevolala by se
**    rekurzivn�);
**  - p�i vyu�it� p�edchoz� varianty by se do rekurzivn� procedury p�ed�val
**    p�edem napln�n� nov� uzel, kter� by se na z�v�r zru�il v p��pad�,
**    �e se uzel nepoda�ilo za�adit (pokud u� uzel s t�mto kl��em existoval,
**    p�epsal by se jen obsah, p��padn� by se uzly vym�nily a ke zru�en�
**    by se p�edal star� uzel);
**
** Nerekurzivn� varianta by v tomto p��pad� byla efektivn�j�� jak z hlediska
** rychlosti, tak z hlediska pam�ov�ch n�rok�. Zde v�ak jde o �koln�
** p��klad. Nedeklarujte ��dnou pomocnou proceduru nebo funkci, probl�m
** �e�te rekurzivn�m vol�n�m procedury sam�.
**
** POZOR: Vzhledem k jist� slo�itosti rekurz�vn�ho vol�n� t�to fce zde uv�d�m
** p��klad jak funkci zavolat (kdy� jsme p�ijali RootPtr jako ukazatel na 
** ukazatel). Spr�vn� zavol�n� nap�. na lev� podstrom:
** BSTInsert(&((*RootPtr)->LPtr), K, Content)
*/

  if(*RootPtr == NULL){
    if(!(*RootPtr = malloc(sizeof(struct tBSTNode)))){
      printf("Nen� pam�!\n");
    }
    else {
      (*RootPtr)->Key = K;
      (*RootPtr)->BSTNodeCont = Content;
      (*RootPtr)->LPtr = NULL;
      (*RootPtr)->RPtr = NULL;
    }
  }
  else {
    if((*RootPtr)->Key < K) {
      BSTInsert(&((*RootPtr)->RPtr), K, Content);
    }
    else if((*RootPtr)->Key > K) {
      BSTInsert(&((*RootPtr)->LPtr), K, Content);
    }
    else {
      (*RootPtr)->BSTNodeCont = Content;
    }
  }

}


/* POZOR NASLEDUJ�C� PROCEDURA BUDE POU�ITA D�LE, 
** PRE�T�TE SI PROTO PODROBN� NEJPRVE KOMENT�� K PROCEDU�E BSTDELETE(),
** NE� ZA�NETE VYTV��ET REPLACEBYRIGHTMOST().
*/
void ReplaceByRightmost (tBSTNodePtr PtrReplaced,tBSTNodePtr *RootPtr) {
/* Pomocn� procedura pro vyhled�n�, p�est�hov�n� a uvoln�n� nejprav�j��ho
** uzlu v podstromu ur�en�m ukazatelem RootPtr. Na vstupu se p�edpokl�d�
** hodnota ukazatele RootPtr r�zn� od NULL (zajist�te to testov�n�m p�ed
** vol�n� procedury). D�le se p�edpokl�d�, �e pomocn� ukazatel PtrReplaced
** ukazuje na uzel, kter� se m� naplnit hodnotami vyhledan�ho uzlu.
*/
  tBSTNodePtr ptr; /* pou��vejte tento pomocn� ukazatel */
  ptr = NULL;
  
  if(*RootPtr){
    if((*RootPtr)->RPtr != NULL) {
      ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr));
    }
    else if((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL) {
      PtrReplaced->Key = (*RootPtr)->Key;
      PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
      ptr = PtrReplaced->LPtr;
      PtrReplaced->LPtr = (*RootPtr)->LPtr;
      free(ptr);
    }
    else {
      ptr = (*RootPtr);
      PtrReplaced->Key = (*RootPtr)->Key;
      PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
      free(ptr);
      *RootPtr = NULL;
    }
  }  

}


void BSTDelete (tBSTNodePtr *RootPtr, char K) {
/* Zru�� uzel stromu, kter� obsahuje kl�� K. Pokud uzel se zadan�m kl��em
** neexistuje, ned�l� nic. Ve�ker� manipulace �e�te rekurzivn�.
**
** Pokud m� ru�en� uzel jen jeden podstrom, pak jej zd�d� otec. Pokud m�
** oba podstromy, pak je ru�en� uzel nahrazen nejprav�j��m uzlem lev�ho
** podstromu. Pozor! Nejprav�j�� uzel nemus� b�t listem. Pro tuto operaci
** jsme deklarovali proceduru ReplaceByRightmost -- viz. jej� koment��
** uveden v��e.
** POZOR: Vzhledem k jist� slo�itosti rekurz�vn�ho vol�n� t�to fce zde uv�d�m
** p��klad jak funkci zavolat (kdy� jsme p�ijali RootPtr jako ukazatel na 
** ukazatel). Spr�vn� zavol�n� nap�. na lev� podstrom:
** BSTDelete(&((*RootPtr)->LPtr), K).
** Podobn� je tomu tak i u ReplaceByRightMost().  
** Nap��klad: ReplaceByRightmost(*RootPtr, (&((*RootPtr)->LPtr)))
*/
  tBSTNodePtr ptr;  /* pou��vejte tento pomocn� ukazatel */
  ptr=NULL;

  if(*RootPtr){
    if((*RootPtr)->Key < K) {
      BSTDelete(&((*RootPtr)->RPtr), K);
    }
    else if((*RootPtr)->Key > K) {
      BSTDelete(&((*RootPtr)->LPtr), K);
    }
    else if((*RootPtr)->Key == K) {
      if((*RootPtr)->LPtr == NULL && (*RootPtr)->RPtr != NULL){
        ptr = (*RootPtr);
        (*RootPtr) = (*RootPtr)->RPtr;
        free(ptr);
      }
      else if((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL){
        ptr = (*RootPtr);
        (*RootPtr) = (*RootPtr)->LPtr;
        free(ptr);
      }
      else if ((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr == NULL){
        free((*RootPtr));
        *RootPtr = NULL;
      }
      else {
        ReplaceByRightmost(*RootPtr, (&((*RootPtr)->LPtr)));
      }
    }
  }
} 


void BSTDispose (tBSTNodePtr *RootPtr) {
/* Korektn� zru�� cel� bin�rn� vyhled�vac� strom. Zvolte nejv�hodn�j��
** druh rekurz�vn�ho pr�chodu stromem. Nedeklarujte ��dn� pomocn� procedury
** nebo funkce.
** POZOR: Vzhledem k jist� slo�itosti rekurz�vn�ho vol�n� t�to fce zde uv�d�m
** p��klad jak funkci zavolat (kdy� jsme p�ijali RootPtr jako ukazatel na 
** ukazatel). Spr�vn� zavol�n� nap�. na lev� podstrom:
** BSTDispose(&(*RootPtr)->LPtr).
*/

  if((*RootPtr)){
    BSTDispose(&(*RootPtr)->LPtr);
    BSTDispose(&(*RootPtr)->RPtr);
    free(*RootPtr);
    *RootPtr = NULL;
  }

}

/* --------------------------- konec c401.c -------------------------------- */
