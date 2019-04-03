#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(void) {

	Graph new_graph = newGraph(MAX_NODES);
	int * array = ReadFile("input_file");
	
	AdjList * curr = GetConnectionsArray(new_graph);
	
	
	
	
	
	free(array);
	
	
}
