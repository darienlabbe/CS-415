/** ***************************************************************************
 * @remark program illustrating an insertion sort with terminal input         *
 *                                                                            *
 * @author Henry M. Walker                                                    *
 * @file  insertion-sort-alt.c                                                *
 * @date  August 1, 2022, Revised December 24, 2022                           *
 *                                                                            *
 * @remark Reference                                                          *
 * @remark Reading on Insertion Sort                                          *
  https://blue.cs.sonoma.edu/~hwalker/courses/415-sonoma.sp23/readings/reading-insertion-sort.php
 *                                                                            *
 *****************************************************************************/
#include <stdio.h>

#define arraylen 10

/** ***************************************************************************
 * print the elements of an array on the same line                            *
 * @param  array   the array to be printed                                    *
 * @param  length  the length of the array                                    *
 *****************************************************************************/
void printArray (int * array, int length)
{
  int i;

  printf ("[ ");
  for (i = 0; i < length; i++)
    printf ("%d ", array[i]);
  printf ("]\n");
} //printArray

/** ***************************************************************************
 * main procedure controls input, sorting, and printing                       *
 *****************************************************************************/
int main()
{
  int i, j, temp;
  int array[arraylen];

  printf ("Enter ten integers (not separated by punctuation), which will be placed in an array to sort.\n");
  for (i = 0; i < arraylen; i++)
    {
      scanf("%d", &temp);
      array[i] = temp;
    }

  printArray (array, arraylen);

  for (i = 1; i < arraylen; ++i)
    {
      temp = array[i];
      j = i - 1;
      while ((j >= 0) && (temp < array[j]))
        {
          array[j + 1] = array[j];
          --j;
        }
      array[j + 1] = temp;
    }

  int size = *(&array + 1) - array;
  if (size != arraylen) printf("Error: Length changed!");

  printArray (array, arraylen);

  return 0;
}
