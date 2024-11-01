#include <stdio.h>
#include <stdlib.h>
int *read_input(int *logs, int *max, int *max_drain)
{
    int from = 0, to = 0, drain = 0;

    logs = (int *)calloc(*max, sizeof(int));
    while (!feof(stdin))
    {
        if (scanf("%d:%d..%d", &drain, &from, &to) != 3)
            return 0;
        printf("%d:%d..%d\n", drain, from, to);
        if (to > *max)
        {
            int tmp = *max;
            *max = to;
            logs = (int *)realloc(logs, *max * sizeof(int));
            for (int i = tmp - 1; i < *max; i++)
                logs[i] = 0;
        }
        for (int i = from; i < to; i++)
        {
            logs[i] += drain;
            if (logs[i] > *max_drain)
                *max_drain = logs[i];
        }
    }
    return logs;
}

void print_max(int *logs, int max, int max_drain)
{
    int from = 0, to = 0;
    printf("Nejvyšší zátěž: %d\n", max_drain);
    for (int i = 0; i < max; i++)
    {
        if (logs[i] == max_drain)
        {
            from = i;
            to = i;
            i++;
        }
        else
            continue;

        while (i < max && logs[i] == max_drain)
        {
            to = i;
            i++;
        }
        printf("%d..%d\n", from, to + 1);
    }
}

int main(void)
{
    int max = 100, max_drain = 0;
    int *logs = NULL;
    logs = read_input(logs, &max, &max_drain);
    print_max(logs, max, max_drain);
    free(logs);
    return 0;
}