//static int NodeWeight (AdjList L);
//static int EdgeSource (Edge e);
//static int EdgeDest   (Edge e);
//static int EdgeWeight (Edge e);

/*
static int NodeWeight (AdjList L) {
	return L->weight;
}

static int EdgeSource (Edge e) {
	return e->source;
}

static int EdgeDest   (Edge e) {
	return e->dest;
}

static int EdgeWeight (Edge e) {
	return e->weight;
}
*/


/*
// Parse input file and grab relevant data
static int * ReadFile (char * filename) {

    int i = 0;
    int lines = 0;

    // Open file for reading
	FILE * fp = fopen(filename , "r");

	char buffer[BUFSIZ];
	if(fp != NULL) {
		// Determine how many sets of entries there are
		while(fgets(buffer , BUFSIZ , fp) != NULL) {
			lines++;
		}
		// Malloc enough space to hold just those numbers
		// where every line has 3 numbers
		int * array = malloc(lines * 3 * sizeof(int));
		// Reset file pointer to beginning of file
		rewind(fp);
		// Package size of array into array index;
		array[i] = (lines * 3);
		i++;
		// Grab data points from input file and store in array
		int data;
		while(fscanf(fp , "%d ,[\n]" , &data) != EOF) {
			array[i] = data;
			i++;
		}
		// Close file
		fclose(fp);
		// return array with data
		return array;

	} else {
		//ERROR: File does not exist
		printf("Could not open file!\n");
		return 0;
	}
}
*/
//  -----------------   HELPER FUNCTIONS START ------------- //
/*
static AdjList * GetConnectionsArray(Graph g) {
	return g->OutLinks;
}
*/

//Graph newGraph(int noNodes) {

	// While iterating over the edge objects in array,
	// modify graph structure.
	/*for(int i = 0; i < no_of_edges; i++) {

		int src = EdgeSource(edges[i]);
		int dest = EdgeDest(edges[i]);
		int weight = EdgeWeight(edges[i]);

		// Set up links between top level vertex array
		// and the vertices they connect to
		AdjList new_node_out = newAdjNode(dest , weight);
		new_node_out->next = new_graph->OutLinks[src];
		new_graph->OutLinks[src] = new_node_out;
		new_graph->L[src]->out_size++;

		AdjList new_node_in = newAdjNode(src , weight);
		new_node_in->next = new_graph->InLinks[dest];
		new_graph->InLinks[dest] = new_node_in;
		new_graph->L[dest]->in_size++;

		//Set first to point to head of each adjacency list that is updated
		new_graph->L[src]->first = new_node_out;
	}*/
	
//}

/*
// Allocate a new Edge object
static Edge newEdge (int source , int dest , int weight) {
	Edge new_edge = malloc(sizeof(Edge));
	assert(new_edge != NULL);
	new_edge->source = source;
	new_edge->dest = dest;
	new_edge->weight = weight;
	return new_edge;
}
*/

//int outIncidentsize(Graph g , Vertex v) {
//	return g->L[v]->out_size;
//}


// Free all memory associated with Edges array
/*static void FreeEdgesArray(Edge * edges , int NEdges) {
	for(int i = 0; i < NEdges; i++) {
		free(edges[i]);
	}
}*/


/*static void PrintAdjList(AdjList List) {
	if(List != NULL) {
		AdjList curr = List;
		while(curr != NULL) {
			printf("Vertex: %d | Weight: %d\n" , NodeDest(curr) , NodeWeight(curr));
			curr = curr->next;

		}
		printf("\n");
	} else {
		printf("Pointer is NULL\n");
	}
}*/
