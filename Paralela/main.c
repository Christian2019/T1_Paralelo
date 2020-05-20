#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//# define NPOINTS 2000
# define MAXITER 2000


struct complex{
  double real;
  double imag;
};

int main(){
int numoutside = 0;
  double area, error, ztemp;
  double start, finish,start2,finish2;
  struct complex z, c;
   int i;
  int j;
  int iter;
  start2 = omp_get_wtime();
for (int NPOINTS=500; NPOINTS<5000; NPOINTS+=500){
for (int x=0; x<4; x++){
printf("\nOla 1 - FORA DA REGIAO PARALELA ...\n\n");

  

/*
 *
 *
 *     Outer loops run over npoints, initialise z=c
 *
 *     Inner loop has the iteration z=z*z+c, and threshold test
 */

  start = omp_get_wtime();
<<<<<<< HEAD
  
  
 
=======

  int i;
  int j;
  int iter;
>>>>>>> c03f166e9206168d209d82775809f7df86cf2961

#pragma omp parallel private (i,j,iter,c,z,ztemp) reduction(+:numoutside)
{
int id = omp_get_thread_num();
int nt = omp_get_num_threads();
printf("Sou a thread %d de um total %d\n",id,nt);
 #pragma omp for
  for ( i=0; i<NPOINTS; i++) {
    for ( j=0; j<NPOINTS; j++) {
     
      c.real = -2.0+2.5*(double)(i)/(double)(NPOINTS)+1.0e-7;
      c.imag = 1.125*(double)(j)/(double)(NPOINTS)+1.0e-7;
      z=c;
     
      for (iter=0; iter<MAXITER; iter++){
	
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
}
finish2 = omp_get_wtime();
printf("Total Time = %12.8f seconds\n",finish2-start2);
  }
