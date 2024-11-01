#include <stdio.h>
#include <math.h>
#include <float.h>

const char *print_obvod = "", *print_obsah = "";

int compare(double x, double y, double z, double w)
{
    if (fabs(x - y) <= 100 * DBL_EPSILON * fabs(x + y))
    {
        print_obvod = "=";
    }
    else if (x > y)
    {
        print_obvod = ">";
    }
    else
    {
        print_obvod = "<";
    }

    if (fabs(z - w) <= 100 * DBL_EPSILON * fabs(z + w))
    {
        print_obsah = "=";
    }
    else if (z > w)
    {
        print_obsah = ">";
    }
    else
    {
        print_obsah = "<";
    }
    return 0;
}

int main(void)
{
    int i;
    double obvod1 = 0, obvod2 = 0, obsah1 = 0, obsah2 = 0;
    const char *first = "", *second = "";

    for (i = 1; i < 3; i++)
    {
        char shape;
        double a = 0, b = 0, c = 0;
        double obsah = 0, obv = 0, s = 0;

        printf("Obrazec #%d\n", i);
        if (scanf(" %c ", &shape) != 1)
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        switch (shape)
        {
        case 'T':
            if (scanf(" %lf %lf %lf ", &a, &b, &c) != 3 || a <= 0 || b <= 0 || c <= 0 || a + b == c || a + c == b || b + c == a || fabs(a + b - c) < 100 * DBL_EPSILON * fabs(a + b + c) || fabs(a - b + c) < 100 * DBL_EPSILON * fabs(a + b + c) || fabs(a + b - c) < 100 * DBL_EPSILON * fabs(-a + b + c))
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            obv = a + b + c;
            s = (a + b + c) / 2;
            obsah = sqrt(s * (s - a) * (s - b) * (s - c));
            if (i == 1)
            {
                obvod1 = obv;
                obsah1 = obsah;
                first = "trojuhelnik #1";
            }
            else
            {
                obvod2 = obv;
                obsah2 = obsah;
                second = "trojuhelnik #2";
            }
            break;
        case 'R':
            if (scanf("%lf %lf", &a, &b) != 2 || a <= 0 || b <= 0 || a == b)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            obv = 2 * a + 2 * b;
            obsah = a * b;

            if (i == 1)
            {
                obvod1 = obv;
                obsah1 = obsah;
                first = "obdelnik #1";
            }
            else
            {
                obvod2 = obv;
                obsah2 = obsah;
                second = "obdelnik #2";
            }
            break;
        case 'S':
            if (scanf(" %lf ", &a) != 1 || a <= 0)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }
            obv = 4 * a;
            obsah = a * a;
            if (i == 1)
            {
                obvod1 = obv;
                obsah1 = obsah;
                first = "ctverec #1";
            }
            else
            {
                obvod2 = obv;
                obsah2 = obsah;
                second = "ctverec #2";
            }
            break;
        default:
            printf("Nespravny vstup.\n");
            return 1;
            break;
        }
    }

    compare(obvod1, obvod2, obsah1, obsah2);
    printf("Obvod: %s %s %s\nObsah: %s %s %s\n", first, print_obvod, second, first, print_obsah, second);
    return 0;
}
