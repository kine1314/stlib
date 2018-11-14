	/*	lefttist_heap.h -- ��ʽ��ͷ�ļ�	*/
#define INSERT(h, x) h = Insert (h, x)			/*	��Ͳ���֮�䲻���пո�	*/
#define DELETEMIN(h) (h = DeleteMin (h))

/*	�������Ͷ���	*/

typedef int Item ;
typedef struct node
{
	Item item ;
	struct node * left ;
	struct node * right ;
	int NPL ;
} Node ;
typedef Node * Heap ;

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ������ʽ��	*/
/*	����ǰ:	pheap ָ��һ����ʽ��	*/
/*	������:	����ڴ����ɹ�, ���� pheap ָ�����ʽ��, ������Ϊ�ն�, ����1; ���򷵻�0	*/
int CreateANullHeap (Heap * const pheap) ;

/*	����:	ȷ��һ����ʽ���Ƿ�Ϊ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�	*/
/*	������:	����ö�Ϊ��, ����1; ���򷵻�0	*/
int HeapIsEmpty (const Heap heap) ;

/*	����:	�ϲ�������ʽ�Ѳ������¶�	*/
/*	����ǰ:	h1, h2 �������ѳ�ʼ������ʽ��	*/
/*	������:	�����ѱ��ϲ����ұ�����	*/
Heap Merge (const Heap h1, const Heap h2) ;

/*	����:	��һ����������ӵ���ʽ����	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�, item ��ָ����������	*/
/*	������:	����ڴ����ɹ�, item ����ӵ�����, �����¶�; ���򷵻�ԭ��	*/
Heap Insert (Heap heap, const Item item) ;

/*	����:	ɾ����ʽ���е���СԪ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�	*/
/*	������:	����Ѳ�Ϊ��, ɾ����СԪ��, �����¶�; ���򷵻�ԭ��	*/
Heap DeleteMin (const Heap heap) ;

/*	����:	���Ҳ�������ʽ���е�һ������ָ���ؼ��ֵĽڵ�	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ������ʽ��, item ��ָ���Ĺؼ���	*/
/*	������:	����ҵ�, ����ָ��ýڵ��ָ��; ���򷵻�NULL	*/
Node * Find (const Heap heap, const Item item) ;

/*	����:	����һ���������鹹��һ����ʽ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�, array ��һ����������, size �������С	*/
/*	������:	����ڴ����ɹ�, ���������� array ΪԪ�عؼ��ֵ���ʽ��, ���ظö�; ���򷵻�NULL	*/
Heap Bulid (Heap heap, const Item * array, const int size) ;

/*	����:	�������һ����ʽ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ������ʽ��	*/
/*	������:	��������ö�	*/
void LevelOrderTraversal (const Heap heap) ;