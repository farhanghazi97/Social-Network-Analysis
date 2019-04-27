/* 
   Graph ADT Interface for Assignment 2
   Written by Kanadech Jirapongtanavech (z5176970) and Farhan Ghazi (z5199861)
   COMP2521 T1 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

typedef struct _adjList *AdjNode;

// Struct representing Graph
typedef struct GraphRep {
	int nV;
	AdjNode * L;
	AdjList * OutLinks;
	AdjList * InLinks;
} GraphRep;

// Struct to keep track of length of adjacency
// lists within connections array in main Graph struct
typedef struct _adjList {
	int out_size;
	int in_size;
} adjList;

// ---------- STATIC FUNCTIONS START ---------- //

// Function to create a new _adjList struct
static AdjNode newAdjList (void);
// Function to create a new struct _adjListNode struct
static AdjList newAdjNode (int dest , int weight);
// Function to grab vertex associated with AdjList struct
static int NodeVertex (AdjList L);

// ---------- STATIC FUNCTIONS END ---------- //

// Initialize graph data structure
Graph newGraph(int noNodes) {

	Graph new_graph = malloc(sizeof(struct GraphRep));
	assert(new_graph != NULL);

	new_graph->nV = noNodes;

    // Initialize OutLinks array to NULL pointers
	new_graph->OutLinks = malloc(noNodes * sizeof(AdjList));
	// Initialize InLinks array to NULL pointers
	new_graph->InLinks = malloc(noNodes * sizeof(AdjList));
	// Initialize Adjacency List Tracker
	new_graph->L = malloc(noNodes * sizeof(AdjNode));
	
	// Set pointers to NULL
	for(int i = 0; i < noNodes; i++) {
		new_graph->OutLinks[i] = NULL;
		new_graph->InLinks[i]= NULL;
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

// Returns list of vertices outgoing from vertex v
AdjList outIncident(Graph g, Vertex v) {
	return g->OutLinks[v];
}

// Return list of vertices incoming to vertex v
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

// Helper function to grab vertex ID of current vertex
static int NodeVertex (AdjList L) {
	return L->w;
}

// Helper function to grab number of total vertices in graph
int numVerticies(Graph g) {
	return g->nV;
}

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

	// Introduced a new ((AdjList)) struct (see above)
	// that will keep track of the length of each individual
	// adjacency list in array, plus have pointers to head and tail

	// Create pointer to iterate over list of outlinks from source node
	AdjList currVertice_out = g->OutLinks[src];
	
	// Create pointer to iterate over list of inlinks to destination node
	AdjList currVertice_in = g->InLinks[dest];

	// Flag to determine if value to be removed has been found
	bool found = false;
	
	if(currVertice_out != NULL) {
		if(NodeVertex(currVertice_out) == dest) {
			// Remove head of list
			// Update OutLinks list
			AdjList temp_1 = currVertice_out;
			g->OutLinks[src] = currVertice_out->next;
			free(temp_1);
			g->L[src]->out_size--;
			// Parallel update to InLinks List
			if(currVertice_in != NULL) {
				if(NodeVertex(currVertice_in) == src) {
					AdjList temp_2 = currVertice_in;
					g->InLinks[dest] = currVertice_in->next;
					free(temp_2);
					g->L[dest]->in_size--;
				} else {
					while(currVertice_in->next != NULL) {
						if(NodeVertex(currVertice_in->next) == src) {
							AdjList temp = currVertice_in->next;
							currVertice_in->next = NULL;
							free(temp);
							g->L[dest]->in_size--;
							break;
						}
						currVertice_in = currVertice_in->next;
					}
				}
			}
		} else {
			int size = g->L[src]->out_size;
			int i = 1;
			while(currVertice_out->next != NULL) {
				if(NodeVertex(currVertice_out->next) == dest) {
					if(i + 1 == size) {
						// Remove tail of list
						AdjList temp = currVertice_out->next;
						currVertice_out->next = NULL;
						free(temp);
						g->L[src]->out_size--;
						found = true;
						break;
					} else {
						// Remove between head and tail of list
						AdjList temp_1 = currVertice_out->next;
						currVertice_out->next = currVertice_out->next->next;
						free(temp_1);
						g->L[src]->out_size--;
						found = true;
						break;
					}
				}
				currVertice_out = currVertice_out->next;
				i++;
			}
			int size_in = g->L[dest]->in_size;
			int j = 1;
			while(currVertice_in != NULL) {
				if(NodeVertex(currVertice_in) == src) {
					AdjList temp = currVertice_in;
					g->InLinks[dest] = currVertice_in->next;
					free(temp);
					g->L[dest]->in_size--;
					break;
				} else {
					while(currVertice_in->next != NULL) {
						if(NodeVertex(currVertice_in->next) == src){
							if(j + 1 == size_in) {
								AdjList temp = currVertice_in->next;
								currVertice_in->next = NULL;
								free(temp);
								g->L[dest]->in_size--;
								break;
							} else {
								AdjList temp_1 = currVertice_in->next;
								currVertice_in->next = currVertice_in->next->next;
								free(temp_1);
								g->L[dest]->in_size--;
								break;
							}
						}
					}
				}
				currVertice_in = currVertice_in->next;
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
		if(NodeVertex(curr) == dest) {
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
			AdjList out_curr = g->OutLinks[i];
			if(out_curr != NULL) {
				while(out_curr->next != NULL) {
					AdjList out_temp = out_curr;
					free(out_temp);
					out_curr = out_curr->next;
				}
			}
		}
		//Free AdjList Tracker array
		for(int i = 0; i < g->nV; i++) {
			AdjNode temp = g->L[i];
			if(temp != NULL) {
				free(temp);
			}
		}
		// Free InLinks array
		for(int i = 0; i < g->nV; i++) {
			AdjList in_curr = g->InLinks[i];
			if(in_curr != NULL) {
				while(in_curr->next != NULL) {
					AdjList in_temp = in_curr;
					free(in_temp);
					in_curr = in_curr->next;
				}
			}
		}
		// Free graph
		free(g);
	} else {
		return;
	}
}
