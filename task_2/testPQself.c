#include <stdio.h>
#include "PQ.h"

int main(void) {

	ItemPQ test_item;
	test_item.key = 2;
	test_item.value = 10;

	PQ new_PQ = newPQ();
	addPQ(new_PQ, test_item);
	printf("First Add\n");
	showPQ(new_PQ);

	test_item.key = 3;
	test_item.value = 12;
	addPQ(new_PQ , test_item);
	printf("Second Add\n");
	showPQ(new_PQ);

	// NOTE: Does not update head of list (instead appends it)
	// TODO: This should become the head of the list as priority
	//       is highest (lowest weight)
	test_item.key = 4;
	test_item.value = 1;
	printf("Third Add\n");
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	// NOTE: Does not update existing key-value pair (instead appends it)
	// TODO: This should instead update the existing node with new value

	test_item.key = 10;
	test_item.value = 0;
	printf("Fourth Add\n");
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Adding dup\n");
	test_item.key = 2;
	test_item.value = 7;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Updating\n");
	test_item.key = 3;
	test_item.value = 5;
	updatePQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Updating not found\n");
	test_item.key = 20;
	test_item.value = 5;
	updatePQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Updating first item\n");
	test_item.key = 10;
	test_item.value = 3;
	updatePQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Add new \n");
	test_item.key = 69;
	test_item.value = 2;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Add new \n");
	test_item.key = 26;
	test_item.value = 4;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Add new \n");
	test_item.key = 28;
	test_item.value = 6;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	printf("Add new \n");
	test_item.key = 11;
	test_item.value = 20;
	addPQ(new_PQ , test_item);
	showPQ(new_PQ);

	freePQ(new_PQ);
	return 0;
}
