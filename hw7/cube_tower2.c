#include <stdio.h>
#include <stdlib.h>

int sorting(const int *a, const int *b)
{
    return (*a < *b) - (*b < *a);
}

//funcion from https://www.geeksforgeeks.org
void tower(int arr[], int n, int r, int index, int data[], int i, int *combinations, int *dupl)
{
    // if (i > 0 && arr[i] == arr[i - 1])
    //     *dupl = 1;
    // else
    //     *dupl = 0;

    if (index == r)
    {

        for (int j = 0; j < r; j++)
        {
            if (j > 0)
                printf(", ");
            printf("%d", data[j]);
        }
        printf("\n");
        (*combinations)++;
        return;
    }

    if (i >= n || r == 0)
        return;

    // if (*dupl != 0)
    data[index] = arr[i];

    // for (int g = 0; g <= index; g++)
    // {
    //     printf("%d ", data[g]);
    // }
    // printf("\n<---------->\n");
    // printf("<---------->\n");

    tower(arr, n, r, index + 1, data, i + 1, combinations, dupl);
    // printf("<---------->\n");
    // tower(arr, n, r, index, data, i + 1, combinations, dupl);
    tower(arr, n, r - 1, 0, data, 0, combinations, dupl);
}

int main(void)
{
    int combinations = 0;
    int cubes_count = 0;
    int *cubes = NULL;
    int dupl = 0;

    printf("Pocet kostek:\n");
    if (scanf("%d", &cubes_count) != 1 || cubes_count < 1)
    {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }

    cubes = (int *)malloc(cubes_count * sizeof(cubes));

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

    // for (int i = cubes_count; i > 0; i--)
    // {
    // if (cubes[i] == cubes[i - 1])
    // {
    //     cubes += 1;
    //     cubes_count--;
    // }
    int *data = NULL;
    data = (int *)malloc(cubes_count * sizeof(data));

    tower(cubes, cubes_count, cubes_count, 0, data, 0, &combinations, &dupl);
    printf("--------------\n");
    free(data);
    // }

    printf("Celkem: %d\n", combinations);
    free(cubes);
    return EXIT_SUCCESS;
}