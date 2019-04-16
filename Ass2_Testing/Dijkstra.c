// Dijkstra ADT interface for Ass2 (COMP2521)

#include "Dijkstra.h"
#include "PQ.h"
#include "BSTree.h"
#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct PredNode * PNode;

static PNode NewPredNode (int val);

ShortestPaths dijkstra(Graph g, Vertex v) {

	// Initialize priority queue for Dijkstra
	PQ new_PQ = newPQ();
	ItemPQ item;

	// Visited array for Dijkstra
	int *visited = calloc(numVerticies(g),sizeof(int));

	// Initialize struct
	ShortestPaths static_SP;
	static_SP.noNodes = numVerticies(g);
	static_SP.src = v;

	// Set dist values to a very large value mimicking infinity
	static_SP.dist = malloc(numVerticies(g)*sizeof(int));
	for(int i = 0; i < static_SP.noNodes; i++) {
		static_SP.dist[i] = 1000000;
	}

	// Initialize all pred pointers to intially point to NULL
	static_SP.pred = malloc(numVerticies(g)*sizeof(struct PredNode*));
	for (int i=0; i<numVerticies(g);i++){
		static_SP.pred[i]=NULL;
	}

	// Add souce vertex to priority queue with shortest distance 0

	static_SP.dist[v] = 0;
	item.key = v;
	item.value = 0;
	addPQ(new_PQ , item);

	// While the priority queue is not empty, grab highest priority vertex and
	// find all its neighbours. Calculate distance between source and egdes and
	// update the array if shortest path is found.

	ItemPQ temp;
	while(!(PQEmpty(new_PQ))) {
		ItemPQ vertex = dequeuePQ(new_PQ);
		if (!visited[vertex.key]) {
			visited[vertex.key] = 1;
			AdjList curr = outIncident(g , vertex.key);
			while(curr) {
				temp.key = curr->w;
				temp.value = curr->weight;
				if(static_SP.dist[temp.key] >= static_SP.dist[vertex.key] + temp.value) {
					if (static_SP.dist[temp.key] == static_SP.dist[vertex.key] + temp.value){
						PNode curr1 = static_SP.pred[temp.key];
						while(curr1->next != NULL){
							curr1 = curr1->next;
						}
						curr1->next = NewPredNode(vertex.key);
					} else {
						static_SP.pred[temp.key] = NewPredNode(vertex.key);
						static_SP.dist[temp.key] = static_SP.dist[vertex.key] + temp.value;
						addPQ(new_PQ , temp);
					}
				}
				curr = curr->next;
			}
		}
	}

	// Account for nodes that are unreachable
	for(int i = 0; i < numVerticies(g); i++) {
		if (!visited[i]) {
			static_SP.dist[i] = 0;
		}
	}

	// Free memory needed for visited array
	free(visited);
	return static_SP;
}

void showShortestPaths(ShortestPaths paths) {
	int i = 0;
	printf("Node %d\n",paths.src);
	printf("  Distance\n");
	for (i = 0; i < paths.noNodes; i++) {
		if(i == paths.src) {
	    	printf("    %d : X\n",i);
		} else {
			printf("    %d : %d\n", i , paths.dist[i]);
		}
	}
	printf("  Preds\n");
	for (i = 0; i < paths.noNodes; i++) {
		printf("    %d : ",i);
		PNode curr = paths.pred[i];
		while(curr!=NULL) {
			printf("[%d]->",curr->v);
			curr = curr->next;
		}
		printf("NULL\n");
	}
}


void freeShortestPaths(ShortestPaths paths) {
	free(paths.dist);
	for(int i = 0; i < paths.noNodes; i++) {
		PNode curr = paths.pred[i];
		if(curr != NULL) {
			while(curr->next != NULL) {
				PNode temp = curr;
				free(temp);
				curr = curr->next;
			}
		}
	}
	free(paths.pred);
}

static PNode NewPredNode (int val){
	struct PredNode * new_node = malloc(sizeof(struct PredNode));
	new_node->v = val;
	new_node->next = NULL;
	return new_node;
}
