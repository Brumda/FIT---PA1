#include <stdio.h>
#include <stdlib.h>

int sorting(const int *a, const int *b)
{
    return (*a < *b) - (*b < *a);
}

void tower(int cubes[], int data[], int i, int *combinations, int cubes_count)
{
    if (i > cubes_count)
    {
        print();
        return;
    }

    data[i] = cubes[i];
    tower(cubes, data, i + 1, combinations, cubes_count);
}

int main(void)
{
    int combinations = 0;
    int cubes_count = 0;
    int *cubes = NULL;
    int *data = NULL;

    printf("Pocet kostek:\n");
    if (scanf("%d", &cubes_count) != 1 || cubes_count < 1)
    {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }

    cubes = (int *)malloc(cubes_count * sizeof(cubes));
    data = (int *)malloc(cubes_count * sizeof(data));
    printf("Velikosti:\n");
    for (int i = 0; i < cubes_count; i++)
    {
        if (scanf("%d", &cubes[i]) != 1 || cubes[i] < 1)
        {
            free(cubes);
            printf("Nespravny vstup.\n");
            return EXIT_FAILURE;
        }
    }

    qsort(cubes, cubes_count, sizeof(*cubes), (int (*)(const void *, const void *))sorting);

    tower(cubes, data, 0, &combinations, cubes_count);
    free(data);

    printf("Celkem: %d\n", combinations);
    free(cubes);
    return EXIT_SUCCESS;
}