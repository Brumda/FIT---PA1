#include <stdio.h>
#include <stdlib.h>

int sorting(const int *a, const int *b)
{
    return (*a < *b) - (*b < *a);
}

int error()
{
    printf("Nespravny vstup.\n");
    return EXIT_FAILURE;
}

void print(int *cubes, int cubes_count, int *combinations, int *black_list)
{
    for (int i = 0; i < cubes_count; i++)
    {
        if (!black_list[i])
        {
            if (i > 0)
                printf(", ");
            printf("%d", cubes[i]);
        }
    }
    printf("\n");
    (*combinations)++;
}
int towers(int *cubes, int cubes_count, int *combinations, int *cnt, int *black_list)
{
    (*cnt)++;
    int *black_list2 = NULL;

    if (!cubes_count)
        return EXIT_SUCCESS;

    if (*cnt > 1)
    {

        black_list[cubes_count - (*cnt - 1)] = 1;
        black_list[cubes_count - (*cnt - 2)] = 0;

        black_list2 = (int *)malloc(cubes_count * sizeof(black_list2));
        for (int i = 0; i < cubes_count; i++)
            black_list2[i] = black_list[i];

        if (*cnt > 2)
        {
            for (int i = 0; i < cubes_count - (cubes_count - (*cnt - 2)); i++)
            {
                black_list2[cubes_count - (i + 1)] = 1;
                // printf("-----\n");
                // for (int j = 0; j < cubes_count; j++)
                //     printf("%d", black_list2[j]);
                // printf("\n-----\n");
                // printf("i is %d-->", i);
                // printf("\n");
                print(cubes, cubes_count, combinations, black_list2);
            }
            for (int i = 1; i < cubes_count - (cubes_count - (*cnt - 2)); i++)
            {
                black_list2[cubes_count - i] = 0;
                // for (int j = 0; j < cubes_count; j++)
                //     printf("%d", black_list2[j]);
                // printf("\n");
                print(cubes, cubes_count, combinations, black_list2);
            }
        }
    }

    // for (int i = 0; i < cubes_count; i++)
    //     printf("%d", black_list[i]);
    // printf("\n         ");
    // printf("\n");

    print(cubes, cubes_count, combinations, black_list);

    if (*cnt < cubes_count)
    {
        free(black_list2);
        towers(cubes, cubes_count, combinations, cnt, black_list);
    }
    free(black_list2);
    (*cnt) = 0;
    for (int i = 0; i < cubes_count; i++)
        black_list[i] = 0;
    towers(cubes + 1, cubes_count - 1, combinations, cnt, black_list);
}

int main(void)
{
    int combinations = 0;
    int cubes_count = 0;
    int *cubes = NULL;
    int cnt = 0;
    int *black_list = NULL;

    printf("Pocet kostek:\n");
    if (scanf("%d", &cubes_count) != 1 || cubes_count < 1)
        error();

    cubes = (int *)malloc(cubes_count * sizeof(cubes));

    printf("Velikosti:\n");
    for (int i = 0; i < cubes_count; i++)
    {
        if (scanf("%d", &cubes[i]) != 1 || cubes[i] < 1)
            error();
    }

    black_list = (int *)malloc(cubes_count * sizeof(black_list));
    for (int i = 0; i < cubes_count; i++)
        black_list[i] = 0;

    qsort(cubes, cubes_count, sizeof(*cubes), (int (*)(const void *, const void *))sorting);
    towers(cubes, cubes_count, &combinations, &cnt, black_list);
    printf("Celkem: %d\n", combinations);
    free(cubes);
    free(black_list);
    return EXIT_SUCCESS;
}