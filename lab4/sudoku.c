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


/////////////////////////////////////////////////
//
// Validation
//
////////////////////////////////////////////////
bool checkRows(int** square){
    for(int i=0; i<9; i++){
        int checkedArray[10] = {0};
        for(int j=0; j<9; j++){
            //column
            if(square[i][j] != 0 && checkedArray[square[i][j]] > 0){
                return false;
            } else {
                checkedArray[square[i][j]]++;
            }
        }
    }
    return true;
}

bool checkColumns(int** square){
     for(int i=0; i<9; i++){
        int checkedArray[10] = {0};
        for(int j=0; j<9; j++){
            //column
            if((square[j][i] > 0) && checkedArray[square[j][i]] > 0){
                return false;
            } else{
                checkedArray[square[j][i]]++;
            }
        }
    }
    return true;
}


bool checkGrid(int** square) {
    int r,c;

    for(int i=0; i<9; i++){
        int checkedArray[10] = {0};
        int row=(i/3)*3;
        int column=(i/3)*3;
        for(r=0;r<3;r++){
            for(c=0;c<3;c++){
                printf("%i ",square[row+r][column+c]); 
                if(square[row+r][column+c] > 0 && checkedArray[square[row+r][column+c]] > 0){
                    return false;
                } else {
                    checkedArray[square[row+r][column+c]]++;
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    return true;
}

bool checkPuzzle(int** square){
    bool rows;
    bool columns;
    bool grid;

    rows = checkRows(square);
    columns = checkColumns(square);
    grid = checkGrid(square);

    printf("Rows true?: %i\n", rows);
    printf("Columns true?: %i\n", columns);
    printf("Grid true?: %i\n", grid);
    return (rows && columns && grid);
}

int main(void){
    char filename[100];
    char** lines;
    int index;
    int** sudoku = malloc(sizeof(int*)*9);
    int size;
    printf("What file would you like to open?\n");
    scanf("%s", filename);
    
    lines = readFile(filename);
    index=0;
    
    
    for(int index=0; lines[index+1] != NULL; index++){
        printf("%s", lines[index]);
        sudoku[index] = splitNumbers(lines[index]);
        
    }
    checkPuzzle(sudoku);
    free(sudoku);
    free(lines);
    return 0;
}
