#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
FILE *fp;

#define SQUARE 9
/////////////////////////////////////////////////
//
// SETTERS
//
////////////////////////////////////////////////
char** readFile(char* filename);

int* splitNumbers(char* line);

/////////////////////////////////////////////////
//
// Validation
//
////////////////////////////////////////////////
bool checkRows(int** square);

bool checkColumns(int** square);

bool checkGrid(int** square);

bool checkPuzzle(int** square);

////////////////////////////////////////////////
//
//Solving
//
///////////////////////////////////////////////
bool solveSudoku(int** square);

int* findUnassigned(int** square);


bool isValid(int** square, int row, int col,int number);

bool inRow(int** square, int row, int number);

bool inColumn(int** square, int col, int number);

bool inGrid(int** square, int initRow, int initCol, int number);

void printSquare(int** square);


int main(void){
    char filename[100];
    char** lines;
    int index;
    int** sudoku = malloc(sizeof(int*)*9);
    bool validSudoku;
    printf("What file would you like to open?\n");
    scanf("%s", filename);

    lines = readFile(filename);

    for(int index=0; lines[index+1] != NULL; index++){
        printf("%s", lines[index]);
        sudoku[index] = splitNumbers(lines[index]);

    }
    validSudoku = checkPuzzle(sudoku);


    clock_t start, end;
    double cpu_time_used;
    start = clock();
    if(validSudoku){
        solveSudoku(sudoku);
    }
    end = clock();
    printf("Time taken  = %f \n", ((double)(end-start))/CLOCKS_PER_SEC);
    printSquare(sudoku);
    free(sudoku);
    free(lines);
    return 0;
}


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
    int *array = malloc(sizeof(int)*SQUARE) ; // Hard coded because each line in the sample file has at most 2 ints.
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
     for(int i=0; i<SQUARE; i++){
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

    for(int i=0; i<SQUARE; i++){
        int checkedArray[10] = {0};
        int row=(i/3)*3;
        int column=(i/3)*3;
        for(r=0;r<3;r++){
            for(c=0;c<3;c++){
                if(square[row+r][column+c] > 0 && checkedArray[square[row+r][column+c]] > 0){
                    return false;
                } else {
                    checkedArray[square[row+r][column+c]]++;
                }
            }
        }
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

//////////////////////////////////////////////////////
//
// Solving
//
/////////////////////////////////////////////////////
bool solveSudoku(int** square){
    int* unassigned;
    int row;
    int col;

    unassigned = findUnassigned(square);

    if(unassigned[0] == -1){
        return true;
    }
    row = unassigned[0];
    col = unassigned[1];

    for (int number = 1; number<10; number++){
        if(isValid(square, row, col, number)){
            square[row][col] = number;
            if(solveSudoku(square)){
                free(unassigned);
                return true;
            }

            square[row][col] = 0;
        }
    }
    free(unassigned);
    return false;
}

int* findUnassigned(int** square){
    int* unassigned = malloc(sizeof(int)*2);
    for (int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(square[row][col] == 0){
                unassigned[0] = row;
                unassigned[1] = col;
                return unassigned;
            }
        }
    }
    unassigned[0] = -1;
    unassigned[1] = -1;
    return unassigned;
}

bool isValid(int** square,int row, int col, int number){
    return !inRow(square, row, number) && ! inColumn(square, col, number) && !inGrid(square, row - row%3, col-col%3, number);
}

bool inRow(int** square, int row, int number){
    for (int col=0; col < 9; col++){
        if(square[row][col] == number){
            return true;
        }
    }
    return false;
}

bool inColumn(int** square,int col,int number){
    for (int row=0; row < 9; row++){
        if(square[row][col] == number){
            return true;
        }
    }
    return false;
}

bool inGrid(int** square, int initRow, int initCol, int number){
    for(int row=initRow; row< initRow+3; row++){
        for(int col=initCol; col< initCol+3; col++){
            if (square[row][col]==number){
                return true;
            }
        }
    }
    return false;
}

void printSquare(int** square){
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            printf("%i ", square[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}
