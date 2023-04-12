/** ***************************************************************************
 * @remark program to determine integer overflow for factorials               *
 *                                                                            *
 * @author Henry M. Walker                                                    *
 * @remark Edited By: Darien Labbe                                            *
 * @file  factorial.c                                                         *
 * @date  April 7, 2023                                                       *
 *                                                                            *
 * @remark Reference                                                          *
 * @remark Consequences of Data Representation on Programming                 *
  https://blue.cs.sonoma.edu/~hwalker/courses/415-sonoma.sp23/readings/data-rep-consequences.html
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>

int main ( ) {
    printf ("program to determine integer overflow for factorials\n");

    int i = 1;
    long fact = 1;
    printf ("  i   factorial\n");

    printf ("%3d  %20ld\n", i, fact);

    while (fact > 0) {
        i++;
        fact *= i;
        printf ("%3d  %20ld\n", i, fact);
    }

    printf ("loop ended with %d factorial = %ld\n", i, fact);

    return 0;
}