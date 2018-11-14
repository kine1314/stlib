#include "st_config.h"

#define MAX_SIZE	8

/* start test for st_list_head */
struct test
{
	stint		a;
	stint8		b;
};
struct ts_hlist
{
	st_list_head 	member1;
	stint			member2;
	stint8			member3;
	stdouble		member4;

};
/* end test for st_list_head */

struct ts_hlist hellots;
struct ts_hlist * rs;

ST_LIST_HEAD(hellolist);



STSList *init_list(stint size, stint *array)
{
	stint i ;
	STSList *slist = NULL ;

	for (i = 0; i < MAX_SIZE; i++)
	{
		slist = st_slist_append(slist, (stpointer)(array[i]));
	}

	return slist ;
}

static stint
sort (stconstpointer p1, stconstpointer p2)
{
	stint a, b;

	a = (stint)(p1);
	b = (stint)(p2);

	return (a > b ? +1 : a == b ? 0 : -1);
}

void stslist_test(void)
{
	STSList *slist = NULL ;
	STSList *temp = NULL ;
	STSList *pend = NULL ;

	stint array[MAX_SIZE] = {444, 666, 154, 556, 244, 966, 224, 456};

	slist = init_list(MAX_SIZE, array);
	st_dump_list(slist);

#if 0	/* 测试链表的排序 */
	temp = st_slist_sort (slist, sort);
	st_dump_list(temp);
#elif 0	/* 直接插入排序 */
	temp = st_slist_direct_insert_sort(slist);
	st_dump_list(temp);
#elif 0	/* 选择排序 */
	temp = st_slist_select_sort(slist);
	st_dump_list(temp);
#elif 0	/* 冒泡排序 */
	temp = st_slist_bubble_sort(slist);
	st_dump_list(temp);
#elif 0	/* 快速排序 */
	pend = st_slist_last(slist);
	temp = st_slist_quick_sort(slist, pend);
	st_dump_list(temp);
#elif 0	/* 快速排序 */
	st_slist_quick_sort2(&slist, NULL);
	st_dump_list(slist);
#elif 0	/* 希尔排序 */
	st_slist_shell_sort(slist);
	st_dump_list(slist);
#elif 1	/* 基数排序 */
	temp = st_slist_radix_sort(slist, 3);
	st_dump_list(slist);
#endif
}


void starray_test(void)
{
	stint array[MAX_SIZE] = {444, 666, 154, 556, 244, 966, 224, 456};

	st_dump_array(array, MAX_SIZE);

#if 0	/* 归并排序 */
	st_arry_recursive_merge_sort(array, 0, MAX_SIZE - 1);
	st_dump_array(array, MAX_SIZE);
#elif 0	/* 堆排序 */
	st_arry_head_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0	/* 快速排序 */
	st_arry_qsort(array, 0, MAX_SIZE-1);
	st_dump_array(array, MAX_SIZE);
#elif 0
	st_arry_shell_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0
	st_arry_select_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0
	st_arry_bubble_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 1
	st_arry_bubble_sort_1(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0	/* 直接插入排序 */
	st_arry_insert_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0	/* 折半插入排序 */
	st_arry_binary_insert_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0	/* 基数排序 */
	st_arry_radix_sort(array, MAX_SIZE);
	st_dump_array(array, MAX_SIZE);
#elif 0	/* 锦标赛排序 */
	st_arry_tournament_sort(array, 10);
	st_dump_array(array, MAX_SIZE);
#elif 0	/*  迭代实现归并排序*/
	st_arry_iteration_merge_sort(array, 10);
	st_dump_array(array, MAX_SIZE);
#endif
}




void stdrlist_test(void)
{

	stint8 *pchar = "testok" ;
	stint i=0;
	stint j=0;
	struct test t1;
	t1.a=8;
	t1.b='z';

	__msg("length of int:%d char:%d double:%d long:%d\n",sizeof(int),sizeof(char),sizeof(double),sizeof(long));
	__msg("Address of t1 is:%p\nddd member of a is:%d\n member of b is:%c\n",&t1,t1.a,t1.b);
	__msg("Address of pchar is:%p\nvalue of pchar is:%s\n",pchar,pchar);
	for(;i<strlen(pchar);i++)
	{
	  __msg("Address of member of pchar in pos %d is %p  ,value of pchar in pos%d is:%c\n",i,pchar+i,i,pchar[i]);
	}
	__msg("address base=0\n,than the address of a:%d\naddress of b:%d\n", &((struct test *)0)->a,&((struct test *)0)->b) ;


	__msg("If the NULL struct as 0 of ts_hlist is given,then the size of 0based willbe:like this:\n\n\n\n");
	__msg("   struct ts_hlist as NULL \n");
	__msg("%u --->|__________|\n",&( ((struct ts_hlist *)0)->member1)  );
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("%u --->|__________|\n",&( ((struct ts_hlist *)0)->member2) );
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("%u--->|__________|\n",&( ((struct ts_hlist *)0)->member3) );
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("%u--->|__________|\n",&( ((struct ts_hlist *)0)->member4) );
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");
	__msg("      |__________|\n");

	__msg("                          \n\n");
	__msg("  struct ts_hlist as allocate space\n");


	__msg(" size of  ts_hlist struct is %d\n",sizeof(struct ts_hlist));
	for(;j<sizeof(struct ts_hlist);j++)
	{
	  __msg("     |__________|<--%p\n",&hellots+(stuint32)j);
	}
	__msg(" the address of head(type of st_head_list) is:%p\n",hellolist);

	hellots.member2=3;
	hellots.member3='A';
	hellots.member4=44.33;
	st_list_add_tail(&hellots.member1,&hellolist);
#if	!defined(WIN32)
	rs=st_list_entry(&hellots.member1, struct ts_hlist, member1);
#endif
	__msg("  the address of member1 is: %p\n",&hellots+(stuint32)&( ((struct ts_hlist *)0)->member1) );
	__msg("  the address of member2 is: %p\n",&hellots+(stuint32)&( ((struct ts_hlist *)0)->member2) );
	__msg("  the address of member3 is: %p\n",&hellots+(stuint32)&( ((struct ts_hlist *)0)->member3) );
	__msg("  the address of member4 is: %p\n",&hellots+(stuint32)&( ((struct ts_hlist *)0)->member4) );
	__msg(" Now we'll test the value area of ts_hlist>>>>>\n");
	__msg("  member2 of rs is:%d\n", rs->member2);
	__msg("  member3 of rs is:%c\n", rs->member3);
	__msg("  member4 of rs is:%g\n", rs->member4);
}



void st_array_queue_test(void)
{
	STQueueA* queue = NULL ;
	queue = st_array_queue_new() ;
	__here__ ;
	st_array_queue_dynamic_init(queue, 10);
	__here__ ;
	st_array_queue_push(queue, 3) ;
	__here__ ;
	st_array_queue_push(queue, 34) ;
	__here__ ;
	st_array_queue_push(queue, 32) ;
	st_array_queue_push(queue, 4) ;
	st_array_queue_pop(queue);
	st_array_queue_dump(queue);
	st_array_queue_push(queue, 55) ;
	st_array_queue_dump(queue);

	__msg("len [%d] front [%d] rear [%d]\n", queue->length, queue->front, queue->rear);

	while(queue->rear != -1)
	{
		stint pop_num = 0 ;
		pop_num = st_array_queue_pop(queue);
		printf("%d ", queue->pData[pop_num]);
	}
	printf("\n");
}

#if 0	// 合并五个队列
#define SIZE (5)

/*	O (NlogK)	*/
// 使用优先队列来合并排序
stbool st_queue_merge (const PSTQueue * const array, const int number, PSTQueue * const pNewQueue)
{
	BHPriorityQueue pq ;
	BinHeadET temp ;
	int i , j;

	if (number <= 0 )
		return FALSE ;

	pq = BHInitialize (number)
	
	
	/*	Bulid heap.	*/
	for (i = 0; i < number; i++)
		BHInsert (&pq, array[i]->front) ;
	/*	Core loop.	*/
	while (FALSE == BHIsEmpty (&pq))
	{	
		printf("%d\n", j++);
		temp = BHDeleteMin (&pq) ;						// 删除最小的
		STEnQueue_Q (pNewQueue, temp->item) ;
		if (temp->next != NULL)
			BHInsert (&pq, temp->next) ;				// 插入下一个
	}
	BHDestroy (&pq) ;

	return TRUE ;
}

int st_queue_merge_test(void)
{
	PSTQueue array[SIZE] ;
	PSTQueue q1, q2, q3, q4, q5, newQueue ;
	QItem item ;

	/*	Artificial element.	*/
	STInitialize_Q (&q1) ;
	STInitialize_Q (&q2) ;
	STInitialize_Q (&q3) ;
	STInitialize_Q (&q4) ;
	STInitialize_Q (&q5) ;

	item = 1 ;
	STEnQueue_Q (&q1, item) ;
	item = 2 ;
	STEnQueue_Q (&q1, item) ;
	item = 2 ;
	STEnQueue_Q (&q1, item) ;
	item = 4 ;
	STEnQueue_Q (&q1, item) ;
	item = 20 ;
	STEnQueue_Q (&q1, item) ;

	item = 3 ;
	STEnQueue_Q (&q2, item) ;
	item = 7 ;
	STEnQueue_Q (&q2, item) ;
	item = 8 ;
	STEnQueue_Q (&q2, item) ;
	item = 8 ;
	STEnQueue_Q (&q2, item) ;
	item = 9 ;
	STEnQueue_Q (&q2, item) ;	
	item = 16 ;
	STEnQueue_Q (&q2, item) ;

	item = 45 ;
	STEnQueue_Q (&q3, item) ;
	item = 56 ;
	STEnQueue_Q (&q3, item) ;	
	item = 77 ;
	STEnQueue_Q (&q3, item) ;

	item = 14 ;
	STEnQueue_Q (&q4, item) ;
	item = 67 ;
	STEnQueue_Q (&q4, item) ;
	item = 78 ;
	STEnQueue_Q (&q4, item) ;
	item = 89 ;
	STEnQueue_Q (&q4, item) ;
	item = 90 ;
	STEnQueue_Q (&q4, item) ;	
	item = 92 ;
	STEnQueue_Q (&q4, item) ;

	item = 11 ;
	STEnQueue_Q (&q5, item) ;
	item = 22 ;
	STEnQueue_Q (&q5, item) ;
	item = 33 ;
	STEnQueue_Q (&q5, item) ;
	item = 34 ;
	STEnQueue_Q (&q5, item) ;
	item = 35 ;
	STEnQueue_Q (&q5, item) ;	
	item = 37 ;
	STEnQueue_Q (&q5, item) ;
	item = 45 ;
	STEnQueue_Q (&q5, item) ;
	item = 56 ;
	STEnQueue_Q (&q5, item) ;	
	item = 67 ;
	STEnQueue_Q (&q5, item) ;

	array[0] = q1 ;
	array[1] = q2 ;
	array[2] = q3 ;
	array[3] = q4 ;
	array[4] = q5 ;

	/*	Initialize new queue.	*/
	STInitialize_Q (&newQueue) ;
	/*	It's so attractive!	*/
	st_queue_merge (array, SIZE, &newQueue) ;
	
	STRelease_Q (&q1) ;
	STRelease_Q (&q2) ;
	STRelease_Q (&q3) ;
	STRelease_Q (&q4) ;
	STRelease_Q (&q5) ;
	STRelease_Q (&newQueue) ;

	return 0 ;
}
#endif	/*  合并五个队列 */

void st_array_stack_test(void)
{
	ST_STACK_NODE* stack ;
	stint data ;

	stack = st_stack_alloc(10) ;
	st_stack_push(stack, 78) ;
	st_stack_push(stack, 44) ;
	st_stack_push(stack, 32) ;
	st_stack_push(stack, 45) ;
	__msg("stack count [%d]\n", st_count_stack(stack));
	st_stack_pop(stack, &data) ;
	__msg("stack count [%d], pop [%d]\n", st_count_stack(stack), data);
	st_stack_dump(stack);
}

void st_stack_list_test(void)
{
	ST_STACK_LIST* stack = NULL ;

	stack = st_stack_list_alloc();

	st_stack_list_push(stack, 6);
	st_stack_list_push(stack, 2);
	st_stack_list_push(stack, 5);
	st_stack_list_push(stack, 4);
	st_stack_list_push(stack, 3);

	__msg("pop [%d]\n", st_stack_list_pop(stack));
	__msg("pop [%d]\n", st_stack_list_pop(stack));
	__msg("pop [%d]\n", st_stack_list_pop(stack));
	__msg("pop [%d]\n", st_stack_list_pop(stack));
	__msg("pop [%d]\n", st_stack_list_pop(stack));
	__msg("pop [%d]\n", st_stack_list_pop(stack));
}

static stint visitT(TElemType e)
{
	printf("%c ",e);
	return 1;
}

void st_btree_test(void)
{
	stint i;
	ST_BTREE 	T, p, c;
	TElemType 	e1, e2;

	st_btree_init(&T);
	__msg("create a NULL tree,is the tree NULL? %d(1:yes 0:no), the depth of tree = [%d]\n", st_btree_empty(T), st_btree_depth(T)) ;
	e1 = st_btree_root(T);
	if(e1!=' ')
		__msg("the root of tree : %c\n",e1);
	else
		__msg("the tree is NULL, no root\n");
	__msg("please input the tree(ep:ab with three space mean a is root, and b is left child\n") ;
	st_btree_create(&T);
	__msg("create a NULL tree,is the tree NULL? %d(1:yes 0:no), the depth of tree = [%d]\n", st_btree_empty(T), st_btree_depth(T)) ;
	e1=st_btree_root(T);
	if(e1!=' ')
		printf("the root of tree: %c\n",e1);
	else
		printf("the tree is NULL, no root\n");

	printf("middle order traverse the tree:\n");
	st_btree_midorder_traverse(T,visitT);
	printf("\nmiddle order traverse the tree with stack:\n");
	st_btree_midorder_iter_traverse(T,visitT);
	printf("middle order traverse the tree with stack(other):\n");
	st_btree_midorder_iter_traverse2(T,visitT);

	__msg("exchange the tree's LR child\n");
	st_btree_exchange_LR(T);
	__msg("count thr leaves num [%d]\n", st_btree_leaves_num(T));

	__msg("iteration prev order traverse the tree\n");
	st_btree_preorder_traverse_iteration(T,visitT);
	__msg("iteration middle order traverse the tree\n");
	st_btree_midorder_traverse_iteration(T,visitT);
	__msg("iteration post order traverse the tree\n");
	st_btree_posorder_traverse_iteration(T,visitT);

	printf("\npost order traverse the tree:\n");
	st_btree_posorder_traverse(T,visitT);

	printf("\nlevel order traverse the tree:\n");
	st_btree_level_order_traverse(T,visitT);

	printf("please input a value of node: ");
	scanf("%*c%c",&e1);
	p=st_btree_point(T,e1); // p为e1的指针
	printf("the node value is %c\n",st_btree_value(p));
	printf("input a value to change the node: ");
	scanf("%*c%c%*c",&e2);
	st_btree_assign(p,e2);
	printf("level order traverse the tree:\n");
	st_btree_level_order_traverse(T,visitT);
	__msg("############################\n");
	e1=st_btree_parent(T,e2);
	if(e1!=' ')
		printf("%c father is %c\n",e2,e1);
	else
		printf("%c have no parent \n",e2);
	e1=st_btree_left_child(T,e2);
	if(e1!=' ')
		printf("%c left child is %c\n",e2,e1);
	else
		printf("%c no left child \n",e2);
	e1=st_btree_right_child(T,e2);
	if(e1!=' ')
		printf("%c right child is %c\n",e2,e1);
	else
		printf("%c no right child \n",e2);
	e1=st_btree_left_sibling(T,e2);
	if(e1!=' ')
		printf("%c left brother is %c\n",e2,e1);
	else
		printf("%c no left brother \n",e2);
	e1=st_btree_right_sibling(T,e2);
	if(e1!=' ')
		printf("%c right brother is %c\n",e2,e1);
	else
		printf("%c no right brother \n",e2);

	st_btree_init(&c);
	printf("create a NULL right subtree c:\n");
	printf("please input the tree(ep:ab with three space mean a is root, and b is left child)\n");
	st_btree_create(&c);

	printf("prev order traverse the tree c:\n");
	st_btree_preorder_traverse(c,visitT);

	printf("\ninsert the tree c to tree T,please input the parent of tree c  c left (0)"
		"or right(1)subtree: ");
	scanf("%*c%c%d",&e1,&i);
	p=st_btree_point(T,e1); 								// p是T中树c的双亲结点指针
	st_btree_insert_child(p,i,c);

	printf("prev order the tree:\n");
	st_btree_preorder_traverse(T,visitT);
	printf("\ndelete the subtree,please input the parent node whitch will delete  L (0) or R (1): ");
	scanf("%*c%c%d",&e1,&i);
	p=st_btree_point(T,e1);
	st_btree_delete_child(p,i);
	printf("prev order the tree:\n");
	st_btree_preorder_traverse(T,visitT);
	printf("\n");
	st_btree_destroy(&T);

}

static void visitBST(BSTElemType c)
{
	printf("(%d,%d) ",c.key,c.others);
}

void st_bstree_test(void)
{
	BSTree dt,p;
	stint i;
	BSTKeyType j;

	BSTElemType r[10] =
	{
		{45,1},{12,2},{53,3},{3,4},{37,5},{24,6},
		{100,7},{61,8},{90,9},{78,10}
	};
	st_bstree_init(&dt); 					// 构造空表
	for(i=0 ; i<10 ; i++)
		st_bstree_insert(&dt, r[i]); // 依次插入数据元素

	st_bstree_delete_traverse(dt, visitBST);
	printf("\nplease input the key to file: ");
	scanf("%d",&j);
	p=st_bstree_search(dt, j);
	if(p)
	{
		printf("the tree exist the key[%d].", p->data.key);
		st_bstree_delete_key(&dt,j);
		printf("and delete the key [%d]:\n", j);
		st_bstree_delete_traverse(dt,visitBST);
		printf("\n");
	}
	else
	{
		printf("the ket don't exist\n");
	}
	st_bstree_destroy(&dt);

}

void st_avltree_test(void)
{
	stint i,j;
	AVLTree pRoot = NULL;

	srand((AVLElemType)time(NULL));

	for (i = 0; i < 6; ++i)
	{
		j = rand()%100;
		printf("%d\n", j);
		pRoot = st_avltree_insert(j, pRoot);
	}
	printf("\n\n");
	//st_avltree_delete(pRoot, 3);
#if 1
	pRoot = st_avltree_insert(1, pRoot);
	pRoot = st_avltree_insert(2, pRoot);
	pRoot = st_avltree_insert(3, pRoot);
	pRoot = st_avltree_insert(4, pRoot);
	pRoot = st_avltree_insert(5, pRoot);

#endif

	st_avltree_traverse(pRoot);

	st_avltree_destroy(&pRoot);

}

#if 1
void visitSPYT(const SPYNode * const pn)
{
	printf("%d ",pn->item);
}

void st_splay_tree_test(void)
{
	stint i, j ;
	SplayTree splay ;
	SPYNode* temp ;

	st_splay_tree_create(&splay) ;

	srand((SPYItem)time(NULL));

	for (i = 0; i < 6; ++i)
	{
		j = rand()%100;
		printf("%d\n", j);
		st_splay_tree_insert (&splay, &j) ;
	}

	printf("root node [%d]\n", splay->root->item);
	printf("\n");
	st_splay_tree_traverse (splay->root,visitSPYT) ;
	temp = st_splay_tree_find_min(&splay);
	printf("the min valuse[%d]\n", temp->item);

	while(1)
	{
		SPYNode* N ;
		static stint i = 2 ;
		printf("[%d][%d][%d]\n", splay->root->item, splay->root->leftSubTreeCount, splay->root->rightSubTreeCount);
		N = st_splay_tree_find_kthmin(&splay, i++);
		printf("[%d][%d][%d]\n", splay->root->item, splay->root->leftSubTreeCount, splay->root->rightSubTreeCount);
		printf("[%d][%d][%d]\n\n", N->item, N->leftSubTreeCount, N->rightSubTreeCount);

		//sleep(1);
	}
	printf("\n");
}
#endif

#if 1	/* st gtree test */
static stpointer destroyed_key = NULL;
static stpointer destroyed_value = NULL;

static stint8 chars[] =
  "0123456789"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz";

static stint8 chars2[] =
  "0123456789"
  "abcdefghijklmnopqrstuvwxyz";

static stint
my_compare (stconstpointer a,
		stconstpointer b)
{
	const stint8 *cha = a;
	const stint8 *chb = b;

	return *cha - *chb;			// 如果a>b:1 a=b:0 a<b:-1
}

static stint
my_search (stconstpointer a,
	   stconstpointer b)
{
	return my_compare (b, a);
}

static void
my_key_destroy (stpointer key)
{
	destroyed_key = key;
}

static void
my_value_destroy (stpointer value)
{
	destroyed_value = value;
}

static stint
my_traverse (stpointer key,
		 stpointer value,
		 stpointer data)
{
	stint8 *ch = key;
	st_assert ((*ch) > 0);

	return FALSE;
}

static stint
my_traverse1 (stpointer key,
		 stpointer value,
		 stpointer data)
{
	stint8 *ch = key;
	printf("%c \n", (int)value);
	return FALSE ;
}

static stint
check_order (stpointer key,
		 stpointer value,
		 stpointer data)
{
	stint8 **p = data;
	stint8 *ch = key;

	st_assert (**p == *ch);

	(*p)++;

	return FALSE;
}

void st_gtree_test(void)
{
	stint i ;
	STGTree* tree = NULL ;
	stint8 *p ;
	stbool removed ;
	stint8 c, d;

	tree = st_tree_new (my_compare);						/* 创建一颗tree */
	for (i = 0; chars[i]; i++)								/* 插入节点 */
		st_tree_insert (tree, &chars[i], &chars[i]);


	st_tree_foreach (tree, my_traverse, NULL);				/* 遍历整棵树，判断全部节点是否都>0 */
	__msg("\n\n");

	st_assert (st_tree_nnodes (tree) == strlen (chars));	/* 判断节点数 */
	st_assert (st_tree_height (tree) == 6);					/* 判断深度 */

	p = chars ;
	st_tree_foreach (tree, check_order, &p);

	for (i = 0; i < 26; i++)
	{
		removed = st_tree_remove (tree, &chars[i + 10]);	/* 删除26个大写英文 */
		st_assert (removed);								/* 判断是否删除成功 */
	}

	c = '\0';
	removed = st_tree_remove (tree, &c);
	st_assert (removed == FALSE);							/* 如果是FALSE 证明没有此节点 */

	st_tree_foreach (tree, my_traverse, NULL);
	st_assert (st_tree_nnodes (tree) == strlen (chars2));	/* 判断是否等于char2 */
	st_assert (st_tree_height (tree) == 6);

	p = chars2;
	st_tree_foreach (tree, check_order, &p);

	for (i = 25; i >= 0; i--)
		st_tree_insert (tree, &chars[i + 10], &chars[i + 10]);

	//st_tree_dump(tree);
	p = chars;
	st_tree_foreach (tree, check_order, &p);

	c = '0';
	p = st_tree_lookup (tree, &c);
	st_assert (p && *p == c);

	c = '!';
	p = st_tree_lookup (tree, &c);
	st_assert (p == NULL);

	c = '|';
	p = st_tree_lookup (tree, &c);
	st_assert (p == NULL);

	c = '0';
	p = st_tree_search (tree, my_search, &c);
	st_assert (p && *p == c);

	st_tree_destroy (tree);

	tree = st_tree_new_full ((STCompareDataFunc)my_compare, NULL, 			/* 创建一颗全树 */
			  my_key_destroy,
			  my_value_destroy);

	for (i = 0; chars[i]; i++)
		st_tree_insert (tree, &chars[i], &chars[i]);

	c = '0';														/* 插入相同的值，覆盖 */
	st_tree_insert (tree, &c, &c);
	st_assert (destroyed_key == &c);
	st_assert (destroyed_value == &chars[0]);
	destroyed_key = NULL;
	destroyed_value = NULL;

	d = '1';
	st_tree_replace (tree, &d, &d);
	st_assert (destroyed_key == &chars[1]);
	st_assert (destroyed_value == &chars[1]);
	destroyed_key = NULL;
	destroyed_value = NULL;

	c = '2';
	removed = st_tree_remove (tree, &c);
	st_assert (removed);
	st_assert (destroyed_key == &chars[2]);
	st_assert (destroyed_value == &chars[2]);
	destroyed_key = NULL;
	destroyed_value = NULL;

	c = '3';
	removed = st_tree_steal (tree, &c);
	st_assert (removed);
	st_assert (destroyed_key == NULL);
	st_assert (destroyed_value == NULL);

}

#endif	/* st gtree test */


#if 1	/* start rbtree test */
void visitRBT(const RBNode * const pn)
{
	printf("%d ",pn->item);
}


void st_rbtree_test(void)
{
	stint i, j ;
	pRBTree rb ;
	stint nodes[14] = {30, 15, 70, 10, 20, 60, 85, 5, 50, 65, 80, 90, 40, 55} ;

	st_rbtree_create(&rb) ;
	srand((RBItem)time(NULL));
	for (i = 0; i < 14; ++i)
	{
		j = rand()%100;
		//printf("%d\n", nodes[i]);
		//st_rbtree_insert (&rb, nodes[i]) ;
		st_rbtree_insert (&rb, j) ;
	}
	st_rbtree_traverse (&rb,visitRBT) ;
	printf("\n");
	__msg("root node is [%d]\n", rb->root->item);
	printf("\n");
	printf("insert the node [10]\n");
	st_rbtree_insert(&rb, 100) ;
	st_rbtree_traverse (&rb,visitRBT) ;
	printf("\n");
	__msg("root node is [%d]\n", rb->root->item);
	printf("\n");
	st_rbtree_release(&rb);
}

#endif	/* end rbtree test */


#if 1	/* start treap tree test */

void st_treap_tree_test(void)
{
	stint i, j ;
	Treap T ;
	T = st_treap_tree_init() ;

	srand((TRElemType)time(NULL));

	for (i = 0; i < 10; ++i)
	{
		j = rand()%100;
		printf("%d\n", j);
		T = st_treap_tree_insert (j, T);
	}
	printf("\n");
	printf("", T->Element);
	st_treap_tree_traverse(T);
	printf("\n");
	printf("", T->Element);

	st_treap_tree_destroy(T);
}



void st_rbtree_downn2up_test(void)
{
	stint i, count = 14;
	RBKey_t key;

	rb_node_t* root = NULL, *node = NULL;
	stint nodes[14] = {30, 15, 70, 10, 20, 60, 85, 5, 50, 65, 80, 90, 40, 55} ;


	//srand(time(NULL));

	for (i = 1; i <= count; ++i)
	{
		//key = rand() % 100;
		if ((root = st_rbt_insert(nodes[i-1], i, root)))
		{
			printf("[i = %d] insert key %d success!\n", i, nodes[i-1]);
		}
		else
		{
			printf("[i = %d] insert key %d error!\n", i, nodes[i-1]);
			exit(-1);
		}

#if 0
		if ((node = st_rbt_search(key, root)))
		{
			printf("[i = %d] search key %d success!\n", i, key);
		}
		else
		{
			printf("[i = %d] search key %d error!\n", i, key);
			exit(-1);
		}

		if (!(i % 10))
		{
			if ((root = st_rbt_erase(key, root)))
			{
				printf("[i = %d] erase key %d success\n", i, key);
			}
			else

			{
				printf("[i = %d] erase key %d error\n", i, key);
			}
		}
#endif
	}

	rb_traverse(root);
	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	root = st_rbt_erase(root->key, root);
	rb_traverse(root);

	printf("\n");
	printf("root node [%d]\n", root->key);


}

#endif	/* end treap tree test */

static stint
mysort1 (stconstpointer a, stconstpointer b, stpointer user_data)
{
  return *(stuint32*)a < *(stuint32*)b ? -1 : 1;
}

static stint
mysort2 (stconstpointer a, stconstpointer b)
{
  return *(stuint32*)a < *(stuint32*)b ? -1 : 1;
}

void st_qsort_test(void)
{
	#define SIZE	10
	int i;
	stuint32 array[SIZE];

	srand((TRElemType)time(NULL));

	for (i = 0; i < SIZE; i++)
		array[i] = rand()%SIZE;

	st_qsort_with_data (array, SIZE, sizeof (stuint32), mysort1, NULL);
	//qsort(array, SIZE, sizeof (stuint32), mysort2);
	for(i = 0 ; i < SIZE ; i++)
	{
		printf("%d ", (stint)array[i]);
	}

	for (i = 0; i < SIZE - 1; i++)
		st_assert(array[i] <= array[i+1]);

	/* 0 elemenents is a valid case */
	st_qsort_with_data (array, 0, sizeof (stuint32), mysort1, NULL);

}


void print_key_value(stpointer key, stpointer value, stpointer user_data);
void display_hash_table(STHashTable *table);
void free_key(stpointer data);
void free_value(stpointer value);
void print_key_value(stpointer key, stpointer value, stpointer user_data)
{
	printf("%s ---> %s\n", (stint8 *)key, (stint8 *)value);
}
void display_hash_table(STHashTable *table)
{
	st_hash_table_foreach(table, print_key_value, NULL);
}
void free_key(stpointer data)
{
	printf("We free key: %s \n", (stint8 *)data);
	free(data);
}
void free_value(stpointer data)
{
	printf("We free value: %s \n", (stint8 *)data);
	free(data);
}

void st_ghash_test(void)
{
	STHashTable *table = NULL;
	table = st_hash_table_new(st_str_hash, st_str_equal);
	st_hash_table_insert(table, "1", "one");
	st_hash_table_insert(table, "2", "two");
	st_hash_table_insert(table, "3", "three");
	st_hash_table_insert(table, "4", "four");
	st_hash_table_insert(table, "5", "five");
	display_hash_table(table);
	printf("Size of hash table: %d \n", st_hash_table_size(table));
	printf("Before replace: 3 ---> %s \n", (stint8 *)st_hash_table_lookup(table, "3"));
	st_hash_table_replace(table, "3", "third");
	printf("After replace: 3 ---> %s \n", (stint8 *)st_hash_table_lookup(table, "3"));
	st_hash_table_remove(table, "2");
	display_hash_table(table);
	printf("Now size of hash table: %d \n", st_hash_table_size(table));
	st_hash_table_destroy(table);
	table = st_hash_table_new_full(st_str_hash, st_str_equal, free_key, free_value);
	st_hash_table_insert(table, strdup("one"), strdup("first"));
	st_hash_table_insert(table, strdup("two"), strdup("second"));
	st_hash_table_insert(table, strdup("three"), strdup("third"));

	printf("Remove an item from hash table: \n");
	st_hash_table_remove(table, "two");
	printf("Destroy hash table: \n");
	st_hash_table_destroy(table);
	return ;
}

void print_hash(stint p,HashElemType r)
{
	printf("address=%d (%d,%d)\n",p,r.key,r.ord);
}
#define HASHNUM		 	10			// 数据元素个数
stint st_hash_test			(void)
{
	HashElemType r[HASHNUM] = {
		{17,1},{60,2},{29,3},{38,4},{1,5},
		{2,6},{3,7},{4,8},{60,9},{13,10}
	};
	HashTable h;
	stint i, j, p;
	HashKeyType k;

	InitHashTable(&h);
	for(i=0;i<HASHNUM-1;i++)
	{
		// 插入前N-1个记录
		j=InsertHash(&h,r[i]);
		if(j==DUPLICATE)
			printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
	}
	printf("按哈希地址的顺序遍历哈希表:\n");
	TraverseHash(h,print_hash);
	printf("请输入待查找记录的关键字: ");
	scanf("%d",&k);
	j=Find(h,k,&p);
	if(j==SUCCESS)
		print_hash(p,h.elem[p]);
	else
		printf("没找到\n");
	j=InsertHash(&h,r[i]); // 插入第N个记录
	if(j==0) // 重建哈希表
		j=InsertHash(&h,r[i]); // 重建哈希表后重新插入第N个记录
	printf("按哈希地址的顺序遍历重建后的哈希表:\n");
	TraverseHash(h,print_hash);
	printf("请输入待查找记录的关键字: ");
	scanf("%d",&k);
	j=Find(h,k,&p);
	if(j==SUCCESS)
		print_hash(p,h.elem[p]);
	else
		printf("没找到\n");
	DestroyHashTable(&h);

	system("pause");
	return 0;

}


/*分离链接散列表实现*/
#define	MAX_HASH_NUM		8

static void seq_hash_print(const SPListNode * const pnode)
{
    printf("%d\n", pnode->item);

    return;
}

void st_separate_chaining_hash_test(void)
{
	SPHashTable HT ;
	HItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};
	int i , ret , index;
	SPHeader h ;

	printf("!!!\n");
	HT = SPInitializeTable(MAX_HASH_NUM);
	printf("hash size [%d]\n", HT->size);
	printf("!!!\n");
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = SPInsert(r[i], &HT);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	SPTraversal(&HT, seq_hash_print);

	h = SPFind(44, HT) ;
	printf("h node [%d]\n", h->item);

	//printf("delete hash table\n");
	//SPDelete(r[0], &HT) ;
	//SPTraversal(&HT, sep_hash_print);

	//index = SPHash(77, MAX_HASH_NUM) ;
	//printf("hash index [%d]\n", index);

	return ;
}

/* 线性开定地址法 */
static void cell_hash_print(const Cell cell)
{
    printf("%d\n", cell.item);

    return;
}

void st_open_address_hash_test(void)
{
	OAHashTable HT ;
	int i , ret , index;
	HItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};

	OAInitializeTable(&HT, MAX_HASH_NUM);
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = OAInsert(&HT, r[i]);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	OATraversal(&HT, cell_hash_print);
}


/* 平方探测法 */

void st_open_address_hash_2_test(void)
{
	OAHashTable HT ;
	int i , ret , index;
	HItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};

	OA2InitializeTable(&HT, MAX_HASH_NUM);
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = OA2Insert(&HT, r[i]);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	OA2Traversal(&HT, cell_hash_print);
}

/* 开放定址双散列探测地址 */
void st_open_address_double_hash_test(void)
{
	OAHashTable HT ;
	int i , ret , index;
	HItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};

	OADInitializeTable(&HT, MAX_HASH_NUM);
	printf("hash size [%d]\n", HT->size);
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = OADInsert(&HT, r[i]);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	OADTraversal(&HT, cell_hash_print);
}

/* 开放再散列定址法 */
void st_hash_with_hashing_again_test(void)
{
	OAHashTable HT ;
	int i , ret , index;
	HItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};

	OAAInitializeTable(&HT, MAX_HASH_NUM);
	printf("hash size [%d]\n", HT->size);
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = OAAInsert(&HT, r[i]);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	printf("hash size [%d]\n", HT->size);
	OAATraversal(&HT, cell_hash_print);
}

/* 可扩展散列 */
void ex_hash_print (const EXSubdir ex_subdir)
{
	printf("[%s]\n", ex_subdir.point->array);
}

void st_extendible_hashing_test(void)
{
	EXHTable HT ;
	int i , ret , index;
	EXItem *r[EX_M] = {"kine", "fei", "NBA","CBA"};

	EXInitializeTable(&HT);
	for(i = 0 ; i < EX_M ; i++)
	{
		printf("r[%d] :%d\n", (int)i, (int)r[i]);
		ret = EXInsert(&HT, r[i]);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",(int)r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	EXTraversal(&HT, ex_hash_print);
}


// st_hash_string
extern NAME NameList[HASH_LENGTH];    		//全局变量NAME  
extern HASH HashList[HASH_LENGTH];        	//全局变量HASH 

char *nameL[NAME_NO] = {"zengqinghui","mayuelong","chenzhicheng","sunpeng","wanghui","liqingbo",
    				"liujunpeng","jiangquanlei","xingzhengchuan","luzhaoqian","gaowenhu","zhuhaoyin",
    				"wuyunyun","huangjuanxia","wangyan","zhoutao","jiangzhenyu","liuxiaolong","wangziming",
    				"fengjunbo","lilei","wangjia","zhangjianguo","zhuqingqing","huangmin","haoyuhan",
    				"zhoutao","zhujiang","lixiaojun","stjq","zengqnghui","mayuelng","chenzhicng","speng","wanghui","liqingbo",
    				"liujunng","jiangqulei","xingzhenhuan","luzoqian","gawenhu","zhuhoyin",
    				"wuyyun","huanganxia","wangan","zhouao","jianzhenyu","lixiaolong","wagziming",
    				"fengjnbo","llei","wanjia","zhangjianuo","zhuqngqing","hungmin","hoyuhan",
    				"zhouao","zhujiag","lixaojun","stjggq"};

void InitNameList() //姓名（结构体数组）初始化          
{   char *f;
    int r,s0,i;

    NameList[0].py="zengqinghui";
    NameList[1].py="mayuelong";
    NameList[2].py="chenzhicheng";
    NameList[3].py="sunpeng";
    NameList[4].py="wanghui";
    NameList[5].py="liqingbo";
    NameList[6].py="liujunpeng";
    NameList[7].py="jiangquanlei";
    NameList[8].py="xingzhengchuan";
    NameList[9].py="luzhaoqian";
    NameList[10].py="gaowenhu";
    NameList[11].py="zhuhaoyin";
    NameList[12].py="chenlili";
    NameList[13].py="wuyunyun";
    NameList[14].py="huangjuanxia";
    NameList[15].py="wangyan";
    NameList[16].py="zhoutao";
    NameList[17].py="jiangzhenyu";
    NameList[18].py="liuxiaolong";
    NameList[19].py="wangziming";
    NameList[20].py="fengjunbo";
    NameList[21].py="lilei"; 
    NameList[22].py="wangjia";
    NameList[23].py="zhangjianguo";
    NameList[24].py="zhuqingqing";
    NameList[25].py="huangmin";
    NameList[26].py="haoyuhan";
    NameList[27].py="zhoutao";
    NameList[28].py="zhujiang";
    NameList[29].py="lixiaojun";

    for(i=0;i<NAME_NO;i++)
	{   
		s0=0;
        f=NameList[i].py;
        for(r=0;*(f+r)!='\0';r++) 
		{
			/* 方法：将字符串的各个字符所对应的ASCII码相加，所得的整数做为哈希表的关键字*/
            s0=*(f+r)+s0;
		}
        NameList[i].k=s0;
	} 
}

void InsertNameList(NAME *NL, char *name, int i)
{
	char *f;
    int r,s0;

	s0 = 0 ;
	__msg("name [%s]\n", name);
	(NL+i)->py = name ;
	f = (NL+i)->py;
#if 0
	for(r=0;*(f+r)!='\0';r++) 
	{
		/* 方法：将字符串的各个字符所对应的ASCII码相加，所得的整数做为哈希表的关键字*/
        s0=*(f+r)+s0;
	}
#else

	while(*f != '\0')
	{
		s0=*(f)+s0;
		f++ ;
		//r++ ;
	}
#endif
    (NL+i)->k=s0;
}

void st_hash_string_test(void)
{
	char ch1;
	int i ;
	for(i = 0 ; i < NAME_NO ; i++)
	{
		//InitNameList();     
		InsertNameList(NameList, nameL[i] ,i);
	}
	__here__;
    CreateHashList(NameList, HashList); 
	__here__;
	do
	{	
		printf("D. 显示哈希表\nF. 查找\nQ. 退出\n请选择：");
		scanf("%c", &ch1);
		//cin>>&ch1;
		switch(ch1)
		{
			case 'D':
				Display(HashList); 
				printf("\n");
				EraseHashList(HashList);
				Display(HashList); 
				CreateHashList(NameList, HashList); 
				Display(HashList); 
				break;
			case 'F':
			{
				char name[20]={0}; 
				printf("请输入姓名的拼音:");     
				scanf("%s",name);
				FindList(HashList, name);
				printf("\n");
			}
				break;
			case 'Q':
				exit(0);
		}
		printf("come on !(y/n):");
		scanf("%c", &ch1);
	}while(ch1!='n'); 
}

void st_hash_string_test1(void)
{
	StringHashTP HT ;
	int i , ret , index;
	NAMEP position ;
	//HItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};

	HT = STRHInitializeTable(HASH_LENGTH);
	printf("hash size [%d]\n", HT->size);
	for(i = 0 ; i < NAME_NO ; i++)
	{
		printf("r[%d] :%s\n", i, nameL[i]);
		ret = STRHInsert(nameL[i], &HT);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",nameL[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	printf("hash size [%d]\n", HT->size);
	STRHDisplay(&HT);	
	position = STRHFind("stjq", &HT);
	__msg("关键字[%s]\t键值[%d]\t查找深度[%d]\n", position->py, position->k, position->si);

#if 0
	ret = STRHDelete("stjq", &HT);
	if(SUCCESS == ret)
	{
		STRHDisplay(&HT);
		__msg("delete node success\n");
	}
	position = STRHFind("stjq", &HT);
	if(position->py == NULL)
	{
		__msg("the name is not exit!\n");
		memset(position, 0, sizeof(NAME));
		__msg("关键字[%s]\t键值[%d]\t查找深度[%d]\n", position->py, position->k, position->si);
	}
#endif

	STRHRelease(&HT);
}

// 暴雪的hash
#define TESTNUM 32
extern long  testid;
void st_stomesnow_hash_c_test(void)
{
	int i ;

	MPQHConstruct(TESTNUM);
	printf("取得初始化散列索引表长为：%d\n", GetTableLength_C());
	stbool is_success = SetHashTable_C( "test" );
	if ( is_success )
	{
		printf("散列结果一：成功！\n");
	}
	else
	{
		printf("散列结果一：失败！\n");
	}
	is_success = SetHashTable_C( "测试" );
	if ( is_success )
	{
		printf("散列结果二：成功！\n");
	}
	else
	{
		printf("散列结果二：失败！\n");
	}
	long pos = GetHashTablePos_C( "test" );
	printf("查找测试字符串：\"test\" 的散列位置：%d\n", pos);
	pos = GetHashTablePos_C( "测试" );
	printf("查找测试字符串：“测试” 的散列位置：%d\n", pos);

	//////////////////////////////////////////////////////////////////////////

	// 散列测试

	for ( i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		is_success = SetHashTable_C(buff);
		//is_success ? cout << buff << "散列结果：成功！位置：" << hash_test.testid << endl : cout << buff << "散列结果：失败！" << endl;

		if(is_success)
			printf("[%s]散列结果：成功！位置：[%d]\n",buff, testid);
		else
			printf("[%s]散列结果：失败！\n", buff);
	}

	//////////////////////////////////////////////////////////////////////////

	// 查找测试

	for ( i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		pos = GetHashTablePos_C( buff );
		//pos != -1 ?  cout << "查找测试字符串："<< buff <<" 的散列位置：" << pos << endl : cout << buff << "存在冲突！" << endl;
		if(pos != -1)
			printf("查找测试字符串：[%s] 的散列位置：[%d]\n", buff, pos);
		else
			printf("[%s]存在冲突！\n", buff);
	}

	MPQHDestruct();
}


/* b-tree 多路搜索树测试 */
//测试order序(阶)的B-TREE结构基本操作。
//查找：search，插入：insert，删除：remove。
//创建：create，销毁：destory，打印：print。

void test_BTree_search(BTree tree, KeyType key)
{
    int pos = -1;
    BTNode*    node = BTree_search(tree, key, &pos);
    if (node)
	{
        __inf("在%s节点（包含 %d 个关键字）中找到关键字 %c，其索引为 %d\n",
            node->isLeaf ? "叶子" : "非叶子",
            node->keynum, key, pos);
    }
    else 
	{
        __inf("在树中找不到关键字 %c\n", key);
    }
}

void test_BTree_remove(BTree* tree, KeyType key)
{
    __inf("\n移除关键字 %c \n", key);
    BTree_remove(tree, key);
    BTree_print(*tree, 1);
    __inf("\n");
}

void st_b_tree_test(void)
{
    KeyType array[] = {
        'G','G', 'M', 'P', 'X', 'A', 'C', 'D', 'E', 'J', 'K',
        'N', 'O', 'R', 'S', 'T', 'U', 'V', 'Y', 'Z', 'F', 'X'
    };
    const int length = sizeof(array)/sizeof(KeyType);
    BTree tree = NULL;
    BTNode* node = NULL;
    int pos = -1;
    KeyType key1 = 'R';        // in the tree.
    KeyType key2 = 'B';        // not in the tree.

    // 创建
    BTree_create(&tree, array, length);

    __inf("\n=== 创建 B- 树 ===\n");
    BTree_print(tree, 1);
    __inf("\n");

    // 查找
    test_BTree_search(tree, key1);
    __inf("\n");
    test_BTree_search(tree, key2);

	// 移除不在B树中的元素
	test_BTree_remove(&tree, key2);
	__inf("\n");

    // 插入关键字
    printf("\n插入关键字 %c \n", key2);
    BTree_insert(&tree, key2);
    BTree_print(tree, 1);
    printf("\n");

    test_BTree_search(tree, key2);

    // 移除关键字
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'M';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'E';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'G';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'A';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'D';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'K';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'P';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'J';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'C';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

    key2 = 'X';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	key2 = 'O';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	key2 = 'V';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	key2 = 'R';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	key2 = 'U';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	key2 = 'T';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	key2 = 'N';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);
	key2 = 'S';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);
	key2 = 'Y';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);
	key2 = 'F';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);
	key2 = 'Z';
    test_BTree_remove(&tree, key2);
    test_BTree_search(tree, key2);

	// 销毁
	BTree_destroy(&tree);	
}


//-------------mem pool-----------------

#define ALLOC_COUNT 10


void alloc_test(char *ptr[])
{
    int i, j;

    for(i = 0; i < ALLOC_COUNT; i++)
    {
        if( (ptr[i] = mem_alloc()) == NULL)
        {
            fprintf(stderr, "mem_alloc error\n");
            return;
        }

        for(j = 0; j < ALLOC_COUNT; j++)
        {
            ptr[i][j] = 'a' + j;
        }
    }

    for(i = 0; i < ALLOC_COUNT; i++)
    {
        for(j = 0; j < ALLOC_COUNT; j++)
        {
            printf("ptr[%d][%d]=%c ", i, j, ptr[i][j]);
        }

        fputc('\n', stdout);
    }
}

int st_mempool_test(int argc, char *argv[])
{
    int base, step;
    char *ptr1[ALLOC_COUNT], *ptr2[ALLOC_COUNT];

    switch(argc)
    {
        case 1:
            base = 0; /* default count */
            step = 0; /* default count */
            break;
        case 2:
            base = atoi(argv[1]);
            step = 0;
            break;
        case 3:
            base = atoi(argv[1]);
            step = atoi(argv[2]);
            break;
        default:
            fprintf(stderr, "Usage: %s [<base> [step]]\n", argv[0]);
            break;
    }

    if(!mem_pool_init(base, step))
    {
        fprintf(stderr, "mem_pool_init error\n");
        return 1;
    }

    print_mem_pool_info();

    alloc_test(ptr1);
    print_mem_pool_info();

    mem_free(ptr1[5]);
    print_mem_pool_info();

    alloc_test(ptr2);
    print_mem_pool_info();
    mem_pool_destroy();

    /* once again */
    if(!mem_pool_init(base, step))
    {
        fprintf(stderr, "mem_pool_init error\n");
        return 1;
    }

    print_mem_pool_info();

    alloc_test(ptr1);
    print_mem_pool_info();

    mem_free(ptr1[5]);
    print_mem_pool_info();

    alloc_test(ptr2);
    print_mem_pool_info();

    mem_pool_destroy();

	return 1 ;
}


//----------------st pthread test------------
//下面是测试代码
void * myprocess (void *arg)
{
	printf ("threadid is 0x%x, working on task %d\n", pthread_self (),*(int *) arg);
	sleep (1);/*休息一秒，延长任务的执行时间*/
	return NULL;
}

int st_pthread_test(void)
{
	pool_init (3);/*线程池中最多三个活动线程*/

	/*连续向池中投入10个任务*/
	int *workingnum = (int *) malloc (sizeof (int) * 10);
	int i;
	for (i = 0; i < 10; i++)
	{
		workingnum[i] = i;
		pool_add_worker (myprocess, &workingnum[i]);
	}
	/*等待所有任务完成*/
	sleep (5);
	/*销毁线程池*/
	pool_destroy ();

	free (workingnum);
	return 0;

}


// 二叉堆的测试程序
#define BHMaxSize 		50
void st_binhead_test(void)
{
	BHPriorityQueue H;
	int i, j ;
	
	//typedef int BinHeadET;
	srand((BinHeadET)time(NULL));
	H = BHInitialize( BHMaxSize );
	for( i=0, j=BHMaxSize/2; i<BHMaxSize; i++, j=rand()%BHMaxSize/*( j+71)%BHMaxSize*/ )
        BHInsert( j, H );

	BHDisplayHead(H);
	BHIncreaseKey_P(H, 1, 2) ;
	BHDisplayHead(H);

	j = 0;
    while( !BHIsEmpty( H ) )
	{
		__inf("the min value [%d]\n", BHFindMin(H));
		BHDeleteMin( H) ;
	}	
	printf( "Done...\n" );
}

// 左式堆测试
#define	LH_ARR_SIZE		10
const LeftHeadET a[LH_ARR_SIZE] = {2, 3, 4, 7, 9, 3, 9, 8, 7, 5} ;
int st_left_head_test(void)
{
	LHPriorityQueue H ;
	struct _LHNode * temp ;
	int i, j;

	CreateANullLHeap(&H );
	H = LHBulid (H, a, LH_ARR_SIZE) ;

	LHLevelOrderTraversal(H);

	temp = LHFind(H, 2);
	LHDisplayOneHeap(temp);

	H = LHDeleteMin(H);

	LHLevelOrderTraversal(H);

    return 0;
}

// 二项队列 测试
#define		BQMaxSize	10
int st_binomial_queue_test(void)
{
    BinQueue H;
    int i, j;
    BQItem AnItem;

    BQInitialize(&H, BQMaxSize);
    for( i=0, j=BQMaxSize/2; i<BQMaxSize; i++, j=( j+71)%BQMaxSize )
    {
		printf( "Inserting %d\n", j );
		H = BQInsert( H, j );
    }
	__here__;
 #if 1
    j = 0;
    while( !BQIsEmpty( H ) )
    {
    	__here__;
#if 0 	    
        AnItem = BQDeleteMin( H );
		printf( "DeleteMin item [%d]\n", AnItem );
#else		
  	    if( BQDeleteMin( H ) != j++ )
            printf( "Error in DeleteMin, %d\n", j );
#endif        
    }
    if( j != BQMaxSize )
        printf( "Error in counting\n" );
#endif
    printf( "Done...\n" );
    return 0;	
}

// 不相交集的测试
//#define DJSItem int
int st_disjoint_sets_test(void)
{

	DisjiontSet S;
	int i, j, k, Set1, Set2;

	S = (DisjiontSet)malloc(sizeof(DJSType)*NumSets+1) ;
	if(NULL == S)
		return ;
	
#if 0	/* 根据高度进行求并 */
	DJSInitializeAsHeight( S, NumSets );
#else
	DJSInitializeAsSize( S, NumSets );
#endif

	j = k = 1;
	while( k <= 8 )
	{
		j = 1;
		while( j < NumSets )
		{
			Set1 = DJSFind( S, j );
			Set2 = DJSFind( S, j + k );
#if 0	/* 根据高度进行求并 */
			DJSSetUnionAsHeight( S, Set1, Set2 );
#else
			DJSSetUnionAsSize( S, Set1, Set2 );
#endif
			j += 2 * k;
		}
		k *= 2;
	}
	i = 1;
	for( i = 1; i <= NumSets; i++ )
	{
		Set1 = DJSFind( S, i );
		printf( "%d**", Set1 );
	}
	printf( "\n" );
	return 0;
}

// 拓扑排序测试
#define GSIZE 11
int st_topsort_test(void)
{
	Adjacent_List adj ;
	int capacity = GSIZE, i ;
	GSName topological[GSIZE] ;

	CreateAdjacent_List (&adj, capacity) ;

	InitializeALineOfAdjacent_List (&adj, 0, 's', 0, 3, 'a', 'd', 'g') ;
	InitializeALineOfAdjacent_List (&adj, 1, 'a', 1, 2, 'b', 'e') ;
	InitializeALineOfAdjacent_List (&adj, 2, 'b', 1, 1, 'c') ;
	InitializeALineOfAdjacent_List (&adj, 3, 'c', 3, 1, 't') ;
	InitializeALineOfAdjacent_List (&adj, 4, 'd', 2, 2, 'a', 'e') ;
	InitializeALineOfAdjacent_List (&adj, 5, 'e', 4, 3, 'c', 'f', 'i') ;
	InitializeALineOfAdjacent_List (&adj, 6, 'f', 2, 2, 'c', 't') ;
	InitializeALineOfAdjacent_List (&adj, 7, 'g', 1, 3, 'd', 'e', 'h') ;
	InitializeALineOfAdjacent_List (&adj, 8, 'h', 1, 2, 'e', 'i') ;
	InitializeALineOfAdjacent_List (&adj, 9, 'i', 2, 2, 'f', 't') ;
	InitializeALineOfAdjacent_List (&adj, 10, 't', 3, 0) ;

	// 打印邻接表
	PrintAdjacent_List (&adj) ;

	// 拓扑排序
	st_topological_sort (&adj, topological) ;

	for (i = 0; i < 11; i++)
		printf ("%c\n", topological[i]) ;
	
	ReleaseForAdjacent_List (&adj) ;

	return 0 ;
}

int st_graph_unweigh_path(void)
{
	Adjacent_List adj ;
	int capacity = 8 ;

	CreateAdjacent_List (&adj, capacity) ;

	InitializeALineOfAdjacent_List (&adj, 0, 'a', 0, 3, 'b', 'c', 'd') ; 	
	InitializeALineOfAdjacent_List (&adj, 1, 'b', 1, 2, 'd', 'e') ; 
	InitializeALineOfAdjacent_List (&adj, 2, 'c', 2, 1, 'f') ; 	
	InitializeALineOfAdjacent_List (&adj, 3, 'd', 3, 3, 'c', 'f', 'g') ; 	
	InitializeALineOfAdjacent_List (&adj, 4, 'e', 1, 2, 'd', 'g') ; 	
	InitializeALineOfAdjacent_List (&adj, 5, 'f', 3, 0) ; 	
	InitializeALineOfAdjacent_List (&adj, 6, 'g', 2, 2, 'f', 'h') ; 	
	InitializeALineOfAdjacent_List (&adj, 7, 'h', 1, 0) ; 
	
	PrintAdjacent_List (&adj) ;
	
	putchar ('\n') ;
	
	Unweightd (&adj) ;
	
	PrintAdjacent_List (&adj) ;
	
	ReleaseForAdjacent_List (&adj) ;

	return 1 ;
}

// 带权图的最短路径
int st_dijkstra_test(void)
{
	Adjacenty_List_w adj ;
	struct Ghash_table *ht ;
	int capacity = 11 ;

	Initialize_GH (&ht, capacity * 2) ;

	Initialize_A_W (&adj, capacity) ;

	InitializeALine_A_W (&adj, &ht, 0, 's', 0, 6, 'a', 1, 'd', 4, 'g', 6) ;
	InitializeALine_A_W (&adj, &ht, 1, 'a', 2, 4, 'b', 2, 'e', 2) ;
	InitializeALine_A_W (&adj, &ht, 2, 'b', 1, 2, 'c', 2) ;
	InitializeALine_A_W (&adj, &ht, 3, 'c', 3, 2, 't', 4) ;
	InitializeALine_A_W (&adj, &ht, 4, 'd', 2, 4, 'a', 3, 'e', 3) ;
	InitializeALine_A_W (&adj, &ht, 5, 'e', 4, 6, 'c', 2, 'f', 3, 'i', 3) ;
	InitializeALine_A_W (&adj, &ht, 6, 'f', 2, 4, 'c', 1, 't', 3) ;
	InitializeALine_A_W (&adj, &ht, 7, 'g', 1, 6, 'd', 2, 'e', 1, 'h', 6) ;
	InitializeALine_A_W (&adj, &ht, 8, 'h', 1, 4, 'e', 2, 'i', 3) ;
	InitializeALine_A_W (&adj, &ht, 9, 'i', 2, 4, 'f', 1, 't', 4) ;
	InitializeALine_A_W (&adj, &ht, 10, 't', 3, 0) ;

	dijkstra (&adj, &ht, 0) ;

	PrintAdjacenty_List_A_W (&adj, &ht) ;

	Release_GH (&ht) ;
	Release_A_W (&adj) ;

	return 0 ;
}

int st_new_dijkstra_test(void)
{
	Adjacenty_List_w adj ;
	struct Ghash_table * ht ;
	int capacity = 5 ;

	Initialize_GH (&ht, capacity * 2) ;
	Initialize_A_W (&adj, capacity) ;

	InitializeALine_A_W (&adj, &ht, 0, 's', 0, 4, 'a', 2, 'd', 3) ;
	InitializeALine_A_W (&adj, &ht, 1, 'a', 0, 2, 'b', 2) ;
	InitializeALine_A_W (&adj, &ht, 2, 'b', 0, 2, 'c', 2) ;
	InitializeALine_A_W (&adj, &ht, 3, 'c', 0, 2, 'd', 2) ;
	InitializeALine_A_W (&adj, &ht, 4, 'd', 0, 2, 'c', 3) ;

	new_dijkstra (&adj, &ht, 0) ;
	PrintAdjacenty_List_A_W (&adj, &ht) ;

	Release_GH (&ht) ;
	Release_A_W (&adj) ;

	return 0 ;
}

int st_prim_test(void)
{
	Adjacenty_List_w adj ;
	struct Ghash_table * ht ;
	int capacity = 10 ;

	Initialize_GH (&ht, capacity * 2) ;
	Initialize_A_W (&adj, capacity) ;
	InitializeALine_A_W (&adj, &ht, 0, 'a', 0, 6, 'd', 4, 'e', 4, 'b', 3) ;
	InitializeALine_A_W (&adj, &ht, 1, 'b', 0, 8, 'a', 3, 'e', 2, 'f', 3, 'c', 10) ;
	InitializeALine_A_W (&adj, &ht, 2, 'c', 0, 6, 'b', 10, 'f', 6, 'g', 1) ;
	InitializeALine_A_W (&adj, &ht, 3, 'd', 0, 6, 'a', 4, 'e', 5, 'h', 6) ;
	InitializeALine_A_W (&adj, &ht, 4, 'e', 0, 12, 'd', 5, 'a', 4, 'b', 2, 'f', 11, 'i', 1, 'h', 2) ;
	InitializeALine_A_W (&adj, &ht, 5, 'f', 0, 12, 'e', 11, 'b', 3, 'c', 6, 'g', 2, 'j', 11, 'i', 3) ;
	InitializeALine_A_W (&adj, &ht, 6, 'g', 0, 6, 'f', 2, 'c', 1, 'j', 8) ;
	InitializeALine_A_W (&adj, &ht, 7, 'h', 0, 6, 'd', 6, 'e', 2, 'i', 4) ;
	InitializeALine_A_W (&adj, &ht, 8, 'i', 0, 8, 'h', 4, 'e', 1, 'f', 3, 'j', 7) ;
	InitializeALine_A_W (&adj, &ht, 9, 'j', 0, 6, 'i', 7, 'f', 11, 'g', 8) ;

	PrintAdjacenty_List_A_W (&adj, &ht) ;
	printf("\n");
	prim (&adj, &ht, 0) ;
	PrintAdjacenty_List_A_W (&adj, &ht) ;

	Release_GH (&ht) ;
	Release_A_W (&adj) ;

	return 0 ;
}


// 贪婪算法kruskal求最小生成树
#define KRUSKAL_SIZE (10)

void print_result (const char (* const result)[2], const int * const weight, const int size)
{
	int i ;

	for (i = 0; i < size; i++)
		printf ("%c to %c is %d\n", result[i][0], result[i][1], weight[i]) ;
}

int st_kruskal_test(void)
{
	Adjacenty_List_w adj ;
	GHash_Table ht ;
	int capacity = 10 ;
	char result[KRUSKAL_SIZE][2] ;
	int weight[KRUSKAL_SIZE], size = KRUSKAL_SIZE ;

	Initialize_GH (&ht, capacity * 2) ;
	Initialize_A_W (&adj, capacity) ;

	/*	Initialize the adjacenty list	*/
	InitializeALine_A_W (&adj, &ht, 0, 'a', 0, 6, 'd', 4, 'e', 4, 'b', 3) ;
	InitializeALine_A_W (&adj, &ht, 1, 'b', 0, 8, 'a', 3, 'e', 2, 'f', 3, 'c', 10) ;
	InitializeALine_A_W (&adj, &ht, 2, 'c', 0, 6, 'b', 10, 'f', 6, 'g', 1) ;
	InitializeALine_A_W (&adj, &ht, 3, 'd', 0, 6, 'a', 4, 'e', 5, 'h', 6) ;
	InitializeALine_A_W (&adj, &ht, 4, 'e', 0, 12, 'd', 5, 'a', 4, 'b', 2, 'f', 11, 'i', 1, 'h', 2) ;
	InitializeALine_A_W (&adj, &ht, 5, 'f', 0, 12, 'e', 11, 'b', 3, 'c', 6, 'g', 2, 'j', 11, 'i', 3) ;
	InitializeALine_A_W (&adj, &ht, 6, 'g', 0, 6, 'f', 2, 'c', 1, 'j', 8) ;
	InitializeALine_A_W (&adj, &ht, 7, 'h', 0, 6, 'd', 6, 'e', 2, 'i', 4) ;
	InitializeALine_A_W (&adj, &ht, 8, 'i', 0, 8, 'h', 4, 'e', 1, 'f', 3, 'j', 7) ;
	InitializeALine_A_W (&adj, &ht, 9, 'j', 0, 6, 'i', 7, 'f', 11, 'g', 8) ;
	
	kruskal (&adj, &ht, 0, result, weight) ;
	print_result (result, weight, size - 1) ;

	Release_GH (&ht) ;
	Release_A_W (&adj) ;

	return 0 ;
}

// 求图的关节点
#define ART_SIZE (7)
extern int art_visited[ART_SIZE];
extern int root ;
int st_find_art_test(void)
{
	Adjacenty_List_w padj ;
	struct Ghash_table * pht ;
	int i, size = ART_SIZE ;

	Initialize_A_W (&padj, size) ;
	Initialize_GH (&pht, size * 2) ;
	InitializeALine_A_W (&padj, &pht, 0, 'a', 0, 4, 'b', 0, 'c', 0) ;
	InitializeALine_A_W (&padj, &pht, 1, 'b', 1, 4, 'd', 0, 'g', 0) ;
	InitializeALine_A_W (&padj, &pht, 2, 'c', 2, 2, 'e', 0) ;
	InitializeALine_A_W (&padj, &pht, 3, 'd', 1, 4, 'c', 0, 'f', 0) ;
	InitializeALine_A_W (&padj, &pht, 4, 'e', 1, 0) ;
	InitializeALine_A_W (&padj, &pht, 5, 'f', 1, 0) ;
	InitializeALine_A_W (&padj, &pht, 6, 'g', 1, 0) ;
	
	for (i = 0, size = ART_SIZE; i < size; i++)
		art_visited[i] = FALSE ;
	root = 0 ;
	find_art (&padj, &pht, root) ;

	Release_A_W (&padj) ;
	Release_GH (&pht) ;

	return 0 ;
}

// 图的测试
extern int visited[MAX_VERTEX_NUM];
extern int low[MAX_VERTEX_NUM];

void g_print(char *i)
{
	printf("%s ",i);
}

int st_graph_adjlist_test(void)
{
	int i,j,k,n;
	ALGraph g;
	VertexType v1,v2;
	GSqStack T ;
	CSTree t;
	
	printf("请选择有向图\n");
	CreateGraph(&g);
	G_Display(g);

	TopologicalSort(g) ;		// 拓扑排序

	CriticalPath(g);			// 必须是网的关键路径

	printf("输出关节点：\n");
	FindArticul(g);				// 找关节点
	printf("\n%2s %9s %14s %8s\n", "i", "G.vertices[i].data","visited[i]", "low[i]");
	for(i=0;i<g.vexnum;++i)
		printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);

	printf("深度优先生成树\n");
	DFSForest(g,&t);
	printf("先根遍历生成森林：\n");
	PreOrderTraverse(t,g_print);
	printf("\n");
	
	printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：");
	scanf("%s%s",v1,v2);
	DeleteArc(&g,v1,v2);
	G_Display(g);
	
	printf("修改顶点的值，请输入原值 新值: ");
	scanf("%s%s",v1,v2);
	PutVex(&g,v1,v2);
	G_Display(g);
	
	printf("插入新顶点，请输入顶点的值: ");
	scanf("%s",v1);
	InsertVex(&g,v1);
	G_Display(g);
	
	
	printf("插入与新顶点有关的弧或边，请输入弧或边数目: ");
	scanf("%d",&n);
	for(k=0;k<n;k++)
	{
		printf("请输入另一顶点的值: ");
		scanf("%s",v2);
		printf("对于有向图，请输入另一顶点的方向(0:弧头 1:弧尾): ");
		scanf("%d",&j);
		if(j)
			InsertArc(&g,v2,v1);
		else
			InsertArc(&g,v1,v2);
	}
	G_Display(g);
	
	printf("删除顶点及相关的弧或边，请输入顶点的值: ");
	scanf("%s",v1);
	DeleteVex(&g,v1);
	G_Display(g);
	
	printf("深度优先搜索的结果:\n");
	DFSTraverse(g,g_print);
	
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g,g_print);
	DestroyGraph(&g);

#if 0 
	printf("请顺序选择有向网,无向图,无向网\n");
	for(i=0;i<3;i++) // 验证另外3种情况 
	{
		CreateGraph(&g);
		G_Display(g);
		printf("插入新顶点，请输入顶点的值: ");
		scanf("%s",v1);
		InsertVex(&g,v1);
		printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
		scanf("%d",&n);
		for(k=0;k<n;k++)
		{
			printf("请输入另一顶点的值: ");
			scanf("%s",v2);
			if(g.kind<=1) // 有向 
			{
				printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
				scanf("%d",&j);
				if(j)
					InsertArc(&g,v2,v1);
				else
					InsertArc(&g,v1,v2);
			}
			else // 无向 
				InsertArc(&g,v1,v2);
		}
		G_Display(g);
		printf("删除顶点及相关的弧或边，请输入顶点的值: ");
		scanf("%s",v1);
		DeleteVex(&g,v1);
		G_Display(g);
		DestroyGraph(&g);
	}
#endif
	return 0;
}


stint main(int argc, char *argv[])
{
	fprintf(stderr, "------------slist test------------\n");
	__msg("------------slist test------------\n");
#if 0
	st_external_log("------------slist test------------\n");
	stslist_test();
#elif 1
	fprintf(stderr, "------------array test------------\n");
	starray_test();
#elif 0
	__msg("------------double round link list test------------\n");
	stdrlist_test();
#elif 0
	__msg("------------array round queue test------------\n");
	//st_array_queue_test();
	//st_queue_merge_test();
#elif 0
	__msg("------------array stack test------------\n");
	//st_array_stack_test();
	st_stack_list_test();
#elif 0
	__msg("------------btree test------------\n");
	//st_btree_test();
	st_bstree_test();
#elif 0
	__msg("------------avl tree test------------\n");
	st_avltree_test();
#elif 0
	__msg("------------splay tree test------------\n");
	st_splay_tree_test();
#elif 0
	__msg("------------st g tree test------------\n");
	st_gtree_test();
#elif 0
	__msg("------------st rb tree test------------\n");
	//st_rbtree_test();
	st_rbtree_downn2up_test();
#elif 0
	__msg("------------st treap tree test------------\n");
	st_treap_tree_test() ;
#elif 0
	__msg("------------st qsort tree test------------\n");
	st_qsort_test();
#elif 0
	__msg("------------st ghash test------------\n");
	//st_ghash_test();
	st_hash_test();
#elif 0
	__msg("------------st hash test------------\n");
	st_separate_chaining_hash_test();
	//st_open_address_hash_test();
	//st_open_address_hash_2_test();
	//st_open_address_double_hash_test();
	//st_hash_with_hashing_again_test();
	//st_extendible_hashing_test();
#elif 0
	__msg("------------st b - tree test------------\n");
	st_b_tree_test();
#elif 0
	__msg("------------st mempool test------------\n");
	st_mempool_test(argc, argv);
#elif 0
	__msg("------------st thread pool test------------\n");
	st_pthread_test();
#elif 0
	__msg("------------st hash string test------------\n");
	//st_hash_string_test();
	//st_hash_string_test1();
	st_stomesnow_hash_c_test();
#elif 0
	__msg("------------st binhead  test------------\n");
	st_binhead_test();
	//st_left_head_test();
	//st_binomial_queue_test();
#elif 0
	__msg("------------st disjoint_sets  test------------\n");
	st_disjoint_sets_test();
#elif 0
	__msg("------------st topsort test  test------------\n");
	//st_topsort_test();
	//st_graph_unweigh_path();
	//st_dijkstra_test();
	st_new_dijkstra_test();
	//st_prim_test();
	//st_kruskal_test();
	//st_find_art_test();
#elif 0
	st_graph_adjlist_test();
#endif
	fprintf(stderr, "------------test end------------\n");


	return 1 ;
}
