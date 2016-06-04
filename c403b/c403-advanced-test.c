

/* Testy pro dom�c� �kol na t�ma Vyhled�vac� tabulka v nese�azen�m poli
se zar. (optimalizace) (c403.c). Obsahuje procedury a funkce, kter� 
testuj� studentsk� verze principem jejich vol�n� (v�pis na stdout). 
Toto je roz���en� verze, obsahuj�c� komplexn� mno�stv� procedur a funkc� 
na otestov�n�. Slou�� pro lektory ke kontrole p��slu�n� dom�c� �lohy */

/* **********************SOUBOR S ST.TESTEM  *********************** */
/* **********************-----------------   *********************** */
/*  vytvo�il: Martin Tu�ek
    p�edm�t: Algoritmy (IAL) - FIT (Fakulta Informacnich Technologi�)
    test pro soubor: c403.c
	datum: z��� 2005												 */	
/* ***************************************************************** */

#include "c403.h"

tASTable TempTable;
int Key, ind;
int content;

/* pomocna procedura pro vypis prvku v poli */
void PrintElement(tASTable *TempTable)			{
	int i;
        printf("Aktu�ln� stav tabulky:\n");
	for (i = 0; i < ASSize; i++)		
		printf("Pozice: %d Kl��: %d, Hodnota: %d\n",
                i,TempTable->arr[i].Key,TempTable->arr[i].Cont);
        printf("Index posledn�ho prvku je: %d\n", TempTable->last);
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
                printf("Index vr�cen: %d\n", *ind);
                printf("Po�et proveden�ch porovn�n�: %d\n", ASCompNum);
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
	
	printf("Vkl�d�n� a vyhled�v�n� v nese�azen�m poli (zar�ka, optimalizace) - pokrocile testy\n");
	printf("===================================================================================\n");
	
	printf("[TEST01]\n");
	printf("Nastav�me testovac� velikost tabulky na 5 a provedeme inicializaci.\n");
	ASSize=5;
	test_ASInit(&TempTable);
		
	printf("[TEST02]\n");
	printf("Pokus�me se vyhledat neexistuj�c� polo�ku s kl��em 1\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=1;
	test_ASSearch(&TempTable, Key, &ind);
	
	printf("[TEST03]\n");
	printf("Vlo��me prvn� polo�ku s hodnotou 1,kl��em 1\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=1;
	Key=1;
	test_ASInsert(&TempTable, Key, content);
	
	printf("[TEST04]\n");
	printf("Pokus�me se znovu vyhledat polo�ku s kl��em 1\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASSearch(&TempTable, Key, &ind);
  	
	printf("[TEST05]\n");
	printf("Je�t� jednou vyhled�me prvn� polo�ku v tabulce (test posouv�n�)\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASSearch(&TempTable, Key, &ind);
	
	printf("[TEST06]\n");
	printf("Pokus�me se vyhledat neexistuj�c� polo�ku s kl��em 2\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=2;
	test_ASSearch(&TempTable, Key, &ind);
  
	printf("[TEST07]\n");
	printf("Provedeme aktualizaci polo�ky 1 na hodnotu 9\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=1;
	content=9;
	test_ASInsert(&TempTable, Key, content);	
	
	printf("[TEST08]\n");
	printf("Vlo��me dal�� polo�ky\n");
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
	printf("Dal�� polo�ka ji� nesm� j�t vlo�it, nebo� by nez�stalo m�sto pro zar�ku\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=4;
	Key=5;
	test_ASInsert(&TempTable, Key, content);
  
	printf("[TEST10]\n");
	printf("Provedeme aktualizaci polo�ky 2 na hodnotu 5. M�l by nastat p�esun.\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=2;
	content=5;
	test_ASInsert(&TempTable, Key, content);	

	printf("[TEST11]\n");
	printf("Budeme 5x vyhled�vat posledn� vlo�enou polo�ku 4\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=4;
	int i;
	for(i = 1;i < 5;i++)
	test_ASSearch(&TempTable, Key, &ind);
	
	printf("[TEST12]\n");
	printf("Provedeme aktualizaci polo�ky 2 na hodnotu 8\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=2;
	content=8;
	test_ASInsert(&TempTable, Key, content);	

	printf("[TEST13]\n");
	printf("Provedeme aktualizaci polo�ky 3 na hodnotu 9\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=3;
	content=9;
	test_ASInsert(&TempTable, Key, content);	
	
	printf("[TEST14]\n");
	printf("Pokus�me se vlo�it dal�� polo�ky, co� nesm� j�t\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=20;
	Key=30;
	test_ASInsert(&TempTable, Key, content);
	content=30;
	Key=40;
	test_ASInsert(&TempTable, Key, content);

	printf("[TEST15]\n");
	printf("Tabulku inicializujeme (ztr�ta v�ech dat)\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASInit(&TempTable);
	
	printf("[TEST16]\n");
	printf("A je�t� jedna inicializace (ztr�ta v�ech dat) \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	test_ASInit(&TempTable);

	printf("[TEST17]\n");
	printf("Pokus�me se vlo�it dal�� polo�ky\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	content=20;
	Key=30;
	test_ASInsert(&TempTable, Key, content);
	content=30;
	Key=40;
	test_ASInsert(&TempTable, Key, content);

	printf("[TEST18]\n");
	printf("Pokus�me se vyhledat polo�ku s kl��em 40\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=40;
	test_ASSearch(&TempTable, Key, &ind);

	printf("[TEST19]\n");
	printf("Pokus�me se vyhledat polo�ku s kl��em 20\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	Key=20;
	test_ASSearch(&TempTable, Key, &ind);

	printf("[TEST20]\n");
	printf("Tabulku inicializujeme (ztr�ta v�ech dat)\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	test_ASInit(&TempTable);

	printf("------------------------------ konec -------------------------------------\n");
	return(0);
}
