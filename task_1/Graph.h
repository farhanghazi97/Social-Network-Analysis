// Graph ADT interface for Ass2 (COMP2521)

#include <stdbool.h>
#define MAX_NODES 10

// vertices are ints
typedef int Vertex;

typedef struct  GraphRep    *Graph;
typedef struct _adjListNode *AdjNode;
typedef struct _adjList     *AdjList;
typedef struct  EdgeRep     *Edge;

// Allocate a new Node structure
AdjNode newAdjNode  (Vertex vertex, int weight);

// Create graph by using data from egdes array
Graph newGraph  (Edge * edges, int no_of_edges);

// Allocate a new Edge structure
Edge newEdge    (Vertex source, Vertex dest, int weight);

// Allocate a new Adjacency List Tracker object
AdjList newAdjList (void);

// Insert an edge between given vertices
void  InsertEdge   (Graph g, Vertex src, Vertex dest, int weight);

//Remove an edge between given vertices
void  RemoveEdge   (Graph g, Vertex src, Vertex dest);

// Free all the memory associated with the graph
void  FreeGraph    (Graph g);

// Display graph structure
void  showGraph    (Graph g);

// Print Adjacency List
void  PrintAdjList  (AdjNode OutList);

// Free all memory associated with Edges array
void  FreeEdgesArray(Edge * edges, int NEdges);

// Determine if given vertices are adjacent to each other
bool  Adjacent     (Graph g, Vertex src, Vertex dest);

// Parse data from given input file
int * ReadFile   (char * filename);

// Various helper functions to test pass-around of data
int    NodeWeight (AdjNode L);
int    NodeDest   (AdjNode L);
int    EdgeSource (Edge e);
int    EdgeDest   (Edge e);
int    EdgeWeight (Edge e);
// AdjNode * GetConnectionsArray (Graph g);

// Returns a list of adjacent vertices
// on outgoing edges from a given vertex.
AdjNode outIncident(Graph g, Vertex v);

// Returns a list of adjacent vertices
// on incoming edges from a given vertex.
AdjNode inIncident(Graph g, Vertex v);
