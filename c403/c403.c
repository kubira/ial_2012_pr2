/* ------------------------------- c403.c ----------------------------------- */
/* T�ma: Vyhled�vac� tabulka v nese�azen�m poli se zar�kou (optimalizace)
**       Prvn� implementace: Petr P�ikryl, prosinec 1994
**       �pravy: Petr P�ikryl, listopad 1997, kv�ten 1998
**       Dal�� �prava: Martin Tu�ek, srpen 2005 (jazyk C)
**       Dal�� �prava: Roman Luk�, ��jen 2006
**
** Implementujte vyhled�vac� tabulku podle n�sleduj�c�ch po�adavk�.
** Tabulka je implementov�na v poli, obsah prvk� pole nen� se�azen.
** P�i vyhled�v�n� se sekven�n� proch�z� cel� vyu�it� pole s vyu�it�m
** takzvan� zar�ky. Maxim�ln� kapacita tabulky je tedy o jedni�ku ni���,
** ne� maxim�ln� vyu�iteln� kapacita pole. Implementujte n�sleduj�c� procedury
** a funkce (zkratka AS poch�z� ze slova Array = pole a Sentinel = zde zar�ka):
** 
**   ASInit ..... inicializace tabulky
**   ASSearch ... vyhled�v�n� se zar�kou v nese�azen�m poli
**   ASInsert ... vkl�d�n� do nese�azen�ho pole s vyu�it�m ASSearch
**
** P�i ka�d�m vyhled�n� se optimalizuje doba vyhled�v�n� �asto hledan�ch
** polo�ek t�m, �e se nalezen� polo�ka v�dy posunuje o jedno m�sto sm�rem
** k za��tku pole.
**
** Definici typ� naleznete v souboru c403.h. Tabulka je reprezentov�na
** datovou strukturou typu tASTable, kter� se skl�d� z pole 'arr' a indexu
** posledn� vyu�it� polo�ky pole 'last'. Polo�ky pole jsou tvo�eny z�znamy
** typu tASData, ve kter�ch se nach�z� slo�ka Key (kl��em je pro jednoduchost
** ��slo typu integer) a obsah Cont (demonstrativn� int). P�i implementaci t�l
** �e�en�ch procedur uva�ujte maxim�ln� rozm�r pole ASSize (viz pozn�mka
** v c403.h).
**
** D�le�it�m rysem vyhled�vac�ch metod je po�et porovn�v�n� vyhled�van�ho
** kl��e s kl��i prohled�van�ch polo�ek pole. K porovn�v�n� vyu��vejte
** povinn� funkce ASCompare (viz d�le). Po�et porovn�v�n� omezte
** na minimum. To znamen�, �e nebudete volat podruh� funkci ASCompare
** pro stejn� kl��e tam, kde jste si mohli v�sledek porovn�n� zapamatovat
** v pomocn� prom�nn�.
*/

#include "c403.h"
int ASCompNum;
int solved;
int errflg;

int ASCompare (int k1, int k2) {
  ASCompNum = ASCompNum + 1;      /* po�et porovn�n� */ 
  if (k1 < k2)                    /* porovn�n� dvou kl��� */
    return(-1);
  else if (k1 == k2)
    return(0);
  else                            /* k1 > k2 */ 
    return(1);
}

void ASError() {
  printf("Chyba: Polozka jiz nemuze byt vlozena\n");
  errflg = TRUE;
}
/* ------------------------------------------------------------------------- */
void ASInit(tASTable *Tab) {
/* Inicializace tabulky (v�sledkem je pr�zdn� tabulka).
** Inicializace tabulky se provede tak, �e se index posledn�ho prvku nastav� na
** hodnotu -1. Hodnoty prvk� ani kl��� se v tabulce nem�n�.
*/

  Tab->last = -1;  //Inicializace tabulky

}


int ASSearch (tASTable *Tab, int key, int* ind) {
/* Vyhled�v�n� v NESE�AZEN�M poli se zar�kou a s p�esunem nalezen�
** polo�ky o jednu pozici dop�edu (v�m�na s p�edchoz� polo�kou).
**
** Vyhled�vac�m kl��em je hodnota key. Funkce vrac� p��znak, zda byl prvek
** nalezen. Pokud ne (vrac� false), pak se v prom�nn� 'ind' vrac� prvn�
** voln� pozice, na kterou se m��e prvek vlo�it.
** Pokud byl prvek nalezen (vrac� true), do�lo k jeho posunut� o jednu
** pozici dop�edu a v prom�nn� ind se vrac� nov� pozice nalezen�ho prvku.
**
** Pro porovn�n� dvou kl��� pou��vejte p�eddefinovanou funkci ASCompare
** (viz. v��e). Vzhledem k tomu, �e se p�i vyhled�v�n� v�dy pou��v�
** zar�ka, bude minim�ln� po�et porovn�n� (p�i pr�zdn� tabulce) roven 1.
**
** POZOR!!!
** P�i vlo�en� zar�ky se hodnota 'last' NEM�N�! Zar�ka se tedy nach�z�
** na pozici 'last' + 1. Zar�ka m��e obsahovat obecn� libovolnou hodnotu, 
** vy ale hodnotu zar�ky nastavte na -1, aby se v�m shodovaly v�sledky test�!
*/

  int index = 0, myKey, myCont;  //Pomocn� prom�nn� pro vyhled�v�n�

  Tab->arr[Tab->last + 1].Key = key;  //Nastav�m kl�� zar�ky na key
  Tab->arr[Tab->last + 1].Cont = -1;  //Nastav�m obsah zar�ky na -1

  while(ASCompare(Tab->arr[index].Key, key)) {  //Dokud se kl��e nerovnaj�,
    if (index == (Tab->last + 1)) {  //pokud je index roven pozici za posledn�m,
      *ind = (Tab->last + 1);  //nastav�m ind na tuto pozici
      return FALSE;  //a vrac�m FALSE - nenalezen
    }
    else {  //pokud nen� index roven indexu za posledn�m,
      index++;  //inkrementace indexu o 1
    }
  }

  if (index != (Tab->last + 1)){  //Pokud se index nerovn� pozici za posledn�m,
    *ind = index;  //nastav�m ind na hodnotu indexu

    if (index != 0) {  //Pokud index nen� nula, budu m�nit pozici,
      myKey = Tab->arr[*ind - 1].Key;  //ulo��m si kl�� p�ed ind,
      myCont = Tab->arr[*ind - 1].Cont;  //ulo��m si obsah p�ed ind,
      Tab->arr[*ind - 1].Key = Tab->arr[*ind].Key;  //posunu o 1 pozici vp�ed,
      Tab->arr[*ind - 1].Cont = Tab->arr[*ind].Cont;  //posunu o 1 pozici vp�ed,
      Tab->arr[*ind].Key = myKey;  //nahrad�m posunut� kl�� ulo�en�m,
      Tab->arr[*ind].Cont = myCont;  //nahrad�m posunut� obsah ulo�en�m,
      *ind = index - 1;  //nastav�m ind na novou pozici prvku
    }

    return TRUE;  //vrac�m TRUE - nalezen
  }  //Pokud se index rovn� pozici za posledn�m,
  else {
    *ind = Tab->last + 1;  //nastav�m ind na pozici za posledn�m
  }

  return FALSE;  //Vrac�m FALSE - nenalezen
}


void ASInsert (tASTable *Tab, int Key, int Content) {
/* Vlo�� novou polo�ku s obsahem Content a kl��em Key do tabulky Tab.
**
** Pokud by vlo�en�m dal�� polo�ky do�lo k p�epln�n� Tab (pokud by ne�lo
** p�i dal��m vyhled�v�n� ulo�it zar�ku), volejte proceduru ASError()
** a novou polo�ku nevkl�dejte.
**
** Pokud dan� polo�ka (udan� kl��em Key) v poli ji� existuje, p�i�ad� se do
** odpov�daj�c� slo�ky z�znamu nov� obsah. P�i vyhled�v�n� ji� existuj�c� 
** polo�ky vyu�ijte d��ve implementovanou funkci ASSearch (to znamen�, �e se
** existuj�c� a modifikovan� polo�ka automaticky posune dop�edu).
*/

  int index;  //Pomocn� prom�nn� pro vkl�d�n�

  if (ASSearch(Tab, Key, &index)) {  //Pokud u� je v poli polo�ka s kl��em Key,
    Tab->arr[index].Cont = Content;  //nastav� se j� nov� obsah
  }
  else {  //Pokud v poli polo�ka s kl��em Key je�t� nen�
    if ((Tab->last + 1) <= (ASSize - 2)) {  //a pokud nen� tabulka pln�,
      Tab->arr[Tab->last + 1].Key = Key;  //vlo��m na dal�� pozici kl�� Key
      Tab->arr[Tab->last + 1].Cont = Content;  //a vlo��m obsah dal�� pozice
      Tab->last = Tab->last + 1;  //Mus�m zv��it index posledn�ho prvku o 1
    }
    else {  //Pokud je tabulka pln�,
      ASError();  //zavol�m funkci ASError()
    }
  }
}

/* -------------------------- konec c403.c --------------------------------- */
