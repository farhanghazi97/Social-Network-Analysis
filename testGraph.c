#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(void) {
	
	//Extract data from file and store in DATA ARRAY
	int * array = ReadFile("input_file");
	
	// Determine how many edge objects we need
	int number_of_edges = array[0]/3;
	
	// Based on number of edges needed , we declare an array of edge objects
	Edge edges[number_of_edges];
	
	int j = 0;
	
	// We populate edge objects with data from DATA ARRAY and place them
	// in an EDGES ARRAY
	
	for(int i = 1; i < array[0]; i = i + 3) {
		Edge new_edge = newEdge(array[i] , array[i+1] , array[i+2]); 
		edges[j] = new_edge;
		j++;
	}
	
	// Using data from the array of edges , we construct graph
	Graph new_graph = newGraph(edges , number_of_edges);
	
	showGraph(new_graph);
	
	free(array);
	
}
