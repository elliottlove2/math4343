#include <stdio.h>
#include <math.h>

//This is a program for homework assignment 2
//For practice, I have delt with the cases where any of the coefficients are 0. 




int main()
{
    double a, b, c;
    double disc;
    double root1, root2;

    
    printf("Please enter 3 real numbers\n");
    scanf("%lf%lf%lf", &a, &b, &c);
    printf("\nThe 3 numbers are %lf, %lf, and  %lf \n", a, b, c);
 
    /* Next we will check that the leading coefficient is non-zero.
       If it is zero, then the user has inputted a linear equation. 
       In this case we will print out the solution to the linear equation. 
    */
    if ( a == 0 ){
        if(b != 0){
            printf("You have inputted a linear equation, not a quadratic.\n");
            double lin_sol = -c/b;
            printf("The solution of this linear equation is %.3lf\n\n", lin_sol );
        }
        else{
            if(c != 0){
                printf("Your input polynomial is a non-zero constant.\nTry a more interesting polynomial.\n\n");
            }
            printf("Your input was (0, 0, 0).\nTry a more interesting polynomial \n\n");
        }
        
        return 0;       
    }   
    //Back to the quadratic case, we first find the discrinant.
    disc = pow(b, 2) - 4 * a * c;
    printf("Discriminant is %lf\n", disc);

    //Let's make sure we have no complex roots.
    if ( disc < 0 ){
        printf("This quadratic has complex roots.\n");
        float realpart = -b /(2 * a);
        float impart = sqrt(-disc)/(2 * a);
        printf("The roots are %lf + %lfi and %lf - %lfi\n\n", realpart, impart, realpart, impart);

        return 0;
    }

    root1 = -b/(2 * a) + (sqrt(disc))/ (2*a);
    root2 = -b/(2 * a) - (sqrt(disc))/ (2*a);

    printf("The solutions to your quadratic are %lf and %lf\n\n", root1, root2);

   return 0;
}


