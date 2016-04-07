RST is a program that computes the rectilinear steiner tree.

To use this program you need an a file that follows the following specification

This program can take in a file of the required information

X Y
Z
1x 1y
...
...
nx ny

Where X and Y are the maximum x and y in the of the points Z is the number of
points that exist in the instance and 1->n are the Z amount of x and y
coordinates for the instance.

Otherwise the program prompts the user for input, where it asks for Max X, Max Y
number of points per instance and the number of generations to print.

The program takes two arguments at runtime.

Arguments:
    -i "filename"
        If you want to pass in a file to the program, you will type in
        './rst -i "filename"'
    -o "output"
        Takes in the options for the program. Currently, the only option is
        "output", which tells the program to output to a file following the
        naming convention "instanceXXX_YYY.txt" where XXX is instance size
        and YYY is the generation number starting at 0.

Ex:
    ./rst -i "filename" -o "outout" will take in an instance file and overwrite
    it with the calculation of the minimal spanning tree and the rectilinear
    steiner tree.

Compiling: To compile the program use the make file included with this tar.

The Alogorithm:
    1. Given a set of coordinates it calculates the minimal spanning tree using
        Prim's Algorithm
    2. We then find the Parent node, or a node with no incoming edges
    3. We use this parent node to build out a tree structure going from parent
        to child. This parent child relationship is indicated in the MST with
        parent being the first element, child the second element and weight as
        the third element
    4.  a)After all nodes are laid out, it then traverses down to the leaf nodes
        and calculate the maximal overlap between each child while inserting
        rectilinear steiner points.
        b) Before it lays down the children it then calculates how that child
        would overlap with it's children (or the grandchildren from the parent),
        while both traversing the X axis first and Y axis first. If the overlap
        between child and grandchild is more than the siblings it counts that
        overlap and that maximal overlapping path for the child.
            i) special case, this algorithm also checks when laying down a node,
            to see if it's child nodes have 0 overlap, if it flips that child's
            traversal if it maximally overlaps with the parent node.
    5. After wards, it recalculates all the overlap in the tree
