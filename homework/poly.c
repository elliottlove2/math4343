#include<stdio.h>
#include<math.h>

double polyn(double x){
    double result = 0;

    int d[10];
    for (int i=0; i<10; i++){
        d[i] = i+1;
    }
    for (int i=0; i<10; i++){
        result += d[i] * pow(x,i);
    }
    return result;
}

int main(){
    double x, result;
    printf("Enter a number.\n");
    scanf("%lf", &x);

    result = polyn(x);
    printf("The polynomial evaluated at %lf is %lf", x, x);

    return 0;
}