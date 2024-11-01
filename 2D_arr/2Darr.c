#include <stdio.h>
#include <stdlib.h>

int **fill(size_t n, size_t m)
{
    int **arr = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int *)malloc(m * sizeof(int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = rand();
        }
    }
    return arr;
}

void print(int **arr, size_t n, size_t m)
{

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("[%llu;%llu] -> %d\n", i, j, arr[i][j]);
        }
    }
}

int main()
{

    size_t size1, size2;

    printf("Velkost pola\n");
    scanf("%llu %llu", &size1, &size2);

    int **array = fill(size1, size2);

    print(array, size1, size2);

    for (int i = 0; i < size2; i++)
        free(array[i]);
    free(array);
    return 0;
}
