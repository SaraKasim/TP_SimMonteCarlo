// simulator of exponential law
// computes the mean value
// usage: expo lambda N


#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// Our random generator

 #define norm 2.328306549295728e-10
 #define m1   4294967087.0
 #define m2   4294944443.0
 #define a2    1403580.0
 #define a3    810728.0
 #define b1    527612.0
 #define b3    1370589.0

 static double
    s10 = 12345, s11 = 12345, s12 = 123,
    s20 = 12345, s21 = 12345, s22 = 123;

 double MRG32k3a (void)
 {
    long   k;
    double p1, p2;
    
    /* Suite x */
    p1 = a2*s11 - a3*s10;
    k = p1 / m1;
    p1 -= k*m1;
    if (p1 < 0.0) p1 += m1;
    s10 = s11;   s11 = s12;   s12 = p1;

    /* Suite y */
    p2 = b1*s22 - b3*s20;
    k  = p2 / m2;
    p2 -= k*m2;
    if (p2 < 0.0) p2 += m2;
    s20 = s21;   s21 = s22;   s22 = p2;

    /* Combinaison */
    if (p1 <= p2) return ((p1 - p2 + m1)*norm);
    else return ((p1 - p2)*norm);
 }


// End of generator

double expo(double rate)
{
  return(-log(MRG32k3a())/rate);
}

int main(int nbOfPars, char* *pars)
{
  double lambda;
  long N;
  long i;
  double sum = 0;
  double sum2 = 0;
  double value;
  double variance,stdvar;


  lambda = atof(pars[1]);
  N = atol(pars[2]);

	   for (i=1;i<=N;i++)
	     {
	      value=  expo(lambda);
	      sum += value;
	      sum2 += value*value;
	     }

	   printf("\n\n The average value for N=%ld is: %.4e\n\n",N, sum/N);

	   variance = (sum2-sum*sum/N)/(N-1);
	   stdvar = sqrt(variance/N);

	   printf("0.90 confidence interval: (%.4e, %.4e)\n",sum/N-1.645*stdvar, sum/N+1.645*stdvar);
	   printf("0.95 confidence interval: (%.4e, %.4e)\n",sum/N-1.96*stdvar, sum/N+1.96*stdvar);
	   printf("0.99 confidence interval: (%.4e, %.4e)\n",sum/N-2.58*stdvar, sum/N+2.58*stdvar);
}
