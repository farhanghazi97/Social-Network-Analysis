/*
  Lance-Williams Algorithm for Agglomerative Clustering
  Written by Kanadech Jirapongtanavech (z5176970) & Farhan Ghazi (z5199861)
  COMP2521 2019 T1
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "LanceWilliamsHAC.h"
#include "Graph.h"
#define numVertices numVerticies

// ---------- STATIC FUNCTIONS START ---------- //

// Function to create initial distance matrix
static double ** InitializeDistArray(Graph g);
// Function to create new distance matrix
static double ** MakeNewDistArray(int size);
// Function to make new Dendrogram node
static Dendrogram MakeDNode (Vertex v);
// Function to make empty dendrogram node during merging
static Dendrogram MakeEmptyDNode ();

// ---------- STATIC FUNCTIONS END ---------- //


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
    // initialise dendrogram array
    for(int i = 0; i < N; i++) {
        dendA[i] = MakeDNode(i);
    }

    int matSize = N;
    for(int s = 0; s < N; s++){
        // Find closest clusters and grab those indices
        float minimum = INFINITY;
        int index1 = 0;
        int index2 = 0; 
        for(int i = 0; i < matSize;i++){
            for(int j = i+1; j < matSize;j++){
                if(dist_array[j][i] <= minimum){
                    //grabbing indices corresponding to the minimum distance
                    minimum = dist_array[j][i];
                    index1 = j;
                    index2 = i;
                }
            }
        }
        if(index1>index2){
            // sort the the two indices
            // making index 1 less than index 2
            int temp = index1;
            index1 = index2;
            index2 = temp;
        }

        // Merging two clusters that are shortest distance apart
        Dendrogram newCluster = MakeEmptyDNode();
        newCluster->left = dendA[index1];
        newCluster->right = dendA[index2];

        // Reduce the size to N-1
        matSize--;

        for(int i = 0; i < matSize; i++){
            // Placing newly formed cluster at the back of dendrogram array
            if(i == matSize -1) {
                dendA[i] = newCluster;
            } else {
                /*
                Data in array should be shifted by 1 to the left if its position
                between index1 and index2-1
                Data after at array[index2-1] should be shifted to the left twice
                */
                if(i >= index1) { dendA[i] = dendA[i+1]; }
                if(i >= index2-1) { dendA[i] = dendA[i+2]; }
            }

        }
        /*
            Create a new distance matrix and update it using matrix manipulation
            Last row of the new matrix is the distance between the newly merged cluster and
            other existing clusters.
                        Col i       Col i+1       Col i+2
            Row j       a[j][i]     a[j][i+1]     a[j][i+2]  
            Row j+1     a[j+1][i]   a[j+1][i+1]   a[j+1][i+2]
            Row j+2     a[j+2][i]   a[j+2][i+1]   a[j+2][i+2]
        */
        double ** updatedDist = MakeNewDistArray(matSize);
        for(int i = 0; i < matSize;i++){
            for(int j = i; j < matSize;j++){
                if (j == i) {
                    continue;
                }
                // When j is the last row, update its distance cells using Lance William
                if (j == matSize -1){
                    /*
                        When accessing the previous distance matrix, possible index shifting must be accounted for
                        because we remove those clusters, 2 rows and 2 columns get removed, and appended
                        the merged one as the last row of the matrixs
                    */
                    int accessIndex = i;
                    
                    if(i>= index1){
                        // Shift by 1 column
                        accessIndex++;
                    }
                    if(i>= index2-1){
                        // Shift by 2 columns
                        accessIndex++;
                    }
                    /*
                        Obtain two numbers Dist(c_i,c_k) and Dist(c_j,c_k)
                        Choose min for single link or max for complete link
                    */
                    double num1 = dist_array[index1][accessIndex];
                    double num2 = dist_array[index2][accessIndex];
                    if (method == 1){
                        // Single link
                        // Update both indices for symmetry
                        if (num1<num2){
                            updatedDist[j][i] = num1;
                            updatedDist[i][j] = num1;
                        } else {
                            updatedDist[j][i] = num2;
                            updatedDist[i][j] = num2;
                        } 
                    } else if (method == 2) {
                        // Complete link
                        // Update both indices for symmetry
                        if (num1>num2){
                            updatedDist[j][i] = num1;
                            updatedDist[i][j] = num1;
                        } else {
                            updatedDist[j][i] = num2;
                            updatedDist[i][j] = num2;
                        } 
                    }
                    // Because this is guaranteed to be the last row we can skip the rest of the code below
                    continue;
                }
                /*
                    This section of distance matrix update executes when j is not the last row
                    No LW needed, just matrix manipulation.
                    If the current column i is less than index1, no right horizontal shifting needed
                    If the current column i is between index1 and index2-1, 1 right horizontal shifting is needed
                    If the current column i is more than or equal to index2-1, 2 right horizontal shifting is needed
                */
                if (i < index1) {
                    /*
                        Similar to horizontal shifting, vertical shifting is also required on certain cases
                        If the current row j is less than index1, no vertical shifting needed
                        If the current row j is between index1 and index2-1, 1 down vertical shifting is needed
                        If the current row j is more than or equal to index2-1, 2 down vertical shifting is needed
                    */
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
        // Copy updated matrix to the original distance matrix
        for(int i = 0; i < matSize; i++) {
            for(int j = 0; j < matSize; j++){
                dist_array[j][i] = updatedDist[j][i];
            }
        }
        // Free the created updated distance matrix
        for(int i = 0; i < matSize; i++){
            free(updatedDist[i]);
        }
        free(updatedDist);

    }
    
    // Free original distance matrix
    for(int i = 0; i < numVerticies(g); i++){
        free(dist_array[i]);
    }
    free(dist_array);
    // Return the dengrogram at index 0
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
        AdjList currOut = outIncident(g,i);
        AdjList currIn = inIncident(g,i);
        /*
            Grab outlinks and inlinks of vertex in question (i)
            For every outlinks and inlinks find its distance and update the distance matrix
            accordingly
        */
        while(currOut != NULL) {
            float distance =  1 / (float) currOut->weight;
            // Choosing higher weight implies smaller distance
            // Compare the current distance in the cell and update it if the calculated
            // distance is smaller
            if(dist[i][currOut->w] > distance || dist[currOut->w][i] > distance) {
                dist[i][currOut->w] = distance;
                dist[currOut->w][i] = distance;
            }
            currOut = currOut->next;
        }
        while(currIn != NULL) {
            float distance =  1 / (float) currIn->weight;
            // Choosing higher weight implies smaller distance
            // Compare the current distance in the cell and update it if the calculated
            // distance is smaller
            if(dist[i][currIn->w] > distance || dist[currIn->w][i] > distance) {
                dist[i][currIn->w] = distance;
                dist[currIn->w][i] = distance;
            }
            currIn = currIn->next;
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
    // Set vertex to -1 because it does not matter
    Dendrogram new_DNode = malloc(sizeof(struct DNode));
    new_DNode->vertex = -1;
    new_DNode->left = NULL;
    new_DNode->right = NULL;
    return new_DNode;
}


// Function to free dendrogram
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
