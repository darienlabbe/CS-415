/** ***************************************************************************
 * @remark program illustrating basic operations on lists of strings          *
 *                                                                            *
 * @author Henry M. Walker                                                    *
 * @file  insertion-sort-alt.c                                                *
 * @date  October 4, 2022; Revised December 24, 2022                          *
 *                                                                            *
 ******************************************************************************/

/* Definition of data structure and operations for working with linked lists
 */

/* libraries for standard I/O, strings, and memory allocation */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/** maximum size of an array within a list node */
#define strMax 50

/** declaration of node-related types */
typedef struct Node * listType;
typedef struct Node {
   char data [strMax];
   listType next;
} listNode;

/** ***************************************************************************
 * insert a new node at the front of a list                                   *
 * @param  str  a string to be placed in a new node at the front of the list  *
 * @param  front  the address of a pointer to the start of a list             *
 * @pre  list has been initialized                                            *
 * @post a new node is created with str as data                               *
 *       and the new node is inserted at the front of previoius list          *
 * @post    the nodes and order of the initial list are unchanged             *
 ******************************************************************************/
void insertFront (char * str, listType *front) {
  listType newFront = (listType) malloc (sizeof (listNode));
  strncpy (newFront->data, str, strMax-1); // allow space for null at end
  newFront->next = *front;
  *front = newFront;
}

/** ***************************************************************************
 * print elements in a list in forward order                                  *
 * @param  list  a pointer to the start of a list                             *
 * @pre  list has been initialized                                            *
 * @post data in each node is printed                                         *
 ******************************************************************************/
void listSimplePrint (listType list){
  listType listPtr = list;

  while (listPtr != NULL) {
    printf (" \"%s\" ", listPtr->data);
    listPtr = listPtr->next;
  }
  printf ("\n");
}

/** ***************************************************************************
 * print list elements in order using a formatted output style                *
 * @param  list  a pointer to the start of a list                             *
 * @pre  list has been initialized                                            *
 * @post data in each node is printed, Scheme-style, within ()                *
 ******************************************************************************/
void listPrint (listType list){
  listType listPtr = list;
  char * separator = "";

  printf ("(");
  while (listPtr != NULL) {
    printf ("%s\"%s\"", separator, listPtr->data);
    separator = ", ";
    listPtr = listPtr->next;
  }
  printf (")\n");
}

/** ***************************************************************************
 * search a list for a desired element                                        *
 * @param  str   a string to be searched for on the list                      *
 * @param  list  a pointer to the start of a list                             *
 * @pre  list is an initialized list                                          *
 * @returns "found" or "not found", depending on whether the given string     *
 *     is the data field for some node on the list                            *
 ******************************************************************************/
char * search (char * str, listType list) {
  listType listPtr = list;
  while (listPtr != NULL) {
    if (strcmp (listPtr->data, str) == 0) {
      return "found";
    }
    listPtr = listPtr->next;
  }
  return ("not  found");
}

/** ***************************************************************************
 * delete a list, setting all pointers to NULL and dallocating space          *
 * @param  list  the address of a pointer to the start of a list              *
 * @pre  list is an initialized list                                          *
 * @post list is changed to a NULL list                                       *
 *        with any previously-defined nodes deallocated                       *
 ******************************************************************************/
void listDelete (listType * list) {
  if (*list != NULL) {
    /* recursively remove the rest of the list nodes */
    listDelete (&((*list)->next));
    /* deallocate the space for the node itself */
    free (*list);
    /* set list pointer to null list */
    *list = NULL;
  }
}

/** ***************************************************************************
 * function using nested loops to print data on a linked list in revers order *
 * @param  list  a pointer to the start of a list                             *
 * @pre  list is an initialized list                                          *
 * @post data in each node are printed in reverse order                       *
 ******************************************************************************/
void printReverseBruteForce (listType list) {
  listType ptr, lastPrinted;
  lastPrinted = NULL;
  // print nodes in reverse until first item printed
  while (lastPrinted != list) {
    ptr = list;
    while (ptr->next != lastPrinted) {
      ptr = ptr->next;
    }
    printf (" \"%s\" ", ptr-> data);
    lastPrinted = ptr;
  }
  printf ("\n");
}

/** ***************************************************************************
 * a recursive function for printing data on a list in reverse order          *
 *   (although the data are printed, the function does not format its output  *
 * @param  list  a pointer to the start of a list                             *
 * @pre  list is an initialized list                                          *
 ******************************************************************************/
void printReverseRecursive (listType list) {
   if (list != NULL) {
    printReverseRecursive (list->next);
    printf ("\"%s\"  ", list-> data);
   }
}

/** ***************************************************************************
 * a recursive kernel function for printing data on a list in reverse order   *
 *   (the output is to be printed with the list enclosed in outer parentheses *
 *    and the list elements separated by commas)                              *
 *    The function uses a pointer to the start of the list that is saved      *
 *    throughout the recursion, in order to tell when the beginning has been  *
 *    reached again.                                                          *
 * @param  list  a pointer to the start of a list                             *
 * @param  first  a pointer to the start of a list                            *
 * @pre  list is an initialized list                                          *
 ******************************************************************************/
void printReverseRecursiveFormatedKernel (listType list, listType first) {
    if (list != NULL) {
        printReverseRecursiveFormatedKernel(list->next, first);
        if (list != first)
            printf("\"%s\", ", list->data);
        else
            printf("\"%s\"", list->data);
    }
}

/** ***************************************************************************
 * a recursive function for printing data on a list in reverse order          *
 *   (the output is to be printed with the list enclosed in outer parentheses *
 *    and the list elements separated by commas)                              *
 * @param  list  a pointer to the start of a list                             *
 * @pre  list is an initialized list                                          *
 ******************************************************************************/
void printReverseRecursiveFormatted (listType list) {
    printf("(");
    printReverseRecursiveFormatedKernel(list, list);
    printf(")");
}

/** ***************************************************************************
 * simple driver program to test list insertion and versions of printing.     *
 ******************************************************************************/

int main ( ) {
  clock_t start_time, end_time;
  double unformatted_elapsed, formated_elapsed;

  printf ("program illustrating list creating and printing procedures\n");

  /* declaration of variables */
  listType first = NULL;

  /* Construction of list with 5 nodes */
  insertFront ("Node E", &first);
  insertFront ("Node D", &first);
  insertFront ("Node C", &first);
  insertFront ("Node B", &first);
  insertFront ("Node A", &first);

  /* printing options */
  printf ("Original list -- Simple Print:     ");
  listSimplePrint (first);

  printf ("Original list -- Formatted Print:  ");
  listPrint (first);

  /* searching options */
  printf ("searching for Node A:  %s\n", search ("Node A", first));
  printf ("searching for Node C:  %s\n", search ("Node C", first));
  printf ("searching for Node E:  %s\n", search ("Node E", first));
  printf ("searching for Node G:  %s\n", search ("Node G", first));

  /*  print list in reverse order */
  printf ("List in Reverse Order -- Brute Force:  ");
  printReverseBruteForce (first);

  printf ("List in Reverse Order -- Recursively:   ");
  start_time = clock();
  printReverseRecursive (first);
  end_time = clock();
  unformatted_elapsed = ((end_time - start_time) / (double) (CLOCKS_PER_SEC / 1000) );
  printf ("---new line added\n");
  printf ("Formatted Reverse List -- Recursively:  ");
  start_time = clock();
  printReverseRecursiveFormatted (first);
  end_time = clock();
  formated_elapsed = ((end_time - start_time) / (double) (CLOCKS_PER_SEC / 1000) );

  /* timing */
  printf("\n\nTiming for Reverse Ordered List Recursive when unformatted and formatted:\n");
  printf ("Unformatted time:  %10.1lf\n", unformatted_elapsed);
  printf ("Formated time:     %10.1lf\n", formated_elapsed);


  /* clean up */
  printf ("\ncleaning up\n");
  listDelete (&first);
  printf ("pragram completed\n");

  return 0;
}