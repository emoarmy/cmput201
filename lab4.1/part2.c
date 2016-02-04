#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isOdd(int num){
    return !((num%2) == 0);
}

int** buildInitialArray(int size){
    int** square = malloc(sizeof(int*)*(size));
    
    for(int i=0; i< size; i++){
        square[i] = malloc(sizeof(int)*size);
        for(int j=0; j<size; j++){
            square[i][j] = 0;
        }
    }
    
    return square;
}

int** create_magic_square(int size){
   int max = size*size;
   int middle=  size/2;
   int** square = buildInitialArray(size);
   int row = 1;
   int column = middle-1;
   
   for(int i=0; i<max; i++){
       int pass = 1;
       // starts at middle of column and works it's way from middle+1 until
       // it reaches the edge and raps around
       column = column == size-1 ? 0: column+1;
       row = row == 0 ? size-1: row -1;

       while(square[row][column] > 0){
           if(pass>1){
               row = (row == size-1) ? 0: row+1;
           } else {
               row = (row == size-1) ? 0: row+2;
               column =  (column == 0) ? size-1 : column-1;
           }
           pass++;
       }
       square[row][column] = i+1;
       
      
   }

   return square;
}

void print_magic_square(int** square, int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size;j++){
            printf("%i\t", square[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    int squareSize;
    int** square;
    
    //Grabbing initial input
    printf("This program creates a magic square if a specified size.\nThe size must be an odd number between 1 and 99.\n");
    printf("Enter size of magic square: ");
    scanf("%i", &squareSize);
    
    // Some basic error checking
    while(!isOdd(squareSize)){
        printf("The size must be an odd number between 1 and 99.\n");
        printf("Enter size of magic square: ");
        scanf("%i", &squareSize);
    }
    
    //Building and printing square
    square = create_magic_square(squareSize);
    print_magic_square(square, squareSize);
    free(square);
    
    return 0;
}
