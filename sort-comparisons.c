/** *******************************************************************************
 * @remark program times several sorting algorithms on data sets of various sizes *
 *                                                                                *
 * @remark this version includes code for straight selection insertion sorts      *
 * stubbs are provided for other sorting algoritms, including                     *
 *     quicksort and improved quicksort,                                          *
 *     merge sort and heap sort                                                   *
 *                                                                                *
 * @author Henry M. Walker                                                        *
 * @remark Assignment  Comparison of Sorting Algorithms                           *
 * @file  sort-comparisons.c                                                      *
 * @date  July 29, 2022                                                           *
 *                                                                                *
 * @remark References                                                             *
 * @remark Dynamic Programming:  Anany Levitin, "The Design and                   *
 *         and Analysis of Algorithms", Second Edition,                           *
 *         Sections 3.1 (Selectino Sort), 4.1 (Insertion Sort),                   *
 *                  5.1 (Mergesort), 5.2 (Quicksort),  6.4 (Heapsort)             *
 *                                                                                *
 * @remark People participating with Problem/Progra Discussions:                  *
 *         Marcia Watts                                                           *
 *                                                                                *
 *********************************************************************************/

#include <stdio.h>
#include <stdbool.h>  // for bool
#include <stdlib.h>   // for malloc, free, srand, rand
#include <time.h>     // for time

/** *******************************************************************************
 * structure to identify both the name of a sorting algorithm and                 *
 * a pointer to the function that performs the sort                               *
 * the main function utilizes this struct to define an array of                   *
 * the sorting algorithms to be timed by this program.                            *
 *********************************************************************************/
typedef struct sorts {
    char * name;                     /**< the name of a sorting algorithm as text  */
    void (*sortProc) (int [ ], int); /**< the procedure name of a sorting function */
} sorts;

/* * * * * * * * * * sorting procedures, with helper, as needed  * * * * * * * * */

/** *******************************************************************************
 * straight selection sort                                                        *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * @post  the first n elements of a are sorted in non-descending order            *
  ********************************************************************************/

void selectionSort (int a [ ], int n) {
    int i, j, smallIndex;
    int temp;
    // put largest remaining element in a[i]
    for (i = n-1; i >= 0; i--) {
        // find largest in a[i..n-1]
        smallIndex = i;
        for (j = i-1; j >= 0; j--) {
            if (a[smallIndex] < a[j])
                smallIndex = j;
        }
        // swap smallest to a[i]
        temp = a[smallIndex];
        a[smallIndex] = a[i];
        a[i] = temp;
    }
}

/** *******************************************************************************
 * insertion sort                                                                 *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * @post  the first n elements of a are sorted in non-descending order            *
  ********************************************************************************/
void insertionSort (int a [], int n) {
// method to sort using the insertion sort
// parameters:  a, the array to be sorted
//              length, the size of the a array
    for (int k = 1; k < n; k++) {
        int item = a[k];
        int i = k-1;
        while ((i >= 0) && a[i] > item){
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = item;
    }
}

/* * * * * * * * * * * quicksort and helper functions * * * * * * * * * * */
/** *******************************************************************************
 * Quicksort helper function                                                      *
 * uses a[left] as pivot value in processing                                      *
 * @param  a  the array to be processed                                           *
 * @param  size  the size of the array                                            *
 * @param  left:  the lower index for items to be processed                       *
 * @param  right  the upper index for items to be processed                       *
 * @post   elements of a are rearranged, so that                                  *
 *             items between left and index mid are <= a[mid]                     *
 *             items between dex mid and right are >= a[mid]                      *
 * @returns  mid                                                                  *
 *********************************************************************************/
int partition (int a[ ], int size, int left, int right) {
    int pivotIndex = left + (rand() % (right-left+1));
    int pivot = a[pivotIndex];
    int l_spot = left+1;
    int r_spot = right;
    int temp;

    //swap a[left] with random pivot
    temp = a[left];
    a[left] = a[pivotIndex];
    a[pivotIndex] = temp;

    while (l_spot <= r_spot) {
        while( (l_spot <= r_spot) && (a[r_spot] >= pivot))
            r_spot--;
        while ((l_spot <= r_spot) && (a[l_spot] <= pivot))
            l_spot++;

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
 * Quicksort helper function                                                      *
 * @param  a  the array to be processed                                           *
 * @param  size  the size of the array                                            *
 * @param  left  the lower index for items to be processed                        *
 * @param  right the upper index for items to be processed                        *
 * @post  sorts elements of a between left and right                              *
 *********************************************************************************/
void quicksorthelper (int a [ ], int size, int left, int right) {
    if (left > right)
        return;

    // hybrid threshold integer to determine when to switch to insertion sort
    int hybridThreshold = 9;

    // use insertion sort for the defined threshold of array segments
    if ((right - left) <= hybridThreshold) {
        insertionSort(a, size);
    }
    else {
        int mid = partition(a, size, left, right);
        quicksorthelper(a, size, left, mid - 1);
        quicksorthelper(a, size, mid + 1, right);
    }
}

/** *******************************************************************************
 * quicksort, main function                                                       *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * @post  the first n elements of a are sorted in non-descending order            *
  ********************************************************************************/
void quicksort (int a [ ], int n) {
    quicksorthelper (a, n, 0, n-1);
}

/* * * * * * improved quicksort and helper functions * * * * * * * * */
/** *******************************************************************************
 * Improved Quicksort helper function                                             *
 * uses random element between left and right as pivot value in processing        *
 * @param  a  the array to be processed                                           *
 * @param  size  the size of the array                                            *
 * @param  left  the lower index for items to be processed                        *
 * @param  right  the upper index for items to be processed                       *
 * @post   elements of a are rearranged, so that                                  *
 *             items between left and index mid are <= a[mid]                     *
 *             items between dex mid and right are >= a[mid]                      *
 * @returns  mid                                                                  *
 *********************************************************************************/
int impPartition (int a[ ], int size, int left, int right) {
    int pivotIndex = left + (rand() % (right-left+1));
    int pivot = a[pivotIndex];
    int l_spot = left+1;
    int r_spot = right;
    int temp;

    //swap a[left] with random pivot
    temp = a[left];
    a[left] = a[pivotIndex];
    a[pivotIndex] = temp;

    while (l_spot <= r_spot) {
        while( (l_spot <= r_spot) && (a[r_spot] >= pivot))
            r_spot--;
        while ((l_spot <= r_spot) && (a[l_spot] <= pivot))
            l_spot++;

        // if misplaced small and large values found, swap them
        if (l_spot < r_spot) {
            temp = a[l_spot];
            a[l_spot] = a[r_spot];
            a[r_spot] = temp;
            l_spot++;
            r_spot--;
        }
    }

    // swap a[left] with biggest small value
    temp = a[left];
    a[left] = a[r_spot];
    a[r_spot] = temp;
    return r_spot;
}

/** *******************************************************************************
 * Improved Quicksort helper function                                             *
 * @param  a  the array tobe processed                                            *
 * @param  size  the size of the array                                            *
 * @param  left  the lower index for items to be processed                        *
 * @param  right  the upper index for items to be processed                       *
 * @post  sorts elements of a between left and right                              *
 *********************************************************************************/
void impQuicksorthelper (int a [ ], int size, int left, int right) {
    if (left > right)
        return;
    int mid = impPartition (a, size, left, right);
    impQuicksorthelper (a, size, left, mid-1);
    impQuicksorthelper (a, size, mid+1, right);
}

/** *******************************************************************************
 * improved quicksort, main function                                              *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * @post  the first n elements of a are sorted in non-descending order            *
 *********************************************************************************/
void impQuicksort (int a [ ], int n) {
    impQuicksorthelper (a, n, 0, n-1);

}

/* * * * * * * *  merge sort and helper functions * * * * * * * * */
/** *******************************************************************************
 * merge sort helper function                                                     *
 * @param  aInit  source array for merging                                        *
 * @param  aRes   target array for merging                                        *
 * @param  aInitLength  the size of the array segment to be merged                *
 * @param  start1  the first index of the first array segment to be merged        *
 * @param  start2  the first index of the second  array segment to be merged      *
 * @param  end2 the last index of the second array segment to be merged           *
 * @post  elements  aInit[start1]..aInit[start1+mergeSize] merged with            *
 *              aInit[start2]..Init[end2]                                         *
 *               with the result placed in aRes                                   *
 * Note:  it may be that start2 >= aInit.length, in which case, only the          *
 *        valid part of aInit[start1] is copied                                   *
 *********************************************************************************/
void merge (int aInit [ ], int aRes [ ], int aInitLength, int start1, int start2, int end2) {
    int newArrayPtr = start1;
    int oldStart2 = start2;

    //Get the smallest element and then increment that side
    while ((start1 < oldStart2) && (start2 < end2 && start2 < aInitLength)) {
        if (aInit[start1] <= aInit[start2]) {
            aRes[newArrayPtr] = aInit[start1];
            start1++;
            newArrayPtr++;
        } else {
            aRes[newArrayPtr] = aInit[start2];
            start2++;
            newArrayPtr++;
        }
    }
    //extra element in left array
    while(start1 < oldStart2 && start1 < aInitLength) {
        aRes[newArrayPtr] = aInit[start1];
        start1++;
        newArrayPtr++;
    }
    //extra element in right array
    while(start2 < end2 && start2 < aInitLength) {
        aRes[newArrayPtr] = aInit[start2];
        start2++;
        newArrayPtr++;
    }
}

/** *******************************************************************************
 * merge sort helper function                                                     *
 * @param  initArr  the array to be sorted                                        *
 * @param  n  the size of the array                                               *
 * @post  the first n elements of a are sorted in non-descending order            *
 *********************************************************************************/
void mergeSort (int initArr [ ], int n) {
    int * resArr = (int *) malloc  (n * sizeof(int));
    int * a0 = initArr;
    int * a1 = resArr;
    bool needCopyBack = false;

    int mergeSize = 1;
    int start1;
    while (mergeSize < n) {
        int end2;
        for (start1 = 0; start1 < n; start1 = end2) {
            int start2 = start1 + mergeSize;
            end2 = start2 + mergeSize;
            merge (a0, a1, n, start1, start2, end2);
        }

        // swap a0, a1 pointers, so a0 is starting array for next merge
        int * temp = a0;
        a0 = a1;
        a1 = temp;
        mergeSize *= 2;

        // keep track of which array holds initArr object
        needCopyBack = !needCopyBack;
    }

    //copy result into initArr, as needed
    if (needCopyBack) {
        for (int i = 0; i < n; i++)
            initArr [i] = a0 [i];
    }

    free (resArr);
}

/* * * * * * * * heap sort and helper functions * * * * * * * * */
/** *******************************************************************************
 * heap sort, helper function                                                     *
 * @param  array  the array to be sorted                                          *
 * @param  hole  index of element to be worked downward in array to give heap     *
 * @param  size the overall size of the array                                     *
 * @pre  subtrees under the hold index are heaps                                  *
 * @post the entire subtree, starting from the original tree, is a heap           8
 *********************************************************************************/
void percDown(int array [ ], int hole, int size) {
    int large = hole;
    int left = 2 * hole + 1;
    int right = 2 * hole + 2;

    if (left < size && array[left] > array[large]) {
        large = left;
    }
    if (right < size && array[right] > array[large]) {
        large = right;
    }

    if (large != hole) {
        int temp = array[hole];
        array[hole] = array[large];
        array[large] = temp;
        percDown(array, large, size);
    }
}

/** *******************************************************************************
 * heap sort, main function                                                       *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * @post  the first n elements of a are sorted in non-descending order            *
 *********************************************************************************/
void heapSort (int a [ ], int n) {
    // Build Heap
    for (int i=n/2 ; i>=0 ; i-- ) {
        percDown(a, i, n);
    }

    for (int i=n-1 ; i>0 ; i-- ) {
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp   ; // deleteMax
        percDown( a, 0, i); // Maintain heap ordering property
    }
}

/* * * * * * * * * * * * procedures to check sorting correctness  * * * * * * * * */


/** *******************************************************************************
 * check all array elements have values 0, 2, 4, . . ., 2(n-1)                    *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * returns  "ok" if array contains required elements; "NO" if not                 *
 *********************************************************************************/
char * checkAscValues (int a [ ], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != 2*i) {
            //printf ("%4d %4d", i, a[i]);
            return "NO";
        }
    }
    return "ok";
}

/** *******************************************************************************
 * check all array elements are in non-descending order                           *
 * @param  a  the array to be sorted                                              *
 * @param  n  the size of the array                                               *
 * returns  "ok" if array elements in non-descending order; "NO" otherwise        *
 *********************************************************************************/
char * checkAscending (int a [ ], int n) {
    for (int i = 0; i < n-1; i++) {
        if (a[i] > a[i+1])
            return "NO";
    }
    return "ok";
}

/** *******************************************************************************
 * driver program for testing and timing sorting algorithms                       *
 **********************************************************************************/
int main ( ) {
    // declare array, indicating sorting algorithm names and function pointers
    #define numAlgs  6
    sorts sortProcs [numAlgs] = {{"selection sort", selectionSort},
                                 {"insertion sort", insertionSort},
                                 {"quicksort     ", quicksort   },
                                 {"imp. quicksort", impQuicksort },
                                 {"merge sort    ", mergeSort    },
                                 {"heap sort     ", heapSort     }};

    //size variables 40960000
    //nSquared 160000
    int maxDataSetSize = 40960000;
    int nSquaredCutoff = 160000; // do not print results from n^2 algorithms beyond this size data set

    // randomize random number generator's seed
    srand (time ((time_t *) 0) );
    //srandom (time ((time_t *) 0) );

    // print headings
    printf ("               Data Set                                Times\n");
    printf ("Algorithm        Size        Ascending Order       Random Order   Descending Order\n");

    int size; //10000
    for (size = 10000; size <= maxDataSetSize; size *= 2) {
        // create and initialize control data set arrays
        int * asc = (int *) malloc (size * sizeof(int));   //array with ascending data
        int * ran = (int *) malloc (size * sizeof(int));   //array with random data
        int * des = (int *) malloc (size * sizeof(int));   // array with descending data

        int i;
        for (i = 0; i< size; i++) {
            asc[i] = 2*i;
            ran[i] = rand();
            des[i] = 2*(size - i - 1);
        }

        // timing variables
        clock_t start_time, end_time;
        double elapsed_time;

        /* loop to test successive sorting procedures */
        // copy to test arrays
        int * tempAsc = (int *) malloc (size * sizeof(int));
        int * tempRan = (int *) malloc (size * sizeof(int));
        int * tempDes = (int *) malloc (size * sizeof(int));

        // break output for this array size
        printf ("\n");

        /* iterate through sorting algorithms */
        int numSort;

        for (numSort = 0; numSort < numAlgs; numSort++) {

            for (i = 0; i< size; i++) {
                tempAsc[i] = asc[i];
                tempRan[i] = ran[i];
                tempDes[i] = des[i];
            }

            // timing for sorting algorithm
            printf ("%14s %8d", sortProcs[numSort].name, size);
            // run-time stack exceeded for quicksort for large ordered arrays
            if ((numSort <= 3) && (size > nSquaredCutoff)) {
                printf ("           ---  --");
            } else {
                // ascending data
                start_time = clock ();
                sortProcs[numSort].sortProc (tempAsc, size);
                end_time = clock();
                elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
                printf ("%14.1lf", elapsed_time);
                printf ("  %2s", checkAscValues (tempAsc, size));
            }

            if ((numSort <= 2) && (size > nSquaredCutoff)) {
                printf ("            ---  --");
            } else {
                // random data
                start_time = clock ();
                sortProcs[numSort].sortProc (tempRan, size);
                end_time = clock();
                elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
                printf ("%15.1lf", elapsed_time);
                printf ("  %2s", checkAscending (tempAsc, size));
            }

            // run-time stack exceeded for quicksort for large ordered arrays
            if ((numSort <= 3) && (size > nSquaredCutoff)) {
                printf ("            ---  --");
            } else {
                // descending data
                start_time = clock ();
                sortProcs[numSort].sortProc (tempDes, size);
                end_time = clock();
                elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
                printf ("%15.1lf", elapsed_time);
                printf ("  %2s", checkAscValues (tempDes, size));
            }

            printf ("\n");

        }

        // clean up copies of test arrays
        free (tempAsc);
        free (tempRan);
        free (tempDes);

        // clean up original test arrays
        free (asc);
        free (ran);
        free (des);

    } // end of loop for testing procedures with different array sizes

    return 0;
}
