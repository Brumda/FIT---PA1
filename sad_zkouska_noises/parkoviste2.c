#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int priority;
    char SPZ[11];

} TMISTO;
typedef struct
{
    int x;
    int y;
    int free_places;
    TMISTO **plocha;

} TPARKOVISTE;

char intToChar(int x, int camel)
{
    return x + 97 - camel * 32;
}

int loadParkoviste(TPARKOVISTE *park)
{
    char a, b;
    if (scanf(" %c %c", &a, &b) != 2 || a < 65 || a > 90 || b < 97 || b > 122)
    {
        return -1;
    }
    park->y = a - 64;
    park->x = b - 96;
    park->plocha = (TMISTO **)malloc((park->y) * sizeof(TMISTO *));
    for (int y = 0; y < park->y; y++)
    {
        park->plocha[y] = (TMISTO *)malloc((park->x) * sizeof(TMISTO));
        for (int x = 0; x < park->x; x++)
        {
            park->plocha[y][x].priority = y * park->x + x + 1;
        }
    }
    park->free_places = park->y * park->x;
    return 1;
}

int getCommands(TPARKOVISTE *park)
{
    char character;
    if (scanf(" %c", &character) == -1)
        return -1;
    if (character == '+')
    {
        char SPZ[11];
        if (scanf(" %10s", SPZ) != 1)
        {
            return -2;
        }
        if (park->free_places == 0)
        {
            printf("Plne obsazeno\n");
            return 1;
        }
        for (int y = 0; y < park->y; y++)
        {
            for (int x = 0; x < park->x; x++)
            {
                if (park->plocha[y][x].priority > 0)
                    park->plocha[y][x].priority--;
                if (park->plocha[y][x].priority == 0)
                {
                    park->plocha[y][x].priority = -1;
                    park->free_places -= 1;
                    strcpy(park->plocha[y][x].SPZ, SPZ);
                    printf("Pozice: %c%c, zbyva: %d\n", intToChar(y, 1), intToChar(x, 0), park->free_places);
                }
            }
        }
        return 1;
    }
    if (character == '-')
    {
        char SPZ[11];
        if (scanf(" %10s", SPZ) != 1)
        {
            return -2;
        }
        for (int y = 0; y < park->y; y++)
        {
            for (int x = 0; x < park->x; x++)
            {
                if (park->plocha[y][x].priority == -1 && strcmp(park->plocha[y][x].SPZ, SPZ) == 0)
                {
                    park->free_places += 1;
                    park->plocha[y][x].priority = park->free_places;
                    printf("Pozice: %c%c, zbyva: %d\n", intToChar(y, 1), intToChar(x, 0), park->free_places);
                    return 1;
                }
            }
        }
        printf("Nenalezeno\n");
        return 1;
    }
    return -2;
}

void freeParkoviste(TPARKOVISTE parkoviste)
{
    for (int x = 0; x < parkoviste.y; x++)
    {
        free(parkoviste.plocha[x]);
    }
    free(parkoviste.plocha);
}
int main()
{
    printf("Velikost:\n");
    TPARKOVISTE parkoviste;
    if (loadParkoviste(&parkoviste) != 1)
    {
        printf("Nespravny vstup.\n");
        return -1;
    }
    printf("Pozadavky:\n");
    int res = 0;
    while (res = getCommands(&parkoviste))
    {
        if (res == -2)
        {
            printf("Nespravny vstup.\n");
            break;
        }
        if (res == -1)
        {
            break;
        }
    }
    freeParkoviste(parkoviste);
}