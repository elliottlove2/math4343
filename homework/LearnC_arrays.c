# include <stdio.h>
# include <math.h>

float average(){
   int array[4];
   array[0]=6;
   array[1]=15;
   array[2]=1;
   array[3]=43;
   float sum = 0;
   int i =0;

   do{
    sum = sum + array[i];
    i++;
   } while( i<4 );

    float avg = sum / 4;

   return avg;

}

int main(){
   int array[4];
   array[0]=6;
   array[1]=15;
   array[2]=1;
   array[3]=43;

   float result = average();

   printf("The average of the array is %.2f\n", result);

    return 0;
}

