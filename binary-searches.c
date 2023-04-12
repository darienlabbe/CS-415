/** ***************************************************************************
 * @remark  program illustrates versions of a binary search,                  *
 *    using different loop invariants                                         *
 *                                                                            *
 * @author Henry M. Walker                                                    *
 * @remark Edited By: Darien Labbe                                            *
 * @file  binary-searches.c                                                   *
 * @date  August 9, 2022                                                      *
 *                                                                            *
 * @remark References                                                         *
 * @remark NSF Grant CDA 9214874, "Integrating Object-Oriented Programming    *
 *         and Formal Methods into the Computer Science Curriculum",          *
 *         with Henry M. Walker as Senior Investigator                        *
 * @remark Henry M. Walker, Computer Science 2: Principles of Software        *
 *         Engineering, Data Types, and Algorithms, Little, Brown, and        *
 *         Company, 1989, Section 10.1, p. 389                                *
 * @remark Reading on Introduction to Loop Invariants,                        *
 *         https://blue.cs.sonoma.edu/~hwalker/courses/415-sonoma.fa22        *
 *         /readings/reading-intro-loop-invariants.php                        *
 *                                                                            *
 * @remark People participating with Problem/Progra Discussions:              *
 *         None                                                               *
 *                                                                            *
 *****************************************************************************/

/* Two versions of binary search */

#define size 50 /* size of the array to be searched */

/* input relevant libraries */
#include <stdio.h>

/** **************************************************************************
 * function performs a binary search, based on the loop invariant where      *
 * @remark  left is index after small items                                  *
 * @remark  right is just before large items                                 *
 * @param   a     the array to be searched                                   *
 * @param   item  the value to be searched for                               *
 * @returns the index if item or                                             *
 *          the location where item should be inserted to maintain ordering  *
 * @remark  size  a defined constant, giving the array size                  *
 *                                                                           *
 ****************************************************************************/
int search1 (int a [], int item) {
    /* program searches the sorted array a for item
       and returns the index if item or the
       location where item should be inserted to maintain ordering
    */

    /* Binary Search, Version 1 */
    int left = 0;
    int right = size - 1;
    int middle = (left + right + 1) / 2;  /* we must round up */
    while ((left <= right) && (a[middle] != item)) {
        if (a[middle] < item)
            left = middle + 1;
        else
            right = middle - 1;
        middle = (left + right + 1) / 2;
    }

    return middle;
}


/** **************************************************************************
 * function performs a binary search, based on the loop invariant where      *
 * @remark  left is index after small items                                  *
 * @remark  right is index of the just before large items                    *
 * @param   a     the array to be searched                                   *
 * @param   item  the value to be searched for                               *
 * @remark  size  a defined constant, giving the array size                  *
 * @returns the index if item or                                             *
 *          the location where item should be inserted to maintain ordering  *
 *                                                                           *
 ****************************************************************************/
int search2 (int a [], int item) {
    /* program searches the sorted array a for item
       and returns the index if item or the
       location where item should be inserted to maintain ordering
    */

    /* Binary Search, Version 2 */
    int left = 0;
    int right = size;
    int middle = (left + right) / 2;  /* rounding does not matter here,
                                        so we round down for simplicity */
    while ((left < right) && (a[middle] != item)) {
        if (a[middle] < item)
            left = middle + 1;
        else
            right = middle;
        middle = (left + right) / 2;
    }
    return middle;
}


/** **************************************************************************
 * function performs a binary search, based on the loop invariant where      *
 * @remark  left is index just before small items                            *
 * @remark  right is index just before large items                           *
 * @param   a     the array to be searched                                   *
 * @param   item  the value to be searched for                               *
 * @remark  size  a defined constant, giving the array size                  *
 * @returns the index if item or                                             *
 *          the location where item should be inserted to maintain ordering  *
 *                                                                           *
 ****************************************************************************/
int search3 (int a [], int item) {
    /* program searches the sorted array a for item
       and returns the index if item or the
       location where item should be inserted to maintain ordering
    */

    /* Binary Search, Version 3 */
    int left = 0;
    int right = size;
    int middle = (left + right + 1) / 2;  /* rounding does not matter here,
                                        so we round down for simplicity */
    while ((left < right) && (a[middle] != item)) {
        if (a[middle] < item)
            left = middle;
        else
            right = middle - 1;
        middle = (left + right + 1) / 2;
    }

    /* If item is found then return the index,
       otherwise round up to the index after.
    */
    if (a[middle] == item)
        return middle;
    else
        return middle + 1;
}


/** **************************************************************************
 * function organizes testing of the binary search procedures                *
 * @param   a     the array to be searched                                   *
 * @param   item  the value to be searched for                               *
 * @post    the result of each binary search is printed                      *
 *                                                                           *
 ****************************************************************************/
void testBothSearches (int a [], int item) {
    /* use both search algorithms and print results */
    printf ("%5d  %5d", item, search1 (a, item));
    printf ("%8d\n", search2 (a, item));
}

/** **************************************************************************
 * driver program coordinates test cases for the binary search algorithms    *
 ****************************************************************************/
int main () {
    int a [size];
    int index;

    /* initialize a as a sorted array */
    for (index = 0; index < size; index++)
        a[index] = 2*index;

    printf ("item  search1   search2\n\n");

    /* test boundary conditions */
    printf ("testing boundary conditions\n");
    testBothSearches (a, -3);
    testBothSearches (a, 0);
    testBothSearches (a, 2*size-2);
    testBothSearches (a, 2*size+10);

    /* testing found and not found within the array */
    printf ("\ntesting within the array\n");
    testBothSearches (a, 5);
    testBothSearches (a, 6);
    testBothSearches (a, 7);
    testBothSearches (a, 8);

    printf("\n\n\nOkay so all of that happened anyways...\n\n");
    printf("It is time to test the third search but lets be more visual\n\n");

    /* Print array first */
    printf("Array: ");
    for (index = 0; index < size; index++)
        printf("%d, ", a[index]);
    printf("\n\n");

    int item = 1;

    /* Print item to be searched */
    printf("Item: %d\n", item);

    /* Now run and print the result */
    printf("Search3: ");
    printf("%d \n", search3(a, item));
}