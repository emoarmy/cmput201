#include <stdio.h>

int main(void){
    int int1, int2, int3, int4;
    int smallest, largest;
    printf("Enter four integers: ");
    scanf("%d%d%d%d", &int1, &int2, &int3, &int4);
    
    smallest = largest = int1;

    printf("Largest: %i\n", largest);
    printf("Smallest: %i\n", smallest);
}
