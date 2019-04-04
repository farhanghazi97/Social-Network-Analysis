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
	
	// Print graph to test output
	showGraph(new_graph);
	
	// Test InsertEdge() function
	printf("\nInserting (3 , 5 , 20)\n\n");
	InsertEdge(new_graph , 3 , 5 , 20); 
	showGraph(new_graph);
	
	printf("\nInserting (0, 6 , 12)\n\n");
	InsertEdge(new_graph , 0 , 6 , 12);
	showGraph(new_graph);
	
	// Test RemoveEdge() function (still buggy - don't know why)
	//printf("\nRemoving (2 , 1 , 6)\n\n");
	//RemoveEdge(new_graph , 2 , 4);
	//showGraph(new_graph);
	
	// Test Adjacent() function
	bool flag;
	
	printf("\nIs 3 adjacent to 5 ?\n");
	flag = Adjacent(new_graph , 3 , 5);
	if(flag) {
		printf("Adjacent\n\n");
	} else {
		printf("Not adjacent\n\n");
	}
	
	// Free malloc'd DATA ARRAY
	free(array);
	FreeEdgesArray(edges , number_of_edges);
	FreeGraph(new_graph);
	
}
