/*Lance-Williams Algorithm for Agglomerative Clustering
  Written by
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#define numVertices numVerticies


static double ** InitializeDistArray(Graph g);
static Dendrogram MakeDNode (Vertex v);
static void PrintDendArray (Dendrogram * D , int size);

/*
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs)
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods.

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 *
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {

    double ** dist_array = InitializeDistArray(g);
    
    Dendrogram * List = malloc(numVertices(g) * sizeof(DNode));
    for(int i = 0; i < numVertices(g); i++) {
        List[i] = MakeDNode(i);
    }
    
    PrintDendArray(List , numVertices(g));

    free(List[1]);

    PrintDendArray(List , numVertices(g));
    
    Dendrogram * temp_list = realloc(List , (numVertices(g) - 2)*sizeof(DNode) );
    List = temp_list;
    PrintDendArray(List, numVerticies(g));
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // Pretty print array
    /*for(int i = 0; i < numVertices(g); i++) {
        for(int j = 0; j < numVertices(g); j++) {
            printf("%.3lf\t" , dist_array[i][j]);
        }
        printf("\n");
    }*/

    // Free array
    free(dist_array);
    return NULL;
}

static double ** InitializeDistArray(Graph g) {

    // Create 2D array
    double ** dist = calloc(numVertices(g) , sizeof(double *));
    for(int i = 0; i < numVertices(g); i++) {
        dist[i] = calloc(numVertices(g) , sizeof(double));
    }

    // Initialize array to IFINITY values
    for(int i = 0; i < numVertices(g); i++) {
        for(int j = 0; j < numVertices(g); j++) {
            dist[i][j] = INFINITY;
        }
    }

    // Calculate distance between vertices i-j
    // according to given distance matrix
    for(int i = 0; i < numVertices(g); i++) {
        AdjList curr = outIncident(g , i);
        while(curr != NULL) {
            float distance =  1 / (float) curr->weight;
            if(dist[i][curr->w] > distance) {
                dist[i][curr->w] = distance;
                dist[curr->w][i] = distance;
            }
            curr = curr->next;
        }
    }
    return dist;
}

static Dendrogram MakeDNode (Vertex v) {
    Dendrogram new_DNode = malloc(sizeof(struct DNode));
    new_DNode->vertex = v;
    new_DNode->left = NULL;
    new_DNode->right = NULL;
    return new_DNode;
}

static void PrintDendArray (Dendrogram * D , int size) {
    for(int i = 0; i < size; i++) {
        printf("VERTEX : %d\n" , D[i]->vertex);
    }
}

void freeDendrogram(Dendrogram d) {
	return;
}
