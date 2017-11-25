#include <stdio.h>
#include <gsl/gsl_linalg.h>


int main (void)
{

  const int N = 2;
  int permutation_sign, i, j;  
  double diag_prod;

  // Create pointers and allocate space to hold the matrices
  gsl_matrix *a = gsl_matrix_alloc(N,N);
  gsl_matrix *b = gsl_matrix_alloc(N,N);

  // Allocate space for the permutation matrix
  gsl_permutation * p = gsl_permutation_alloc (N);

  // Build the Hilbert Matrix, store in a  
  for ( i=1; i<=N; i++ )
      for ( j=1; j<=N; j++ )
          gsl_matrix_set( a, i-1, j-1, (double) 1 / ( (double) (i+j-1)) );

  // Decompose the matrix using the PLU method
  gsl_linalg_LU_decomp (a, p, &permutation_sign);

  // Do the inversion  
  gsl_linalg_LU_invert (a, p, b);

  // Now print 
  printf("The inverse matrix\n");
  for (i=0; i<N; i++ ) {
      for (j=0; j<N; j++) { 
         printf("\t%g", gsl_matrix_get(b,i,j));
      }
      printf("\n");
  } 

  gsl_matrix_free(a);
  gsl_matrix_free(b);
  gsl_permutation_free (p);
  return 0;
}
