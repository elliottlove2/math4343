# include <stdio.h>
# include <math.h>

int main(){
    int a = 0;
    int b = 0;
    int c = 0;
    printf("Enter 2 integers.\n");
    scanf("%d %d", &a, &b);
    c = a*b;
    printf("The product of %d and %d is %d \n", a, b, c);

    return 0;
}

