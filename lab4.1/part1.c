#include <stdio.h>

void pb(int n){
    if(n!=0){
        pb(n / 2);
        putchar('0' + n % 2);
    }
}

int main(void){
    int num;
    printf("Please pick an integer: ");
    scanf("%i", &num);
    
    pb(num);
    printf("\n");
    return 0;
}
