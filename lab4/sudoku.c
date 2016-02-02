#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
FILE *fp;
/////////////////////////////////////////////////
//
// SETTERS
//
////////////////////////////////////////////////
char** readFile(char* filename){
    size_t nBytes = 255;
    char **lines = malloc(1000*sizeof(char*));
    lines[0] = NULL;

    fp = fopen(filename, "rt");
    if (fp == NULL){
        return NULL;
    }
    int index =0;
    while(feof(fp) == 0){
        getline(&lines[index], &nBytes, fp);
        index++;
    }
    lines[index+1] = NULL;
    fclose(fp);
    return lines;
}

int* splitNumbers(char* line){
    int *array = malloc(sizeof(int)*9) ; // Hard coded because each line in the sample file has at most 2 ints.
    char **delim;
    char* argv[10];
    delim = argv;
    if(strcmp(&line[0], " ") != 0){
        // this line is magic
        for(int i=0; (*delim = strsep(&line, " ")) != NULL; i++){
            array[i] = atoi(*delim);
        }
    } else {
        array = NULL;
    }
   return array;
}

bool checkRows(int** square){
    for(int i=0; i<9; i++){
        int checkedArray[9] = {0};
        for(int j=0; j<9; j++){
            //column
            if(square[i][j] != 0 && checkedArray[square[i][j]] > 0){
                return false;
            }
        }
    }
    return true;
}

bool checkColumns(int** square){
     for(int i=0; i<9; i++){
        int checkedArray[9] = {0};
        for(int j=0; j<9; j++){
            //column
            if(square[j][i] != 0 && checkedArray[square[i][j]] > 0){
                return false;
            }
        }
    }
    return true;
}

int checkGrid(int** square, int row, int column) {
    row=(row/3)*3;
    column=(column/3)*3;
    int r,c;
    int checkedArray[9] = {0};
    for(int i=0; i<3; i++){
        row=(i)*3;
        column=(i)*3;
        for(r=0;r<3;r++){
            for(c=0;c<3;c++){
                if(square[row+r][column+c] != 0 && checkedArray[square[row+r][column+c]] > 0){
                    return false;
                }
            }
        }
    }
    return true;
}


int main(void){
    char filename[100];
    char** lines;
    int index;
    int** sudoku = malloc(sizeof(int*)*9);
    int size;
    bool rows;
    bool columns;
    printf("What file would you like to open?\n");
    scanf("%s", filename);
    
    lines = readFile(filename);
    index=0;
    
    
    for(int index=0; lines[index+1] != NULL; index++){
        printf("%s", lines[index]);
        sudoku[index] = splitNumbers(lines[index]);
        
    }
    
    rows = checkRows(sudoku);
    columns = checkColumns(sudoku);
    
    printf("Rows true?: %i\n", rows);
    printf("Columns true?: %i\n", columns);
    printf("Columns true?: %i\n", grid);
    free(sudoku);
    free(lines);
    return 0;
}
