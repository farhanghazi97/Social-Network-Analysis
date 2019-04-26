/*
  Priotity Queue ADT Interface for Assignment 2
  Written by Kanadech Jirapongtanavech (z5176970) & Farhan Ghazi (z5199861)
  COMP2521 2019 T1
*/

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

// ---------- STATIC FUNCTIONS START ---------- //

// Function to create a new Node struct
static Link NewNode (void);
// Function to search PQ for given key
static void searchPQ(PQ pq, int key);
// Function that implements INSERTION SORT to sort given PQ
static void sortPQ(PQ pq); 

// ---------- STATIC FUNCTIONS END ---------- //

// Allocate space for a new PQ struct
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

// Allocate space to make a new Node struct 
// comprising of an ItemPQ and Link
static Link NewNode (void) {
	Link new_node = malloc(sizeof(struct Node));
	new_node->next = NULL;
	return new_node;
}

// Boolean function to check if a PQ is empty
int PQEmpty(PQ p) {
	if(p->size == 0) {
		return 1;
	}
	return 0;
}

// Enqueue function for PQ
void addPQ(PQ pq, ItemPQ element) {

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
			sortPQ(pq);
		} else {
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

// Dequeue function for PQ
ItemPQ dequeuePQ(PQ pq) {
	assert(pq->front != NULL);
	ItemPQ item = pq->front->val;
	Link old = pq->front;
	pq->front = old->next;
	if (pq->front == NULL){
		pq->end = NULL;
	}
	free(old);
	pq->size--;
	return item;
}

// Helpter function to rearrange a PQ
void updatePQ(PQ pq, ItemPQ element) {
	searchPQ(pq, element.key);
	if(!pq->found){
		return;
	} else {
		pq->search->val = element;
		pq->found = false;
		sortPQ(pq);
	}
}

// Helper function to display PQ
void showPQ(PQ pq) {
	Link curr = pq->front;
	while(curr != NULL) {
		printf("Key : %d | Value: %d\n" , curr->val.key , curr->val.value);
		curr = curr->next;
	}
}

// Helper function to search for given key in PQ
static void searchPQ(PQ pq,int key){
	pq->search = pq->front;
	while(pq->search != NULL){
		if(pq->search->val.key == key){
			pq->found = true;
			return;
		}
		pq->search = pq->search->next;
	}
}

// Helper function to associated sort function to swap given pointers 
static void swap(Link p1 , Link p2) {
	ItemPQ temp = p1->val;
	p1->val = p2->val;
	p2->val = temp;
}

// A sort helper function that implements 
// INSERTION SORT to reorder items in PQ
static void sortPQ(PQ pq) {
	
	Link start = pq->front;
	Link traverse;
	Link min;

	while(start->next) {
		min = start;
		traverse = start->next;
		while(traverse) {
			if(min->val.value > traverse->val.value) {
				min = traverse;
			}
			traverse = traverse->next;
		}
		swap(start , min);
		start = start->next;
	}
}

// Helper function to free all data associated with PQ
void freePQ(PQ pq) {
	if(pq != NULL) {
		Link curr = pq->front;
		while(curr->next != NULL) {
			Link temp = curr;
			free(temp);
			curr = curr->next;
		}
		free(pq);
	}
}
