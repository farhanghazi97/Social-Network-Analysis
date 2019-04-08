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
	bool found;
	Link search;
} PQRep;

typedef struct Node {
	ItemPQ val;
	Link next;
} Node;

static Link NewNode (void);

static void searchPQ(PQ pq, int key);

PQ newPQ() {
	PQ new_PQ = malloc(sizeof(struct PQRep));
	assert(new_PQ != NULL);
	new_PQ->size = 0;
	new_PQ->front = NULL;
	new_PQ->curr = NULL;
	new_PQ->end = NULL;
	new_PQ->found = false;
	new_PQ->search = NULL;
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
		pq->size++;
	} else {
		searchPQ(pq,element.key);
		if(pq->found){
			pq->search->val = element;
			pq->found = false;
			// need to call a sort fucntion here
			assert(0);
		} else {
			Link iter = pq->front;
			pq->curr = pq->front;
			Link new_node = NewNode();
			new_node->val = element;
			if(pq->size == 1) {
				if(pq->front->val.value <= element.value){
					pq->front->next = new_node;
					pq->end = new_node;
					pq->size++;
				} else {
					new_node->next = pq->front;
					pq->front = new_node;
					pq->size++;
				}
			} else {
				while(pq->curr->next != NULL){
					if (pq->curr->val.value > element.value){
						new_node->next = pq->front;
						pq->front = new_node;
						pq->size++;
						return;
					}
					if (pq->curr->val.value <= element.value && pq->curr->next->val.value > element.value){
						new_node->next = pq->curr->next;
						pq->curr->next = new_node;
						pq->size++;
						return;
					}
					pq->curr = pq->curr->next;
				}
				pq->end->next = new_node;
				pq->end = new_node;
				pq->size++;
			}

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
	Link curr = pq->front;
	while(curr != NULL) {
		printf("Key : %d | Value: %d\n" , curr->val.key , curr->val.value);
		curr = curr->next;
	}
}

static void searchPQ(PQ pq,int key){
	pq->search = pq->front;
	while(pq->search->next != NULL){
		if(pq->search->val.key == key){
			pq->found == true;
			break;
		}
		pq->search = pq->search->next;
	}
}

void freePQ(PQ pq) {
	Link curr = pq->front;
	while(curr->next != NULL) {
		Link temp = curr;
		free(temp);
		curr = curr->next;
	}
	free(pq);
}
