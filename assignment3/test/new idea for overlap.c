int findOverlap(RST* root, int overlap, Path currentPath){
    if(root->parent == NULL){
        return overlap;
    }
    else{
        currentOverlap = anyOverlap(currentPath root->parent->path)
        if currentOverlap > overlap{
            overlap = currentOverlap
        }
        return findOverlap(root->parent, overlap, currentPath);
    }
}
