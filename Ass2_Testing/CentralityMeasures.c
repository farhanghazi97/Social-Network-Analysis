// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "GraphVis.h"

static double numPathThroughV(int s,int t, int v, PredNode **pred);
static double numPath(int s,int t, PredNode **pred);

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
	//int *pathCountArr = calloc(numVerticies(g),sizeof(int));
	assert(new_NV.values != NULL);
	graphVis(g,0);
	for (int v = 0; v < new_NV.noNodes; v++){
		for (int s = 0; s < new_NV.noNodes; s++){
			if(v == s){
				continue;
			}
			ShortestPaths paths = dijkstra(g,s);
			for (int t = 0; t <paths.noNodes; t++){
				if(s == t || v == t){
					continue;
				}
				double npv = numPathThroughV(s,t,v,paths.pred);
				double n = numPath(s,t,paths.pred);
				printf("%f~~%f~~s~%d~t~%d~v~%d\n",npv,n,s,t,v);
				if(n){
					new_NV.values[v] = new_NV.values[v] + npv/n;
				}
				
			}
		}
	}
	//Counting done;
	//Now we scale
	// for (int i = 0; i<new_NV.noNodes; i++){
	// 	new_NV.values[i] = new_NV.values[i]/(numVerticies(g)-1); 
	// }
	// for (int i = 0; i<new_NV.noNodes; i++){
	// 	if(new_NV.values[i]!=0){
	// 		printf("Value before scale = %lf\n",new_NV.values[i]);
	// 		new_NV.values[i] = new_NV.values[i]/(double)pathCountArr[i]; 
	// 	}
		
	// }
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

static double numPathThroughV(int s,int t, int v, PredNode **pred){
	double count = 0;
	struct PredNode *curr = pred[t];
	if(!curr){
		return 0;
	}
	// if(curr->v == s){
	// 	//count = 1;
	// 	curr = curr->next;
	// }
	if(curr->v == v){
		count = 1;
		curr = curr->next;
	}
	while(curr!=NULL) {
		t = curr->v;
		count = numPathThroughV(s,t,v,pred) + count;
		curr = curr->next;
	}
	return count;
}

static double numPath(int s,int t, PredNode **pred){
	double count = 0;
	if(pred[t]==NULL){
		return 0;
	}
	struct PredNode *curr = pred[t];
	if(curr->v == s){
		count = 1;
		curr = curr->next;
	}
	while(curr!=NULL){
		t = curr->v;
		count = numPath(s,t,pred) + count;
		curr = curr->next;
	}
	return count;
}