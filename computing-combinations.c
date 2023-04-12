/** ***************************************************************************
 * @remark computing combinations using similar algorithms used to calculate  *
 *  the combinations using the basic recursive formula for the sequence with  *
 *  and without dynamic programming                                           *
 *                                                                            *
 * @author Darien Labbe                                                       *
 * @file  computing-combinations.c                                            *
 * @date  April 7, 2023                                                       *
 *                                                                            *
 * @remark References                                                         *
 * @remark Dynamic Programming:  Anany Levitin, "The Design and               *
 *         and Analysis of Algorithms", Second Edition,                       *
 *         Chapter 8:  Dynamic Programming                                    *
 *                                                                            *
 * @remark People participating with Problem/Program Discussions:             *
 *         None                                                               *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>      // for printf
#include <stdlib.h>     // for malloc
#include <time.h>       // for time

/** ***************************************************************************
 * computing combinations directly,                                           *
 * using the recursive definition of the formula                              *
 * @param  n:  the number of choices                                          *
 * @param  k:  the number of options to choose                                *
 * @pre   0 <= n                                                              *
 * @pre   0 <= k                                                              *
 * @returns  the result of n choose k                                         *
 *****************************************************************************/
int combo1(int n, int k) {
    if ((k == 0 || k == n) || n <= 1) {
        return 1;
    }
    else {
        return combo1(n-1, k-1) + combo1(n-1, k);
    }
}

/** ***************************************************************************
 * helper function to compute the combination,                                *
 * using the recursive definition and dynamic programming                     *
 * @param  n:  the number of choices                                          *
 * @param  k:  the number of options to choose                                *
 * @param  comboArr:  an initialize array, recording                          *
 *              combination numbers already computed                          *
 * @pre   0 <= n <= 1 + row length of comboArr array                          *
 * @pre   0 <= k <= 1 + column length of comboArr array                       *
 * @returns  the result of n choose k                                         *
 *****************************************************************************/
int combo2Helper (int n, int k, int** comboArr) {
    // use the array if already calculated
    if (comboArr[n][k] != 0) {
        return comboArr[n][k];
    }
    if ((k == 0 || k == n) || n <= 1) {
        return comboArr[n][k] = 1;
    }
    else {
        return comboArr[n][k] = combo2Helper(n-1, k-1, comboArr)
                                + combo2Helper(n-1, k, comboArr);
    }
}

/** ***************************************************************************
 * compute the combination,                                                   *
 * using the recursive definition and dynamic programming                     *
 * @param  n:  the number of choices                                          *
 * @param  k:  the number of options to choose                                *
 * @pre   0 <= n                                                              *
 * @pre   0 <= k                                                              *
 * @returns  the result of n choose k                                         *
 *****************************************************************************/
int combo2 (int n, int k) {
    // create an initialized local array for bookkeeping before recurring
    int* arr[n+1];

    // initialize a second dimension to the array
    for (int i = 0; i < n+1; i++) {
        arr[i] = (int*) malloc ((k+1) * sizeof(int));
    }

    // initialize with 0's
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            arr[i][j] = 0;
        }
    }
    return combo2Helper(n, k,arr);
}

/** ***************************************************************************
 * main procedure controls computation, timing, and printing                  *
 *****************************************************************************/
int main ( ) {
    int reps = 100;  // number of times call repeated to help timings

    // print the title
    printf ("timing of two functions to compute the result of n choose k\n");
    printf ("         (each function call repeated %d times)\n", reps);
    printf ("                     Approach 1          Approach 2\n");
    printf ("     n     k     Combo[n]   time     Combo[n]   time\n");

    // variables for C(n, k). Change k for different tests
    int n, k = 9;

    // variables used for loops and timing
    int value;
    clock_t start_time, end_time;
    double elapsed_time;

    for (n = k; n <= 41; n += 4) {
        printf ("%6d", n);
        printf ("%6d", k);

        // time first approach
        start_time = clock ();
        for (int j = 0; j < reps; j++) {
            value = combo1(n, k);
        }
        end_time = clock();
        elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;
        printf ("%11d   %6.1lf", value, elapsed_time);

        // time second approach
        start_time = clock ();
        for (int l = 0; l < reps; l++) {
            value = combo2(n, k);
        }
        end_time = clock();

        // calculate time
        elapsed_time = (end_time - start_time) / (double) CLOCKS_PER_SEC;

        // print the result
        printf ("%11d   %6.1lf\n", value, elapsed_time);
    }
}