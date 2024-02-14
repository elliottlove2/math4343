#include<stdio.h>
#include<math.h>

//Sterling Approximation,  Homework 2

//Factorial function
double factorial(int n){
    double result =1.0;
    int i;

    for (i=1;  i<=n; i++){
        result *= i;
}       
    return result;
}

//Approximation of n!
double stirling(int n){
    double result;
    result = sqrt(2 * n * M_PI) * pow((n / M_E), n);
    return result;
}

//absolute error function
double absolute_error(double x, double y){
    return fabs(x-y);
}

//relative error functionf
double relative_error(double x, double y){
    return (fabs(x-y))/fabs(x);
}

int main()
{
    int n;
    double actual, approx;
    double rel_err, abs_err;

    for(n=1; n<=10; n++){
        //defining the values of interest
        actual = factorial(n);
        approx = stirling(n);
        rel_err = relative_error(actual, approx);
        abs_err = absolute_error(approx, actual);

        //printing the results
         printf("%-2d%13g%15g%15g%10g\n", n, actual, approx, rel_err, abs_err);
    }

   

    
   return 0;
}
