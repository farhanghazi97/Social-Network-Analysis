// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

ShortestPaths dijkstra(Graph g, Vertex v) {

	PQ new_PQ = newPQ();
	ItemPQ item;

	ShortestPaths static_SP;
	static_SP.noNodes = numVerticies(g);
	static_SP.src = v;
	static_SP.dist = malloc(numVerticies(g) * sizeof(int));
	for(int i = 0; i < static_SP.noNodes; i++) {
		static_SP.dist[i] = 1000000;
	}
	static_SP.pred = NULL;

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
		AdjList curr = outIncident(g , vertex.key);
		while(curr != NULL) {
			temp.key = curr->w;
			temp.value = curr->weight;
			if(static_SP.dist[temp.key] > static_SP.dist[vertex.key] + temp.value) {
				static_SP.dist[temp.key] = static_SP.dist[vertex.key] + temp.value;
				addPQ(new_PQ , temp);
			}
			curr = curr->next;
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
