// Graph ADT interface for Ass2 (COMP2521)

#include <stdbool.h>
#define MAX_NODES 10

// vertices are ints
typedef int Vertex;

typedef struct  GraphRep    *Graph;
typedef struct _adjListNode *AdjList;
typedef struct  EdgeRep     *Edge;

Edge    newEdge         (int source   , int dest , int weight);
Graph   newGraph        (Edge * edges , int no_of_edges);							
AdjList newAdjListNode  (int vertex   , int weight);

void  InsertEdge   (Graph g, Vertex src, Vertex dest, int weight);  // DONE
void  RemoveEdge   (Graph g, Vertex src, Vertex dest);				// KINDA DONE
bool  Adjacent     (Graph g, Vertex src, Vertex dest);				

int *  ReadFile   (char * filename);

// Various helper functions to test pass-around of data
int    NodeWeight (AdjList L);
int    NodeDest   (AdjList L);
int    EdgeSource (Edge e);
int    EdgeDest   (Edge e);
int    EdgeWeight (Edge e);

void FreeEdgesArray(Edge * edges, int NEdges);


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
void  showGraph(Graph g);


/**
 * Free all the memory associated with the graph g 
 **/

void  FreeGraph(Graph g);

