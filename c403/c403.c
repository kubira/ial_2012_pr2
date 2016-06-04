/* ------------------------------- c403.c ----------------------------------- */
/* Téma: Vyhledávací tabulka v neseøazeném poli se zará¾kou (optimalizace)
**       První implementace: Petr Pøikryl, prosinec 1994
**       Úpravy: Petr Pøikryl, listopad 1997, kvìten 1998
**       Dal¹í úprava: Martin Tuèek, srpen 2005 (jazyk C)
**       Dal¹í úprava: Roman Luká¹, øíjen 2006
**
** Implementujte vyhledávací tabulku podle následujících po¾adavkù.
** Tabulka je implementována v poli, obsah prvkù pole není seøazen.
** Pøi vyhledávání se sekvenènì prochází celé vyu¾ité pole s vyu¾itím
** takzvané zará¾ky. Maximální kapacita tabulky je tedy o jednièku ni¾¹í,
** ne¾ maximální vyu¾itelná kapacita pole. Implementujte následující procedury
** a funkce (zkratka AS pochází ze slova Array = pole a Sentinel = zde zará¾ka):
** 
**   ASInit ..... inicializace tabulky
**   ASSearch ... vyhledávání se zará¾kou v neseøazeném poli
**   ASInsert ... vkládání do neseøazeného pole s vyu¾itím ASSearch
**
** Pøi ka¾dém vyhledání se optimalizuje doba vyhledávání èasto hledaných
** polo¾ek tím, ¾e se nalezená polo¾ka v¾dy posunuje o jedno místo smìrem
** k zaèátku pole.
**
** Definici typù naleznete v souboru c403.h. Tabulka je reprezentována
** datovou strukturou typu tASTable, která se skládá z pole 'arr' a indexu
** poslední vyu¾ité polo¾ky pole 'last'. Polo¾ky pole jsou tvoøeny záznamy
** typu tASData, ve kterých se nachází slo¾ka Key (klíèem je pro jednoduchost
** èíslo typu integer) a obsah Cont (demonstrativnì int). Pøi implementaci tìl
** øe¹ených procedur uva¾ujte maximální rozmìr pole ASSize (viz poznámka
** v c403.h).
**
** Dùle¾itým rysem vyhledávacích metod je poèet porovnávání vyhledávaného
** klíèe s klíèi prohledávaných polo¾ek pole. K porovnávání vyu¾ívejte
** povinnì funkce ASCompare (viz dále). Poèet porovnávání omezte
** na minimum. To znamená, ¾e nebudete volat podruhé funkci ASCompare
** pro stejné klíèe tam, kde jste si mohli výsledek porovnání zapamatovat
** v pomocné promìnné.
*/

#include "c403.h"
int ASCompNum;
int solved;
int errflg;

int ASCompare (int k1, int k2) {
  ASCompNum = ASCompNum + 1;      /* poèet porovnání */ 
  if (k1 < k2)                    /* porovnání dvou klíèù */
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
/* Inicializace tabulky (výsledkem je prázdná tabulka).
** Inicializace tabulky se provede tak, ¾e se index posledního prvku nastaví na
** hodnotu -1. Hodnoty prvkù ani klíèù se v tabulce nemìní.
*/

  Tab->last = -1;  //Inicializace tabulky

}


int ASSearch (tASTable *Tab, int key, int* ind) {
/* Vyhledávání v NESEØAZENÉM poli se zará¾kou a s pøesunem nalezené
** polo¾ky o jednu pozici dopøedu (výmìna s pøedchozí polo¾kou).
**
** Vyhledávacím klíèem je hodnota key. Funkce vrací pøíznak, zda byl prvek
** nalezen. Pokud ne (vrací false), pak se v promìnné 'ind' vrací první
** volná pozice, na kterou se mù¾e prvek vlo¾it.
** Pokud byl prvek nalezen (vrací true), do¹lo k jeho posunutí o jednu
** pozici dopøedu a v promìnné ind se vrací nová pozice nalezeného prvku.
**
** Pro porovnání dvou klíèù pou¾ívejte pøeddefinovanou funkci ASCompare
** (viz. vý¹e). Vzhledem k tomu, ¾e se pøi vyhledávání v¾dy pou¾ívá
** zará¾ka, bude minimální poèet porovnání (pøi prázdné tabulce) roven 1.
**
** POZOR!!!
** Pøi vlo¾ení zará¾ky se hodnota 'last' NEMÌNÍ! Zará¾ka se tedy nachází
** na pozici 'last' + 1. Zará¾ka mù¾e obsahovat obecnì libovolnou hodnotu, 
** vy ale hodnotu zará¾ky nastavte na -1, aby se vám shodovaly výsledky testù!
*/

  int index = 0, myKey, myCont;  //Pomocné promìnné pro vyhledávání

  Tab->arr[Tab->last + 1].Key = key;  //Nastavím klíè zará¾ky na key
  Tab->arr[Tab->last + 1].Cont = -1;  //Nastavím obsah zará¾ky na -1

  while(ASCompare(Tab->arr[index].Key, key)) {  //Dokud se klíèe nerovnají,
    if (index == (Tab->last + 1)) {  //pokud je index roven pozici za posledním,
      *ind = (Tab->last + 1);  //nastavím ind na tuto pozici
      return FALSE;  //a vracím FALSE - nenalezen
    }
    else {  //pokud není index roven indexu za posledním,
      index++;  //inkrementace indexu o 1
    }
  }

  if (index != (Tab->last + 1)){  //Pokud se index nerovná pozici za posledním,
    *ind = index;  //nastavím ind na hodnotu indexu

    if (index != 0) {  //Pokud index není nula, budu mìnit pozici,
      myKey = Tab->arr[*ind - 1].Key;  //ulo¾ím si klíè pøed ind,
      myCont = Tab->arr[*ind - 1].Cont;  //ulo¾ím si obsah pøed ind,
      Tab->arr[*ind - 1].Key = Tab->arr[*ind].Key;  //posunu o 1 pozici vpøed,
      Tab->arr[*ind - 1].Cont = Tab->arr[*ind].Cont;  //posunu o 1 pozici vpøed,
      Tab->arr[*ind].Key = myKey;  //nahradím posunutý klíè ulo¾eným,
      Tab->arr[*ind].Cont = myCont;  //nahradím posunutý obsah ulo¾eným,
      *ind = index - 1;  //nastavím ind na novou pozici prvku
    }

    return TRUE;  //vracím TRUE - nalezen
  }  //Pokud se index rovná pozici za posledním,
  else {
    *ind = Tab->last + 1;  //nastavím ind na pozici za posledním
  }

  return FALSE;  //Vracím FALSE - nenalezen
}


void ASInsert (tASTable *Tab, int Key, int Content) {
/* Vlo¾í novou polo¾ku s obsahem Content a klíèem Key do tabulky Tab.
**
** Pokud by vlo¾ením dal¹í polo¾ky do¹lo k pøeplnìní Tab (pokud by ne¹lo
** pøi dal¹ím vyhledávání ulo¾it zará¾ku), volejte proceduru ASError()
** a novou polo¾ku nevkládejte.
**
** Pokud daná polo¾ka (udaná klíèem Key) v poli ji¾ existuje, pøiøadí se do
** odpovídající slo¾ky záznamu nový obsah. Pøi vyhledávání ji¾ existující 
** polo¾ky vyu¾ijte døíve implementovanou funkci ASSearch (to znamená, ¾e se
** existující a modifikovaná polo¾ka automaticky posune dopøedu).
*/

  int index;  //Pomocná promìnná pro vkládání

  if (ASSearch(Tab, Key, &index)) {  //Pokud u¾ je v poli polo¾ka s klíèem Key,
    Tab->arr[index].Cont = Content;  //nastaví se jí nový obsah
  }
  else {  //Pokud v poli polo¾ka s klíèem Key je¹tì není
    if ((Tab->last + 1) <= (ASSize - 2)) {  //a pokud není tabulka plná,
      Tab->arr[Tab->last + 1].Key = Key;  //vlo¾ím na dal¹í pozici klíè Key
      Tab->arr[Tab->last + 1].Cont = Content;  //a vlo¾ím obsah dal¹í pozice
      Tab->last = Tab->last + 1;  //Musím zvý¹it index posledního prvku o 1
    }
    else {  //Pokud je tabulka plná,
      ASError();  //zavolám funkci ASError()
    }
  }
}

/* -------------------------- konec c403.c --------------------------------- */
