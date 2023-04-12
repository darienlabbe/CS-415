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
 * @remark People participating with Problem/Program Discussions:             *
 *         None                                                               *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>   // for malloc, free
#include <time.h>     // for time

#define printCopyTime 0  // 1 =  print times to copy arrays; 0 = omit this output

/** *******************************************************************************
 * structure to identify both the name of a partition algorithm and               *
 * a pointer to the function that performs the partition                          *
 * the main function utilizes this struct to define an array of partition         *
 * algorithms, based on different loop invariants, in to be timed by this program.*
 *********************************************************************************/
typedef struct algs {
  char * name;
int (*proc) (int [ ], int, int, int);
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
 * procedure to help check partition worked correctly                             *
 * @param  pivotSpot   index where pivot was supposed to be moved                 *
 * @param correctPivot value that should have been used as the pivot in partition *
 * @param a            the array being partitioned                                *
 * @param first        the index at the start of the segment to be partitioned    *
 * @param last         the index at the end of the segment to be partitioned      *
 * @post returns NO1 if correctPivot is not at index pivotSpot                    *
 *               NO2 if at least one elements between index first and pivotSpot   *
 *                      are greater than correctPivot                             *
 *               NO3 if at least one elements between index pivotSpot and last    *
 *                      are less than correctPivot                                *
 *               OK! if the array segment passes the above checks                 *
 *********************************************************************************/
char * checkPivotSpot (int pivotSpot, int correctPivot, int a [ ], int first, int last) {
  if( a[pivotSpot] != correctPivot) {
    return "NO1";
  }
  int i;
  for (i = first; i < pivotSpot; i++) {
    if (a[i] > a[pivotSpot])
      return "NO2";
  }
  for (i = pivotSpot+1; i <= last; i++) {
    if (a[i] < a[pivotSpot])
      return "NO3";
  }
  return "OK!";
}

/** *******************************************************************************
 * procedure implements the partition operation, following Loop Invariant 1a      *
 *    the Reading on Quicksort referenced above                                   *
 *    in brief: array segment has pivot, then small, unprocessed, large elements  *
 *              both unprocessed endpoints examined, swapping done in line        *
 * @param   a      the array containing the segment to be partitioned             *
 * @param   size   the size of array a                                            *
 * @param   left   the index of the first array element in the partition          *
 * @param   right  the index of the last array element in the partitionn          *
 * @post    a[left] is moved to index mid, with left <= mid <= right              *
 * @post    elements between left and right are permuted, so that                 *
 *             a[left], ..., a[mid-1] <= a[mid]                                   *
 *             a[mid+1], ..., a[right] >= a[mid]                                  *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns  mid                                                                  *
/ *********************************************************************************/
int invariant1a (int a[ ], int size, int left, int right) {
  int pivot = a[left];
  int l_spot = left+1;
  int r_spot = right;
  int temp;

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
 * procedure implements the partition operation, following Loop Invariant 1a      *
 *    the Reading on Quicksort referenced above                                   *
 *    in brief: array segment has pivot, then small, unprocessed, large elements  *
 *              both unprocessed endpoints examined, swapping uses swap function  *
 * @param   a      the array containing the segment to be partitioned             *
 * @param   size   the size of array a                                            *
 * @param   left   the index of the first array element in the partition          *
 * @param   right  the index of the last array element in the partitionn          *
 * @post    a[left] is moved to index mid, with left <= mid <= right              *
 * @post    elements between left and right are permuted, so that                 *
 *             a[left], ..., a[mid-1] <= a[mid]                                   *
 *             a[mid+1], ..., a[right] >= a[mid]                                  *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns mid                                                                   *
  *********************************************************************************/
int invariant1aSwap (int a[ ], int size, int left, int right) {
  int pivot = a[left];
  int l_spot = left+1;
  int r_spot = right;
  int temp;

  while (l_spot <= r_spot) {
    while( (l_spot <= r_spot) && (a[r_spot] >= pivot))
      r_spot--;
    while ((l_spot <= r_spot) && (a[l_spot] <= pivot))
      l_spot++;

    // if misplaced small and large values found, swap them
    if (l_spot < r_spot) {
      swap (&a[l_spot], &a[r_spot]);
      l_spot++;
      r_spot--;
      }
  }

  // swap a[left] with biggest small value
  swap (&a[left], &a[r_spot]);

  return r_spot;
}

/** *******************************************************************************
 * procedure implements the partition operation, following Loop Invariant 1b      *
 *    the Reading on Quicksort referenced above                                   *
 *    in brief: array segment has pivot, then small, large, unprocessed elements  *
 *              left unprocessed endpoints examined, swapping uses swap function  *
 * @param   a      the array containing the segment to be partitioned             *
 * @param   size   the size of array a                                            *
 * @param   left   the index of the first array element in the partition          *
 * @param   right  the index of the last array element in the partitionn          *
 * @post    a[left] is moved to index mid, with left <= mid <= right              *
 * @post    elements between left and right are permuted, so that                 *
 *             a[left], ..., a[mid-1] <= a[mid]                                   *
 *             a[mid+1], ..., a[right] >= a[mid]                                  *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns mid                                                                   *
 *********************************************************************************/

/* invariant 1b:  partition, swapping many interactions, plus separate swap */
int invariant1b (int a[ ], int size ,int first, int last) {
  int pivot = a[first];
  int left;
  int right = last;

  for (left = first+1; left <= right;) {
    if (a[left] < pivot) {
      left++;
    }
    else {
      swap (&a[left], &a[right]);
      right--;
    }
  }

  swap (&a[first], &a[right]);

  return right;
}


/** *******************************************************************************
 * procedure implements the partition operation, following Loop Invariant 2       *
 *    the Reading on Quicksort referenced above                                   *
 *    in brief: array segment has pivot, then small, large, unprocessed elements  *
 *              left unprocessed endpoints examined, swapping uses swap function  *
 * @param   a      the array containing the segment to be partitioned             *
 * @param   size   the size of array a                                            *
 * @param   first   the index of the first array element in the partition         *
 * @param   last  the index of the last array element in the partition            *
 * @post    a[left] is moved to index mid+1, with left <= mid <= right            *
 * @post    elements between left and right are permuted, so that                 *
 *             a[left], ..., a[mid-1] <= a[mid]                                   *
 *             a[mid+1], ..., a[right] >= a[mid]                                  *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns mid                                                                   *
 *********************************************************************************/

/* invariant 2:  partition, swapping many interactions, plus separate swap */
int invariant2 (int a[ ], int size ,int first, int last) {
    int pivot = a[first];
    int left = first + 1;
    int right = first + 1;

    while (right <= last)
    {
        if (pivot < a[right])
            right++;
        else {
            swap (&a[left], &a[right]);
            left++;
            right++;
        }
    }
    // put a[first] in its place
    swap (&a[first], &a[left-1]);

    return left-1;
}


/** *******************************************************************************
 * procedure implements the partition operation, following Loop Invariant 3       *
 *    the Reading on Quicksort referenced above                                   *
 *    in brief: array segment has pivot, then unprocessed elements, small, large, *
 *              swapping uses swap function                                       *
 * @param   a      the array containing the segment to be partitioned             *
 * @param   size   the size of array a                                            *
 * @param   first   the index of the first array element in the partition          *
 * @param   last  the index of the last array element in the partition           *
 * @post    a[left] is moved to index first+1, with left <= mid <= right          *
 * @post    elements between left and right are permuted, so that                 *
 *             a[left], ..., a[mid-1] <= a[mid]                                   *
 *             a[mid+1], ..., a[right] >= a[mid]                                  *
 * @post    elements outside left, ..., right are not changed                     *
 * @returns mid                                                                   *
 *********************************************************************************/

/* invariant 3:  partition, swapping many interactions, plus separate swap */
int invariant3 (int a[ ], int size ,int first, int last) {
    int pivot = a[first];
    int left = last;
    int right = last;

    while (left > first)
    {
        if (pivot > a[left])
            left--;
        else {
            swap (&a[left], &a[right]);
            left--;
            right--;
        }
    }
    // put a[first] in its place
    swap (&a[first], &a[right]);

    return right;
}


/** *******************************************************************************
 * driver program for testing and timing partition algorithms                     *
 *********************************************************************************/

int main ( ) {
  // identify partition procedures used and their descriptive names
  #define numAlgs  5
  partitionType procArray [numAlgs] = {{"invariant 1a ", invariant1a   },
                                       {"inv 1a w/swap", invariant1aSwap   },
                                       {"invariant 1b ", invariant1b   },
                                       {"invariant 2  ", invariant2},
                                       {"invariant 3  ", invariant3}};

  // print output headers
  printf ("timing/testing of partition functions\n");
  // print headings
  printf ("               Data Set                             Times\n");
  printf ("Algorithm        Size     Ascending Order       Random Order  Descending Order\n");

  int size;
  int reps;
  int maxreps = 1000;

  // organize data sets of increasing size for ascending, random, and descending data
  for (size = 100000; size <= 1600000; size *= 2) {
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
       double copy_time, elapsed_time;
       int pivotSpot;

       /* * * * * * * * * * * * * * * * * * * * * * * *
        *      test and time algorithm:  algProc[alg] *
        * * * * * * * * * * * * * * * * * * * * * * * */

       /* * * * * * * test ascending data * * * * * * */

       // determine average time to copy array
       start_time = clock ();
       for (reps = 0; reps < maxreps; reps++) {
         for (i = 0; i< size; i++) {
           tempAsc[i] = asc[i];
         }
       }
       end_time = clock();
       copy_time = ((end_time - start_time) / (double) CLOCKS_PER_SEC );
       if (printCopyTime)
         printf ("copy time:  %10.1lf\n", copy_time);

       // timing for algorithm
      start_time = clock ();
      for (reps = 0; reps < maxreps; reps++) {
        for (i = 0; i< size; i++) {
          tempAsc[i] = asc[i];
        }
          pivotSpot = procArray[alg].proc (tempAsc, size, 0, size-1);
      }
       end_time = clock();
       elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
       printf ("%13.1lf ", elapsed_time - copy_time);
       printf ("%3s  ", checkPivotSpot (pivotSpot, 0, tempAsc, 0, size-1));

       /* * * * * * * test random data * * * * * * */

       // determine time to copy array
       start_time = clock ();
       for (reps = 0; reps < maxreps; reps++) {
         for (i = 0; i< size; i++) {
           tempRan[i] = ran[i];
         }
       }
       end_time = clock();
       copy_time = ((end_time - start_time) / (double) CLOCKS_PER_SEC );
       if (printCopyTime)
         printf ("copy time:  %10.1lf", copy_time);

       // timing for algorithm
       start_time = clock ();
       for (reps = 0; reps < maxreps; reps++) {
         for (i = 0; i< size; i++) {
           tempRan[i] = ran[i];
         }
         pivotSpot = procArray[alg].proc (tempRan, size, 0, size-1);
         }
       end_time = clock();
       elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
       printf ("%13.1lf ", elapsed_time - copy_time);
       printf ("%3s ", checkPivotSpot (pivotSpot, ran[0], tempRan, 0, size-1));


       /* * * * * * * test descending data * * * * * * */

       // determine time to copy array
       start_time = clock ();
       for (reps = 0; reps < maxreps; reps++) {
         for (i = 0; i< size; i++) {
           tempDes[i] = des[i];
         }
       }
       end_time = clock();
       copy_time = ((end_time - start_time) / (double) CLOCKS_PER_SEC );
       if (printCopyTime)
         printf ("copy time:  %10.1lf", copy_time);

       // timing for algoirthm
       start_time = clock ();
       for (reps = 0; reps < maxreps; reps++) {
         for (i = 0; i< size; i++) {
           tempDes[i] = des[i];
         }
         pivotSpot = procArray[alg].proc (tempDes, size, 0, size-1);
       }
       end_time = clock();
       elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
       printf ("%13.1lf ", elapsed_time - copy_time);
       printf ("%3s ", checkPivotSpot (pivotSpot, 2*(size - 1), tempDes, 0, size-1));

       printf ("\n");

     } // end of loop for testing an algorithm

     // leave blank line before output of next size
     printf ("\n");

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
