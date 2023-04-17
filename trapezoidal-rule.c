/** ***************************************************************************
 * @remark This program implements the trapezoidal rule to determine the area *
 *   under a curve. In this particular program, the intervals [a,b], the      *
 *   number of intervals, and the line represented by f(x) are hard coded.    *
 *   However, each one of these numbers (except for f(x)) could be replaced   *
 *   with prompting the user to provide these values.                         *
 *                                                                            *
 * @author Darien Labbe                                                       *
 * @file  trapezoidal-rule.c                                                  *
 * @date  April 17, 2023                                                      *
 *                                                                            *
 * @remark References                                                         *
 * @remark Henery M. Walker                                                   *
 *         Notes:  17-numerical-error                                         *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>

int main() {
    // x is number of sub-intervals, a is start, b is end in interval [a,b]
    // 'result' contains (x0^2)/2 + (xn^2)/2
    // 'interval' is the height between each sub-interval
    int x = 5;
    float a = 1, b = 3, temp = a, result = ((a * a) + (b * b))/2;
    float interval = (b - a) / (float)x;

    // Add each sub-interval x1^2 + x2^2...+xn-1^2 then multiply by height
    for (int i = (int)a; i < x; i++) {
        a += interval;
        result += a * a;
    }
    result *= interval;

    //Print the result of the calculation
    printf("\nImplementation of the Trapezoidal Rule:\n\n");
    printf("The area under the curve f(x) = x^2 is determined\n");
    printf("by using the intervals [%.1f, %.1f] with %d\n", temp, b, x);
    printf("trapezoids. \n\nThe resulting calculation is %f\n", result);

    return 0;
}
