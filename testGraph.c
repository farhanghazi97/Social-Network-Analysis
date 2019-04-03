#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(void) {

	Graph new_graph = newGraph(10);
	int * array = ReadFile("input_file");
	
	AdjList * curr = GetConnectionsArray(new_graph);
	for(int i = 0; i < 1; i++) {
		curr[i] = newAdjListNode(array[0] , array[2]);
	}
	
	printf("Vertex: %d\nWeight: %d\n" , NodeVertex(curr[0]) , NodeWeight(curr[0]));
	
	free(array);
	
	
}
