#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Graph.h"

typedef struct GraphRep {
	AdjList connections[MAX_NODES];
} GraphRep;

typedef struct _adjListNode {
   Vertex      dest;
   int         weight;
   AdjList     next;
} adjListNode;

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
	
	// While iterating over the edge objects in array,
	// modify graph structure. 
	for(int i = 0; i < no_of_edges; i++) {
		
		int src = EdgeSource(edges[i]);
		int dest = EdgeDest(edges[i]);
		int weight = EdgeWeight(edges[i]);
		
		// Set up links between top level vertex array
		// and the vertices they connect to
		
		AdjList new_node = newAdjListNode(dest , weight);
		new_node->next = new_graph->connections[src];
		new_graph->connections[src] = new_node;
		
	}
	
	return new_graph;
}


// Allocate a new Adjacency List Node
AdjList newAdjListNode (int dest , int weight) {
	AdjList new_node = malloc(sizeof(struct _adjListNode));
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

int * ReadFile (char * filename) {
    
    int i = 0;
    int lines = 0;
    
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
			
		// Grab data points from input file
		int data;
		
		array[i] = (lines * 3);
		i++;
		
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

AdjList * GetConnectionsArray(Graph g) {
	return g->connections;
}

int NodeDest (AdjList L) {
	return L->dest;
}

int NodeWeight (AdjList L) {
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

// Helper function to print Graph data.
void showGraph(Graph g) {
	
	for(int i = 0; i < MAX_NODES; i++) {
		AdjList curr = g->connections[i];
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
	
	AdjList new_node = newAdjListNode(dest , weight);
	new_node->next = g->connections[src];
	g->connections[src] = new_node;
	
}

// Remove an edge from appropriate top level adjacency list
void RemoveEdge (Graph g, Vertex src, Vertex dest) {
	
	AdjList curr = g->connections[src];
	AdjList temp;
	
	while(curr != NULL) {
		if(NodeDest(curr) == dest) {
			temp = curr;
			free(temp);
		}
		curr = curr->next;
	}
	
}
