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
		Link iter = pq->front;
		pq->curr = pq->front;
		while(pq->curr->next != NULL){
			if(pq->curr->val.value <= element.value && pq->curr->next->val.value > element.value){
				iter = pq->curr;
			}
			if(pq->curr->val.key == element.key){
				found = true;
				break;
			}
		}
		if(found){
			updatePQ(pq,element);
		} else {
			Link new_node = NewNode();
			new_node->val = element;
			new_node->next = iter->next->next;
			iter->next = new_node;
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
	Link curr = pq->curr;
	while(curr != NULL) {
		printf("Key : %d | Value: %d\n" , curr->val.key , curr->val.value);
		curr = curr->next;
	}
}

void  freePQ(PQ pq) {

}
