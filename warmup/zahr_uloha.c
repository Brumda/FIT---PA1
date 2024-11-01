#include <stdio.h>

int main(void)
{
    char citaty[5][102] = {
        "Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.",
        "Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.",
        "Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.",
        "Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.",
        "Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej."};
    int cislo;
    printf("ml' nob:\n");
    if (scanf("%d", &cislo) != 1 || cislo < 1 || cislo > 5 || cislo == EOF)
    {
        printf("luj\n");
        return 1;
    }
    switch (cislo)
    {
    case 1:
        printf("%s\n", citaty[cislo - 1]);
        break;
    case 2:
        printf("%s\n", citaty[cislo - 1]);
        break;
    case 3:
        printf("%s\n", citaty[cislo - 1]);
        break;
    case 4:
        printf("%s\n", citaty[cislo - 1]);
        break;
    case 5:
        printf("%s\n", citaty[cislo - 1]);
        break;
    }
    return 0;
}
