#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool isPalindrome(char* toCheck, int length);

bool isPalindromePointer(char* toCheck, int length);


int main(void){
    char* toCheck = malloc(sizeof(char)*100);
    char temp;
    int index;
    printf("Please enter a message: ");
    
    while(scanf("%c", &temp)!=0 && temp != '\n'){
       if(isalpha(temp) !=0){
           toCheck[index] = tolower(temp);
           
           index++;
       }
    }

    if(isPalindrome(toCheck, index)){
        printf("Is a palindrome \n");
    } else {
        printf("Not a palindrome \n");
    }

    printf("Pointers\n");
     if(isPalindrome(toCheck, index)){
        printf("Is a palindrome \n");
    } else {
        printf("Not a palindrome \n");
    }
    return 0;
}


bool isPalindrome(char* toCheck, int length){

    for(int i=0; i< length; i++){
        if(toCheck[i] != toCheck[length-1-i]){
            return false;
        }
    }
    return true;
  
}

bool isPalindromePoint(char *toCheck, int length){
    char* end = toCheck + length;
    while(&toCheck != &end){
        if(*toCheck != *end){
            return false;
        }
        toCheck++;
        end--;
    }
    return true;
}

