#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Graph.h"
#define MAX_NODES 10

//HI there!

typedef struct GraphRep {
	int nV;
	int nE;
	AdjList connections[MAX_NODES];
} GraphRep;

typedef struct _adjListNode {
   Vertex      v;
   int         weight;
   AdjList     next;
} adjListNode;


Graph newGraph(int noNodes) {
	Graph new_graph = malloc(sizeof(Graph));
	assert(new_graph != NULL);
	new_graph->nV = noNodes;
	new_graph->nE = 0;
	new_graph->connections[MAX_NODES] = NULL;
	return new_graph;
}

AdjList newAdjListNode (int vertex , int weight) {
	AdjList new_node = malloc(sizeof(AdjList));
	new_node->v = vertex;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}

int numVerticies (Graph g) {
	return g->nV;
}

int * ReadFile (char * filename) {
    
    int number; int actual_number; int i = 0; int lines = 0;
    
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
		
		// Find relevant data from file (vertex , connects-to , weight)
		/*while((number = fgetc(fp)) != '\n') {
			if((number != 44 && number != 32)) {
				number = number - 48;
				array[i] = number;
				i++;
			}
		}*/
		
		int data;
		while(fscanf(fp , "%d ,[\n]" , &data) != EOF) {
			printf("%d\n" , data);
		}
		
		// Close file
		fclose(fp);
		
		//return array of data
		return array;
	} else {
	
		//ERROR: File does not exist
		printf("Could not open file!\n");
	}
}

AdjList * GetConnectionsArray(Graph g) {
	return g->connections;
}

int NodeVertex (AdjList L) {
	return L->v;
}

int NodeWeight (AdjList L) {
	return L->weight;
}
