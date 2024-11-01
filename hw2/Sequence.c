#include <stdio.h>
#include <math.h>
#include <string.h>

void result(char number, int arrow_placement);
void convert(long int number, unsigned int base, int arrow_placement);

int find_number(long int order, int base)
{

    if (base < 2 || base > 36 || order < 0)
    {
        return 1;
    }

    int arrow_placement = 0;
    long int number = order;
    int i = 0;

    if (order > base)
    {
        order--;
        while (order - ((base - 1) * (i + 1) * (pow(base, i))) >= 0)
        {
            i++;
            order -= (base - 1) * i * (pow(base, i - 1));
        }

        number = (order / (i + 1)) + pow(base, i);
        arrow_placement = order % (i + 1);
    }

    if (base == 10)
    {
        printf("%ld\n", number);
        for (int i = 0; i < arrow_placement; i++)
        {
            printf(" ");
        }
        printf("^\n");
    }

    else
        convert(number, base, arrow_placement);

    return 0;
}

// Idea taken from geeksforgeeks.org
char reValuate(int num)
{
    if (num < 10)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'a');
}

void reverse_string(char *string)
{
    int len = strlen(string);
    int i;
    for (i = 0; i < len / 2; i++)
    {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
}
void convert(long int number, unsigned int base, int arrow_placement)
{
    char result[1000];

    int index = 0;
    while (number > 0)
    {
        result[index++] = reValuate(number % base);
        number /= base;
    }
    result[index] = '\0';
    reverse_string(result);
    printf("%s\n", result);

    for (int i = 0; i < arrow_placement; i++)
    {
        printf(" ");
    }
    printf("^\n");
}

void result(char *number, int arrow_placement)
{
    printf("%s\n", number);
    for (int i = 0; i < arrow_placement; i++)
    {
        printf(" ");
    }
    printf("^\n");
}

int main(void)
{
    long int input_number = -1;
    int base = 0;
    printf("Pozice a soustava:\n");
    while (scanf("%ld %d\n", &input_number, &base) == 2)
    {
        if (find_number(input_number, base) != 0)
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    if (!feof(stdin) || input_number == -1 || base == 0)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    return 0;
}