/** ***************************************************************************
 * @remark program illustrating a quicksort partition to find the kth element *
 *                                                                            *
 * @author Darien Labbe                                                       *
 * @file  quicksort-kth-element.c                                             *
 * @date  March 6, 2022                                                       *
 *                                                                            *
 * @remark Reference                                                          *
 * @remark Reading on Quicksort                                               *
  https://blue.cs.sonoma.edu/~hwalker/courses/415-sonoma.sp23/readings/reading-quicksort.php
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>   // for malloc, free
#include <time.h>     // for time

/* program to find the kth largest element of a given array using the quicksort
   partition */

/** *******************************************************************************
 * procedure implements the partition operation, following Loop Invariant 1a      *
 *    the Reading on Quicksort referenced above                                   *
 *    in brief: array segment has pivot, then small, unprocessed, large elements  *
 *              both unprocessed endpoints examined, swapping done in line        *
 * @param   a      the array containing the segment to be partitioned             *
 * @param   left   the index of the first array element in the partition          *
 * @param   right  the index of the last array element in the partition           *
 * @post    a[left] is moved to index mid, with left <= mid <= right              *
 * @post    elements between left and right are permuted, so that                 *
 *             a[left], ..., a[mid-1] <= a[mid]                                   *
 *             a[mid+1], ..., a[right] >= a[mid]                                  *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns  r_spot                                                               *
 *********************************************************************************/
int partition (int a[ ], int left, int right) {
    int pivot = a[left];
    int l_spot = left+1;
    int r_spot = right;
    int temp;

    while (l_spot <= r_spot) {
        while( (l_spot <= r_spot) && (a[r_spot] >= pivot)) {
            r_spot--;
        }
        while ((l_spot <= r_spot) && (a[l_spot] <= pivot)) {
            l_spot++;
        }

        // if misplaced small and large values found, swap them
        if (l_spot < r_spot) {
            temp = a[l_spot];
            a[l_spot] = a[r_spot];
            a[r_spot] = temp;
            l_spot++;
            r_spot--;
        }
    }

    // swap a[left] with the biggest small value
    temp = a[left];
    a[left] = a[r_spot];
    a[r_spot] = temp;

    return r_spot;
}

/** *******************************************************************************
 * recursive function finds the kth element in the array using the quicksort      *
 *    partitioning                                                                *
 * @param   a      the array containing the segment to be sorted for searching    *
 * @param   left   the index of the first array element in the partition          *
 * @param   right  the index of the last array element in the partition           *
 * @param   k  the kth element to be searched for (if 1 then largest, if size     *
 *              then smallest)                                                    *
 * @pre     array can be in any order, k must be between 1 and size               *
 * @post    elements are sorted in the direction of the kth element being         *
 *           searched for                                                         *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns  mid    the index for the kth element                                 *
 *********************************************************************************/
int select (int a [ ], int left, int right, int k) {
    // check k is not out of scope
    if (k >= 0 && k <= right - left + 1) {

        // use quicksort to get mid
        int mid = partition(a, left, right);

        // case: mid is k so return mid
        if (mid - left == k) {
            return mid;
        }
        // case: mid > k-1 so recurse to the right
        else if (mid - left > k) {
            return select(a, left, mid - 1, k);
        }
        // case: mid < k-1 so recurse to the left
        else {
            return select(a, mid + 1, right, k - mid + left - 1);
        }
    }
    printf("Invalid value of k\n");
    return -1;
}

/** *******************************************************************************
 * driver program for testing the select function                                 *
 *********************************************************************************/
int main() {
    int a[] = {3, 1, 6, 8, 4, 2, 5, 9, 0, 7};
    int size = 10;

    srand(time ((time_t *) 0)); // set rand() seed

    // set k to 1 for kth largest element or set to size for kth smallest
    int k = 1;

    // find kth element
    int kthElement = select(a, 0, size-1, size-k);

    // display index and then element for the hard coded array
    printf("\nFor a hard coded array 3, 1, 6, 8, 4, 2, 5, 9, 0, 7:");
    printf("\nThe index of the kth largest element after quicksort is: ");
    printf("%d\n", kthElement);
    printf("The element at the index of the kth largest element is: ");
    printf("%d\n", a[kthElement]);

    /* reset size and create a random integer array for test */
    size = 15;
    int * ran = (int *) malloc (size * sizeof(int));   //array with random data

    for (int i = 0; i < size; i++) {
        ran[i] = rand();
    }

    // print the array to see what the kth element should be
    printf("\nFor a random array: ");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", ran[i]);
    }
    printf("%d", ran[size - 1]);

    // find kth element
    kthElement = select(ran, 0, size-1, size-k);

    // display index and then element for the random array
    printf("\nThe index of the kth largest element after quicksort is: ");
    printf("%d\n", kthElement);
    printf("The element at the index of the kth largest element is: ");
    printf("%d\n", ran[kthElement]);

    free (ran);

    return 0;
}