#include <stdio.h>

int totalBills(int amount, int* bills, int len, char* phrase){
    // This is making the assumption that the array is sorted
    int billsUsed;
    for(int i=0; i < len; i++){
        billsUsed = amount / bills[i];
        amount = (amount % bills[i]);
        printf(phrase, bills[i], billsUsed);
    }
    return amount;
}

int main(void){
    int amount;
    int billTypes[] = {20, 10, 5, 1};
    printf("Enter a dollar amount: ");
    scanf("%i", &amount);
    totalBills(amount, billTypes, 4,"$%i bills : %i\n");
}


