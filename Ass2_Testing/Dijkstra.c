// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
typedef struct PredNode * PNode;
static struct PredNode * NewPredNode (int val);
ShortestPaths dijkstra(Graph g, Vertex v) {

	PQ new_PQ = newPQ();
	ItemPQ item;
	int *visited = calloc(numVerticies(g),sizeof(int));
	ShortestPaths static_SP;
	static_SP.noNodes = numVerticies(g);
	static_SP.src = v;
	static_SP.dist = malloc(numVerticies(g)*sizeof(int));
	for(int i = 0; i < static_SP.noNodes; i++) {
		static_SP.dist[i] = 1000000;
	}
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

	// NOT IMPLEMENTED: If connection does not exist, dist defualts to 1000000
	// (BAD!)

	ItemPQ temp;
	while(!(PQEmpty(new_PQ))) {
		ItemPQ vertex = dequeuePQ(new_PQ);
		printf("Pop %d\n",vertex.key);
		if (!visited[vertex.key]) {
			visited[vertex.key] = 1;					//mark as visited first
			AdjList curr = outIncident(g , vertex.key); //grab outIncident List
			while(curr) {
				temp.key = curr->w;
				temp.value = curr->weight;
				printf("Check %d\n",curr->w);
				if(static_SP.dist[temp.key] >= static_SP.dist[vertex.key] + temp.value) {
					if (static_SP.dist[temp.key] == static_SP.dist[vertex.key] + temp.value){
						struct PredNode *curr1 = static_SP.pred[temp.key];
						while(curr1->next != NULL){
							printf("Curr is %d\n",curr1->v);
							curr1 = curr1->next;
						}
						curr1->next = NewPredNode(vertex.key);
					} else {
						static_SP.pred[temp.key] = NewPredNode(vertex.key);
						static_SP.dist[temp.key] = static_SP.dist[vertex.key] + temp.value;
						printf("Update %d dist to %d\n",temp.key,static_SP.dist[temp.key]);
						addPQ(new_PQ , temp);
						printf("Add %d to Q\n",temp.key);
					}
				}
				curr = curr->next;
			}
			printf("End while\n");
		}
	}
	for(int i = 0; i < numVerticies(g); i++) {
		if (!visited[i]) {
			static_SP.dist[i] = 0;
		}
	}


	//Throwing error!
	//freePQ(new_PQ);

	return static_SP;
}

void showShortestPaths(ShortestPaths paths) {

}


void  freeShortestPaths(ShortestPaths paths) {

}

static struct PredNode * NewPredNode (int val){
	struct PredNode * new_node = malloc(sizeof(struct PredNode));
	new_node->v = val;
	new_node->next = NULL;
	return new_node;
}