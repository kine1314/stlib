#ifndef	__ST_GRAPH_H__
#define	__ST_GRAPH_H__

#include "stlib.h"
#include "st_hash_common.h"
#include "st_adjacenty_list.h"
#include "st_adjacenty_list_w.h"

ST_BEGIN_DECLS ;
/*
 * ͼ����ظ���:
 *	1.ͼG�Ķ�����n�ͱ���e�Ĺ�ϵ,
 *	��1����G������ͼ����0��e��n(n-1)/2,ǡ��n(n-1)/2���ߵ�����ͼ��������ȫͼ(Undireet-ed Complete Graph)
 *	��2����G������ͼ����0��e��n(n-1)��ǡ��n(n-1)���ߵ�����ͼ��Ϊ������ȫͼ(Directed Complete Graph)��	
 *	��3����ȫͼ�������ı���������һ�Զ������б�������
 *		��ȫͼ(complete graph)��
 *		��ȫ����ͼ��
 *	������n����������ͼ������n(n-1)/2���ߣ�
 *		��ȫ����ͼ��
 *	������n����������ͼ������n(n-1)���ߣ�
 *	��4����������ͼ��˵��ͼ������һ�Զ��� v i �� v j (i �� j) ���д� v i �� v j ���� v j �� v i ������·������Ƹ�����ͼ��ǿ��ͨ�ġ�
 *		���Ӷ��� v i ������ v j (i �� j) ��·������ v i �� v j ����ͨ�ġ�
 *	2.1ͼ���ڽӾ����ʾ��
    ����ͼ���ڽӾ����ʾ���У��� ���ڽӾ����ʾ���������ڹ�ϵ �� ��һ��˳������洢������Ϣ
    2��2ͼ���ڽӾ���(Adacency Matrix)
    ����G=(V��E)�Ǿ���n�������ͼ����G���ڽӾ����Ǿ����������ʵ�n�׷���A[n,n]:1��ʾ��G�ıߣ�0��ʾ����G�ıߣ�
     ��ͼ���ڽӾ����ʾ���п��Եõ����½��ۣ� ����
	��1������n�����������ͼ����A��i��i��=0��1��i��n��
������2������ͼ���ڽӾ����ǶԳƵģ���A��i��j��=A��j��i����1��i��n��1��j��n��
������3������ͼ���ڽӾ���һ���ԳƵġ�������ڽӾ�������ʾһ������n�����������ͼʱ��Ҫn2����λ���洢�ڽӾ��󣻶���n�����������ͼ��������ϣ��£������Σ���ֻ��n��n+1��/2����λ��
������4������ͼ���ڽӾ���ĵ�i�У����i�У�����Ԫ�صĸ��������ǵ�i������Ķ�TD��vi����
������5������ͼ���ڽӾ���ĵ�i�У����i�У�����Ԫ�صĸ��������ǵ�i������ĳ���OD��vi��[�����ID��vi��]��
	3��������Ȩֵ��ͼ�����ڽӾ�����G�����磬���ڽӾ���ɶ���Ϊ�����У�wij��ʾ���ϵ�Ȩֵ���ޱ�ʾһ�����������ġ��������б���Ȩֵ������
	4.ͼ�ı����㷨�����Ҫ����3�����⣺
	  ��1��ͼ���ص�û����β֮�֣������㷨�Ĳο�Ҫָ�����ʵĵ�һ�����㡣
	  ��2����ͼ�ı���·���п��ܹ���һ����·���Ӷ������ѭ���������㷨���Ҫ���Ǳ���·�����ܵĻ�·���⡣
	  ��3��һ��������ܺ����ɸ����㶼�����ڶ��㣬Ҫʹһ��������������ڶ��㰴��ĳ�ִ��򱻷��ʡ�
	����������ͨͼ���ӳ�ʼ�������һ������·����ͼ�е����������������������Զ�����ͨͼ�ӳ�ʼ�������һ�����Ա�����ͼ��
		1.��ͨͼ��������ȱ����㷨˼�롣
		��1�����ʳ�ʼ����v����Ƕ���v�ѷ��ʡ�
		��2�����Ҷ���v�ĵ�һ���ڽӶ���w��
		��3��������v���ڽӶ���w���ڣ������ִ�У�������ݵ�v������v������һ��δ���ʹ����ڽӵ㡣
		��4��������w��δ�����ʣ�����ʶ���w����Ƕ���wΪ�ѷ��ʡ�
		��5���������Ҷ���w����һ���ڽӶ���wi�����vȡֵwiת�����裨3����ֱ����ͨͼ�����ж���ȫ�����ʹ�Ϊֹ��
		1.��ͨͼ�Ĺ�����ȱ����㷨˼�롣
		��1������v����С�
		��2�������зǿ�ʱ�����ִ�У������㷨������
		��3��������ȡ�ö�ͷ����v�����ʶ���v����Ƕ���v�ѱ����ʡ�
		��4�����Ҷ���v�ĵ�һ���ڽӶ���col��
		��5����v���ڽӶ���colδ�����ʹ��ģ���col����С�
		��6���������Ҷ���v����һ���µ��ڽӶ���col��ת�����裨5����ֱ������v������δ�����ʹ����ڽӵ㴦���ꡣת�����裨2����
 */

//ջADTʵ��
/*	�������Ͷ���	*/

typedef char GSName ;
typedef struct Gstack_node
{
	GSName name ;
	struct Gstack_node * next ;
} GStack_Node ;
typedef GStack_Node * GStack ;

/*	�ӿں�������	*/

/*	����:	��ʼ��һ��ջ	*/
/*	����ǰ:	pstack ָ��һ��ջ	*/
/*	������:	����ڴ����ɹ�, ��ջ����ʼ��������Ϊ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int InitializeGStack (GStack * const pstack) ;

/*	����:	ȷ��һ��ջ�Ƿ�Ϊ��	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ	*/
/*	������:	���ջΪ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int GStackIsEmpty (const GStack * const pstack) ;

/*	����:	��һ��Ԫ����ջ	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ, panme ָ����ջ��Ԫ�ص�����	*/
/*	������:	����ڴ����ɹ�, Ԫ��������Ϊ *pname ��Ԫ����ջ, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int GSPush (GStack * const pstack, const GSName * const pname) ;

/*	����:	��ջ�е���һ��Ԫ��	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ, pname ָ��һ��Ԫ�������������	*/
/*	������:	���ջ��Ϊ��, ջ��Ԫ�س�ջ���� *panme ����ֵ, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int GSPop (GStack * const pstack, GSName * const pname) ;

/*	����:	��һ��������ջ����ջ������������ջ������Ԫ��1��	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ, pfun ָ��һ��û�з���ֵ, ����һ��Stack_Node���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ�����������ջ������Ԫ��1��	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
void GSTraversal (const GStack * const pstack, void (* pfun) (const GStack_Node * const pstack_node)) ;

/*	����:	�ͷ�һ��ջ���õ��ڴ�ռ�	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ	*/
/*	������:	��ջ��ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
void ReleaseGStack (const GStack * const pstack) ;

// ����ADT��ʵ��
/*	�������Ͷ���	*/
typedef struct vertex * GQueue_Item ;

typedef struct Gqueue_node
{
	GQueue_Item queue_item ;
	struct Gqueue_node * next ;
} GQueue_Node ;

typedef struct queue
{
	GQueue_Node * front ;
	GQueue_Node * rear ;
} * GQueue ;

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ������	*/
/*	����ǰ:	pqueue ָ��һ������	*/
/*	������:	����ڴ����ɹ�, ���б�����������ʼ��Ϊ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int InitializeGQueue (GQueue * const pqueue) ;

/*	����:	ȷ��һ�������Ƿ�Ϊ��	*/
/*	����ǰ:	pqueue ָ��һ���ѳ�ʼ���Ķ���	*/
/*	������:	����ö���Ϊ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int GQueueIsEmpty (const GQueue * const pqueue) ;

/*	����:	����������������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	pqueue ָ��һ���ѳ�ʼ���Ķ���, pqueue_item ָ����ӵ�����	*/
/*	������:	����ڴ����ɹ�, ������Ϊ *pqueue_item ��Ԫ�ر���ӵ�������, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int EnGQueue (GQueue * const pqueue, const GQueue_Item * const pqueue_item) ;

/*	����:	�Ӷ�����ɾ��һ��Ԫ��	*/
/*	����ǰ:	pqueue ָ��һ���ѳ�ʼ���Ķ���, pqueue_item ��һ��Queue_Item *���͵ı���	*/
/*	������:	������в�Ϊ��, �Ӷ�����ɾ��һ��Ԫ��, ������Ԫ�ص����ݸ��� *pqueue_item ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int DeGQueue (GQueue * const pqueue, GQueue_Item * const pqueue_item) ;

/*	����:	�ͷ�һ��������ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pqueue ָ��һ���ѳ�ʼ���Ķ���	*/
/*	������:	�ö�����ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
void ReleaseGQueue (GQueue * const pqueue) ;


// ��ʱ����ڽӱ�ʹ�õ�hash��
/*	�������Ͷ���	*/

typedef char GHName ;
typedef struct GHcell
{
	GHName name ;
	int be_deleted ;		//	�����ȶ������Ƿ�����ɾ������
	enum KindOfEntry entry ;
	int index_in_adjacenty_list ;
} GHCell ;
typedef struct Ghash_table
{
	GHCell * lists ;
	int current ;
	int capacity ;
} * GHash_Table ;

/*	�ӿں�������	*/

/*	����:	����һ�����ݲ���һ����ֵ������	*/
/*	����ǰ:	pht ָ��һ���ѳ�ʼ����ɢ�б�, pname ָ��һ������	*/
/*	������:	���ݸ����ݲ���һ����ֵ������	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int GHash (const GHash_Table * const pht, const GHName * const pname) ;

/*	����:	��������ʼ��һ��ɢ�б�	*/
/*	����ǰ:	pht ָ��һ��ɢ�б�, capacity ��ָʾ���С������	*/
/*	������:	��� capacity > 0 && �ڴ����ɹ�, ��ɢ�б�����Ϊ >= capacity ��С������С����ʼ��Ϊ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int Initialize_GH (GHash_Table * const pht, const int capacity) ;

/*	����:	���Ҳ�����һ��ָ��������ɢ�б��е�λ�õ�ָ��	*/
/*	����ǰ:	pht ָ��һ���ѳ�ʼ����ɢ�б�, pname ָ�򱻲��ҵ�����	*/
/*	������:	����ҵ�������Ϊ *pname ��Ԫ��, ����ָ���Ԫ�ص�ָ��; ���򷵻�ָ����ҽ���ʱֹͣ��ɢ�б�Ԫ�ص�ָ��	*/
/*	ʱ�临�Ӷ�: O(N)	*/
GHCell * Find_GH (const GHash_Table * const pht, const GHName * const pname) ;

/*	����:	��ɢ�б������һ��Ԫ�ز�������ɢ�б��е�����	*/
/*	����ǰ:	pht ָ��һ���ѳ�ʼ����ɢ�б�, pname ��ָ�����ֵ�ָ��, index ��Ԫ�����ڽӱ��е�����	*/
/*	������:	�����ǰ��С <= ���С��һ��, ��Ӹ�Ԫ��, ���ص�ǰ����; ���򷵻� FAILED	*/
/*	ʱ�临�Ӷ�: O(N)	*/
int Insert_GH (const GHash_Table * const pht, const GHName * const pname, const int index) ;

/*	����:	��ɢ�б�������ɾ��������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	pht ָ��һ���ѳ�ʼ����ɢ�б�, pname ��ָ�����ֵ�ָ��	*/
/*	������:	����ҵ���Ԫ��, �����������ɾ��, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
int Delete_GH (const GHash_Table * const pht, const GHName * const pname) ;

/*	����:	�ͷ�һ��ɢ�б���ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pht ָ��һ���ѳ�ʼ����ɢ�б�	*/
/*	������:	��ɢ�б���ռ�ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
void Release_GH (const GHash_Table * const pht) ;

// ���dijkstraʵ�ֵĶ����
/*	�������Ͷ���	*/

typedef struct vertex_w* GHeap_Item ;
typedef struct Gbinary_heap
{
	GHeap_Item * heap ;
	int capacity ;
	int current ;
} * GBinary_Heap ;

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ�������	*/
/*	����ǰ:	pbh ָ��һ�������, capacity ָʾ�öѵĴ�С	*/
/*	������:	��� capacity > 0 && �ڴ����ɹ�, �����ö�, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�: O(1)	*/
int Initialize_GB (GBinary_Heap * const pbh, const int capacity) ;

/*	����:	��������һ��������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	pbh ָ��һ���ѳ�ʼ���Ķ����, hi �Ǵ���ӵ�ָ������	*/
/*	������:	�����δ��, �������������Ԫ��, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�: O (log N)	*/
int Insert_GB (const GBinary_Heap * const pbh, const GHeap_Item hi) ;

/*	����:	ɾ�������ض�����С��Ԫ��	*/
/*	����ǰ:	pbh ָ��һ���ѳ�ʼ���Ķ����	*/
/*	������:	�����δ��, ɾ��������СԪ�ز�����; ���򷵻ض��е���Ԫ��	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
GHeap_Item DeleteMin_GB (const GBinary_Heap * const pbh) ;

/*	����:	������ָ��Ԫ�ص� dist ���ֵ���� ��	*/
/*	����ǰ:	phb ָ��һ���ѳ�ʼ���Ķ����, index ָʾָ��Ԫ�ص�����, triangle ָʾ���Ĵ�С	*/
/*	������:	����Ѳ�Ϊ�� && index �ǺϷ������� && �� >= 0, ��������Ϊ index ��Ԫ�ص� dist ������ ��, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
int IncreaseKey_GB (const GBinary_Heap * const pbh, const int index, const int triangle) ;

/*	����:	������ָ��Ԫ�ص� dist ��ֵ���� ��	*/
/*	����ǰ:	pbh ָ��һ��һ��ʼ���Ķ����, index ָʾָ��Ԫ�ص�����, triangle ָʾ���Ĵ�С	*/
/*	������:	����Ѳ�Ϊ�� && index �ǺϷ������� && �� >= 0, ��������Ϊ index ��Ԫ�ص� dist �򱻼��� ��, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
int DecreaseKey_GB (const GBinary_Heap * const pbh, const int index, const int triangle) ;

/*	����:	�ͷ�һ���������ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pbh ָ��һ���ѳ�ʼ���Ķ����	*/
/*	������:	�ö���ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
void Release_GB (const GBinary_Heap * const pbh) ;


// ����� for kruskal�㷨
/*	�������Ͷ���	*/

typedef struct edge_kruskal
{
	int v_hash_value ;
	int w_hash_value ;
	int weight ;
} Edge_kruskal ;
typedef struct binary_heap_kruskal
{
	Edge_kruskal * heap ;
	int capacity ;
	int current ;
} * Binary_Heap_kruskal ;

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ�������	*/
/*	����ǰ:	pbh ָ��һ�������, capacity ָʾ�öѵĴ�С	*/
/*	������:	��� capacity > 0 && �ڴ����ɹ�, �����ö�, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�: O(1)	*/
int Initialize_B_kruskal (Binary_Heap_kruskal * const pbh, const int capacity) ;

/*	����:	��������һ��������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	pbh ָ��һ���ѳ�ʼ���Ķ����, pd ָ�����ӵı�	*/
/*	������:	�����δ��, �������������Ԫ��, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�: O (log N)	*/
int Insert_B_kruskal (const Binary_Heap_kruskal * const pbh, const Edge_kruskal * const pd) ;

/*	����:	ɾ�����е� weight ����С��Ԫ��	*/
/*	����ǰ:	pbh ָ��һ���ѳ�ʼ���Ķ����, pd ��ָ�������ݵ�ָ��	*/
/*	������:	�����δ��, ɾ����СԪ��, ����ֵ���� pd ָ�������, ���� 1 ; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
int DeleteMin_B_kruskal (const Binary_Heap_kruskal * const pbh, Edge_kruskal * const pd) ;

/*	����:	�ͷ�һ������ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pbh ָ��һ���ѳ�ʼ���Ķ����	*/
/*	������:	�ö���ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
void Release_B_kruskal (const Binary_Heap_kruskal * const pbh) ;


ST_END_DECLS ;
#endif	/* __ST_GRAPH_H__ */

