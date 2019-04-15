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
static bool isConnected(Graph g);
static void DFS(Graph g , Vertex v , int * visited);

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

	bool is_connected = isConnected(g);
	for(int i = 0; i < new_NV.noNodes; i++) {

		ShortestPaths paths = dijkstra(g , i);
		double sum_of_paths = 0;
		
		double count = 0.0;
		for(int i = 0; i < paths.noNodes; i++) {
			sum_of_paths += paths.dist[i];
			if(paths.dist[i]){
				count++;
			}
		}

		
		//AdjList curr = outIncident(g, i);
		// while(curr != NULL) {
		// 	count++;
		// 	curr = curr->next;
		// }

		//printf("Vertx %d | Outlinks %lf | SOP %lf\n" , i , count , sum_of_paths);

		if(sum_of_paths <= 0.0) {
			new_NV.values[i] = 0.0;
		} else if(is_connected) {
			new_NV.values[i] = (numVerticies(g) - 1) / sum_of_paths;
		} else {
			new_NV.values[i] = ((count) * (count)) / ((numVerticies(g) - 1) * sum_of_paths);
		}


	}
	return new_NV;
}


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
			for (int t = 0; t <paths.noNodes; t++){
				if(s == t || v == t){
					continue;
				}
				double npv = numPathThroughV(s,t,v,paths.pred);
				double n = numPath(s,t,paths.pred);
				if(n){
					new_NV.values[v] = new_NV.values[v] + npv/n;
				}

			}
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
		count = numPath(s,t,pred) + count;
		curr = curr->next;
	}
	return count;
}

static bool isConnected(Graph g) {
	for(int i = 0; i < numVerticies(g); i++) {
		int * visited = calloc(numVerticies(g) , sizeof(int));
		DFS(g , i , visited);
		for(int i = 0; i < numVerticies(g); i++) {
			bool flag = visited[i];
			if(flag  == 0) {
				return false;
			}
		}
	}
	return true;
}

static void DFS(Graph g , Vertex v , int * visited) {
	visited[v] = 1;
	AdjList curr = outIncident(g , v);
	while(curr != NULL) {
		if(!visited[curr->w]) {
			DFS(g , curr->w , visited);
		}
		curr = curr->next;
	}
}
