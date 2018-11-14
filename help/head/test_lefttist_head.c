#include "lefttist_heap.h"

#define		ARRY_SIZE	10
const Item a[ARRY_SIZE] = {2, 3, 4, 7, 9, 3, 9, 8, 7, 5} ;

int main(void)
{
	Heap H ;
	Node * temp ;
	int i, j;

	CreateANullHeap(&H );
	H = Bulid (H, a, ARRY_SIZE) ;

	LevelOrderTraversal(H);

	temp = Find(H, 2);
	printf("temp [%d]\n", temp->left->item);

	H = DeleteMin(H);

	LevelOrderTraversal(H);

	return 1 ;
}


