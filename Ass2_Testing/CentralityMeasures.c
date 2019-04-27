/*
  Various centrality measuring algorithms (outDegree , inDegree , Closeness , Betweenness)
  Written by Kanadech Jirapongtanavech (z5176970) & Farhan Ghazi (z5199861)
  COMP2521 2019 T1
*/

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "GraphVis.h"

// ---------- STATIC FUNCTIONS START ---------- //

// Calculate number of paths that exist between given nodes
static double numPath(int s,int t, PredNode **pred);

// ---------- STATIC FUNCTIONS END ---------- //

// Function to calculate outDegree centrality
NodeValues outDegreeCentrality(Graph g){

	NodeValues new_NV;
	new_NV.noNodes = numVerticies(g);
	new_NV.values = calloc(numVerticies(g)  , sizeof(double));
	assert(new_NV.values != NULL);

	for(int i = 0; i < new_NV.noNodes; i++) {
		AdjList currVertex = outIncident(g , i);
		float count = 0;
		if(currVertex != NULL) {
			while(currVertex != NULL) {
				count++;
				currVertex = currVertex->next;
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
		AdjList currVertex = inIncident(g , i);
		float count = 0;
		if(currVertex != NULL) {
			while(currVertex != NULL) {
				count++;
				currVertex = currVertex->next;
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
		AdjList currVertex_out = outIncident(g , i);
		float out_count = 0;
		if(currVertex_out != NULL) {
			while(currVertex_out != NULL) {
				out_count++;
				currVertex_out = currVertex_out->next;
			}
		}
		AdjList currVertex_in = inIncident(g , i);
		float in_count = 0;
		if(currVertex_in != NULL) {
			while(currVertex_in != NULL) {
				in_count++;
				currVertex_in = currVertex_in->next;
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

		// Count the number of paths from vertex
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
				double n = numPath(s,t,paths.pred);
				double nv1 = numPath(s,v,paths.pred);
				double nv2 = numPath(v,t,paths.pred);
				// Multiplying paths from s to v and from v to t
				// gives number of paths through v
				double npv = nv1*nv2;
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

// Recursively counting the path to get from s to t
static double numPath(int s,int t, PredNode **pred){
	double count = 0;
	if(pred[t]==NULL){
		return 0;
	}
	struct PredNode *currVertex = pred[t];
	if(currVertex->v == s){
		count = 1;
		currVertex = currVertex->next;
	}
	while(currVertex!=NULL){
		t = currVertex->v;
		if(t==s){
			count++;
		}
		count = numPath(s,t,pred) + count;
		currVertex = currVertex->next;
	}
	return count;
}
