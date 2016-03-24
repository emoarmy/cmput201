#include <stdio.h>
#include <string.h>

int main(void){
    char* phrase = "Enter word: ";
    char word[21];
    char longestWord[21];
    char shortestWord[21];
    int longCompare;
    int shortCompare;
    int flag = 0;

    do{
        printf("%s", phrase);
        scanf("%20s", word);

        if(flag == 0){
            strcpy(longestWord, word);
            strcpy(shortestWord, word);
            flag =1;
        }

        longCompare = strcmp(longestWord, word);
        shortCompare = strcmp(shortestWord, word);
        if(longCompare>0){
            strcpy(longestWord, word);

        }

        if(shortCompare < 0){
            strcpy(shortestWord, word);
        }
    } while(strlen(word) != 4);
    
    printf("Smallest word: %s\n", shortestWord);
    printf("Largest word: %s\n", longestWord);

}


