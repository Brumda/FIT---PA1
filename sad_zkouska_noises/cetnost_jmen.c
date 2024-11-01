#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cetnost_jmen
{
  int cnt;
  char * name;
} NAME;

char * cutName ( char * names )
{
  int len = strlen(names);
  int wasAplha = 0;
  for (int i = len; i > 0; i--)
  {
    if ( isalpha(names[i]) )
    {
      wasAplha = 1;
    }
    if ( isspace(names[i]) != 0 && wasAplha == 1 )
    {
      names[i] = '\0';
      break;
    }
    //names[i] = ' ';
  }
  return names;
}

int compare_ints(const void* a, const void* b)
{
  NAME* arg1 = (NAME*)a;
  NAME* arg2 = (NAME*)b;

  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

void freeName( NAME * arr, int n )
{
  for (int i = 0; i < n; i++)
  {
    free(arr[i].name);
  }
  free(arr);
}

void printName ( NAME * arr, int n )
{
  qsort( arr, n, sizeof(NAME), compare_ints );
  printf("Nejcastejsi jmeno: %dx\n", arr[0].cnt);
  for (int i = 0; i < n; i++)
  {
    printf("%s\n",arr[i].name);
    if ( arr[i+1].cnt != arr[i].cnt )
    {
      break;
    }
  }
  freeName(arr,n);
}

int findDup ( NAME * arr, int n, char * names )
{
  for (int i = 0; i < n; i++)
  {
    if ( strcasecmp(arr[i].name,names) == 0 )
    {
      return i;
    }
  }
  return -1;
}

int main (void)
{
  printf("Jmena:\n");
  int size_arr = 2, input = 0, n = 0, dup = 0, len = 0;
  NAME * arr = (NAME*) malloc( size_arr * sizeof(NAME) );  
  char * names = NULL;
  size_t buffer;

  while ( 1 )
  {
    input = getline(&names,&buffer,stdin);

    if ( input == EOF && n > 0 )
    {
      printName(arr,n);
      return 0;
    }
    if ( input == EOF && n == 0 )
    {
      freeName(arr,0);
      printf("Chyba.\n");
      return 0;
    }

    names = cutName(names);
    dup = findDup(arr,n,names);

    if ( dup != (-1) )
    {
      arr[dup].cnt += 1;
    }
    else
    {
      len = strlen(names)+1;
      arr[n].name = (char*)malloc( len * sizeof(char) );
      strncpy( arr[n].name, names, strlen(names)+1 );
      arr[n].cnt = 1;
      n++;
      if ( n == size_arr )
      {
        size_arr *= 2;
        arr = (NAME*)realloc(arr,size_arr*sizeof(NAME));
      }
    }
  }

  return 1;
}