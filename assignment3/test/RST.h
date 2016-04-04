
void calcRST(int** instance, int** MST, int instance_length);

int findSharedPath(int** MST, int start, int index);

void calcRST(int** instance, int** MST, int instance_length);

int findSharedPath(int** MST, int start, int index);

int findSharedPath(int** MST, int start, int index);

int calcOverlap(Path pathA, int posSharedA, Path pathB);

int findSharedNode(int** MST,int pathIndexA, int pathIndexB);

int findMaxOverlap(RST steinerTree, Path currentPath,int** MST, int index);

int findSharedAxis(Path pathA, Path pathB);

void calcRSTrecursive(RST steinerTree, int** instance, int** MST,int axis, int length);

bool inRange(int number, int coord1, int coord2);

Path buildPath(int* node1, int* node2, int axis);

void calcRST(int** instance, int** MST, int instance_length){
    RST tree;
    printf("calcRST: ");
    printf("%i\n", instance[0][0]);
    calcRSTrecursive(instance, MST, instance_length-1)
    return tree;
}

int findSharedPath(int** MST, int start, int index){
    int startNode = MST[index][0];
    int endNode = MST[index][1];
    // Grab the X and Y ranges of
    for(int i=start; i<index; i++){
        //for start and end every node in RST check to see if they match with
        //start or end node of Path
        if(MST[i][0] == startNode || MST[i][1] == startNode || MST[i][0] == endNode
        MST[i][1] == startNode){
            return i;
        };
    }
    return -1
}


int calcOverlap(Path pathA, int posSharedA, Path pathB){
    int overLap = 0;
    int* midpointA = pathA[1];
    int* midpointB = pathB[1];

    int sharedAxis = findSharedAxis(pathA, pathB);

    if(sharedAxis==-1 || sharedAxis > 1){
        return 0;
    }
    if(midpointA[sharedAxis] > pathA[posSharedA][sharedAxis] &&
             midpointB[sharedAxis] > pathB[posSharedB][sharedAxis]){
    // if both midpointA and midpointB exist on the graph after the point of their
    // shared node, there is overlap
    // Subtract the path
        if(midpointA[sharedAxis] > midpointB[sharedAxis]){
            return midpointB[sharedAxis] - pathB[posSharedB][sharedAxis];
        } else{
            return midpointA[sharedAxis] - pathA[posSharedB][sharedAxis];
        }

    } else if(midpointA[sharedAxis] < pathA[posSharedA][sharedAxis] &&
                 midpointB[sharedAxis] < pathB[posSharedB][sharedAxis]){
    // if both midpointA and midpointB exist on the graph before the point of their
    // shared node, there is overlap
        // Find which point is closer to their point in the shared node and
        //subtract that from the sharedAxis position
        if(midpointA[sharedAxis] > midpointB[sharedAxis]){
            return pathA[posSharedA][sharedAxis] - midpointA[sharedAxis];
        } else{
            return pathB[posSharedB][sharedAxis] - midpointB[sharedAxis];
        }
    }
}

int findSharedNode(int** MST,int pathIndexA, int pathIndexB){
    //find the node that PathA has in common with PathB and return the index of the node form A
    if(MST[pathIndexA][0] == MST[pathIndexB][0] || MST[pathIndexA][0] == MST[pathIndexB][1]){
        return 0;
    } else if(MST[pathIndexA][1] == MST[pathIndexB][0] || MST[pathIndexA][1] == MST[pathIndexB][1]){
        return 1
    }

    return -1;
}

int findMaxOverlap(RST steinerTree, Path currentPath,int** MST, int index){
    int start=0;
    int currentPath = MST[index];
    int sharedAxis;
    int pathIndex;
    int overlap = 0;
    int maxOverlap= 0;

    do {
        start= findSharedPath(MST, start, index);
        if(start => 0){
            sharedAIndex = findSharedNode(MST, index, start);
            overlap = calcOverlap(currentPath, sharedAIndex, steinerTree[start]);
        }
        if(overlap > maxOverlap){
            maxOverlap = overlap;
        }
    }while(start != -1 && start < index);
    return maxOverlap;
}

int findSharedAxis(Path pathA, Path pathB)
{
    // Returns the shared axis of both Paths, if any exists. Where 0 = x, 1 = y
    // and -1 means a path is not shared.
    // We can tell what axis is shared between two paths by checking if the
    // x or y of their midpoints lie on the same axis
    if(pathA[1][0] == pathB[1][0]){
        return 0;
    } else if(pathA[1][1] == pathB[1][1]){
        return 1;
    }
    return -1;
}

void calcRSTrecursive(RST steinerTree, int** instance, int** MST,int axis, int length){
    if(length == 0){
        return;
    } else {
        Path currentPath = buildPath(instance[MST[index][0]], instance[MST[index][0]]);
        int maxOverlap = findMaxOverlap(steinerTree, MST, currentPath);
        minimizedDistance = Distance - maxOverlap;
        distX = calcRSTrecursive(newTree, instance, MST, 0, length-1);
        distY = calcRSTrecursive(newTree, instance, MST, 1, length-1);
        return shortestDistance;
    }
}

bool inRange(int number, int coord1, int coord2){
    if(coord1 < coord2){
        return (number => coord1 && number =< coord2);
    } else if(coord1 > coord2) {
        return (number => coord2 && number =< coord1);
    } else {
        return false;
    }
}

Path buildPath(int* node1, int* node2, int axis){
    int node3[2] ={0,0};
    Path path = malloc(sizeof(int)*6);
    if(axis == 0){
        //midpoint on x axis
        node3[0] = node2[0];
        node3[1] = node1[1];
    } else {
        //midpoint on y axis
        node3[0] = node1[0];
        node3[1] = node2[1];
    }
    path[0]=node1;
    path[1]=node2;
    path[2]=node3;
    return path;
}
