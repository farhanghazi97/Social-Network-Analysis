// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Node * Link;

typedef struct PQRep {
	int size;
	Link front;
	Link curr;
	Link end;
} PQRep;

typedef struct Node {
	ItemPQ val;
	Link next;
} Node;

static Link NewNode (void);

PQ newPQ() {
	PQ new_PQ = malloc(sizeof(struct PQRep));
	assert(new_PQ != NULL);
	new_PQ->size = 0;
	new_PQ->front = NULL;
	new_PQ->curr = NULL;
	new_PQ->end = NULL;
	return new_PQ;
}

static Link NewNode (void) {
	Link new_node = malloc(sizeof(struct Node));
	new_node->val = NULL;
	new_node->next = NULL;
	return new_node;
}

int PQEmpty(PQ p) {
	if(p->size == 0) {
		return 1;
	}
	return 0;
}

void addPQ(PQ pq, ItemPQ element) {
	
	bool found = false;
	if(PQEmpty(pq)) {
		
		Link new_node = NewNode();
		new_node->val = element;
		
		pq->front = pq->curr = pq->end = new_node;
	
	} else {
	
		Link curr = pq;
		while(curr->next != NULL) {
			curr = curr->next;
		}
		
	}
}

ItemPQ dequeuePQ(PQ pq) {
	ItemPQ throwAway = {0};
	return throwAway;
}

void updatePQ(PQ pq, ItemPQ element) {

}

void  showPQ(PQ pq) {

}

void  freePQ(PQ pq) {

}