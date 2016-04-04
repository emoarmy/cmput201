#include "plane.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "BST.h"

FILE *fp;
////////////////////////////////////////////////
// BST
//
////////////////////////////////////////////////

int rectDistance(int* coordA, int* coordB){
    // find the rectilinear distance of two coordinates
    return (abs(coordA[0] - coordB[0]) + abs(coordA[1] - coordB[1]));
}

int* copyInstance(int* instance, int len){
    //this is WTF code, need to think about this some more
    int* newInstance = malloc(sizeof(int)*len+1);
    memcpy(newInstance, instance, len);
    return newInstance;
}

int* addVisited(int* visited, int len,  int newPoint){
    // Return a new array that incudes the new point
    // Dead code
    int* newVisited;
    newVisited = copyInstance(visited, len);
    newVisited[len] = newPoint;
    return newVisited;
}

void removeVisited(int* unvisited, int len, int pos){
    // Delete elements from an array, such that it keeps all undeleted values in a contiguous section of the array
    int index = 0;
    for(int i=0; i<len; i++){
        if(unvisited[i] != pos){
            unvisited[index] = unvisited[i];
            index++;
        }
    }
}


int** prims(Plane plane){
    // Returns a MST of format indices1, indice2, weight;
    int visited[plane.instance_size];
    int unvisited[plane.instance_size];
    int* newEdge;
    int sizeUnvisited = plane.instance_size-1;
    int sizeVisited = 0;
    int** MST =  malloc(sizeof(int)*3*plane.instance_size);

    //initialize unvisited
    for(int i=0; i < plane.instance_size-1; i++){
      unvisited[i] = i+1;
    }
    // Set an arbitrary starting point
    visited[0] = 0;

    // Go through ta set of coordinates and create a MST according to prim's algorithm
    // Prim's algorithm:
    // Arbitrarily choose a starting node
    // Find the shortest distance between the starting node and all nodes that it can connect to
    // add the new node, that has the smallest distance, to visited.
    // Now, until you have visited all nodes, find the minimum distance of all nodes from visited
    // to unvisited
    while(sizeUnvisited >0){
       newEdge = findMin(plane.instance, visited, sizeVisited,  unvisited, sizeUnvisited);
       MST[sizeVisited] = newEdge;
       sizeVisited++;
       visited[sizeVisited] = newEdge[1];
       removeVisited(unvisited, sizeUnvisited, newEdge[1]);
       sizeUnvisited--;
    }
    return MST;

}

int* findMin(int** coords, int* visited, int visitedSize, int* unvisited, int unvisitedSize){
    int minNodeUnvis;
    int minNodeVis;
    int currentDistance;
    int minDistance;
    int* edge = malloc(sizeof(int)*3);
    // Algorithm for finding the minimum distance between two arrays of coordinates
    //i = index of visited array
    for(int i=0; i== 0 || i < visitedSize+1; i++){
        //j = index of unvistied array
        for(int j=0; j < unvisitedSize; j++){
            // calculate the distance between visited[i] and visited[j]
            currentDistance = rectDistance(coords[visited[i]], coords[unvisited[j]]);
            if(i==0 && j==0){
                // if this is the first run through of the for loop set current distance to minDistance and mark
                // each node as visited
                minDistance = currentDistance;
                minNodeUnvis = unvisited[j];
                minNodeVis = visited[i];
            } else if(currentDistance < minDistance){
                // if current distance is less then min distance assign this new combination to minDistance
                minDistance = currentDistance;
                minNodeUnvis = unvisited[j];
                minNodeVis = visited[i];minDistance = currentDistance;

            } else if(currentDistance == minDistance){
                //If there is a tie, reassign minNodeUnvis with return value of breakTie
                minNodeUnvis = breakTie(coords, visited[i], unvisited[j], minNodeUnvis);
                minNodeVis = visited[i];
            }
        }
    }
    edge[0] = minNodeVis;
    edge[1] = minNodeUnvis;
    edge[2] = minDistance;
    return edge;
}

int breakTie(int** coords, int visited, int unvisited, int minNodeUnvis){
    // Breaks the tie by returning the point with the larger delata Y value
    // If delta y values are same, choose the one with highest x value
    // if both x values are the same, choose the minNodeUnvis
    if(abs(coords[minNodeUnvis][1] - coords[visited][1]) > abs(coords[unvisited][1] - coords[visited][1])){
        // Check to see if delta y of MinNode is larger
        return minNodeUnvis;
    } else if(abs(coords[unvisited][1] - coords[visited][1]) > abs(coords[minNodeUnvis][1] - coords[visited][1])){
        // Check to see if delta y of unvisited is largers
        return unvisited;
    } else{
        // find MaxX
        return maxX(coords, minNodeUnvis, unvisited);
    }
}

int maxX(int** coords, int minNodeUnvis, int unvisited){
    //return the max of two ints, in the event of a tie the first int is chosen.
    return coords[unvisited][0] > coords[minNodeUnvis][0]? unvisited: minNodeUnvis;
}

void appendWeight(int* instance, FILE* filename){
    fprintf(filename, "# edges of the MST by Prim’s algorithm:\t");
    fprintf(filename, "%i %i %i", instance[0], instance[1], instance[2]);
}

int totalWeight(int** MST, int length){
    int total = 0;
    for(int i=0; i<length; i++){
        total += MST[i][2];
    }
    return total;
}

int* nodeDegree(int** MST, int size){
    int* degrees = malloc(sizeof(int)*(size+1));
    int count;
    for(int i=0; i< size+1; i++){
        count=0;
        for(int j=0; j< size; j++){
            if(MST[j][0] == i || MST[j][1] ==i){
                count++;
            }
        }
        degrees[i]=count;
    }
    return degrees;
}

void printMST(int** MST,int size,char* filename, char* options){
    // Determine, based on the options being passed in, how to print the given Plane
    if(options != NULL && strcmp(options, "output")==0){
        //if option output, print to a file
        fp = fopen(filename, "a");
        fprintf(fp, "# edges of the MST by Prim’s algorithm:\n");
        for(int i=0; i < size-1; i++){
            fprintf(fp, "%i %i %i\n", MST[i][0], MST[i][1], MST[i][2]);
        }
        fprintf(fp, "# total weight of the MST by Prim's algorithm is %i\n", totalWeight(MST, size-1));
        fclose(fp);
    } else {
        //print to terminal
        printf( "# edges of the MST by Prim’s algorithm:\n");
        for(int i=0; i < size-1; i++){
            printf("%i %i %i\n", MST[i][0], MST[i][1], MST[i][2]);
        }
        printf("# total weight of the MST by Prim's algorithm is %i\n", totalWeight(MST, size-1));
    }
}
