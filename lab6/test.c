find_min_dist(int* array_y, int* array_x, int rows, int initial_index){
    
// initial calc:
    int minimal_index = initial_index;
    
    minDistance = rectDist(array_y[minimal_index], array_y[initial_index+1], array_x[minimal_index], array_x[initial_index+1]);

    for(int i =0; i< rows; i++){
        if(check for visitied) continue//wheverver you store the check to see if it's visited
        dist = rectDdistance(array_y[minimal_index), array_y[i], array_x[minimal_index], array_x[i]);
        if (dist < minDistance){
            minDistance = dist;
            minimal_index = i;
        } else if(dist == minDistance){
            minimal_index = tiebreaker((array_y[minimal_index], array_y[i], array_x[minimal_index], array_y[i]);
           
        }
    }

}
