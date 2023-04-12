/* program to time several partition algorithms on data sets of various sizes
 */

/** ***************************************************************************
 * @remark  program to time several partition algorithms on data sets         *
 * of various sizes                                                           *
 *                                                                            *
 * @author Henry M. Walker                                                    *
 * @file  partition.c                                                         *
 * @date  August 7, 2022                                                      *
 *                                                                            *
 * @remark References                                                         *
 * @remark Henry M. Walker, Pascal: Problem Solving and Structured Program    *
 *         Design, Little, Brown, and Company, 1987, pages 500-506            *
 * @remark Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivset, and      *
 *         Clifford Stein, Introduction to Algorithms, Third Edition          *
 *         The MIT Press, 2009, pages170-185                                  *
 * @remark Reading on Quicksort, https://blue.cs.sonoma.edu/~hwalker/courses  *
 *                 /415-sonoma.fa22/readings/reading-quicksort.php            *
 *                                                                            *
 * @remark People participating with Problem/Progra Discussions:              *
 *         None                                                               *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>   // for malloc, free
#include <time.h>     // for time

#define printOrder 0    // 1 displays the before and after for the sorts
                        // 0 does not display

/** *******************************************************************************
 * structure to identify both the name of a partition algorithm and               *
 * a pointer to the function that performs the partition                          *
 * the main function utilizes this struct to define an array of partition         *
 * algorithms, based on different loop invariants, in to be timed by this program.*
 *********************************************************************************/
typedef struct algs {
    char * name;
    void (*proc) (int*, int, int);
} partitionType;

/** *******************************************************************************
 * swap function to interchange integers at two designed addresses                *
 * @param   a  the address of one integer                                         *
 * @param   b  the address of one integer                                         *
 * @post    the integers stored at addresses a and b are changed                  *
 *********************************************************************************/
void swap (int * a, int * b) {
    int temp = * a;
    * a = * b;
    *b = temp;
}


/** *******************************************************************************
 * function for displaying an array                                               *
 * @param array   the array to be displayed                                       *
 * @param size    the size of the array                                           *
 * @post prints the array to the output stream                                    *
 *********************************************************************************/
void printArray (int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d\n\n", array[size - 1]);
}


char * checkArrayOrder (int *array, int size) {
    for (int i = 1; i < size; i++) {
        if (array[i-1] > array[i])
            return "no";
    }
    return "ok";
}


/** *******************************************************************************
 * kernel function of the merge sort                                              *
 * @remark  function taken from tutorialspoint.com as instructed in the           *
 *            assignment and will be used for the recursive version and the       *
 *            iterative version                                                   *
 * @param array   the array to be sorted                                          *
 * @param l       left most point of the array                                    *
 * @param m       the middle of the array                                         *
 * @param r       right most point of the array                                   *
 * @post sorts the section of array passed as a parameter                         *
 *********************************************************************************/
void mergeKernel(int *array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m-l+1; nr = r-m;
    int larr[nl], rarr[nr];
    //fill left and right sub-arrays
    for(i = 0; i<nl; i++)
        larr[i] = array[l+i];
    for(j = 0; j<nr; j++)
        rarr[j] = array[m+1+j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while(i < nl && j<nr) {
        if(larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        }else{
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while(i<nl) {       //extra element in left array
        array[k] = larr[i];
        i++; k++;
    }
    while(j<nr) {       //extra element in right array
        array[k] = rarr[j];
        j++; k++;
    }
}

/** *******************************************************************************
 * function of the recursive merge sort                                           *
 * @remark  function taken from tutorialspoint.com as instructed in the homework  *
 * @param array   the array to be sorted                                          *
 * @param l       left most point of the array                                    *
 * @param r       right most point of the array                                   *
 * @post sorts the array passed as a parameter                                    *
 *********************************************************************************/
void mergeSortRecursive(int *array, int l, int r) {
    if(l < r) {
        int m = l+(r-l)/2;
        // Sort first and second arrays
        mergeSortRecursive(array, l, m);
        mergeSortRecursive(array, m + 1, r);
        mergeKernel(array, l, m, r);
    }
}


/** *******************************************************************************
 * function of the iterative merge sort                                           *
 * @remark  function taken from tutorialspoint.com as instructed in the homework  *
 * @param array   the array to be sorted                                          *
 * @param l       left most point of the array                                    *
 * @param r       right most point of the array                                   *
 * @pre  array size must be size 2 or larger, otherwise, displays error message   *
 * @post sorts the array passed as a parameter                                    *
 *********************************************************************************/
void mergeSortIterative(int *array, int l, int r) {
    int size = r+1, leftPtr, rightPtr, m;

    // check that there is at least two elements in the array
    if (size >= 2) {
        for (int segSize = 1; segSize < size; segSize *= 2) {
            for (leftPtr = 0; leftPtr < size - 1; leftPtr += 2 * segSize) {
                // find ending point of left subarray
                if (leftPtr + segSize - 1 < size - 1)
                    m = leftPtr + segSize - 1;
                else
                    m = size - 1;

                // find ending point of right subarray
                if ((leftPtr + 2 * segSize - 1) < (size - 1))
                    rightPtr = leftPtr + 2 * segSize - 1;
                else
                    rightPtr = size - 1;

                // sort the current segment of array
                mergeKernel(array, leftPtr, m, rightPtr);
            }
        }
    }
    else {
        // display if precondition of array size is not met
        printf("Array is, by default, sorted or empty.\n");
    }
}

/** *******************************************************************************
 * driver program for testing and timing partition algorithms                     *
 *********************************************************************************/

int main() {
    srand(time(NULL));

    // identify partition procedures used and their descriptive names
    #define numAlgs  2
    partitionType procArray [numAlgs] = {{"Merge Sort Recursive: ", mergeSortRecursive},
                                         {"Merge Sort Iterative: ", mergeSortIterative}};

    // print output headers
    printf ("timing/testing of partition functions\n");
    // print headings
    printf ("                       Data Set              Times (milliseconds)\n");
    printf ("Algorithm                Size     Ascending Order   Random Order   Descending Order\n");

    int size;

    // organize data sets of increasing size for ascending, random, and descending data 10000 160000
    for (size = 10000; size <= 160000; size *= 2) {
        // create control and initial data set arrays
        int * asc = (int *) malloc (size * sizeof(int));   //array with ascending data
        int * ran = (int *) malloc (size * sizeof(int));   //array with random data
        int * des = (int *) malloc (size * sizeof(int));   // array with descending data

        int i;
        for (i = 0; i< size; i++) {
            asc[i] = 2*i;
            ran[i] = rand();
            des[i] = 2*(size - i - 1);
        }

        // copy to test arrays
        int * tempAsc = (int *) malloc (size * sizeof(int));
        int * tempRan = (int *) malloc (size * sizeof(int));
        int * tempDes = (int *) malloc (size * sizeof(int));

        // repeat for each algorithm
        for (int alg = 0; alg < numAlgs; alg++) {
            // identify function and data set size
            printf ("%s %7d", procArray[alg].name, size);
            // timing variables
            clock_t start_time, end_time;
            double elapsed_time;

            /* * * * * * * * * * * * * * * * * * * * * * * *
             *      test and time algorithm:  algProc[alg] *
             * * * * * * * * * * * * * * * * * * * * * * * */

            /* * * * * * * test ascending data * * * * * * */
            // timing for algorithm
            for (i = 0; i< size; i++) {
                tempAsc[i] = asc[i];
            }
            start_time = clock ();
            procArray[alg].proc (tempAsc, 0, size-1);
            end_time = clock();
            //Timing displayed in milliseconds
            elapsed_time = (end_time - start_time) / (double) (CLOCKS_PER_SEC/1000);
            printf ("%13.1lf %s", elapsed_time, checkArrayOrder(tempAsc, size));
            //printf(" %s", checkArrayOrder(tempAsc, size));

            /* * * * * * * test random data * * * * * * */
            // timing for algorithm
            for (i = 0; i< size; i++) {
                tempRan[i] = ran[i];
            }
            start_time = clock ();
            procArray[alg].proc (tempRan, 0, size-1);
            end_time = clock();
            //Timing displayed in milliseconds
            elapsed_time = (end_time - start_time) / (double) (CLOCKS_PER_SEC/1000);
            printf ("%13.1lf %s", elapsed_time, checkArrayOrder(tempRan, size));

            /* * * * * * * test descending data * * * * * * */
            // timing for algoirthm
            for (i = 0; i< size; i++) {
                tempDes[i] = des[i];
            }
            start_time = clock ();
            procArray[alg].proc (tempDes, 0, size-1);
            end_time = clock();
            //Timing displayed in milliseconds
            elapsed_time = (end_time - start_time) / (double) (CLOCKS_PER_SEC/1000);
            printf ("%13.1lf %s", elapsed_time, checkArrayOrder(tempDes, size));

            printf ("\n");
        } // end of loop for testing an algorithm

        // leave blank line before output of next size
        printf ("\n");

        if (printOrder == 1) {
            // print before sort
            printf("\nRandom order array before either sort (each use the unsorted version and then sort):\n");
            printArray(ran, size);
            // print after sort
            printf("Random order array after recursive sort:\n");
            printArray(tempRan, size);
            // print after sort
            printf("Random order array after iterative sort:\n");
            printArray(tempRan, size);
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

    int minHeap[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    int minHeapRev[13] = {};

    printf("\n\n\n~Other array~\n");
    printf("This is to help with making: ");
    for (int i = 1; i <= 13; i++) {
        if (i < 10)
            printf(" %d ", i);
        else
            printf(" %d ", i);
    }
    printf("\nPrint the array with size 13: ");

    for (int i = 0; i < 13; i++) {
        minHeap[i] = i;
    }

    printArray(minHeap, 13);

    return 0;
}