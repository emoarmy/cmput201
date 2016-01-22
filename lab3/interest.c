#include <stdio.h>

float calcLoan(float current, float interest, float payment){
    return (current * interest) - payment;
}

void monthlyStatement(char* statement, float loan, float interest, float payment, int toMake){
    for(int i=0; i < toMake; i++){
        loan = calcLoan(loan, interest, payment);
        printf(statement, (i+1), loan);
    }
}

int main(void){
    float loan;
    float interest;
    float payment;
    int paymentsToMake;
    
    
    printf("Enter amount of loan: ");
    scanf("%f", &loan);

    printf("Enter interest rate: ");
    scanf("%f", &interest);


    interest = 1 + (interest/ 1200);

    printf("Enter monthly payment: ");
    scanf("%f", &payment);

    printf("How many payments would you like to make: ");
    scanf("%i", &paymentsToMake);
    monthlyStatement("Balance remaining after payment # %i: %.2f\n", loan, interest, payment, paymentsToMake);
}
