#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Graph.h"

// Struct representing Graph
typedef struct GraphRep {
	int nV;
	AdjList L [MAX_NODES];
	AdjNode OutLinks [MAX_NODES];
	AdjNode InLinks [MAX_NODES];
} GraphRep;

// Struct to keep track of length of adjacency
// lists within connections array in main Graph struct
typedef struct _adjList {
	int out_size;
	int in_size;
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
Graph newGraph(Edge * edges , int no_of_edges , int noNodes) {

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

	// While iterating over the edge objects in array,
	// modify graph structure.
	for(int i = 0; i < no_of_edges; i++) {

		int src = EdgeSource(edges[i]);
		int dest = EdgeDest(edges[i]);
		int weight = EdgeWeight(edges[i]);

		// Set up links between top level vertex array
		// and the vertices they connect to
		AdjNode new_node_out = newAdjNode(dest , weight);
		new_node_out->next = new_graph->OutLinks[src];
		new_graph->OutLinks[src] = new_node_out;
		new_graph->L[src]->out_size++;

		AdjNode new_node_in = newAdjNode(src , weight);
		new_node_in->next = new_graph->InLinks[dest];
		new_graph->InLinks[dest] = new_node_in;
		new_graph->L[dest]->in_size++;

		//Set first to point to head of each adjacency list that is updated
		new_graph->L[src]->first = new_node_out;
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

AdjNode outIncident(Graph g, Vertex v) {
	return g->OutLinks[v];
}

AdjNode inIncident(Graph g , Vertex v) {
	return g->InLinks[v];
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
	L->out_size = 0;
	L->in_size = 0;
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
	if(g != NULL) {
		return g->OutLinks;
	}
}

int NodeDest (AdjNode L) {
	if(L != NULL) {
		return L->dest;
	}
}

int NodeWeight (AdjNode L) {
	if(L != NULL) {
		return L->weight;
	}
}

int EdgeSource (Edge e) {
	if(e != NULL) {
		return e->source;
	}
}

int EdgeDest   (Edge e) {
	if(e != NULL) {
		return e->dest;
	}
}

int EdgeWeight (Edge e) {
	if(e != NULL) {
		return e->weight;
	}
}

//  -----------------   HELPER FUNCTIONS END ------------- //

// Display graph structure
void showGraph(Graph g) {

	for(int i = 0; i < g->nV; i++) {
		AdjNode curr_out = g->OutLinks[i];
		/*if(g->L[i]->out_size > 0) {
			printf("OutLinks size: %d\n" , g->L[i]->out_size);
		}
		if(g->L[i]->in_size > 0) {
			printf("InLinks size: %d\n" , g->L[i]->in_size);
		}*/
		if(curr_out != NULL) {
			printf("OutLinks: ");
			while(curr_out != NULL) {
				printf("%d -> %d (%d)  " , i , curr_out->dest , curr_out->weight);
				curr_out = curr_out->next;
			}
			printf("\n");
		}
		AdjNode curr_in = g->InLinks[i];
		if(curr_in != NULL) {
			printf("InLinks: ");
			while(curr_in != NULL) {
				printf("%d <- %d (%d) " , i ,curr_in->dest , curr_in->weight);
				curr_in = curr_in->next;
			}
			printf("\n");
		}
		printf("\n");
	}
}

void PrintAdjList(AdjNode List) {
	if(List != NULL) {
		AdjNode curr = List;
		while(curr != NULL) {
			printf("Vertex: %d | Weight: %d\n" , NodeDest(curr) , NodeWeight(curr));
			curr = curr->next;

		}
		printf("\n");
	} else {
		printf("Pointer is NULL\n");
	}
}

// Appends to appropriate top level adjacency list
void InsertEdge (Graph g, Vertex src, Vertex dest, int weight) {

	AdjNode new_node_out = newAdjNode(dest , weight);
	new_node_out->next = g->OutLinks[src];
	g->OutLinks[src] = new_node_out;
	g->L[src]->out_size++;

	AdjNode new_node_in = newAdjNode(src , weight);
	new_node_in->next = g->InLinks[dest];
	g->InLinks[dest] = new_node_in;
	g->L[dest]->in_size++;

}

// Remove an edge from appropriate top level adjacency list
void RemoveEdge (Graph g, Vertex src, Vertex dest) {

	// NEED TO RETHINK APPROACH TO MAKING THIS WORK

	// Update - Introduced a new ((AdjList)) struct (see above)
	//          that will keep track of the length of each individual
	//			adjacency list in array, plus have pointers to head and tail

	AdjNode curr_out = g->OutLinks[src];
	AdjNode curr_in = g->InLinks[dest];

	bool found = false;
	if(curr_out != NULL) {
		if(NodeDest(curr_out) == dest) {
			// Remove head of list
			// Update OutLinks list
			AdjNode temp_1 = curr_out;
			g->OutLinks[src] = curr_out->next;
			free(temp_1);
			g->L[src]->out_size--;
			// Parallel update to InLinks List
			if(curr_in != NULL) {
				if(NodeDest(curr_in) == src) {
					AdjNode temp_2 = curr_in;
					g->InLinks[dest] = curr_in->next;
					free(temp_2);
					g->L[dest]->in_size--;
				} else {
					while(curr_in->next != NULL) {
						if(NodeDest(curr_in->next) == src) {
							AdjNode temp = curr_in->next;
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
						AdjNode temp = curr_out->next;
						curr_out->next = NULL;
						free(temp);
						g->L[src]->out_size--;
						found = true;
						break;
					} else {
						// Remove between head and tail of list
						AdjNode temp_1 = curr_out->next;
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
					AdjNode temp = curr_in;
					g->InLinks[dest] = curr_in->next;
					free(temp);
					g->L[dest]->in_size--;
					break;
				} else {
					while(curr_in->next != NULL) {
						if(NodeDest(curr_in->next) == src){
							if(j + 1 == size_in) {
								AdjNode temp = curr_in->next;
								curr_in->next = NULL;
								free(temp);
								g->L[dest]->in_size--;
								break;
							} else {
								AdjNode temp_1 = curr_in->next;
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
bool Adjacent (Graph g, Vertex src, Vertex dest) {
	AdjNode curr = g->OutLinks[src];
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

// Free all memory associated with Edges array
void FreeEdgesArray(Edge * edges , int NEdges) {
	for(int i = 0; i < NEdges; i++) {
		free(edges[i]);
	}
}

// Free all the memory associated with the graph
void FreeGraph(Graph g) {
	if(g != NULL) {
		//Free OutLinks array
		for(int i = 0; i < MAX_NODES; i++) {
			AdjNode curr = g->OutLinks[i];
			while(curr != NULL) {
				AdjNode temp = curr;
				free(temp);
				curr = curr->next;
			}
		}
		//Free AdjList Tracker array
		for(int i = 0; i < MAX_NODES; i++) {
			AdjList temp = g->L[i];
			free(temp);
		}
		// Free InLinks array
		for(int i = 0; i < MAX_NODES; i++) {
			AdjNode curr = g->InLinks[i];
			while(curr != NULL) {
				AdjNode temp = curr;
				free(temp);
				curr = curr->next;
			}
		}
	}
	// Free graph
	free(g);
}
