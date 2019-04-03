#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(void) {

	Graph new_graph = newGraph(MAX_NODES);
	int * array = ReadFile("input_file");
	
	AdjList * curr = GetConnectionsArray(new_graph);
	
	// The readFile() function only grabs vertex number and weight (for now) , puts it 
	// an array and returns it which we then use to modify our graph structure. 

	// The readFile() function only returns the array without returning size of array 
	// (problematic). Down below, I've assumed that we know the size of the array 
	// for testing purposes. Ideally, we'd want the readFile function to also return
	// size of array so we know what the range to iterate over.
		
	
	int i = 0;
	int j = 0;
	int carry;
	while(i < 15) {
		if(i == 0) {
			curr[j] = newAdjListNode(array[i] , array[i+2]);	
		} else {
			i = i + 2;
			curr[j] = newAdjListNode(array[i] , array[i+2]);
		}
		i++;
		j++;
	}
	
	for(int i = 0; i < MAX_NODES; i++) {
		if(curr[i] != NULL) {
			printf("Vertex: %d\nWeight: %d\n\n" , NodeVertex(curr[i]) , NodeWeight(curr[i]));
			}
	}
	
	
	
	
	free(array);
	
	
}
