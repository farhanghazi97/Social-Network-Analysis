#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

#define MAX_NODES 150

typedef struct _adjList     *AdjNode;

// Struct representing Graph
typedef struct GraphRep {
	int nV;
	AdjNode L        [MAX_NODES];
	AdjList OutLinks [MAX_NODES];
	AdjList InLinks  [MAX_NODES];
} GraphRep;

// Struct to keep track of length of adjacency
// lists within connections array in main Graph struct
typedef struct _adjList {
	int out_size;
	int in_size;
} adjList;

// Struct representing the connections
// between nodes and the weight between them
typedef struct EdgeRep {
	int source;
	int dest;
	int weight;
} EdgeRep;

static AdjNode newAdjList (void);
static AdjList newAdjNode (int dest , int weight);
static int NodeDest (AdjList L);

// Construct graph from array of edge objects
Graph newGraph(int noNodes) {

	Graph new_graph = malloc(sizeof(struct GraphRep));
	assert(new_graph != NULL);

	new_graph->nV = noNodes;

	// Initialize OutLinks array to NULL pointers
	for(int i = 0; i < noNodes; i++) {
		new_graph->OutLinks[i] = NULL;
	}
	// Initialize InLinks array to NULL pointers
	for(int i = 0; i < noNodes; i++) {
		new_graph->InLinks[i]= NULL;
	}
	// Initialize Adjacency List Tracker
	for(int i = 0; i < noNodes; i++) {
		new_graph->L[i] = newAdjList();
	}

	// Return updated graph structure
	return new_graph;
}


// Allocate a new Adjacency List Node
static AdjList newAdjNode (int dest , int weight) {
	AdjList new_node = malloc(sizeof(struct _adjListNode));
	new_node->w = dest;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;
}

AdjList outIncident(Graph g, Vertex v) {
	return g->OutLinks[v];
}

AdjList inIncident(Graph g , Vertex v) {
	return g->InLinks[v];
}

// Allocate a new Adjacency List Tracker object
static AdjNode newAdjList (void) {
	AdjNode L = malloc(sizeof(struct _adjList));
	L->out_size = 0;
	L->in_size = 0;
	return L;
}


static int NodeDest (AdjList L) {
	return L->w;
}

int numVerticies(Graph g) {
	return g->nV;
}

//  -----------------   HELPER FUNCTIONS END ------------- //

// Display graph structure
void showGraph(Graph g) {

	for(int i = 0; i < g->nV; i++) {
		AdjList curr_out = g->OutLinks[i];
		if(curr_out != NULL) {
			printf("OutLinks: ");
			while(curr_out != NULL) {
				printf("%d -> %d (%d)  " , i , curr_out->w , curr_out->weight);
				curr_out = curr_out->next;
			}
			printf("\n");
		}
		AdjList curr_in = g->InLinks[i];
		if(curr_in != NULL) {
			printf("InLinks: ");
			while(curr_in != NULL) {
				printf("%d <- %d (%d) " , i ,curr_in->w , curr_in->weight);
				curr_in = curr_in->next;
			}
			printf("\n");
		}
		printf("\n");
	}
}

// Appends to appropriate top level adjacency list
void insertEdge (Graph g, Vertex src, Vertex dest, int weight) {

	AdjList new_node_out = newAdjNode(dest , weight);
	new_node_out->next = g->OutLinks[src];
	g->OutLinks[src] = new_node_out;
	g->L[src]->out_size++;

	AdjList new_node_in = newAdjNode(src , weight);
	new_node_in->next = g->InLinks[dest];
	g->InLinks[dest] = new_node_in;
	g->L[dest]->in_size++;

}

// Remove an edge from appropriate top level adjacency list
void removeEdge (Graph g, Vertex src, Vertex dest) {

	// NEED TO RETHINK APPROACH TO MAKING THIS WORK

	// Update - Introduced a new ((AdjList)) struct (see above)
	//          that will keep track of the length of each individual
	//			adjacency list in array, plus have pointers to head and tail

	AdjList curr_out = g->OutLinks[src];
	AdjList curr_in = g->InLinks[dest];

	bool found = false;
	if(curr_out != NULL) {
		if(NodeDest(curr_out) == dest) {
			// Remove head of list
			// Update OutLinks list
			AdjList temp_1 = curr_out;
			g->OutLinks[src] = curr_out->next;
			free(temp_1);
			g->L[src]->out_size--;
			// Parallel update to InLinks List
			if(curr_in != NULL) {
				if(NodeDest(curr_in) == src) {
					AdjList temp_2 = curr_in;
					g->InLinks[dest] = curr_in->next;
					free(temp_2);
					g->L[dest]->in_size--;
				} else {
					while(curr_in->next != NULL) {
						if(NodeDest(curr_in->next) == src) {
							AdjList temp = curr_in->next;
							curr_in->next = NULL;
							free(temp);
							g->L[dest]->in_size--;
							break;
						}
						curr_in = curr_in->next;
					}
				}
			}
		} else {
			int size = g->L[src]->out_size;
			int i = 1;
			while(curr_out->next != NULL) {
				if(NodeDest(curr_out->next) == dest) {
					if(i + 1 == size) {
						// Remove tail of list
						AdjList temp = curr_out->next;
						curr_out->next = NULL;
						free(temp);
						g->L[src]->out_size--;
						found = true;
						break;
					} else {
						// Remove between head and tail of list
						AdjList temp_1 = curr_out->next;
						curr_out->next = curr_out->next->next;
						free(temp_1);
						g->L[src]->out_size--;
						found = true;
						break;
					}
				}
				curr_out = curr_out->next;
				i++;
			}
			int size_in = g->L[dest]->in_size;
			int j = 1;
			while(curr_in != NULL) {
				if(NodeDest(curr_in) == src) {
					AdjList temp = curr_in;
					g->InLinks[dest] = curr_in->next;
					free(temp);
					g->L[dest]->in_size--;
					break;
				} else {
					while(curr_in->next != NULL) {
						if(NodeDest(curr_in->next) == src){
							if(j + 1 == size_in) {
								AdjList temp = curr_in->next;
								curr_in->next = NULL;
								free(temp);
								g->L[dest]->in_size--;
								break;
							} else {
								AdjList temp_1 = curr_in->next;
								curr_in->next = curr_in->next->next;
								free(temp_1);
								g->L[dest]->in_size--;
								break;
							}
						}
					}
				}
				curr_in = curr_in->next;
			}
			if(!found) printf("Connection does not exist!\n");
		}
	}
}

// Determines if vertices are adjacent to each other
bool adjacent (Graph g, Vertex src, Vertex dest) {
	AdjList curr = g->OutLinks[src];
	bool flag = false;
	while(curr != NULL) {
		if(NodeDest(curr) == dest) {
			flag = true;
			break;
		}
		curr = curr->next;
	}
	return flag;
}

// Free all the memory associated with the graph
void freeGraph(Graph g) {
	if(g != NULL) {
		//Free OutLinks array
		for(int i = 0; i < g->nV; i++) {
			AdjList curr = g->OutLinks[i];
			while(curr != NULL) {
				AdjList temp = curr;
				free(temp);
				curr = curr->next;
			}
		}
		//Free AdjList Tracker array
		for(int i = 0; i < g->nV; i++) {
			AdjNode temp = g->L[i];
			free(temp);
		}
		// Free InLinks array
		for(int i = 0; i < g->nV; i++) {
			AdjList curr = g->InLinks[i];
			while(curr != NULL) {
				AdjList temp = curr;
				free(temp);
				curr = curr->next;
			}
		}
	}
	// Free graph
	free(g);
}
