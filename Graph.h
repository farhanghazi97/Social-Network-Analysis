// Graph ADT interface for Ass2 (COMP2521)

#include <stdbool.h>
#define MAX_NODES 10

// vertices are ints
typedef int Vertex;

typedef struct  GraphRep    *Graph;
typedef struct _adjListNode *AdjList;

Graph newGraph(int noNodes);										// KINDA DONE

void  insertEdge   (Graph g, Vertex src, Vertex dest, int weight);
void  removeEdge   (Graph g, Vertex src, Vertex dest);
bool  adjacent     (Graph g, Vertex src, Vertex dest);
int   numVerticies (Graph g);		   								// DONE

int  * ReadFile   (char * filename);
int    NodeWeight (AdjList L);
int    NodeVertex (AdjList L);

AdjList * GetConnectionsArray (Graph g);
AdjList   newAdjListNode      (int vertex , int weight);




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

void  freeGraph(Graph g);

