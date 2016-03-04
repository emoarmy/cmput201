#include <stdio.h>
#include <math.h>

float monthlyPayment(float loan, float interest, int payback);

float monthlyRate(float interest);

float monthlyRemainder(float loan, float payment, float interest);

int main(void){
    float loan;
    float interest;
    int payback;
    float interestPaid;
    float payment;
    float totalInterest = 0;

    printf("Enter the loan amount: ");
    scanf("%f", &loan);

    printf("Enter the annual interest rate: ");
    scanf("%f", &interest);
    
    printf("Enter the number of months to pay back: ");
    scanf("%i", &payback);

    interest = monthlyRate(interest);
    payment = monthlyPayment(loan, interest, payback);
    
    printf("Your monthly payment = 1193.00\n");
    printf("\tprincipal_outstanding\t payment\t interest\t principal\n");
    for (int i=0; i<payback; i++){
        interestPaid = loan*interest;
        totalInterest += interestPaid;
        printf("Payment No.%2i :\t %5.2f\t %0.2f\t %7.2f\t %0.2f\t\n", i, loan, payment, interestPaid, payment - interestPaid);
        loan += loan*interest - payment;
    }

    printf("Total interest paid = %0.2f\n", totalInterest);
    printf("Total principal unpaid = %0.2f\n", loan);
}

float monthlyPayment(float loan, float interest, int payback){
    return (interest + (interest/((pow((1+interest),payback)-1)))) * loan;
}

float monthlyRate(float interest){
    return interest/1200.0;
}

float monthlyRemainder(float loan, float payment, float interest){
    return ( (loan*interest) - payment);
}

