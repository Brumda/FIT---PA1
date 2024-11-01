#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct parkmisto {
	int value; //value == 0 - místo je prázdné; value == 1 - místo je obsazené  
	char rz[11]; // +1 na ukončovací nulu
}PARKMISTO;
 
void freePark(PARKMISTO **array, int x) //funkce pro uvolnění 2D pole
{
	for (int i = 0; i < x; i++)
	{
		free(array[i]);
	}
	free(array);
}
 
int main()
{
	int x, y;
	printf("Velikost:\n");
	if (scanf(" %d %d", &x,&y)!=2 || x <= 0 || y <= 0) //načteme velikost
	{
		printf("Nespravny vstup:\n");
		return 1;
	}
	PARKMISTO **array = (PARKMISTO**)calloc(x, sizeof(PARKMISTO*)); //dynamicky alokujeme parkoviště (2D pole)
	for (int i = 0; i < x; i++ )
	{
		array[i]= (PARKMISTO*)calloc(y, sizeof(PARKMISTO));
	}
 
	printf("Pozadavky:\n");
	int pozx, pozy, err;
	char ch; //do proměnné ch uložíme první znak a kontrolujeme jestli je to + nebo -
	char buffer[11]; //dočasné uložiště pro RZ
 
	while ((err = (scanf(" %c", &ch)) == 1))
	{
		if (ch !='+' && ch !='-') //kontrola prvního znaku
		{
			printf("Nespravny vstup\n");
			freePark(array, x);
			return 1;
		}
		if (ch == '+') //příjezd auta
		{
			if (scanf(" %d %d %10s", &pozx, &pozy, buffer) != 3 || pozx >= x || pozy >= y || pozx < 0 || pozy < 0 ) //načteme umístění a RZ nového auta
			{
				printf("Nespravny vstup\n");
				freePark(array, x);
				return 1;
			}
			if (array[pozx][pozy].value == 1) //zjistíme jestli je místo volné
			{
				printf("Obsazeno %s\n", array[pozx][pozy].rz);
			}
			else //je volné - označíme místo jako obsazené a nakopírujeme RZ
			{
				array[pozx][pozy].value = 1;
				strcpy(array[pozx][pozy].rz, buffer);
				printf("OK\n");
			}
		}
		if (ch == '-') //odjezd auta
		{
			int found = 0;  //found nastavíme na 1 pokud jsme našli RZ
			if (scanf(" %10s", buffer)!=1) //načteme RZ
			{
				printf("Nespravny vstup\n");
				freePark(array, x);
				return 1;
			}
			for (int i = 0; i < x; i++) //prohledáme celé parkoviště, jestli se v něm zadaná RZ vyskytuje
			{
				if (found == 1)break;
				for (int j = 0; j < y; j++)
				{
					if (strcmp(array[i][j].rz, buffer) == 0) //pokud nalezneme RZ:
					{
						array[i][j].value = 0; //označíme toto místo za prázdné 
						strcpy(array[i][j].rz, ""); //vymažeme RZ
						found = 1; 
						break;
					}
 
				}
			}
			if (found == 1) //pokud nalezneme RZ
			{
				printf("OK\n");
			}
			else //pokud nenalezneme
			{
				printf("Nenalezeno\n"); 
			}
		}
	}
	if (err != EOF)
	{
		printf("Nespravny vstup.\n");
		freePark(array, x);
		return 0;
	}
}