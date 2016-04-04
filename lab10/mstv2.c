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


int* splitNumbers(char* line, int number);

char** readFile(char* filename);

bool isComment(char* line);

int grabMST(char* line[], int** instance);

int findRoot(int** instance, int length);

point* newPoint(int index, point* parent,int distance);

void buildTree(point* root, int** mst, int mst_length);

void printList(point* node, int depth);

void freeMST(int** instance, int length);


int main(void){
    char** lines;
    int size;
    int** mst = malloc(sizeof(int[3])*100);
    int mst_size;
    char* name= malloc(sizeof(char)*100);
    int index=0;
    char temp;


    printf("Filename: ");

    while(scanf("%c", &temp)!=0 && temp != '\n' && index < 100){
        name[index] = temp;
        index++;
    }
    printf("name %s", name);
    lines = readFile(name);

    mst_size = grabMST(lines, mst);

    if(mst_size < 1){
        printf("\nSomething  is messed up %i %i\n", mst_size, size);
        return -1;
    }

    point* root = newPoint(0, NULL, 0);
    buildTree(root, mst, mst_size);

    printList(root,0);

    freeMST(mst, mst_size);
}


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
                temp = splitNumbers(line[i],3);
                instance[size] = temp;
                size++;
            }
            index++;
        }
    }
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
    if(current->indegree >0){
        printf("point[%i] has in-degree %i:\n", current->idx, current->indegree);
    } else {
        printf("point[%i] has in-degree %i//\n", current->idx, current->indegree);
    }
    for(int j=0; j< current->indegree; j++) {
        printList(current->child[j], depth+1);
    }
}

void freeMST(int** instance, int length){
    for(int i =0; i< length; i++){
        free(instance[i]);
    }
    free(instance);
    return;
}
