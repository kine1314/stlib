/*	new_adjacenty_list.c -- 邻接表实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "st_adjacenty_list_w.h"
#include "st_disjoint_sets.h"
#include "st_log.h"

/*	局部函数声明	*/

static Adjoin_To_Vertex * Make_Adjoin_To_Vertex (const GHash_Table * const pht, const ADJLWName name, const int cvw) ;

/*	接口函数定义	*/

int Initialize_A_W (Adjacenty_List_w * const padj, const int capacity)
{
	if (capacity <= 0)
		return 0 ;
	*padj = (struct adjacenty_list_w *) malloc (sizeof (struct adjacenty_list_w)) ;
	if (NULL == *padj)
		return 0 ;
	(*padj)->list = (Vertex_w *) malloc (sizeof (Vertex_w) * capacity) ;
	if (NULL == (*padj)->list)
	{
		free (*padj) ;
		return 0 ;
	}
	(*padj)->indegree = (int *) malloc (sizeof (int) * capacity) ;
	if (NULL == (*padj)->indegree)
	{
		free ((*padj)->list) ;
		free (*padj) ;
		return 0 ;
	}
	(*padj) -> capacity = capacity ;

	return 1 ;
}

int InitializeALine_A_W (Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int index, const ADJLWName name, const int indegree, const int sub, ...)
{
	va_list ap ;
	Adjoin_To_Vertex * temp ;
	ADJLWName others ;
	int i, cvw ;

	if (index > (*padj)->capacity || indegree < 0 || sub < 0)
		return 0 ;
	if (FAILED == Insert_GH (pht, &name, index))
		return 0 ;
	va_start (ap, sub) ;
	/*	Suppose the function will not generate a iterant return value	*/
	(*padj)->list[index].hash_value = GHash (pht, &name) ;
	(*padj)->list[index].known = FALSE ; 
	(*padj)->list[index].dist = INFINITY ;
	(*padj)->list[index].path = NUL ;
	(*padj)->indegree[index] = indegree ;
	if (0 == sub)
	{
		(*padj)->list[index].adjoin_to = NULL ;
		va_end (ap) ;
		return 1 ;
	}
	else if (sub % 2)
	{
		(*padj)->list[index].adjoin_to = NULL ;
		va_end (ap) ;
		return 0 ;
	}
	else
	{
		others = va_arg (ap, int) ;
		cvw = va_arg (ap, int) ;
		temp = (*padj)->list[index].adjoin_to = Make_Adjoin_To_Vertex (pht, others, cvw) ;
		if (NULL == temp)
		{
			va_end (ap) ;
			return 0 ;
		}
		for (i = 2; i < sub; i += 2)
		{
			others = va_arg (ap, int) ;
			cvw = va_arg (ap, int) ;
			temp->next = Make_Adjoin_To_Vertex (pht, others, cvw) ;
			temp = temp->next ;
		}
		va_end (ap) ;
		return 1 ;
	}
}

void PrintAdjacenty_List_A_W (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht)
{
	int i, capacity ;

	for (i = 0, capacity = (*padj) -> capacity; i < capacity; i++)
		printf ("Vertex_w ADJLWName:%-3c Dist:%-2d Path:%-3c\n", (*pht)->lists[(*padj)->list[i].hash_value].name, (*padj)->list[i].dist, (*padj)->list[i].path) ;
}

void Release_A_W (const Adjacenty_List_w * const padj)
{
	Adjoin_To_Vertex * scan, * temp;
	int i, capacity ;

	for (i = 0, capacity = (*padj)->capacity; i < capacity; i++)
	{
		scan = (*padj)->list[i].adjoin_to ;
		while (scan)
		{
			temp = scan ;
			scan = scan->next ;
			free (temp) ;
		}
	}
	free ((*padj)->list) ;
	free ((*padj)->indegree) ;
	free (*padj) ;
}

/*	局部函数定义	*/

static Adjoin_To_Vertex * Make_Adjoin_To_Vertex (const GHash_Table * const pht, const ADJLWName name, const int cvw)
{
	Adjoin_To_Vertex * new_vertex ;

	new_vertex = (Adjoin_To_Vertex *) malloc (sizeof (Adjoin_To_Vertex)) ;
	if (new_vertex)
	{
		/*	Suppose the function will not generate a iterant return value	*/
		new_vertex->hash_value = GHash (pht, &name) ;
		new_vertex->cvw = cvw ;
		new_vertex->next = NULL ;
	}

	return new_vertex ;
}

int dijkstra (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start)
{
	GBinary_Heap  bh ;
	Vertex_w * v ;
	Adjoin_To_Vertex * w ;
	int capacity = (*padj)->capacity, i ;

	Initialize_GB (&bh, capacity * 2) ;
	(*padj)->list[start].dist = 0 ;
	for (i = 0; i < capacity; i++)
		Insert_GB (&bh, (*padj)->list + i) ;
	while (1)
	{
		do
		{
			v = DeleteMin_GB (&bh) ;
			if (NEGATIVEINFINITY == v->dist)
				break ;
		}
		while (TRUE == (*pht)->lists[v->hash_value].be_deleted)
			;
		if (NEGATIVEINFINITY == v->dist)
			break ;
		(*pht)->lists[v->hash_value].be_deleted = TRUE ;
		v->known = TRUE ;
		w = v->adjoin_to ;
		while (w)
		{
			if (FALSE == (*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].known)
			{
				if (v->dist + w->cvw < (*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].dist)
				{
					(*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].dist = v->dist + w->cvw ;
					Insert_GB (&bh, (*padj)->list + (*pht)->lists[w->hash_value].index_in_adjacenty_list) ;
					(*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].path = (*pht)->lists[v->hash_value].name ;
				}
			}
			w = w->next ;
		}
	}
	Release_GB (&bh) ;

	return 1 ;
}

int new_dijkstra (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start)
{
	GBinary_Heap bh ;
	Vertex_w * v ;
	Adjoin_To_Vertex * w ;
	int capacity = (*padj)->capacity, i, v_index, w_index ;
	int * count ;

	count = (int *) calloc (sizeof (int), capacity) ;
	if (NULL == count)
		return 0 ;
	Initialize_GB (&bh, capacity * 2) ;
	(*padj)->list[start].dist = 0 ;
	for (i = 0; i < capacity; i++)
		Insert_GB (&bh, (*padj)->list + i) ;
	while (1)
	{
		do
		{
			v = DeleteMin_GB (&bh) ;
			if (NEGATIVEINFINITY == v->dist)
				break ;
		}
		while (TRUE == (*pht)->lists[v->hash_value].be_deleted);
		
		if (NEGATIVEINFINITY == v->dist)
			break ;
		(*pht)->lists[v->hash_value].be_deleted = TRUE ;
		v->known = TRUE ;
		w = v->adjoin_to ;
		v_index = (*pht)->lists[v->hash_value].index_in_adjacenty_list ;
		while (w)
		{
			w_index = (*pht)->lists[w->hash_value].index_in_adjacenty_list ;
			if (FALSE == (*padj)->list[w_index].known)
			{
				if (v->dist + w->cvw < (*padj)->list[w_index].dist)
				{
					count[w_index] = count[v_index] + 1 ;
					(*padj)->list[w_index].dist = v->dist + w->cvw ;
					Insert_GB (&bh, (*padj)->list + w_index) ;
					(*padj)->list[w_index].path = (*pht)->lists[v->hash_value].name ;
				}
				else if (v->dist + w->cvw == (*padj)->list[w_index].dist)
				{
					if (count[v_index] + 1 < count[w_index])
					{
						count[w_index] = count[v_index] + 1 ;
						(*padj)->list[w_index].path = (*pht)->lists[v->hash_value].name ;
					}
				}
			}
			w = w->next ;
		}
	}
	free (count) ;
	Release_GB (&bh) ;

	return 1 ;
}


int prim (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start)
{
	GBinary_Heap bh ;
	Vertex_w * v ;
	Adjoin_To_Vertex * w ;
	int capacity = (*padj)->capacity, i ;

	Initialize_GB (&bh, capacity * 2) ;
	(*padj)->list[start].dist = 0 ;
	for (i = 0; i < capacity; i++)
		Insert_GB (&bh, (*padj)->list + i) ;
	
	while (1)
	{
		do
		{
			v = DeleteMin_GB (&bh) ;
			if (NEGATIVEINFINITY == v->dist)
				break ;
		}
		while (TRUE == (*pht)->lists[v->hash_value].be_deleted);
		
		if (NEGATIVEINFINITY == v->dist)
			break ;
		
		(*pht)->lists[v->hash_value].be_deleted = TRUE ;
		v->known = TRUE ;
		w = v->adjoin_to ;
		while (w)
		{
			if (FALSE == (*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].known)
			{
				if (w->cvw < (*padj)->list[(*pht)->lists[w ->hash_value].index_in_adjacenty_list].dist)
				{
					(*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].dist = w->cvw ;
					(*padj)->list[(*pht)->lists[w->hash_value].index_in_adjacenty_list].path = (*pht)->lists[v->hash_value].name ;
				}
				Insert_GB (&bh, (*padj)->list + (*pht)->lists[w->hash_value].index_in_adjacenty_list) ;
			}
			w = w->next ;
		}
	}
	Release_GB (&bh) ;

	return 1 ;
}


void kruskal (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int start, char (* const result)[2], int * const weight)
{
	Adjoin_To_Vertex * scan ;
	DisjiontSet d ;
	DJSType vset, wset ;
	Binary_Heap_kruskal bh ;
	Edge_kruskal edge ;
	int capacity = (*padj)->capacity, vertex_sub = capacity, i ;

	d = (DJSType *) malloc (sizeof (DJSType) * ((*pht)->capacity + 1)) ;
	if (NULL == d)
		return ;
	
	/*	Make sure the size of Disjiont is enough large.	*/
	DJSInitializeAsHeight (d, (*pht) -> capacity) ;
	/*	Every edge has two vertexs and every edge will enqueueing twice.	*/
	Initialize_B_kruskal (&bh, capacity * 4) ;
	
	for (i = 0; i < capacity; i++)
	{
		edge.v_hash_value = (*padj)->list[i].hash_value ;
		scan = (*padj)->list[i].adjoin_to ;
		while (scan)
		{
			edge.w_hash_value = scan->hash_value ;
			edge.weight = scan->cvw ;
			Insert_B_kruskal (&bh, &edge) ;
			scan = scan->next ;
		}
	}
	i = 0 ;
	while  (i < vertex_sub - 1)
	{
		DeleteMin_B_kruskal (&bh, &edge) ;
		vset = DJSFind (d, edge.v_hash_value) ;
		wset = DJSFind (d, edge.w_hash_value) ;
		if (vset != wset)
		{
			DJSSetUnionAsHeight (d, vset, wset) ;
			result[i][0] = (*pht)->lists[edge.v_hash_value].name ;
			result[i][1] = (*pht)->lists[edge.w_hash_value].name ;
			weight[i] = edge.weight ;
			i++ ;
		}
	}
	free (d) ;
	Release_B_kruskal (&bh) ;
}

#if 0
int Reverse_A_W (Adjacenty_List_w * const padj, const struct Ghash_table ** const pht)
{
	ADJLWName name ;
	Adjoin_To_Vertex * scan, * new_vertex, * temp_1, * * temp_2 ;
	int w, i, capacity = (*padj)->capacity ;

	for (i = 0; i < capacity; i++)
	{
		scan = (*padj)->list[i].adjoin_to ;
		name = (*pht)->lists[(*padj)->list[i].hash_value].name ;
		while (scan)
		{
			w = (*pht)->lists[scan->hash_value].index_in_adjacenty_list ;
			/*	The incipient value of cvw is FALSE	*/
			if (FALSE == scan->cvw)
			{
				/*	Create a new vertex	*/
				new_vertex = Make_Adjoin_To_Vertex (pht, name, 0) ;
				/*	Borrow the territory of cvw to target	*/
				new_vertex->cvw = TRUE ;
				if (NULL == new_vertex)
					return 0 ;
				if (NULL == (*padj)->list[w].adjoin_to)
					(*padj)->list[w].adjoin_to = new_vertex ;
				else
				{
					temp_2 = Find_End (&(*padj)->list[w].adjoin_to) ;
					(*temp_2)->next = new_vertex ;
				}
				temp_1 = scan ;
				(*padj)->list[i].adjoin_to = scan->next ;
				scan = scan->next ;
				free (temp_1) ;
			}
			else
				scan = scan -> next ;
		}
	}

	return 1 ;
}
#endif

#define ART_SIZE (7)
int art_visited[ART_SIZE], root;
static int number[ART_SIZE], low[ART_SIZE], counter = 1 ;
static char parent[ART_SIZE] ;
void find_art (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int v)
{
	Adjoin_To_Vertex * scan ;
	int w ;

	art_visited[v] = TRUE ;
	low[v] = number[v] = counter++ ;
	scan = (*padj)->list[v].adjoin_to ;
	while (scan)
	{
		w = (*pht)->lists[scan->hash_value].index_in_adjacenty_list ;
		/*	Forward edge	*/
		if (FALSE == art_visited[w])
		{
			parent[w] = (*pht)->lists[v].name ;
			find_art (padj, pht, w) ;
			if (low[w] >= number[v] && v != root)
				printf ("%c is an articulation point.\n", (*pht)->lists[(*padj)->list[v].hash_value].name) ;
			low[v] = MIN (low[v], low[w]) ;
		}
		/*	Back edge	*/
		else if (parent[v] != (*pht)->lists[w].name)
			low[v] = MIN (low[v], number[w]) ;
		scan = scan->next ;
	}
}




