/** ***************************************************************************
 * @remark  program illustrates versions of a binary search,                  *
 *    using different loop invariants                                         *
 *                                                                            *
 * @author Darien M. Labbe                                                    *
 * @file  dutch-national-flag-problem.c                                       *
 * @date  February 25, 2022                                                   *
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
 * @remark People participating with Problem/Program Discussions:             *
 *         None                                                               *
 *                                                                            *
 *****************************************************************************/

/* Two versions of the Dutch national flag problem */

#define size 6 /* size of the array to be searched */

/* input relevant libraries */
#include <stdio.h>

/** **************************************************************************
 * function performs a dutch national flag sort, sorting the separate colors *
 * of an array into red white and blue respectively                          *
 * @remark  low is the index that partitions the red section                 *
 * @remark  mid is the index that partitions the white section               *
 * @remark  high is the index that partitions the blue section               *
 * @param   a     the array to be sorted                                     *
 * @returns nothing                                                          *
 * @remark  size  a defined constant, giving the array size                  *
 * @remark  invariant B: red, red, white, white, unprocessed, blue, blue     *
 ****************************************************************************/
 void invariantB (int a []) {
    /* Initialize the partition indices and temp for swap */
    int low = 0, mid = 0, high = size - 1, temp = 0;

    /* Run the sort algorithm */
    while (mid <= high) {
        /* For creating and growing the red section */
        if (a[mid] == 0) {
            temp = a[mid];
            a[mid] = a[low];
            a[low] = temp;
            low++;
            mid++;
        }
        /* For creating and growing the white section */
        else if (a[mid] == 1)
            mid++;
        /* For creating and growing the blue section */
        else {
            temp = a[mid];
            a[mid] = a[high];
            a[high] = temp;
            high--;
        }
    }
 }


/** **************************************************************************
* function performs a dutch national flag sort, sorting the separate colors *
* of an array into red white and blue respectively                          *
* @remark  low is the index that partitions the red section                 *
* @remark  mid is the index that partitions the white section               *
* @remark  high is the index that partitions the blue section               *
* @param   a     the array to be sorted                                     *
* @returns nothing                                                          *
* @remark  size  a defined constant, giving the array size                  *
* @remark  invariant C: red, red, unprocessed, white, white, blue, blue     *
****************************************************************************/
void invariantC (int a []) {
    /* Initialize the partition indices and temp for swap */
    int low = 0, mid = size - 1, high = size - 1, temp = 0;

    /* Run the sort algorithm */
    while (mid >= low) {
        /* For creating and growing the red section */
        if (a[mid] == 0) {
            temp = a[mid];
            a[mid] = a[low];
            a[low] = temp;
            low++;
        }
            /* For creating and growing the white section */
        else if (a[mid] == 1)
            mid--;
            /* For creating and growing the blue section */
        else {
            temp = a[mid];
            a[mid] = a[high];
            a[high] = temp;
            high--;
            mid--;
        }
    }
}


/** **************************************************************************
* driver program coordinates test cases for the dutch national flag          *
* algorithms                                                                 *
*****************************************************************************/
int main() {
    int a[size] = {1,0,1,2,0,2};

    /* Print the array before the sort */
    printf("Array before sort: ");
    for (int i = 0; i < size - 1; i++)
        printf("%d, ", a[i]);
    printf("%d\n\n", a[size - 1]);

    /* Sort the array */
    invariantC(a);

    /* Print the sorted array */
    printf("Array after sort: ");
    for (int i = 0; i < size - 1; i++)
        printf("%d, ", a[i]);
    printf("%d\n", a[size - 1]);

    return 0;
}