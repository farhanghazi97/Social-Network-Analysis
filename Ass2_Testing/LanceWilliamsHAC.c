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

typedef struct Cluster {

} Cluster;

static double ** InitializeDistArray(Graph g);

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

    // Pretty print array
    for(int i = 0; i < numVertices(g); i++) {
        for(int j = 0; j < numVertices(g); j++) {
            printf("%.3lf\t" , dist_array[i][j]);
        }
        printf("\n");
    }

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

void freeDendrogram(Dendrogram d) {
	return;
}
