#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_linalg.h>


/* Solving complex linear system 
 *      (3+i)x -    2y  = 3-4i
 *      -3x    + (1-2i) = -1+.5i
 *
 * using the Gnu Scientific Library.  There is some strange 
 * packing that has to be done to set up the matrices. 
 * The gsl defines the complex data type as a struct
 *
 * typedef struct
 *   {
 *       double dat[2];
 *   }
 * gsl_complex;
 *
 * compile with...
 *
 * gcc complex_simeq.c -lgsl -L/usr/lib64/atlas -latlas -lcblas
 *
 * -or-
 *
 * g++ complex_simeq.c -lgsl -L/usr/lib64/atlas -latlas -lcblas
 *
 */ 

int main (void)
{

 
  // The gsl_complex_rect function can be used to assign complex numbers 
  gsl_complex a00 = gsl_complex_rect(3.0,1.0);
  gsl_complex a01 = gsl_complex_rect(-2.0,0.0);
  gsl_complex a10 = gsl_complex_rect(-3.0,0.0);
  gsl_complex a11 = gsl_complex_rect(1.0,-2.0);

  gsl_complex b0 = gsl_complex_rect(3.0,-4.0);
  gsl_complex b1 = gsl_complex_rect(-1.0,0.5);

  // Create pointers to hold the matrices and vectors
  gsl_matrix_complex *a_data = NULL;
  gsl_vector_complex *x      = NULL;
  gsl_vector_complex *b_data = NULL;

  // Allocate space for the matices and vectors
  a_data = gsl_matrix_complex_alloc(2,2);
  x      = gsl_vector_complex_alloc(2);
  b_data = gsl_vector_complex_alloc(2);
 
  // Put the data into the matrix a_data
  gsl_matrix_complex_set( a_data, 0, 0, a00);
  gsl_matrix_complex_set( a_data, 0, 1, a01);
  gsl_matrix_complex_set( a_data, 1, 0, a10);
  gsl_matrix_complex_set( a_data, 1, 1, a11);

  // Put hte data into the vector b
  gsl_vector_complex_set( b_data, 0, b0);
  gsl_vector_complex_set( b_data, 1, b1);
 
  /* "s" will hold the sign of (-1)^n where n is the number of
   * row interchanges needed in the PLU decomposition of the matrix
   * a_data.  The actual row interchanges are maintained in the permutation
   * matrix p.
   */

  int s;

  // Allocate space for the permutation matrix
  gsl_permutation * p = gsl_permutation_alloc (2);

  // Decompose the matrix using the PLU method
  gsl_linalg_complex_LU_decomp (a_data, p, &s);

  // Do the back substitution to solve x 
  gsl_linalg_complex_LU_solve (a_data, p, b_data, x);

  printf ("x = \n");
  gsl_vector_complex_fprintf(stdout, x, "%g");

  gsl_matrix_complex_free(a_data);
  gsl_vector_complex_free(b_data);
  gsl_vector_complex_free(x);
  gsl_permutation_free (p);
  return 0;
}
