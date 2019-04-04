// Graph ADT interface for Ass2 (COMP2521)

#include <stdbool.h>
#define MAX_NODES 10

// vertices are ints
typedef int Vertex;

typedef struct  GraphRep    *Graph;
typedef struct _adjListNode *AdjList;
typedef struct  EdgeRep     *Edge;


// Create graph by using data from egdes array
Graph newGraph  (Edge * edges, int no_of_edges);

// Allocate a new Edge structure
Edge newEdge    (Vertex source, Vertex dest, int weight);

// Allocate a new Node structure						
AdjList newAdjListNode  (Vertex vertex, int weight);

// Insert an edge between given vertices
void  InsertEdge   (Graph g, Vertex src, Vertex dest, int weight);  // DONE

//Remove an edge between given vertices
void  RemoveEdge   (Graph g, Vertex src, Vertex dest);				// KINDA DONE

// Free all the memory associated with the graph g 
void  FreeGraph    (Graph g);

// Display graph structure
void  showGraph    (Graph g);

// Determine if given vertices are adjacent to each other
bool  Adjacent     (Graph g, Vertex src, Vertex dest);				

// Parse data from given input file
int *  ReadFile   (char * filename);

// Various helper functions to test pass-around of data
int    NodeWeight (AdjList L);
int    NodeDest   (AdjList L);
int    EdgeSource (Edge e);
int    EdgeDest   (Edge e);
int    EdgeWeight (Edge e);

// Free memory associated with Edges array
void FreeEdgesArray(Edge * edges, int NEdges);

// Return connections list of graph
//AdjList * GetConnectionsArray (Graph g);


/*
 * Returns a list of adjacent vertices
 * on outgoing edges from a given vertex.
**/
AdjList outIncident(Graph g, Vertex v);
/*

 * Returns a list of adjacent vertices
 * on incoming edges from a given vertex.
**/
AdjList inIncident(Graph g, Vertex v);


/**
* The following  "showGraph" functions is defined for you to be able 
* to print out your output and write your own tests. 
* You can choose a suitable implemention (output format) for the following "showGraph" function. 
* 
* Note that we will *not* use your implementation of "showGraph" function
* for our own testing.

* The only reason we provided some show function for dijkstra is so we 
* could give you some sample output to compare against. 

* Again, our tests will not use your show function, it's there for your use.
* 
* */


