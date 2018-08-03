/**
 * File: main.c
 * Assignment: Assignment 4
 * Creation date: July 23, 2018
 * Last Modified: August 2, 2018
 * Description: Used for reading in  a file to create a graph structure
 *
 * GitHub Link: https://github.com/Xsais/graph-a-court/
 *
 * Group Members:
 *    - James Grau
 *    - Bhavay Grover
 *    - Nathaniel Primo
 *
 **/

// Include the Needed Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define needed items
#define MaxWordSize 20
#define MaxVertices 50

/**
 *
 * This structure is used for creating a graph edge structure
 *
 * @item child: location of the child vertex
 * @item weight: weight on the edge
 * @item nextEdge: is the pointer to the next edge
 *
 */
typedef struct gEdge {
	// Declare the needed structure items
	int child;
	int weight;
	struct gEdge *nextEdge;
} GEdge, *GEdgePtr;

/**
 *
 * This structure is used for creating a graph vertex structure
 *
 * @item id: is the id of the vertex
 * @item firstEdge: is the first edge of the vertex
 *
 */
typedef struct {
	// Declare the needed structure items
	char id[MaxWordSize + 1];
	GEdgePtr firstEdge;
} GVertex;

/**
 *
 * This structure is used for creating a graph structure
 *
 * @item numV: number of vertexes the graph has
 * @item vertex: is the array of vertexes
 *
 */
typedef struct graph {
	// Declare the needed structure items
	int numV;
	GVertex vertex[MaxVertices + 1];
} *GraphPtr;

/**
 *
 * This method is used to run the core of the application section
 *
 */
int main() {
	// Create needed variables
	int numVertices;
	char choice;

	// Create the new graph
	GraphPtr newGraph(int);

	// Declare the abstract function protodypes
	void buildGraph(FILE *, GraphPtr);
	void printGraph(GraphPtr);

	// Perform the reading in of the graph file
	FILE *in = fopen("graph.in", "r"); // Opening a text file for reading
	fscanf(in, "%d", &numVertices);     // Read in from text file
	GraphPtr G = newGraph(numVertices); // Creating a new Graph
	buildGraph(in, G);                  // Builds the graph using the data from the input file
	fclose(in);                         // Closing the file

	// Perform the menu loop
	do {
		// Notifies the user of available options
		printf("---- Assignment #4 ----\n"
			   "1. Print\n"
			   "2. Exit\n"
			   "------------------------\n"
			   "Enter choice number: ");

		// Retrieves the entered user choice
		fscanf(stdin, "%d", &choice);

		// Check if the entered menu option is 1
		if (choice == 1) {
			// Print the Graph
			printGraph(G);
		}else if(choice == 2) {
			// Free the allocated graph memory from the heap
			free(G);
		}else{
			// Print error message
			printf("\nInvalid option choice, try again!\n\n");
		}
	} while (choice != 2); // Loops the menu when the user has not requested to exit the program

	// Return 0 out of application
	return 0;
}

/**
 *
 * This function is used to create and initialize the graph
 *
 * @param n: number of vertices
 *
 * @return p: is the pointer to the graph
 *
 */
GraphPtr newGraph(int n) {
	// Check if the 'n' is more than 'MaxVertices'
	if(n > MaxVertices) {
		// Display error message and then error (exit) out of application
		printf("\nToo big. Only %d vertices allowed.\n", MaxVertices);
		exit(1);
	}

	// Create a new graph pointer on the heap and assign numV of pointer to n
	GraphPtr p = (GraphPtr)malloc(sizeof(struct graph));
	p->numV = n;

	// Return the pointer
	return p;
}

/**
 *
 * This function is used to add verticies and edges to the graph
 *
 * @param in: is the file to be read in
 * @param G: is the graph to build the graph into
 *
 */
void buildGraph(FILE *in, GraphPtr G) {
	// Create needed variables
	int numEdges, weight;
	char nodeID[MaxWordSize + 1], adjID[MaxWordSize + 1];

	// Declare the abstract function prototypes
	GVertex newGVertex(char[]);
	void addEdge(char[], char[], int, GraphPtr);

	// Loop through and  create the vertex node and assign it its id
	for(int h = 1; h <= G->numV; h++) {
		// Create the vertex node
		G->vertex[h] = newGVertex("");

		// Read the name in the id
		fscanf(in, "%s", G->vertex[h].id);
	}

	// Loop through and
	for (int h = 1; h <= G->numV; h++) {
		// Read in the parent-id and numEdges
		fscanf(in, "%s %d", nodeID, &numEdges);

		// Loop through and
		for (int k = 1; k <= numEdges; k++) {
			//  Read in the child-id and weight
			fscanf(in, "%s %d", adjID, &weight);

			// Add the edge to the graph
			addEdge(nodeID, adjID, weight, G);
		}
	}
}

/**
 *
 * This function is used to create a new graph vertex
 *
 * @param name: is the name of the vertex
 *
 * @return temp: is the tmp graph vertex
 *
 */
GVertex newGVertex(char name[]) {
	// Create a tmp vertex
	GVertex temp;

	// Copy in the name of the vertex to the tmp.id
	strcpy(temp.id, name);

	// Assign the tmp.firstEdge to NULL
	temp.firstEdge = NULL;

	// Return the tmp graph vertex
	return temp;
}

/**
 *
 * This function is used for adding in a new edges into the graph
 *
 * @param x: is the y of the edge
 * @param y: is the x of the edge
 * @param weight: is the weight of the edge
 * @param G: is the graph
 *
 */
void addEdge(char X[], char Y[], int weight, GraphPtr G) {
	// Declare the abstract function prototypes
	GEdgePtr newGEdge(int, int);

	// Create the needed variables
	int h, k;

	// Loop through and find x in the list of nodes (its location is h)
	for(h = 1; h <= G->numV; h++) {
		// Check if the string copy was successful
		if(strcmp(X, G->vertex[h].id) == 0) {
			// Break out of the loop
			break;
		}
	}

	// Loop through and find y in the list of nodes (its location is k)
	for(k = 1; k <= G->numV; k++) {
		// Check if the string copy was successful
		if(strcmp(Y, G->vertex[k].id) == 0) {
			// Break out of the loop
			break;
		}
	}

	// Check if x(h) or y(k) is greater than the g.numV
	if(h > G->numV || k > G->numV) {
		// Print an error message and exit the application in error
		printf("No such edge: %s -> %s\n", X, Y);
		exit(1);
	}

	// Create a new edge
	GEdgePtr ep = newGEdge(k, weight);
	// add it to the list of edges, possible empty, from X;
	// it is added so that the list is in order by vertex id

	// Create needed graph edge pointers
	GEdgePtr prev, curr;

	// Set the previous and current graph edge pointer to the x(h) graph vertex.firstEdge
	prev = curr = G->vertex[h].firstEdge;

	// Loop through and make sure that curr is not null
	while (curr != NULL && strcmp(Y, G->vertex[curr->child].id) > 0) {
		// Set the previous edge pointer the current edge poitner
		prev = curr;

		// Assign the current edge pointer the the next edge pointer
		curr = curr->nextEdge;
	}

	// Check if adding to the front of the edge list
	if(prev == curr) {
		// Assign the next edge of the edge pointer to the first edge of the x(h) graph vertex
		ep->nextEdge = G->vertex[h].firstEdge;

		// Assign the first x(h) graph vertex to the edge pointer
		G->vertex[h].firstEdge = ep;
	}else{ // adding orderly in the edge list
		// Set the edge pointer next edge to the current edge pointer
		ep->nextEdge = curr;

		// Set the previous edge pointer next nege to the edge pointer
		prev->nextEdge = ep;
	}
}

/**
 *
 * This function is used to create a new weighted edge
 *
 * @param c: is the child of the edge
 * @param w: is the weight of the edge
 *
 * @return p: is the new weighted edge pointer
 *
 */
GEdgePtr newGEdge(int c, int w) {
	// Create a new graph edge pointer on the heap
	GEdgePtr p = (GEdgePtr)malloc(sizeof(GEdge));

	// Assign the child to c
	p->child = c;

	// Assign the weight to w
	p->weight = w;

	// Assign the next edge to NULL
	p->nextEdge = NULL;

	// Return the new graph edge pointer
	return p;
}

/**
 *
 * This function is used to print the graph according the representative model
 *
 * @param G: is the grpah
 *
 */
void printGraph(GraphPtr G) {
	// Loop through the graph
	for (int h = 1; h <= G->numV; h++) {
		// Print the id of the iterated vertex
		printf("%s: ", G->vertex[h].id);

		// Assign the new p graph edgw to the first edge of the grpah vertex
		GEdgePtr p = G->vertex[h].firstEdge;

		// Loop through edge and print its information
		while (p != NULL) {
			// Print the vertex id and weight
			printf("%s %d ", G->vertex[p->child].id, p->weight);

			// Assign the pointer to the next edge
			p = p->nextEdge;
		}

		// Print a new line for formatting
		printf("\n");
	}
}
