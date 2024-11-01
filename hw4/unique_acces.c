#include <stdio.h>

#define MAX_ENTRIES 1000000
#define MAX_UNIQUE_USERS 100000

//Takes id from input
//Checks whether the id was already used or not
//Increases the number of recorded entries
//id - the number from input
//users - array of ids as they were entered
//number_of_visits - tracks how many times was id entered
//order - stores value of how many ids was already entered
void add_id(int id, int users[], int number_of_visits[], int order)
{
    users[order] = id;
    number_of_visits[id] += 1;
    if (number_of_visits[id] == 1)
        printf("> prvni navsteva\n");
    else
        printf("> navsteva #%d\n", number_of_visits[id]);
}

//prints out how many unique ids were entered in a given interval
//Checks if id was already counted
//users - array of ids as they were entered
//from - start of an interval
//to - end of an interval
void unique_users(int users[], int from, int to)
{
    int unique_users = 0;
    int counted[MAX_UNIQUE_USERS] = {0};
    for (int i = from; i <= to; i++)
    {

        if (counted[users[i]] == 0)
        {
            counted[users[i]] = 1;
            unique_users++;
        }
    }
    printf("> %d / %d\n", unique_users, to - from + 1);
}

int main(void)
{
    char request_type = 'a';
    int id = -1, from = -1, to = -1;
    int order = 0;
    int users[MAX_ENTRIES], number_of_visits[MAX_UNIQUE_USERS] = {0};

    printf("Pozadavky:\n");
    //Reads inputs form user.
    //Based on the given character it decides what to do.
    //Allowed characters are + and ?
    //If other character is given, program ends.
    while (scanf(" %c \n", &request_type) == 1)
    {
        switch (request_type)
        {
        case '+':
            if (scanf(" %d \n", &id) != 1 || id < 0 || id > MAX_UNIQUE_USERS - 1 || order > MAX_ENTRIES)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }

            add_id(id, users, number_of_visits, order);

            order++;
            break;

        case '?':
            if (scanf(" %d %d \n", &from, &to) != 2 || from < 0 || to >= order || from > to)
            {
                printf("Nespravny vstup.\n");
                return 1;
            }

            unique_users(users, from, to);
            break;

        default:
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    //When there was no input, program ends
    if (request_type == 'a' || !feof(stdin))
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    return 0;
}