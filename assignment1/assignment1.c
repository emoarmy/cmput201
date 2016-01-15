#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fr;

int* getInput(char* prompt, int num_of_values){
    int *option = malloc(sizeof(int)*2);
    char newLine;
    printf("%s", prompt);
    for(int i = 0; i < num_of_values; i++){
        scanf("%d%c", &option[i], &newLine);
    }
    return option;
}

int* getOptions(void){
    int* max_x_y;
    int* num_pt;
    int* num_inst;
    
    max_x_y = getInput("Enter the circuit board size MAX_X MAX_Y: ");
    num_pt = getInput("Enter the number of points NUM_PT: ");
    num_inst = getInput("Enter the number of random instances to be generated: ");

    static int options[4];
    options[0] = max_x_y[0];
    options[1] = max_x_y[1];
    options[2] = num_pt[0];
    options[3] = num_inst[0]
 
    free(max_x_y);
    free(num_pt);
    free(num_inst);

    return options;
}

int main(int argc, char *argv[]){
    char* filename; 
    int max_x, max_y;
    int num_pt;
    int num_to_generate;

    /* if(argc > 1){ */
    /*     for(int i=0; argc > i; i++){ */
    /*         if(strcmp(argv[i], "-i")){ */
    /*             filename = argv[i+1]; */
    /*             break; */
    /*         } */
    /*     } */
    /* }else { */

    /* } */
    int* parameters;
    parameters =  getOptions();
    printf("%i %i %i %i\n", parameters[0], parameters[1], parameters[2], parameters[3]);
}
