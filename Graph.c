#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Graph.h"

// Struct representing Graph
typedef struct GraphRep {
	AdjList L [MAX_NODES];
	AdjNode connections [MAX_NODES];
} GraphRep;

// Struct to keep track of length of adjacency 
// lists within connections array in main Graph struct
typedef struct _adjList {
	int size;
	AdjNode first;
	AdjNode last;
} adjList;

// Struct representing individual nodes 
// that populate the Graph struct
typedef struct _adjListNode {
   Vertex      dest;
   int         weight;
   AdjNode     next;
} adjListNode;

// Struct representing the connections 
// between nodes and the weight between them 
typedef struct EdgeRep {
	int source;
	int dest;
	int weight;
} EdgeRep;

// Construct graph from array of edge objects
Graph newGraph(Edge * edges , int no_of_edges) {
	
	Graph new_graph = malloc(sizeof(struct GraphRep));
	assert(new_graph != NULL);
	
	// Initialize top level vertex array to NULL pointers
	for(int i = 0; i < MAX_NODES; i++) {
		new_graph->connections[i] = NULL;
	}
	
	for(int i = 0; i < MAX_NODES; i++) {
		new_graph->L[i] = newAdjList();
	}
	
	// While iterating over the edge objects in array,
	// modify graph structure. 
	for(int i = 0; i < no_of_edges; i++) {
		
		int src = EdgeSource(edges[i]);
		int dest = EdgeDest(edges[i]);
		int weight = EdgeWeight(edges[i]);
		
		// Set up links between top level vertex array
		// and the vertices they connect to
		
		AdjNode new_node = newAdjNode(dest , weight);
		new_node->next = new_graph->connections[src];
		new_graph->connections[src] = new_node;
		new_graph->L[src]->size++;
		new_graph->L[src]->first = new_node;
	}
	
	// Return updated graph structure
	return new_graph;
}


// Allocate a new Adjacency List Node
AdjNode newAdjNode (int dest , int weight) {
	AdjNode new_node = malloc(sizeof(struct _adjListNode));
	new_node->dest = dest;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}

// Allocate a new Edge object
Edge newEdge (int source , int dest , int weight) {
	Edge new_edge = malloc(sizeof(Edge));
	assert(new_edge != NULL);
	new_edge->source = source;
	new_edge->dest = dest;
	new_edge->weight = weight;
	return new_edge;
}


// Allocate a new Adjacency List Tracker object
AdjList newAdjList (void) {
	AdjList L = malloc(sizeof(struct _adjList));
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// Parse input file and grab relevant data
int * ReadFile (char * filename) {
    
    int i = 0;
    int lines = 0;
    
    // Open file for reading
	FILE * fp = fopen(filename , "r");
	
	char buffer[BUFSIZ];
	if(fp != NULL) {
		
		// Determine how many sets of entries there are
		while(fgets(buffer , BUFSIZ , fp) != NULL) {
			lines++;
		}
		
		// Malloc enough space to hold just those numbers
		// where every line has 3 numbers
		int * array = malloc(lines * 3 * sizeof(int));
		
		// Reset file pointer to beginning of file
		rewind(fp);
			
		// Package size of array into array index;
		array[i] = (lines * 3);
		i++;
		
		// Grab data points from input file and store in array
		int data;
		while(fscanf(fp , "%d ,[\n]" , &data) != EOF) {
			array[i] = data;
			i++;
		}
		
		// Close file
		fclose(fp);

		// return array with data
		return array;
		
	} else {
	
		//ERROR: File does not exist
		printf("Could not open file!\n");
	}
}

//  -----------------   HELPER FUNCTIONS START ------------- //

AdjNode * GetConnectionsArray(Graph g) {
	return g->connections;
}

int NodeDest (AdjNode L) {
	return L->dest;
}

int NodeWeight (AdjNode L) {
	return L->weight;
}

int EdgeSource (Edge e) {
	return e->source;
}

int EdgeDest   (Edge e) {
	return e->dest;
}

int EdgeWeight (Edge e) {
	return e->weight;
}

AdjList * getList(Graph new_graph) {
	return new_graph->L;
}

//  -----------------   HELPER FUNCTIONS END ------------- //

// Display graph structure
void showGraph(Graph g) {
	
	for(int i = 0; i < MAX_NODES; i++) {
		AdjNode curr = g->connections[i];
		//if(g->L[i]->size > 0) {
		//	printf("Size: %d\n" , g->L[i]->size);
		//}
		if(curr != NULL) {
			while(curr != NULL) {
				printf("%d -> %d (%d)  " , i , curr->dest , curr->weight);
				curr = curr->next;
			}
			printf("\n");
		}
	}	
}

// Appends to appropriate top level adjacency list
void InsertEdge (Graph g, Vertex src, Vertex dest, int weight) {
	
	AdjNode new_node = newAdjNode(dest , weight);
	new_node->next = g->connections[src];
	g->connections[src] = new_node;
	g->L[src]->size++;
	
}

// Remove an edge from appropriate top level adjacency list
void RemoveEdge (Graph g, Vertex src, Vertex dest) {
	
	// NEED TO RETHINK APPROACH TO MAKING THIS WORK
	
	AdjNode curr = g->connections[src];
	int size = g->L[src]->size;
	
	int i = 0;
	while(curr->next != NULL) {
		if(NodeDest(curr->next) == dest) {
			// Handles removal between head and tail
			AdjNode temp = curr->next;
			curr->next = curr->next->next;
			free(temp);
			g->L[src]->size--;
		}
		curr = curr->next;
		i++;
	}
}

// Determines if vertices are adjacent to each other
bool Adjacent (Graph g, Vertex src, Vertex dest) {

	AdjNode curr = g->connections[src];
	bool flag = false;
	
	while(curr != NULL) {
		if(NodeDest(curr) == dest) {
			flag = true;
		}
		curr = curr->next;
	}
	return flag; 
}

// Free all memory associated with Edges array
void FreeEdgesArray(Edge * edges , int NEdges) {
	for(int i = 0; i < NEdges; i++) {
		free(edges[i]);
	}
}

// Free all the memory associated with the graph
void FreeGraph(Graph g) {
	if(g != NULL) {
		for(int i = 0; i < MAX_NODES; i++) {
			AdjNode curr = g->connections[i];
			while(curr != NULL) {
				AdjNode temp = curr;
				free(temp);
				curr = curr->next;
			}
		}
		for(int i = 0; i < MAX_NODES; i++) {
			AdjList temp = g->L[i];
			free(temp);
		}
	}	
	free(g);
}
