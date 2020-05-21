#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


# define MAXITER 2000
//export OMP_NUM_THREADS=8

struct complex{
  double real;
  double imag;
};

int main(){

  double area, error, ztemp;
  double start, finish,start2,finish2;
  struct complex z, c;
  int i;
  int j;
  int iter;
  
    
  start2 = omp_get_wtime();

 #pragma omp parallel
 {
	int id = omp_get_thread_num();
	int nt = omp_get_num_threads();
	printf("Sou a thread %d de um total %d\n",id,nt);

  }
for (int NPOINTS=500; NPOINTS<=5000; NPOINTS+=500){
printf("NPOINTS = %1.2d \n",NPOINTS);
for (int k=0; k<4; k++){
printf("k = %1.2d \n",k);
int numoutside = 0;

  

/*
 *
 *
 *     Outer loops run over npoints, initialise z=c
 *
 *     Inner loop has the iteration z=z*z+c, and threshold test
 */

  start = omp_get_wtime();


  int i;
  int j;
  int iter;


#pragma omp parallel private (i,j,iter,c,z,ztemp) reduction(+:numoutside)
{

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
