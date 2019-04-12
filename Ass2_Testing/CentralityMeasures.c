// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "GraphVis.h"

NodeValues outDegreeCentrality(Graph g){

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {
		AdjList curr = outIncident(g , i);
		float count = 0;
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
		float count = 0;
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

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {
		AdjList out_curr = outIncident(g , i);
		float out_count = 0;
		if(out_curr != NULL) {
			while(out_curr != NULL) {
				out_count++;
				out_curr = out_curr->next;
			}
		}
		AdjList in_curr = inIncident(g , i);
		float in_count = 0;
		if(in_curr != NULL) {
			while(in_curr != NULL) {
				in_count++;
				in_curr = in_curr->next;
			}
		}
		float total_count = out_count + in_count;
		new_NV.values[i] = total_count;
	}

	return new_NV;
}

NodeValues closenessCentrality(Graph g){

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {
		ShortestPaths paths = dijkstra(g , i);
		double sum_of_paths = 0;
		for(int i = 0; i < paths.noNodes; i++) {
			sum_of_paths += paths.dist[i];
		}
		new_NV.values[i] = (numVerticies(g) - 1) / sum_of_paths;
	}
	return new_NV;
}


NodeValues betweennessCentrality(Graph g){
	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g),sizeof(double));
	int *pathCountArr = calloc(numVerticies(g),sizeof(int));
	assert(new_NV.values != NULL);
	graphVis(g,0);
	for (int i = 0; i < new_NV.noNodes; i++){
		ShortestPaths paths = dijkstra(g,i);
		for (int j = 0; j <paths.noNodes; j++){
			struct PredNode * curr = paths.pred[j];
			if(curr!=NULL) {
				int pathCount = 0;
				while(curr!=NULL) {
					if(curr->v != i){
						new_NV.values[curr->v]++;
						printf("Vertex %d Found\n",curr->v);
					}
					curr = curr->next;
					pathCount++;
				}
				printf("Pair %d and %d = %d\n",i,j,pathCount);
				//Gotta reset curr pointer back to update pathCountArr
				struct PredNode * curr = paths.pred[j];
				while(curr!=NULL){
					if(curr->v != i){
						pathCountArr[curr->v]+=pathCount;
						printf("Update path array of %d to %d\n",curr->v,pathCountArr[curr->v]);
						
					}
					curr = curr->next;
				}
			}
		}
	}
	//Counting done;
	//Now we scale
	// for (int i = 0; i<new_NV.noNodes; i++){
	// 	new_NV.values[i] = new_NV.values[i]/(numVerticies(g)-1); 
	// }
	for (int i = 0; i<new_NV.noNodes; i++){
		if(new_NV.values[i]!=0){
			new_NV.values[i] = new_NV.values[i]/(double)pathCountArr[i]; 
		}
		
	}
	return new_NV;
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

//static void fillBetween(double value[],)