#include <stdio.h>
#include <math.h>
double newtonSquare(double x){
    double y = 1;
    double product;
    double avg;
    double diff;
    
   do{
        product = x/y;
        avg = (y + product)/2;
        diff = fabs(y- avg);
        y = avg;
    } while(diff > (y*0.00001));
    return y;
}

int main(void){
    double sqrRt;
    printf("Enter a positive number: ");
    scanf("%lf", &sqrRt);
    
    printf("Square root: %.5lf\n", newtonSquare(sqrRt));
}
