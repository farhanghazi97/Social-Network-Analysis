#include <stdio.h>
#include "PQ.h"

int main(void) {

	ItemPQ test_item;
	test_item.key = 2;
	test_item.value = 10;

	PQ new_PQ = newPQ();
	addPQ(new_PQ, test_item);
	showPQ(new_PQ);
	
	test_item.key = 3;
	test_item.value = 12;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);
	
	// NOTE: Does not update head of list (instead appends it)
	// TODO: This should become the head of the list as priority 
	//       is highest (lowest weight)
	test_item.key = 4;
	test_item.value = 1;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);
	
	// NOTE: Does not update existing key-value pair (instead appends it)
	// TODO: This should instead update the existing node with new value
	
	test_item.key = 3;
	test_item.value = 9;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);
	
	freePQ(new_PQ);

	return 0;
}
