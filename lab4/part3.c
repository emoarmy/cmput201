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
        for(int j=0; j<size; j++)
            {
                square[i][j] = 0;
            }
    }
    
    return square;
}

int** buildSquare(int size){
   int max = size*size;
   int middle=  size/2;
   int** square = buildInitialArray(size);
   int row;
   int column;
   
   
   for(int i=0; i<max; i++){
       // starts at middle of column and works it's way from middle+1 until
       // it reaches the edge and raps around
       column = size - (size - ((middle+i) % size));
       row = ((size - ((i)%size))%size);
       printf("column: %i\trow: %i\tvalue: %i\n", column, row,  i+1);
       while(square[row][column] > 0){
           printf("Correction...\n");
           printf("column: %i\trow: %i\tvalue: %i\n", column, row,  i+1);
           row = row == size-1 ? 0: row+1;
       }
       square[row][column] = i+1;
   }
   
   return square;
}

void printSquare(int** square, int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size;j++){
            printf("%i ", square[i][j]);
        }
        printf("\n");
    }
    return;
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
    square = buildSquare(squareSize);
    printSquare(square, squareSize);
    free(square);
    
    return 0;
}
