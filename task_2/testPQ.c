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

	return 0;
}
