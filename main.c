// Program to build and print a graph data structure.  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxWordSize 20
#define MaxVertices 50

// Edge definition
typedef struct gEdge {
    int child;  //'child' is the location of the child vertex
    int weight; // weight on the edge
    struct gEdge *nextEdge;
} GEdge, *GEdgePtr;

// Vertex Definition
typedef struct {
    char id[MaxWordSize + 1];
    GEdgePtr firstEdge;
} GVertex;

// Graph Definition
typedef struct graph {
    int numV;
    GVertex vertex[MaxVertices + 1];
} *GraphPtr;

int main() {
    int numVertices;
    char choice;

    GraphPtr newGraph(int);
    void buildGraph(FILE *, GraphPtr);  // function prototype abstracted
    void printGraph(GraphPtr);          // function prototype abstracted

    FILE *in = fopen("graph2.in", "r"); // Opening a text file for reading
    fscanf(in, "%d", &numVertices);     // reading from a text file
    GraphPtr G = newGraph(numVertices); // Creating a new Graph
    buildGraph(in, G);
    fclose(in);                         // Closing the file

    do {

        printf("------- Assignment #4 -------\n"
               "1. Print\n"
               "2. Exit\n"
               "---------------------\n"
               "Enter choice number: ");

        fscanf(stdin, "%d", &choice);

        if (choice == 1) {

            printGraph(G);
        } else {

            printf("\nInvalid option choice, try again!!\n\n");
        }
    } while (choice != 2);
} // end main

// Creating & initialising a new Graph
GraphPtr newGraph(int n) {
    if (n > MaxVertices) {
        printf("\nToo big. Only %d vertices allowed.\n", MaxVertices);
        exit(1);
    }
    GraphPtr p = (GraphPtr) malloc(sizeof(struct graph));
    p->numV = n;
    return p;
} //end newGraph

//Adding Vertices & Edges to the Graph
void buildGraph(FILE *in, GraphPtr G) {
    int numEdges, weight;

    GVertex newGVertex(char[]);         // function prototype abstracted
    void addEdge(char[], char[], int, GraphPtr); //   "

    char nodeID[MaxWordSize + 1], adjID[MaxWordSize + 1];
    for (int h = 1; h <= G->numV; h++) {
        G->vertex[h] = newGVertex("");      //create a vertex node
        fscanf(in, "%s", G->vertex[h].id);   //read the name into id
    }
    for (int h = 1; h <= G->numV; h++) {
        fscanf(in, "%s %d", nodeID, &numEdges); //get parent-id and numEdges
        for (int k = 1; k <= numEdges; k++) {
            fscanf(in, "%s %d", adjID, &weight); //get child-id and weight
            addEdge(nodeID, adjID, weight, G);   // add edge to graph
        }
    }
} //end buildGraph

// Creating new vertex
GVertex newGVertex(char name[]) {
    GVertex temp;
    strcpy(temp.id, name);
    temp.firstEdge = NULL;
    return temp;
}

// Adding new edges
void addEdge(char X[], char Y[], int weight, GraphPtr G) {
    GEdgePtr newGEdge(int, int);
    //add an edge X -> Y with a given weight
    int h, k;
    //find X in the list of nodes; its location is h
    for (h = 1; h <= G->numV; h++)
        if (strcmp(X, G->vertex[h].id) == 0)
            break;

    //find Y in the list of nodes; its location is k
    for (k = 1; k <= G->numV; k++)
        if (strcmp(Y, G->vertex[k].id) == 0)
            break;

    if (h > G->numV || k > G->numV) {
        printf("No such edge: %s -> %s\n", X, Y);
        exit(1);
    }

    GEdgePtr ep = newGEdge(k, weight); //create new edge
    // add it to the list of edges, possible empty, from X;
    // it is added so that the list is in order by vertex id
    GEdgePtr prev, curr;
    prev = curr = G->vertex[h].firstEdge;
    while (curr != NULL && strcmp(Y, G->vertex[curr->child].id) > 0) {
        prev = curr;
        curr = curr->nextEdge;
    }

    if (prev == curr) // adding at front of edge-list
    {
        ep->nextEdge = G->vertex[h].firstEdge;
        G->vertex[h].firstEdge = ep;
    } else {            // adding orderly in the edge list
        ep->nextEdge = curr;
        prev->nextEdge = ep;
    }
} //end addEdge

// Creating new weighted Edge
GEdgePtr newGEdge(int c, int w) {
    //return a pointer to a new GEdge node
    GEdgePtr p = (GEdgePtr) malloc(sizeof(GEdge));;
    p->child = c;
    p->weight = w;
    p->nextEdge = NULL;
    return p;
}

// Printing the Graph according to representative model
void printGraph(GraphPtr G) {
    for (int h = 1; h <= G->numV; h++) {
        printf("%s: ", G->vertex[h].id);
        GEdgePtr p = G->vertex[h].firstEdge;
        while (p != NULL) {
            printf("%s %d ", G->vertex[p->child].id, p->weight);
            p = p->nextEdge;
        }
        printf("\n");
    }
} //end printGraph

     
