#include <stdio.h>
#include <gsl/gsl_linalg.h>


int main (void)
{

  const int N = 5;
  int i, j;  
  double diag_prod;
  int permutation_sign;
  

  // Create pointers and allocate space to hold the matrices
  gsl_matrix *a = gsl_matrix_alloc(N,N);

  // Allocate space for the permutation matrix
  gsl_permutation *p = gsl_permutation_alloc (N);

  // Build the Hilbert Matrix, store in a  
  for ( i=1; i<=N; i++ )
      for ( j=1; j<=N; j++ )
          gsl_matrix_set( a, i-1, j-1, (double) 1 / ( (double) (i+j-1)) );

  // Decompose the matrix using the PLU method
  permutation_sign = 1;
  gsl_linalg_LU_decomp (a, p, &permutation_sign);

  // Now compute the product of the diagonal of the decomposed a matrix
  diag_prod = (double) 1.0;
  for (i=0; i<N; i++ ) {
      diag_prod = diag_prod * gsl_matrix_get(a, i, i);
      printf("element = %g, sign = %d, prod = %g\n", gsl_matrix_get(a,i,i), permutation_sign, diag_prod);      
  }

  
  // Now fix the sign based on row interchange data
  diag_prod = diag_prod * (double) permutation_sign;

  printf ("The determinant of the matrix is = %g\n", diag_prod);

  gsl_matrix_free(a);
  gsl_permutation_free (p);
  return 0;
}
