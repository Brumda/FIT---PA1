#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

int leap_year_day_checker(int y, int m, int d)
{
       if (m == 4 || m == 6 || m == 9 || m == 11)
       {
              if (d > 30)
                     return 0;
       }

       if (m == 2)
       {
              if (y % 4 == 0)
              {
                     if (y % 4000 == 0 || y % 100 == 0)
                     {
                            if (d > 29 && y % 400 == 0)
                                   return 0;
                            if (d > 28 && y % 400 != 0)
                                   return 0;
                     }
                     if (d > 29)
                            return 0;
              }
              else
              {
                     if (d > 28)
                            return 0;
              }
       }
       return 1;
}

int date_checker(int y1, int m1, int d1, int h1, int i1,
                 int y2, int m2, int d2, int h2, int i2)
{
       if (y1 > y2 || y1 < 1600 || y2 < 1600 || m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 || d1 < 1 || d1 > 31 || d2 < 1 || d2 > 31 || h1 < 0 || h1 > 23 || h2 < 0 || h2 > 23 || i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59)
              return 0;

       if (y1 == y2)
       {
              if (m1 > m2)
                     return 0;
              else if (m1 == m2)
              {
                     if (d1 > d2)
                            return 0;

                     else if (d1 == d2)
                     {
                            if (h1 > h2)
                                   return 0;

                            else if (h1 == h2)
                            {
                                   if (i1 > i2)
                                          return 0;
                            }
                     }
              }
       }

       return 1;
}

int date_to_days(int y, int m, int d)
{
       int days_per_moth[12] = {31, 28, 31, 30, 31, 30,
                                31, 31, 30, 31, 30, 31};
       long long int days = 0;
       long long int leap_years_count = y, tmp = 0;

       if (m < 2 || (m == 2 && d < 29))
       {
              leap_years_count--;
       }
       tmp = leap_years_count / 4;
       tmp -= leap_years_count / 100;
       tmp -= leap_years_count / 4000;
       tmp += leap_years_count / 400;
       leap_years_count = tmp;
       days = y * 365 + leap_years_count + d;

       for (int i = 0; i < m - 1; i++)
       {
              days += days_per_moth[i];
       }

       return days;
}
int display_changes(int time1, int time2, int time_interval)
{
       int energy = 0, units1 = time1 % 10, units2 = time2 % 10, dozens1 = time1 / 10, dozens2 = time2 / 10;
       while (units1 != units2 || dozens1 != dozens2)
       {
              switch (units1)
              {
              case 0:
                     energy += 4;
                     units1++;
                     break;
              case 1:
                     energy += 5;
                     units1++;
                     break;
              case 2:
                     energy += 2;
                     units1++;
                     break;
              case 3:
                     if (time_interval == 24 && dozens1 == 2)
                     {
                            energy += 3;
                            energy += 3;
                            dozens1 = 0;
                            units1 = 0;
                            break;
                     }
                     energy += 3;
                     units1++;

                     break;
              case 4:
                     energy += 3;
                     units1++;
                     break;
              case 5:
                     energy += 1;
                     units1++;
                     break;
              case 6:
                     energy += 5;
                     units1++;
                     break;
              case 7:
                     energy += 4;
                     units1++;
                     break;
              case 8:
                     energy += 1;
                     units1++;
                     break;
              case 9:
                     energy += 2;
                     units1 = 0;
                     dozens1++;
                     switch (dozens1)
                     {
                     case 1:
                            energy += 4;
                            break;
                     case 2:
                            energy += 5;
                            break;
                     case 3:

                            energy += 2;
                            break;
                     case 4:
                            energy += 3;
                            break;
                     case 5:
                            energy += 3;
                            break;
                     case 6:
                            energy += 3;
                            dozens1 = 0;
                            break;
                     default:
                            break;
                     }

                     break;

              default:
                     break;
              }
       }
       return energy;
}

int time_to_energy(int h1, int i1, int h2, int i2)
{
       int h, i, j_per_hour = 12200, j_per_minute = 200;
       long long int energy = 0;
       h = h2 - h1;

       if (h < 0)
       {
              h += 24;
       }
       i = i2 - i1;

       if (i < 0)
       {
              i += 60;
       }
       energy += h * j_per_hour + i * j_per_minute + display_changes(h1, h2, 24) + display_changes(i1, i2, 60);

       if (i1 > i2)
       {
              energy -= j_per_hour;
       }
       return energy;
}

int energyConsumption(int y1, int m1, int d1, int h1, int i1,
                      int y2, int m2, int d2, int h2, int i2, long long int *consumption)
{
       long long int date1, date2;
       int j_per_day = 292886;

       if (date_checker(y1, m1, d1, h1, i1,
                        y2, m2, d2, h2, i2) == 0)
       {
              return 0;
       }

       if (leap_year_day_checker(y1, m1, d1) == 0)
       {
              return 0;
       }
       if (leap_year_day_checker(y2, m2, d2) == 0)
       {
              return 0;
       }

       date1 = date_to_days(y1, m1, d1);
       date2 = date_to_days(y2, m2, d2);
       *consumption = (date2 - date1) * j_per_day + time_to_energy(h1, i1, h2, i2);

       if (h1 > h2)
       {
              *consumption -= j_per_day;
       }

       return 1;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
       long long int consumption;
       assert(energyConsumption(2400, 2, 29, 12, 0,
                                2400, 2, 29, 12, 1, &consumption) == 1 &&
              consumption == 204LL);

       return 0;
}
#endif /* __PROGTEST__ */
