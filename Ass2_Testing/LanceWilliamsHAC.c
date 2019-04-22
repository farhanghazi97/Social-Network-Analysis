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
//static void PrintDendArray (Dendrogram * D , int size);
// static void PrintDistArray (double ** dist_array , int size) {
//     // Pretty print array
//     for(int i = 0; i < size; i++) {
//         for(int j = 0; j < size; j++) {
//             printf("%.4lf\t" , dist_array[i][j]);
//         }
//         printf("\n");
//     }
// }
//static void PrintDistArray (double ** dist_array , int size);
static Dendrogram MakeEmptyDNode ();
static double ** MakeNewDistArray(int size);
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
    int N = numVertices(g);
    Dendrogram * dendA = malloc(N * sizeof(DNode));
    for(int i = 0; i < N; i++) {
        dendA[i] = MakeDNode(i);
    }
    
    // PrintDistArray(dist_array , N);
    int matSize = N;
    for(int s = 0; s < N; s++){
        // Find closest clusters and grab those indices
        float minimum = INFINITY;
        int index1 = 0;
        int index2 = 0; 
        for(int i = 0; i < matSize;i++){
            for(int j = 0; j < matSize;j++){
                if(dist_array[j][i] <= minimum){
                    //grabbing these indices
                    minimum = dist_array[j][i];
                    index1 = j;
                    index2 = i;
                }
            }
        }

        // By now we would know which clusters to merge
        // Need to remove items/clean the dendA
        // printf("Minimum: %lf\n",minimum);
        // printf("Index 1: %d\n",index1);
        // printf("Index 2: %d\n",index2);
        if(index1>index2){
            // I want index1 to be less than index2
            int temp = index1;
            index1 = index2;
            index2 = temp;
        }
        // printf("Index 1: %d\n",index1);
        // printf("Index 2: %d\n",index2);
        Dendrogram newCluster = MakeEmptyDNode();
        newCluster->left = dendA[index1];
        newCluster->right = dendA[index2];
        // Begin resizing dendA
        matSize--;
        for(int i = 0; i < matSize; i++){
            //Wanna keep all cells before index1 intact only moving cells after
            if(i == matSize -1) {
                dendA[i] = newCluster;
            } else {
                if(i >= index1) { dendA[i] = dendA[i+1]; }
                if(i >= index2-1) { dendA[i] = dendA[i+2]; }
            }

        }
        //By now we would have the new dendA array
        //Create new dist array and perform calculation
        double ** updatedDist = MakeNewDistArray(matSize);
        for(int i = 0; i < matSize;i++){
            for(int j = i; j < matSize;j++){
                if (j == i) {
                    continue;
                }
                if (j == matSize-1){
                    int grabIndex = i;
                    if( i>= index1){
                        grabIndex++;
                    }
                    if( i>= index2-1 ){
                        grabIndex++;
                    }
                    double num1 = dist_array[index1][grabIndex];
                    double num2 = dist_array[index2][grabIndex];
                    if(!(num1 < INFINITY)){ num1 = dist_array[grabIndex][index1];}
                    if(!(num2 < INFINITY)){ num2 = dist_array[grabIndex][index2];}
                    
                    if (num1<num2){
                        updatedDist[j][i] = num1;
                        updatedDist[i][j] = num1;
                    } else {
                        updatedDist[j][i] = num2;
                        updatedDist[i][j] = num2;
                    }
                    continue;
                }

                if (i < index1) {
                    if (j < index1) { updatedDist[j][i] = dist_array[j][i]; updatedDist[i][j] = dist_array[j][i]; }
                    if (j >= index1) { updatedDist[j][i] = dist_array[j+1][i]; updatedDist[i][j] = dist_array[j+1][i]; }
                    if (j >= index2-1) { updatedDist[j][i] = dist_array[j+2][i]; updatedDist[i][j] = dist_array[j+2][i]; }
                } 
                if (i >= index1) {
                    if (j < index1) { updatedDist[j][i] = dist_array[j][i+1]; updatedDist[i][j] = dist_array[j][i+1]; }
                    if (j >= index1) { updatedDist[j][i] = dist_array[j+1][i+1]; updatedDist[i][j] = dist_array[j+1][i+1]; }
                    if (j >= index2-1) { updatedDist[j][i] = dist_array[j+2][i+1]; updatedDist[i][j] = dist_array[j+2][i+1]; }
                }

                if (i >= index2-1) {
                    if (j < index1) { updatedDist[j][i] = dist_array[j][i+2]; updatedDist[i][j] = dist_array[j][i+2]; }
                    if (j >= index1) { updatedDist[j][i] = dist_array[j+1][i+2]; updatedDist[i][j] = dist_array[j+1][i+2]; }
                    if (j >= index2-1) { updatedDist[j][i] = dist_array[j+2][i+2]; updatedDist[i][j] = dist_array[j+2][i+2]; }
                }
            }
        }
        for(int i = 0; i < matSize; i++) {
            for(int j = 0; j < matSize; j++){
                dist_array[j][i] = updatedDist[j][i];
            }
        }
        for(int i = 0; i < matSize; i++){
            free(updatedDist[i]);
        }
        free(updatedDist);
        //PrintDistArray(dist_array , matSize);
    }
    
    // Free array
    for(int i = 0; i < numVerticies(g); i++){
        free(dist_array[i]);
    }
    free(dist_array);
    return dendA[0];
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
        AdjList curr = outIncident(g,i);
        AdjList curr1 = inIncident(g,i);
        while(curr != NULL) {
            float distance =  1 / (float) curr->weight;
            if(dist[i][curr->w] > distance || dist[curr->w][i] > distance) {
                dist[i][curr->w] = distance;
                dist[curr->w][i] = distance;
            }
            curr = curr->next;
        }
        while(curr1 != NULL) {
            float distance =  1 / (float) curr1->weight;
            if(dist[i][curr1->w] > distance || dist[curr1->w][i] > distance) {
                dist[i][curr1->w] = distance;
                dist[curr1->w][i] = distance;
            }
            curr1 = curr1->next;
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

static Dendrogram MakeEmptyDNode () {
    Dendrogram new_DNode = malloc(sizeof(struct DNode));
    new_DNode->left = NULL;
    new_DNode->right = NULL;
    return new_DNode;
}

// static void PrintDendArray (Dendrogram * D , int size) {
//     for(int i = 0; i < size; i++) {
//         printf("VERTEX : %d\n" , D[i]->vertex);
//     }
// }

void freeDendrogram(Dendrogram d) {
    if(d != NULL) {
        freeDendrogram(d->left);
        freeDendrogram(d->right);
        free(d);
    }
}

static double ** MakeNewDistArray(int size) {
    // Create 2D array
    double ** dist = calloc(size, sizeof(double *));
    for(int i = 0; i < size; i++) {
        dist[i] = calloc(size , sizeof(double));
    }

    // Initialize array to IFINITY values
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            dist[i][j] = INFINITY;
        }
    }
    return dist;
}
