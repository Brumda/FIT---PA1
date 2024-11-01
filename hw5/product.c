#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_OF_PRODUCT_MAX 100

typedef struct product
{
    char m_Name[NAME_OF_PRODUCT_MAX];
    int m_Count;

} PRODUCT;

PRODUCT *add_products(PRODUCT *data, int *number_of_products, int *unique_products, int *max)
{
    char name[NAME_OF_PRODUCT_MAX + 1];

    if ((scanf("%100s", name)) == 1)
    {
        if (strlen(name) >= NAME_OF_PRODUCT_MAX)
        {
            free(data);
            return NULL;
        }

        (*number_of_products)++;

        if (*unique_products >= *max)
        {
            *max += (*max < 100) ? 10 : *max / 2;
            data = (PRODUCT *)realloc(data, *max * sizeof(*data));
        }

        for (int i = 0; i < *unique_products; i++)
        {
            if (*number_of_products == 1)
            {
                strcpy(data[0].m_Name, name);
                data[0].m_Count = 1;
                return data;
            }

            if (strcmp(data[i].m_Name, name) == 0)
            {
                data[i].m_Count++;
                return data;
            }
        }
        strcpy(data[*unique_products].m_Name, name);
        data[*unique_products].m_Count = 1;
        (*unique_products)++;
    }
    else
    {
        free(data);
        return NULL;
    }
    return data;
}

int studentCmp(const PRODUCT *a, const PRODUCT *b)
{
    return (b->m_Count > a->m_Count) - (a->m_Count > b->m_Count);
}

void best_sells(PRODUCT *data, int unique_products)
{
    qsort(data, unique_products, sizeof(*data), (int (*)(const void *, const void *))studentCmp);
}

void print_rankings(PRODUCT *data, int watched, int unique_products, int *sold)
{
    int j = 0;
    int rank_lenght = 0;
    int look_forward = 0;

    if (unique_products < watched)
    {
        rank_lenght = unique_products;
    }
    else
    {
        rank_lenght = watched;
    }

    for (int i = 0; i < rank_lenght; i++)
    {
        look_forward = 0;
        if (i + 1 < unique_products && data[i].m_Count == data[i + 1].m_Count)
        {

            for (int j = i + 1; j < unique_products; j++)
            {
                if (data[i].m_Count == data[j].m_Count)
                {
                    look_forward++;
                }
            }
            for (j = 0; j < look_forward + 1; j++)
            {
                printf("%d.-%d. %s, %dx\n", i + 1, look_forward + 1 + i, data[i + j].m_Name, data[i + j].m_Count);
            }

            i += look_forward;
        }
        else

        {
            printf("%d. %s, %dx\n", i + 1, data[i].m_Name, data[i].m_Count);
        }
    }
}
void print_result(PRODUCT *data, int *sold, int watched, int unique_products, int max)
{
    int look_ahead = 0, count_how_much = 0;
    *sold = 0;

    if (unique_products < watched)
    {
        count_how_much = unique_products;
    }
    else
    {
        count_how_much = watched;
    }
    for (int i = 0; i < count_how_much; i++)
    {
        *sold += data[i].m_Count;
    }
    while (count_how_much + look_ahead < max && data[count_how_much - 1].m_Count == data[count_how_much + look_ahead].m_Count)
    {
        *sold += data[count_how_much + look_ahead].m_Count;
        look_ahead++;
    }
    printf("Nejprodavanejsi zbozi: prodano %d kusu\n", *sold);
}

int main(void)
{
    char request_type = 'a';
    int watched = 0, number_of_products = 0, sold = 0;
    int max = 0, unique_products = 1;
    PRODUCT *data = NULL;

    printf("Pocet sledovanych:\n");

    if (scanf("%d", &watched) == 1 && watched > 0)
    {
        printf("Pozadavky:\n");

        while (scanf(" %c \n", &request_type) == 1)
        {

            switch (request_type)
            {
            case '+':

                data = add_products(data, &number_of_products, &unique_products, &max);
                if (!data)
                {

                    printf("Nespravny vstup.\n");
                    free(data);
                    return EXIT_FAILURE;
                }
                break;

            case '?':
                if (number_of_products < 1)
                {
                    printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sold);
                    break;
                }

                best_sells(data, unique_products);
                print_result(data, &sold, watched, unique_products, max);
                break;

            case '#':
                if (number_of_products < 1)
                {
                    printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sold);
                    break;
                }

                best_sells(data, unique_products);
                print_rankings(data, watched, unique_products, &sold);
                print_result(data, &sold, watched, unique_products, max);
                break;

            default:
                printf("Nespravny vstup.\n");
                free(data);
                return EXIT_FAILURE;
            }
        }
    }
    if (request_type == 'a' || !feof(stdin))
    {
        printf("Nespravny vstup.\n");
        return EXIT_FAILURE;
    }
    free(data);
    return EXIT_SUCCESS;
}