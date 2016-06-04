/**/

/* **********************SOUBOR SE ST.TESTEM  ********************** */
/* **********************-----------------   *********************** */
/*  vytvoril: Martin Tucek
    predmet: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologii)
    test pro soubor: c403.c
	datum: rijen 2005
    kompletni upravy: Roman Lukas, 2006
													 */	
/* ***************************************************************** */


#include "c403.h"

tASTable TempTable;
int Key, ind;
int content;

/* pomocna procedura pro vypis prvku v poli */
void PrintElement(tASTable *TempTable)			{
	int i;
        printf("Aktualni stav tabulky:\n");
	for (i = 0; i < ASSize; i++)		
		printf("Pozice: %d Klic: %d, Hodnota: %d\n",
                i,TempTable->arr[i].Key,TempTable->arr[i].Cont);
        printf("Index posledniho prvku je: %d\n", TempTable->last);
        printf("=========================================================\n");

}


/* .............................. vypis jednotlivych testu .............................. */ 

int test_ASInit(tASTable *TempTable) {
	solved=TRUE;
	ASInit(TempTable);
	if (!solved)	{
		printf("Operace ASInit() nebyla implementovana \n");
		return(FALSE);
	}	
	else	{	 	
		PrintElement(TempTable);
		return(TRUE);	
	}		
}
	
int test_ASSearch (tASTable *TempTable, int Content, int *ind) {
	solved=TRUE;
	int found;
        ASCompNum = 0;
        found = ASSearch(TempTable, Content, ind);	
	if (!solved)	{
		printf("Operace ASSearch() nebyla implementovana \n");
		return(FALSE);
	}
	else	{
		PrintElement(TempTable);
                printf("Hodnota nalezena: ");
                if (found) 
                   printf("ANO\n");
                else
                   printf("NE\n");
                printf("Index vracen: %d\n", *ind);
                printf("Pocet provedenych porovnani: %d\n", ASCompNum);
	        printf("=========================================================\n");
                ASCompNum = 0;  
		return(TRUE);
	}	
}

int test_ASInsert(tASTable *TempTable, int Key, int Content) {
	solved=TRUE;
	ASInsert(TempTable, Key, Content);	
	if (!solved)	{
		printf("Operace ASInsert() nebyla implementovana \n");
		return(FALSE);
	}
	else	{	
		PrintElement(TempTable);
		return(TRUE);
	}	
}

/* .......................... sekce volani jednotlivych testu .............................*/ 

int main(int argc, char *argv[])			{
	
	printf("Vkladani a vyhledavani v neserazenem poli (zarazka, optimalizace)\n");
        printf("===================================================================================\n");
	
	printf("[TEST01]\n");
	printf("Nastavime testovaci velikost tabulky na 5 a provedeme inicializaci.\n");
	ASSize=5;
	test_ASInit(&TempTable);
		
	printf("[TEST02]\n");
	printf("Pokusime se vyhledat neexistujici polozku s klicem 1\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=1;
	test_ASSearch(&TempTable, Key, &ind);
	
	printf("[TEST03]\n");
	printf("Vlozime prvni polozku s hodnotou 1,klicem 1\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=1;
	Key=1;
	test_ASInsert(&TempTable, Key, content);
	
	printf("[TEST04]\n");
	printf("Pokusime se znovu vyhledat polozku s klicem 1\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASSearch(&TempTable, Key, &ind);
  	
	printf("[TEST05]\n");
	printf("Jeste jednou vyhledame prvni polozku v tabulce (test posouvani)\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASSearch(&TempTable, Key, &ind);
	
	printf("[TEST06]\n");
	printf("Pokusime se vyhledat neexistujici polozku s klicem 2\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=2;
	test_ASSearch(&TempTable, Key, &ind);
  
	printf("[TEST07]\n");
	printf("Provedeme aktualizaci polozky 1 na hodnotu 9\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=1;
	content=9;
	test_ASInsert(&TempTable, Key, content);	
	
	printf("[TEST08]\n");
	printf("Vlozime dalsi polozky\n");
	printf("~~~~~~~~~~~~~~~~~~~~~\n");
	content=1;
	Key=2;
	test_ASInsert(&TempTable, Key, content);
	content=2;
	Key=3;
	test_ASInsert(&TempTable, Key, content);
	content=3;
	Key=4;
	test_ASInsert(&TempTable, Key, content);

	printf("[TEST09]\n");
	printf("Dalsi polozka jiz nesmi jit vlozit, nebot by nezustalo misto pro zarazku\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=4;
	Key=5;
	test_ASInsert(&TempTable, Key, content);
  
	printf("[TEST10]\n");
	printf("Provedeme aktualizaci polozky 2 na hodnotu 5. Mel by nastat presun.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=2;
	content=5;
	test_ASInsert(&TempTable, Key, content);	

	printf("[TEST11]\n");
	printf("Budeme 5x vyhledavat posledni vlozenou polozku 4\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=4;
	int i;
	for(i = 1;i < 5;i++)
	test_ASSearch(&TempTable, Key, &ind);
	
	printf("[TEST12]\n");
	printf("Provedeme aktualizaci polozky 2 na hodnotu 8\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=2;
	content=8;
	test_ASInsert(&TempTable, Key, content);	
	
	printf("[TEST13]\n");
	printf("Pokusime se vlozit dalsi polozky, coz nesmi jit\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=20;
	Key=30;
	test_ASInsert(&TempTable, Key, content);
	content=30;
	Key=40;
	test_ASInsert(&TempTable, Key, content);

	printf("[TEST14]\n");
	printf("A na zaver tabulku inicializujeme (ztrata vsech dat)\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASInit(&TempTable);
	
	printf("[TEST15]\n");
	printf("A jeste jedna inicializace (ztrata vsech dat) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_ASInit(&TempTable);

	printf("------------------------------ konec -------------------------------------\n");
	return(0);
}
