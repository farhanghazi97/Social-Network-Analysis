// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

NodeValues outDegreeCentrality(Graph g){

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {
		AdjList curr = outIncident(g , i);
		int count = 0;
		if(curr != NULL) {
			while(curr != NULL) {
				count++;
				curr = curr->next;
			}
		}
		new_NV.values[i] = count;
	}
	return new_NV;
}
NodeValues inDegreeCentrality(Graph g){

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {
		AdjList curr = inIncident(g , i);
		int count = 0;
		if(curr != NULL) {
			while(curr != NULL) {
				count++;
				curr = curr->next;
			}
		}
		new_NV.values[i] = count;
	}
	return new_NV;

}
NodeValues degreeCentrality(Graph g) {
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues closenessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues throwAway = {0};
	return throwAway;
}

void showNodeValues(NodeValues values){
	for(int i = 0; i < values.noNodes; i++) {
		printf("%d: %lf\n" , i , values.values[i]);
	}
}

void freeNodeValues(NodeValues values){
	free(values.values);
}
