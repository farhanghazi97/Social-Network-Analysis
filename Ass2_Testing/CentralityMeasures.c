// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "GraphVis.h"

// ---------- STATIC FUNCTIONS START ---------- //

static double numPathThroughV(int s,int t, int v, PredNode **pred);
static double numPath(int s,int t, PredNode **pred);

// ---------- STATIC FUNCTIONS END ---------- //

// Function to calculate outDegree centrality
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

// Function to calculate inDegree centrality
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

// Function to calculate degree centrality 
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

// Function to calculate closeness centrality
NodeValues closenessCentrality(Graph g){

	// Initialize static NodeValues struct
	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {

		// Perform Dijkstra on current vertex to obtain ShortestPaths struct
		ShortestPaths paths = dijkstra(g , i);

		// Counters to keep track of sum of paths and count
		double sum_of_paths = 0;
		double count = 0.0;

		// Count the number of paths from verte
		for(int i = 0; i < paths.noNodes; i++) {
			sum_of_paths += paths.dist[i];
			if(paths.dist[i]){
				count++;
			}
		}

		// If sum of paths is 0 , closeness is set to 0
		if(sum_of_paths <= 0.0) {
			new_NV.values[i] = 0.0;
		} else {
			// Otherwise, we use the Wasserman and Faust formula
			// for closeness
			new_NV.values[i] = ((count) * (count)) / ((numVerticies(g) - 1) * sum_of_paths);
		}
	}
	return new_NV;
}

// Function to calculate betweenness centrality
NodeValues betweennessCentrality(Graph g){

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g),sizeof(double));
	assert(new_NV.values != NULL);

	for (int v = 0; v < new_NV.noNodes; v++){
		for (int s = 0; s < new_NV.noNodes; s++){
			if(v == s){
				continue;
			}
			ShortestPaths paths = dijkstra(g,s);
			for (int t = 0; t < paths.noNodes; t++){
				if(s == t || v == t){
					continue;
				}
				double npv = numPathThroughV(s, t, v, paths.pred);
				double n = numPath(s,t,paths.pred);
				double nv1 = numPath(s,v,paths.pred);
				double nv2 = numPath(v,t,paths.pred);
				npv = nv1*nv2;
				if(n){
					new_NV.values[v] = new_NV.values[v] + npv/n;
				}

			}
		}
	}
	return new_NV;
}

// Function to calculate normalised betweenness centrality
NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues new_NV = betweennessCentrality(g);
	for(int i = 0; i < new_NV.noNodes; i++) {
		new_NV.values[i] = new_NV.values[i] / ((numVerticies(g) - 1) * (numVerticies(g) - 2));
	}
	return new_NV;
}

// Helper function to dispaly NodeValues struct
void showNodeValues(NodeValues values){
	for(int i = 0; i < values.noNodes; i++) {
		printf("%d: %lf\n" , i , values.values[i]);
	}
}

// Free all data assocaied with NodeValues struct
void freeNodeValues(NodeValues values){
	free(values.values);
}

static double numPathThroughV(int s,int t, int v, PredNode **pred){
	double count = 0;
	struct PredNode *curr = pred[t];
	if(!curr){
		return 0;
	}
	if(t == v ){
		{count = 1;}
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
		if(t==s){
			count++;
		}
		count = numPath(s,t,pred) + count;
		curr = curr->next;
	}
	return count;
}