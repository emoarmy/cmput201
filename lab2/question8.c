#include <stdio.h>

float calcLoan(float current, float interest, float payment){
    return (current * interest) - payment;
}

void monthlyStatement(char* statement, float loan, float interest, float payment){
    char* month[]= {"first", "second", "third"};
    for(int i=0; i < 3; i++){
        loan = calcLoan(loan, interest, payment);
        printf(statement, month[i], loan);
    }
}

int main(void){
    float loan;
    float interest;
    float payment;
    
    
    printf("Enter amount of loan: ");
    scanf("%f", &loan);

    printf("Enter interest rate: ");
    scanf("%f", &interest);

    interest = 1 + (interest/ 1200);

    printf("Enter monthly payment: ");
    scanf("%f", &payment);
    monthlyStatement("Balance remaining after %s payment: %.2f\n", loan, interest, payment);
}
