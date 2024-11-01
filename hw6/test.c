#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

char **split_to_words(size_t n, char *tmp, char **arr, size_t *word_count)
{
  size_t i = 0;
  size_t j = 0;
  int char_count = 0;
  int tmp_char_count = 0;
  int words = 0;
  int new_word = 0;

  arr = (char **)malloc(1250 * sizeof(*arr));
  for (size_t i = 0; i < 1250; i++)
  {
    arr[i] = (char *)malloc(n * sizeof(**arr));
  }
  for (; i < *word_count; i++)
  {
    char_count = 0;
    for (; tmp[j]; j++)
    {
      if (isalpha(tmp[j]) != 0)
      {
        if (!words)
        {
          words = 1;
          (*word_count)++;
        }
        new_word = 1;
        // printf("%c\n", tmp[j]);
        arr[i][char_count] = tolower(tmp[j]);
        char_count++;
        tmp_char_count = char_count;
      }

      else
      {
        words = 0;
        if (new_word)
        {
          arr[i][char_count] = '\0';
          new_word = 0;
          j++;
          // printf("here\n");
          break;
        }
        // printf("there\n");
        i--;
        j++;
        break;
      }

      // printf("here is char %d\n", char_count);
      // printf("here is j %ld\n", j);
      // printf("here is wordcount %ld\n", *word_count);
    }
    // printf("here is again j %ld\n", j);
    if (tmp[j] == '\0')
    {
      // printf("here charcount is %d and tmp is %d\n", char_count, tmp_char_count);
      if (tmp_char_count != 0)
      {
        char_count = tmp_char_count;
      }
      (*word_count)--;
      // i++;
      break;
    }
  }

  // i--;

  if (*word_count <= 0)
  {
    return 0;
  }
  // printf("i in the end is %ld and j is %ld\n", i, j);
  // printf("wordcount is %ld\n", *word_count);
  // printf("charcount is %d\n", char_count);

  arr[i][char_count] = '\0';
  // printf("string:\n");
  // for (size_t i = 0; i < *word_count; i++)
  // {
  //   printf("|%s\n", arr[i]);
  // }
  return arr;
}

int comparator(char **arr1, char **arr2, int words, int words2)
{
  int same_words = 0;
  for (int i = 0; i < words; i++)
  {
    for (int j = 0; j < words2; j++)
    {
      if (strcmp(arr1[i], arr2[j]) == 0)
      {
        same_words++;
        break;
      }
    }
  }

  if (same_words == words)
  {
    return 1;
  }

  return 0;
}

int sameWords(const char *a, const char *b)
{
  size_t word_count = 1, word_count1 = 0, word_count2 = 0;
  int same = 0;
  // size_t max = 0;
  // size_t max1 = 0, max2 = 0;

  char *tmpa = strdup(a);
  char *tmpb = strdup(b);

  size_t help_im_in_hell = strlen(tmpa) + 1;
  size_t and_i_cant_get_out = strlen(tmpb) + 1;

  char **new_string = NULL;
  new_string = split_to_words(help_im_in_hell, tmpa, new_string, &word_count);
  word_count1 = word_count;
  word_count = 1;
  // max1 = max;
  // max = 0;
  // printf("workin\n");
  char **new_string2 = NULL;
  new_string2 = split_to_words(and_i_cant_get_out, tmpb, new_string2, &word_count);
  word_count2 = word_count;
  word_count = 1;
  // max2 = max;
  // max = 0;

  int same1 = comparator(new_string, new_string2, word_count1, word_count2);
  int same2 = comparator(new_string2, new_string, word_count2, word_count1);

  if (same1 == same2)
  {
    same = same1;
  }
  // printf("gasdfa %ld and %ld\n", word_count1, word_count2);
  if (word_count1 > 0)
  {
    // printf("here\n");
    for (size_t i = 0; i < 1250; i++)
    {
      free(new_string[i]);
    }
    free(new_string);
  }
  else
  {
    //   free(new_string[0]);
    free(new_string);
  }
  if (word_count2 > 0)
  {
    for (size_t i = 0; i < 1250; i++)
    {
      free(new_string2[i]);
    }
    free(new_string2);
  }
  else
  {
    //   free(new_string2[0]);
    free(new_string2);
  }
  // free(new_string);
  // free(new_string2);
  free(tmpa);
  free(tmpb);
  return same;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{

  return 0;
}
#endif /* __PROGTEST__ */
