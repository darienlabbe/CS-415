/** *******************************************************************************
 * @remark program implements Horner's rule for polynomial evaluation             *
 *                                                                                *
 * @author Darien Labbe                                                           *
 * @remark Assignment  Using Algebra to Improve Efficiency                        *
 * @file  compute-poly.c                                                          *
 * @date  March 20, 2023                                                          *
 *                                                                                *
 * @remark References                                                             *
 * @remark Assignment on Comparing Sorting Algorithms and on the Use of Algebra   *
 *         to Improve Efficiency:                                                 *
 *         Henry M. Walker                                                        *
 * @remark 13b-notes-homers-rule.pdf in the section Polynomial Evaluation:        *
 *         Henry M. Walker                                                        *
 *                                                                                *
 *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>   // for malloc, free

/** *******************************************************************************
 * compute_poly                                                                   *
 * @param  x  the real number value that x in the polynomial p(x) is to be        *
 *                evaluated to                                                    *
 * @param  n  the first degree in the polynomial, also the size of the array + 1  *
 * @param  a  the array of real number coefficients                               *
 * @returns  the integer result from the polynomial computation                   *
 *********************************************************************************/
double compute_poly (double x, int n, double a[]) {
    double pOfX = a[n];

    // working from a[n] to a[0]
    for (int i = n-1; i >= 0; i--) {
        pOfX = pOfX*x + a[i];
    }
    // return the resulting int of p(x)
    return pOfX;
}

/** ********************************************************************************
 * driver program for testing the compute_poly function                            *
 **********************************************************************************/
int main() {
    /* simple test */
    // p(x) = 1x^4 - 18x^3 + 9x^2 -24x^1 + 8
    // when x=3 evaluated using a calculator the value should be 38.0
    double a [] = {8,-2,7,-16, 5};
    double x = 3.0;
    int n = 4;

    // print simple test
    printf("\nSimple Test:\n");
    printf("Value of p(x) when p(%1.1f) is: ", x);
    printf("%1.1f\n", compute_poly(x, n, a));

    /* larger test */
    n = 9;
    double * des = (double *) malloc ((n + 1) * sizeof(double));

    // p(x) = 2.3x^9 + 4.6x^8 + 6.9x^7 + 9.2x^6 + 11.5x^5 + 13.8x^4
    //        + 16.1x^3 + 18.4x^2 + 20.7x^1 + 23.0
    // when x=3 evaluated using a calculator the value should be 101846.3
    for (int i = 0; i <= n; i++) {
        des[i] = 2.3 * (n - i + 1);
        printf("%1.1f, ", des[i]);
    }

    // print larger test
    printf("\nLarge Test:\n");
    printf("Value of p(x) when p(%1.1f) is: ", x);
    printf("%1.1f\n", compute_poly(x, n, des));

    // clean up test array
    free (des);

    return 0;
}
