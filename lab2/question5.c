#include <stdio.h>
#include <string.h>

void printRows(int list[4][4], int len){
    int *array;
    for(int i=0; i<len; i++){
        array = list[i];
        printf("%i %i %i %i \n", array[0], array[1], array[2], array[3]);
    }
}

void sumRows(int list[4][4], int len){
    int sum[4];
    int* row;
    for(int i=0; i < len; i++){
        row = list[i];
        sum[i] = row[0] + row[1] + row[2] + row[3];
    }
    printf("\n");

}

void sumColumns(int list[4][4], int len){
    int sum[4];
    for(int i=0; i < len; i++){
        sum[i] = list[i][0] + list[i][1] + list[i][2] + list[i][3];

    }
    printf("\n");
}

void sumDiagonal(int list[4][4], int len){
    int sumDiag1 = 0;
    int sumDiag2 = 0;
    for(int i=0; i<len; i++){
        sumDiag1 += list[i][i];
        sumDiag2 += list[i][len-i];
    }
    printf("%d \n", sumDiag1);
    printf("%d \n", sumDiag2);
    printf("\n");
}


int main(void){
    int input[16];
    int list[4][4];

    printf("Enter numbers: ");
    for(int i=0; i<16; i++){
        scanf("%d", &input[i]);
    }
    
    int row = -1;
    for(int j=0; j<16; j++){
        if(j%4 == 0){
            row++;
        }
        list[row][j%4] = input[j];
        printf("row %i \n", row);
    }
    printRows(list, 4);
    sumRows(list, 4);
    sumColumns(list, 4);
    sumDiagonal(list, 4);
}
