#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define DIES 0
#define ALIVE 1

/* function to measure time taken */
double gettime(void) {
  struct timeval tval;

  gettimeofday(&tval, NULL);

  return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
}

void printarray(int *a, int M, int N, FILE *fp) {
  int i, j;
  for (i = 0; i < M+2; i++) {
    for (j = 0; j< N+2; j++)
      fprintf(fp, "%d ", a[i*(N+2) + j]);
    fprintf(fp, "\n");
  }
}

int check_array(int *a, int M, int N) {
  int value=0;
  for (int i = 1; i < M+1; i++)
    for (int j = 1; j< N+1; j++)
      value+= a[i*(N+2) + j];
  return value;
}

void compute(int *life, int *temp, int M, int N) {
  int i, j, value;

  for (i = 1; i < M+1; i++) {
    for (j = 1; j < N+1; j++) {
      /* find out the value of the current cell */
      value = life[(i-1)*(N+2) + (j-1)] + life[(i-1)*(N+2) + j] + 
              life[(i-1)*(N+2) + (j+1)] + life[i*(N+2) + (j-1)] + 
              life[i*(N+2) + (j+1)] + life[(i+1)*(N+2) + (j-1)] + 
              life[(i+1)*(N+2) + j] + life[(i+1)*(N+2) + (j+1)] ;
      
      /* check if the cell dies or life is born */
      if (life[i*(N+2) + j]) { // cell was alive in the earlier iteration
	if (value < 2 || value > 3) {
	  temp[i*(N+2) + j] = DIES ;
	}
	else // value must be 2 or 3, so no need to check explicitly
	  temp[i*(N+2) + j] = ALIVE ; // no change
      } 
      else { // cell was dead in the earlier iteration
	if (value == 3) {
	  temp[i*(N+2) + j] = ALIVE;
	}
	else
	  temp[i*(N+2) + j] = DIES; // no change
      }
    }
  }

}

int main(int argc, char **argv) {
  int N, NTIMES, *life=NULL, *temp=NULL;
  int i, j, k;
  double t1, t2;

#if defined(DEBUG1) || defined(DEBUG2)
  FILE *fp;
  char filename[32];
#endif

  N = atoi(argv[1]);
  NTIMES = atoi(argv[2]);

  /* Allocate memory for both arrays */
  life = malloc((N+2)*(N+2)*sizeof(int));
  temp = malloc((N+2)*(N+2)*sizeof(int));

  /* Initialize the boundaries of the life matrix */
  for (i = 0; i < N+2; i++) {
    life[i*(N+2)] = life[i*(N+2) + (N+1)] = DIES ;
    temp[i*(N+2)] = temp[i*(N+2) + (N+1)] = DIES ;
  }
  for (j = 0; j < N+2; j++) {
    life[j] = life[(N+1)*(N+2) + j] = DIES ;
    temp[j] = temp[(N+1)*(N+2) + j] = DIES ;
  }

  /* Initialize the life matrix */
  for (i = 1; i < N+1; i++) {
    for (j = 1; j< N+1; j++) {
      if (drand48() < 0.5) 
	life[i*(N+2) + j] = ALIVE ;
      else
	life[i*(N+2) + j] = DIES ;
    }
  }
  cudaDeviceSynchronize();

#ifdef DEBUG1
  /* Display the initialized life matrix */
  printf("Printing to file: output.%d.0\n",N);
  sprintf(filename,"output.%d.0",N);
  fp = fopen(filename, "w");
  printarray(life, N, N, fp);
  fclose(fp);
#endif

  t1 = gettime();
  /* Play the game of life for given number of iterations */
  for (k = 0; k < NTIMES; k += 2) {
    compute(life, temp, N, N);
    compute(temp, life, N, N);
  }
  t2 = gettime();

  int life_remaining = check_array(life, N, N);
  printf("Time taken for size = %d after %d iterations = %f\n",
          N, k, t2-t1);
  printf("No. of cells alive after %d iterations = %d\n",
          k, life_remaining);

#ifdef DEBUG1
  /* Display the life matrix after k iterations */
  printf("Printing to file: output.%d.%d\n",N,k);
  sprintf(filename,"output.%d.%d",N,k);
  fp = fopen(filename, "w");
  printarray(life, N, N, fp);
  fclose(fp);
#endif

  free(life);
  free(temp);

  return 0;
}
