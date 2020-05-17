#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 2000
# define MAXITER 2000


struct complex{
  double real;
  double imag;
};

int main(){
printf("\nOla 1 - FORA DA REGIAO PARALELA ...\n\n");
    printf("teste\n");
  int numoutside = 0;
  double area, error, ztemp;
  double start, finish;
  struct complex z, c;

/*
 *
 *
 *     Outer loops run over npoints, initialise z=c
 *
 *     Inner loop has the iteration z=z*z+c, and threshold test
 */

  start = omp_get_wtime();
  
  omp_set_num_threads(4);

#pragma omp parallel private (c,z)
{
int id = omp_get_thread_num();
int nt = omp_get_num_threads();
printf("Sou a thread %d de um total %d\n",id,nt);
 #pragma omp for
  for (int i=0; i<NPOINTS; i++) {
    for (int j=0; j<NPOINTS; j++) {
      c.real = -2.0+2.5*(double)(i)/(double)(NPOINTS)+1.0e-7;
      c.imag = 1.125*(double)(j)/(double)(NPOINTS)+1.0e-7;
      z=c;
      for (int iter=0; iter<MAXITER; iter++){
	ztemp=(z.real*z.real)-(z.imag*z.imag)+c.real;
	z.imag=z.real*z.imag*2+c.imag;
	z.real=ztemp;
	if ((z.real*z.real+z.imag*z.imag)>4.0e0) {
	  numoutside++;
	  break;
	}
      }
    }
  }
}

  finish = omp_get_wtime();

/*
 *  Calculate area and error and output the results
 */

      area=2.0*2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
      error=area/(double)NPOINTS;

      printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
      printf("Time = %12.8f seconds\n",finish-start);

  }
