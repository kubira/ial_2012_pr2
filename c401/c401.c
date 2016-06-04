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

  *RootPtr = NULL;  //Inicializace ko�ene stromu na NULL

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

  if(!RootPtr){  //Pokud je aktu�ln� uzel pr�zdn�,
    return FALSE;  //tak vrac�m FALSE - uzel nenalezen
  }
  else if(RootPtr->Key > K) {  //Pokud je kl�� aktu�ln�ho uzlu v�t�� ne� hled�m,
    return BSTSearch(RootPtr->LPtr, K, Content);  //vol�m rekurz� lev� podstrom
  }
  else if(RootPtr->Key < K) {  //Pokud je kl�� aktu�ln�ho uzlu men�� ne� hled�m,
    return BSTSearch(RootPtr->RPtr, K, Content);  //vol�m rekurz� prav� podstrom
  }
  else {  //Pokud nenastala ��dn� situace v��e, na�el jsem hledan� uzel
    *Content = RootPtr->BSTNodeCont;  //a jeho hodnotu ulo��m do Content
    return TRUE;  //Vrac�m TRUE - uzel nalezen
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

  if(*RootPtr == NULL){  //Pokud je aktu�ln� uzel pr�zdn�,
    if(!(*RootPtr = malloc(sizeof(struct tBSTNode)))){  //p�id�l�m mu pam�,
      printf("Nen� pam�!\n");  //pokud se nepoda�ilo pam� alokovat, ozn�m�m
      errflg = TRUE;
    }
    else {  //Pokud alokov�n� pam�ti prob�hlo v po��dku,
      (*RootPtr)->Key = K;  //nastav�m kl�� uzlu,
      (*RootPtr)->BSTNodeCont = Content;  //nastav�m obsah uzlu,
      (*RootPtr)->LPtr = NULL;  //lev� potomek zat�m neexistuje,
      (*RootPtr)->RPtr = NULL;  //prav� potomek tak� zat�m neexistuje
    }
  }
  else {  //Pokud nen� aktu�ln� uzel pr�zdn�,
    if((*RootPtr)->Key < K) {  //tak kdy� je jeho kl�� men�� ne� vkl�dan�,
      BSTInsert(&((*RootPtr)->RPtr), K, Content);  //vol�m rekurz� prav� podstrom
    }
    else if((*RootPtr)->Key > K) {  //kdy� je jeho kl�� v�t�� ne� vkl�dan�,
      BSTInsert(&((*RootPtr)->LPtr), K, Content);  //vol�m rekurz� lev� podstrom
    }
    else {  //pokud nenastala ��dn� situace v��e, tak uzel s kl��em K existuje
      (*RootPtr)->BSTNodeCont = Content;  //a nastav�m mu novou hodnotu
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
  
  if(*RootPtr){  //Pokud nen� aktu�ln� uzel pr�zdn�,
    if((*RootPtr)->RPtr != NULL) {  //tak pokud m� prav� podstrom,
      //zavol�m na prav� podstrom funkci ReplaceByRightMost
      ReplaceByRightmost(PtrReplaced, &((*RootPtr)->RPtr));
    }
    else if((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL) {
    //kdy� nem� prav� podstrom ,ale z�rove� m� lev� podstrom
      PtrReplaced->Key = (*RootPtr)->Key;
      //nastav�m ru�en� kl�� na aktu�ln� kl��,
      PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
      //nastav�m ru�en� obsah na aktu�ln� obsah,
      ptr = PtrReplaced->LPtr;
      //ulo��m si lev�ho potomka ru�en�ho uzlu do pomocn�ho ukazatele,
      PtrReplaced->LPtr = (*RootPtr)->LPtr;
      //nastav�m lev�ho potomka ru�en�ho uzlu na lev�ho potomka sou�asn�ho uzlu,
      free(ptr);  //uvoln�m pam� po zru�en�m uzlu
    }
    else {  //Pokud nenastala ��dn� situace v��e, aktu�ln� prvek nem� potomky,
      ptr = (*RootPtr);  //ulo��m si ho do pomocn�ho ukazatele pro zru�en�,
      PtrReplaced->Key = (*RootPtr)->Key;
      //nastav�m kl�� ru�en�ho uzlu na kl�� aktu�ln�ho uzlu,
      PtrReplaced->BSTNodeCont = (*RootPtr)->BSTNodeCont;
      //nastav�m obsah ru�en�ho uzlu na obsah aktu�ln�ho uzlu,
      free(ptr);  //uvoln�m pam� po zru�en�m uzlu
      *RootPtr = NULL;  //a nastav�m aktu�ln� uzel na NULL
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

  if(*RootPtr){  //Pokud nen� aktu�ln� uzel pr�zdn�,
    if((*RootPtr)->Key < K) {  //kdy� je kl�� aktu�ln�ho uzlu men�� ne� ru�en�ho,
      BSTDelete(&((*RootPtr)->RPtr), K);  //vol�m rekurzi na prav� podstrom
    }
    else if((*RootPtr)->Key > K) {  //kdy� je kl�� aktu�ln�ho uzlu v�t��,
      BSTDelete(&((*RootPtr)->LPtr), K);  //vol�m rekurzi na lev� podstrom
    }
    else if((*RootPtr)->Key == K) {  //kdy� jsem na�el uzel s ru�en�m kl��em,
      if((*RootPtr)->LPtr == NULL && (*RootPtr)->RPtr != NULL){
      //tak pokud nem� lev� podstrom, ale z�rove� m� prav� podstrom,
        ptr = (*RootPtr);  //ulo��m si aktu�ln� uzel pro zru�en�,
        (*RootPtr) = (*RootPtr)->RPtr;  //nahrad�m aktu�ln� uzel prav�m podstromem
        free(ptr);  //a uvoln�m pam� po ru�en�m uzlu
      }
      else if((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr != NULL){
      //pokud nem� prav� podstrom, ale z�rove� m� lev� podstrom,
        ptr = (*RootPtr);  //ulo��m si aktu�ln� uzel pro zru�en�,
        (*RootPtr) = (*RootPtr)->LPtr;  //nahrad�m aktu�ln� uzel lev�m podstromem
        free(ptr);  //a uvoln�m pam� po ru�en�m uzlu
      }
      else if ((*RootPtr)->RPtr == NULL && (*RootPtr)->LPtr == NULL){
      //pokud nem� aktu�ln� ru�en� uzel ��dn� potomky,
        free((*RootPtr));  //uvoln�m po n�m pam�
        *RootPtr = NULL;  //a nastav�m ho na NULL
      }
      else {  //kdy� nenastala ��dn� situace v��e,
        ReplaceByRightmost(*RootPtr, (&((*RootPtr)->LPtr)));
        //zavol�m funkci ReplaceByRightmost na lev� podstrom
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

  if((*RootPtr)){  //Pokud nen� aktu�ln� uzel pr�zdn�,
    BSTDispose(&(*RootPtr)->LPtr);  //zavol�m funkci rekurzivn� na lev� podstrom
    BSTDispose(&(*RootPtr)->RPtr);  //zavol�m funkci rekurzivn� na prav� podstrom
    free(*RootPtr);  //uvoln�m pam� po aktu�ln�m uzlu
    *RootPtr = NULL; //a nastav�m jej na NULL
  }

}

/* --------------------------- konec c401.c -------------------------------- */
