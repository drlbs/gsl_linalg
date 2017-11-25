#include <stdio.h>
#include <gsl/gsl_linalg.h>


int main (void)
{

  const int N = 20;
  int permutation_sign, i, j;  
  double diag_prod;

  // Create pointers and allocate space to hold the matrices
  gsl_matrix *a = gsl_matrix_alloc(N,N);
  gsl_matrix *b = gsl_matrix_alloc(N,N);
  gsl_vector *x = gsl_vector_alloc(N);

  // Allocate space for the permutation matrix
  gsl_permutation * p = gsl_permutation_alloc (N);

  // Build the Hilbert Matrix, store in a  
  for ( i=1; i<=N; i++ )
      for ( j=1; j<=N; j++ )
          gsl_matrix_set( a, i-1, j-1, (double) 1 / ( (double) (i+j-1)) );

  // Build the Identiry Matrix, store in b  
  for ( i=0; i<N; i++ )
      for ( j=0; j<N; j++ )
          if ( i != j ) 
             gsl_matrix_set( b, i, j, (double) 0 );
          else
             gsl_matrix_set( b, i, j, (double) 1 );

  // Decompose the matrix using the PLU method
  gsl_linalg_LU_decomp (a, p, &permutation_sign);

  // Do the back substitution to solve x 
  gsl_linalg_LU_solve (a, p, b, x);

  // Now compute the product of the diagonal of the decomposed a matrix
  diag_prod = (double) 1.0
  for (i=0; i<N; i++ ) 
      diag_prod = diag_prod * gsl_matrix_get(a, i, i);

  // Now fix the sign based on row interchange data
  diag_prod = diag_prod * permutation_sign;

  gsl_vector_complex_fprintf(stdout, x, "%g");

  printf ("The determinant of the matrix is = %f\n", diag_prod);

  gsl_matrix_free(a_data);
  gsl_matrix_free(b_data);
  gsl_vector_free(x);
  gsl_permutation_free (p);
  return 0;
}
