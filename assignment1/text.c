#include <stdio.h>

FILE *fr;
int main(){
    //char line[80]; //create a character array that is of length 80
    char somechar;
    
    //printf("%s", argv[1]);
    fr = fopen("./test.txt", "rt");

    while(1){
        if (feof(fr)){
            // checking to see if we're pointing at end of the file
            break;
        }
        somechar = fgetc(fr);
        printf("%c", somechar);
    }
    fclose(fr);
    return 0;
}
