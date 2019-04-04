#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// Test bed for graph ADT

// TODO: Adjacent()
//       outIncident()
//		 inIncident()

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

	printf("// ---------- INITIAL STATE OF GRAPH ---------- //\n\n");

	// Print graph to test output
	showGraph(new_graph);

	printf("\n// ---------- TEST INSERTEDGE() FUNCTION ---------- //\n");

	// ---------- TEST INSERTEDGE() FUNCTION ---------- //
	printf("\nInserting ( 3 --> 5 (20) )\n\n");
	InsertEdge(new_graph , 3 , 5 , 20);
	showGraph(new_graph);

	printf("\nInserting ( 0 --> 6 (12) )\n\n");
	InsertEdge(new_graph , 0 , 6 , 12);
	showGraph(new_graph);

	printf("\nInserting ( 4 --> 8 (25) )\n\n");
	InsertEdge(new_graph , 4 , 8 , 25);
	showGraph(new_graph);

	printf("\n// ---------- TEST OUTINCIDENT() FUNCTION ----------//\n\n");

	AdjNode OutList = outIncident(new_graph , 2);
	PrintAdjList(OutList);

	printf("\n// ---------- TEST ADJACENT() FUNCTION ---------- //\n");

	// ---------- TEST ADJACENT() FUNCTION ---------- //
	bool flag;
	printf("\nIs 3 adjacent to 5 ?\n");
	flag = Adjacent(new_graph , 3 , 5);

	if(flag) {
		printf("Adjacent\n\n");
	} else {
		printf("Not adjacent\n\n");
	}

	printf("\n// ---------- TEST REMOVEEDGE() FUNCTION ---------- //\n");

	// ---------- TEST REMOVEEDGE() FUNCTION ---------- //
	printf("\nRemoving (2 --> 10) - HEAD OF LIST\n\n");
	RemoveEdge(new_graph , 2 , 10);
	showGraph(new_graph);

	printf("\nRemoving (2 --> 1) - INBETWEEN HEAD AND TAIL\n\n");
	RemoveEdge(new_graph , 2, 1);
	showGraph(new_graph);

	printf("\nRemoving (2 --> 7) - INBETWEEN HEAD AND TAIL\n\n");
	RemoveEdge(new_graph , 2, 7);
	showGraph(new_graph);

	printf("\nRemoving (2 --> 4) - TAIL OF SAME LIST\n\n");
	RemoveEdge(new_graph , 2, 4);
	showGraph(new_graph);

	printf("\nRemoving (0 --> 4) - TAIL OF DIFFERENT LIST (1)\n\n");
	RemoveEdge(new_graph , 0, 4);
	showGraph(new_graph);

	printf("\nRemoving (3 --> 2) - TAIL OF DIFFERNT LIST (2)\n\n");
	RemoveEdge(new_graph , 3, 2);
	showGraph(new_graph);

	printf("\nRemoving (3 --> 5) - SINGLE NODE (HEAD + TAIL)\n\n");
	RemoveEdge(new_graph , 3, 5);
	showGraph(new_graph);

	printf("\nRemoving (0 --> 6) - SINGLE NODE (HEAD + TAIL)\n\n");
	RemoveEdge(new_graph , 0, 6);
	showGraph(new_graph);

	printf("\nRemoving (2 --> 3)\n\n");
	RemoveEdge(new_graph , 2, 3);
	showGraph(new_graph);

	printf("\nRemoving (2 --> 8)\n\n");
	RemoveEdge(new_graph , 2, 8);
	showGraph(new_graph);

	printf("\nRemoving (2 --> 9) - INVALID INPUT\n\n");
	RemoveEdge(new_graph , 2 , 9);
	showGraph(new_graph);

	printf("\nRemoving (1 --> 4) - INVALID INPUT\n\n");
	RemoveEdge(new_graph , 1 , 4);
	showGraph(new_graph);

	printf("\nRemoving (4 --> 9) - INVALID INPUT\n\n");
	RemoveEdge(new_graph , 4 , 9);
	showGraph(new_graph);

	printf("\nRemoving (1 --> 3)\n\n");
	RemoveEdge(new_graph , 1 , 3);
	showGraph(new_graph);

	printf("\nRemoving (4 --> 8)\n\n");
	RemoveEdge(new_graph , 4 , 8);
	showGraph(new_graph);

	printf("\nRemoving (1 --> 2)\n\n");
	RemoveEdge(new_graph , 1 , 2);
	showGraph(new_graph);

	printf("\nRemoving (4 --> 6)\n");
	RemoveEdge(new_graph , 4 , 6);
	showGraph(new_graph);

	printf("\nALL CONNECTIONS REMOVED AT THIS POINT - EMPTY GRAPH\n\n");

	// Free malloc'd DATA ARRAY
	free(array);
	FreeEdgesArray(edges , number_of_edges);
	FreeGraph(new_graph);

}
