#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct point{
         int idx;
         struct point *parent;
         int distance;
         struct point *child[7];
         int indegree;
} point;



//typedef struct point point;
int* splitNumbers(char* line, int number){
    //Split numbers in a string based on white space
    //This function does a little too much work as it, checks for errors and prints to screen as well
    int *array = malloc(sizeof(int)*number) ; // Hard coded because each line in the sample file has at most 2 ints.
    int number2;
    int count = 0;
    int offset = 0;
    int total_offset =  0;

    // check for a blank line
    if(strcmp(&line[0], " ") != 0){
        for(int i=0; (sscanf(line + total_offset, "%d%n", &number2, &offset))==1; i++){
            total_offset += offset;
            array[i] = number2;
            count++;
        }
    } else {
        array = NULL;
    }
   if(count == number){
       return array;
   } else {
       printf("File is corrupt, the instance file does not match specification\n");
       exit(EXIT_FAILURE);
   }
}

char** readFile(char* filename){
    // Takes a file name, and searches for that file in the same direcotry as the program is being executed
    // If it fails, to find a file it returns NULL otherwise it returns an array of \n terminated strings
    FILE *fp;
    size_t nBytes = 255;
    char** lines = malloc(1000*sizeof(char*));
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

bool isComment(char* line){
    // Returns true if the line starts with #
    if(strncmp(&line[0], "#", strlen("#"))==0){
        return true;
    } else {
        return false;
    }
}

int grabMST(char* line[], int** instance){
    int size = 0;
    int* temp;
    int index=0;
    for(int i=0; line[i] != NULL; i++){
        if(!isComment(line[i])){
            if(index >0){
                printf("Line: %s", line[i]);
                temp = splitNumbers(line[i],3);
                instance[size] = temp;
                size++;
            }
            index++;
        }
    }
    printf("\n%i\n", instance[0][0]);
    return size;
}

int findRoot(int** instance, int length){
    int count[length];
    int search;


    // initialize count to 0
    for(int i=0; i<length; i++){
        count[i] = 0;
    }

    // count all the indexes from 0 to length -1
    for(int i=0; i<length; i++){
       count[instance[i][1]]++;
    }
    
    // search through count for the index parent
    for(int i=0; i<length; i++){
        if(count[i]==0){
            search = count[i];
            break;
        }
    }
    //find this index in instance[i][0] and return it
    for(int i=0; i<length; i++){
        if(instance[i][0] == search){
            return i;
        }
    }
    return -1;
}

point* newPoint(int index, point* parent,int distance){
    point* newPoint = malloc(sizeof(point));
    newPoint->idx = index;
    newPoint->parent = parent;
    newPoint->distance = distance;
    newPoint->indegree = 0;

    for(int i=0; i< 7; i++){
        newPoint->child[i]=NULL;
    }
    return newPoint;
}

void buildTree(point* root, int** mst, int mst_length){
    for(int i=0; i< mst_length; i++){
        if(mst[i][0] == root->idx){
            //this must contain a child
            //static point child;
            point* child = newPoint(mst[i][1], root, mst[i][2]);
            root->child[root->indegree] = child;
            root->indegree++;
            buildTree(child, mst, mst_length);
        }
    }
    return;
};

void printList(point* node, int depth) {
    point* current = node;
    if (depth==0){
        printf("root is %i\n", current->idx);
    }
    for(int i =0; i< depth; i++){
            printf("\t");
    }
   printf("point[%i] has in-degree %i:\n", current->idx, current->indegree);
    for(int j=0; j< current->indegree; j++) {
        printList(current->child[j], depth+1);
    }
}

int main(void){
    char** lines;
    int size;
    int** mst = malloc(sizeof(int[3])*100);
    int mst_size;
    lines = readFile("sample.txt");
    size = 9;
    
    mst_size = grabMST(lines, mst);
    printf("%i", mst[0][0]);
    if(mst_size != size){
        printf("\nSomething  is messed up %i %i\n", mst_size, size);
        return -1;
    }
    for(int i=0; i<mst_size; i++){
        printf("%i %i %i\n", mst[i][0], mst[i][1], mst[i][2]);
    }

    point* root = newPoint(0, NULL, 0);
    buildTree(root, mst, mst_size);
    
    printList(root,0);
    
}
