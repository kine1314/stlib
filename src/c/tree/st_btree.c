#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "st_btree.h"
#include "st_log.h"


TElemType SPACE = ' ';							// 字符型以空格符为空 

// 构造空二叉树T 
stint st_btree_init(ST_BTREE *T) 
{
	*T = NULL ;
	return 1 ;
}


// 销毁二叉树T 
void st_btree_destroy(ST_BTREE *T)
{
	if(*T) 										// 非空树 
	{
		if((*T)->lchild) 						// 有左孩子 
			st_btree_destroy(&(*T)->lchild); 	// 销毁左孩子子树 
		if((*T)->rchild) 						// 有右孩子 
			st_btree_destroy(&(*T)->rchild); 	// 销毁右孩子子树 
		free(*T); 								// 释放根结点 
		*T=NULL; 								// 空指针赋0 
	}
}



// 按先序次序输入二叉树中结点的值，构造二叉链表表示的二叉树T
// 变量Nil表示空（子）树。 
void st_btree_create(ST_BTREE *T)
{
	TElemType ch;
	scanf("%c",&ch);							// 输入符合二叉树的字符串

	/* 根据输入的字符，递归创建树 */
	if(SPACE == ch)								// 如果字符为空格
	{
		*T = NULL ;
	}
	else										// 否则递归创建树
	{
		*T = (ST_BTREE)malloc(sizeof(ST_BNODE));
		if(NULL == (*T))
		{
			__err("alloc mem for tree failed !\n");
			exit(0);
		}
		(*T)->data = ch ;
		st_btree_create(&(*T)->lchild);
		st_btree_create(&(*T)->rchild);
	}
}



// 若T为空二叉树,则返回1,否则0 
stint st_btree_empty(ST_BTREE T)
{
	if(NULL != T)
		return 0 ;
	else
		return 1 ;
}



// 返回T的深度 
stint st_btree_depth(ST_BTREE T)
{
	stint r ; 								// 右字树的深度
	stint l ;								// 左子树的深度

	if(NULL == T)
		return 0 ;
	if(NULL != T->lchild)
		l = st_btree_depth(T->lchild) ;		// 递归求左子树深度
	else
		l = 0 ;

	if(NULL != T->rchild)
		r = st_btree_depth(T->rchild) ;		// 递归求右子树深度
	else
		r = 0 ;

	return l > r ? l+1 : r+1 ;				
}



// 返回T的根 
TElemType st_btree_root(ST_BTREE T)
{
	if(st_btree_empty(T))
		return SPACE ;
	else
		return T->data ;
}




// 返回p所指结点的值
TElemType st_btree_value(ST_BTREE p)
{
	return p->data ;
}


// 给p所指结点赋值为value
void st_btree_assign(ST_BTREE p,TElemType value)
{
	p->data = value ;
}

#if 0			/* beacuse use st queue */
// 构造一个空队列Q 
static stint InitQueue(LinkQueue *Q)
{
	//动态分配一个空间
	(*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front)
		exit(0);
	//队头指针指向空，无数据域，这样构成了一个空队列
	(*Q).front->next=NULL;
	return 1;
}

// 插入元素e为Q的新的队尾元素
static stint EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) // 存储分配失败 
		exit(0);
	//生成一个以为e为数据域的队列元素
	p->data=e;
	p->next=NULL;
	//将该新队列元素接在队尾的后面
	(*Q).rear->next=p;
	(*Q).rear=p;
	return 1;
}

// 若队列不空,删除Q的队头元素,用e返回其值,并返回1,否则返回0
static stint DeQueue(LinkQueue *Q,QElemType *e)
{ 
	QueuePtr p;
	if((*Q).front==(*Q).rear)
		return 0;
	p=(*Q).front->next;	//队头元素
	*e=p->data;
	(*Q).front->next=p->next;
	if((*Q).rear==p)
		(*Q).rear=(*Q).front;
	free(p);
	return 1;
}

// 若Q为空队列,则返回1,否则返回0
static stint QueueEmpty(LinkQueue Q)
{ 
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}
#endif


// 若e是T的非根结点,则返回它的双亲,否则返回＂空＂
TElemType st_btree_parent(ST_BTREE T,TElemType e)
{						
	QElemType a;											// 队列元素
	STQueue	*q ;											// 队列
	q = st_queue_new() ;

	if(NULL != T)
	{
		st_queue_init(q) ;
		st_queue_push_tail(q, (stpointer)T);		
		while(!st_queue_is_empty(q))						// 队列非空
		{
			a = (QElemType)st_queue_pop_head(q) ;			// 出队,队列元素赋给a 
			if((a->lchild) && (a->lchild->data==e) ||	\
				(a->rchild) && (a->rchild->data==e))		// 判断是否e的父节点的条件
			{
				return a->data ;
			}
			else 											// 没找到e,则入队其左右孩子指针(如果非空) 
			{
				if(a->lchild)
					st_queue_push_tail(q, (stpointer)a->rchild);
				if(a->rchild)
					st_queue_push_tail(q, (stpointer)a->rchild);
			}
		}
	}

	return SPACE ;
}





// 返回二叉树T中指向元素值为s的结点的指针。
ST_BTREE st_btree_point(ST_BTREE T,TElemType s)
{
	QElemType a;
	STQueue	*q ;
	q = st_queue_new() ;

	if(NULL != T)
	{				
		st_queue_init(q) ;										// 初始化队列 
		st_queue_push_tail(q, (stpointer)T);					// 根结点入队 

		while(!st_queue_is_empty(q))
		{				 
			a = (QElemType)st_queue_pop_head(q) ;				// 出队,队列元素赋给a
			if(a->data == s)	
				return a;
			if(a->lchild) 										// 有左孩子 
				st_queue_push_tail(q, (stpointer)a->lchild);	// 入队左孩子
			if(a->rchild) 										// 有右孩子 
				st_queue_push_tail(q, (stpointer)a->rchild);	// 入队右孩子 	
		}
	}

	return NULL ;
}



// 返回e的左孩子。若e无左孩子,则返回＂空＂
TElemType st_btree_left_child(ST_BTREE T,TElemType e)
{
	ST_BTREE a ;

	if(NULL != T)
	{
		a = st_btree_point(T, e) ;							// 找到节点
		if(a && a->lchild)
			return a->lchild->data ;
	}

	return SPACE ;
}



// 返回e的右孩子。若e无右孩子,则返回＂空＂
TElemType st_btree_right_child(ST_BTREE T,TElemType e)
{
	ST_BTREE a ;

	if(NULL != T)
	{
		a = st_btree_point(T, e);
		if(a && a->rchild)
			return a->rchild->data ;
	}

	return SPACE ;
}




// 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂
TElemType st_btree_left_sibling(ST_BTREE T,TElemType e)
{
	TElemType a;
	ST_BTREE p;

	if(NULL != T)											// 非空树 
	{
		a = st_btree_parent(T, e) ;							// 找到节点e的父亲
		if(SPACE == a)										// 如果是跟节点
			return SPACE ;
		p = st_btree_point(T, a);							// 找到节点a
		if(p->lchild && p->rchild && p->rchild->data == e)
			return p->lchild->data ;						// 返回p的左孩子(e的左兄弟)	
		
	}

	return SPACE ;
}



// 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
TElemType st_btree_right_sibling(ST_BTREE T,TElemType e)
{
	TElemType a;
	ST_BTREE p;

	if(NULL != T)
	{
		a = st_btree_parent(T, e);
		if(SPACE == a)
			return SPACE ;

		p = st_btree_point(T, a);
		if(p->lchild && p->rchild && p->lchild->data == e)
			return p->rchild->data ;
	}

	return SPACE ;
}




//　根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 
//　原有左或右子树则成为c的右子树 
stint st_btree_insert_child(ST_BTREE p, stint LR,ST_BTREE c) // 形参T无用,c是一个无右子树的树 
{
	if(NULL != p)									// p不空 
	{
		if(0 == LR)									// 插入为左子树
		{
			c->rchild = p->lchild;
			p->lchild = c;
		}
		else										// 插入为右子树
		{
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return 1 ;
	}

	return 0 ;
}



// 根据LR为0或1,删除T中p所指结点的左或右子树 
stint st_btree_delete_child(ST_BTREE p, stint LR) 
{
	if(NULL != p)
	{
		if(0 == LR)									// 删除左子树
		{
			STClearBtree(&p->lchild);
		}
		else										// 删除右子树
		{
			STClearBtree(&p->rchild);
		}
		return 1 ;
	}

	return 0 ;
}


// 先序递归遍历T,对每个结点调用函数Visit一次且仅一次
void st_btree_preorder_traverse(ST_BTREE T, VisitFunc Visit)
{
	if(NULL != T) 												// T不空 
	{
		Visit(T->data); 										// 先访问根结点 
		st_btree_preorder_traverse(T->lchild, Visit); 			// 再先序遍历左子树 
		st_btree_preorder_traverse(T->rchild, Visit); 			// 最后先序遍历右子树 
	}	
}

// 先序非递归遍历T
void st_btree_preorder_traverse_iteration(ST_BTREE T, VisitFunc Visit)
{
	ST_BTREE p ;
	SElemType stack[100];
    stint top ;
    p=T;
   
	if(T!=NULL)
    {
		top=1;
        stack[top]=p;
        while(top>0)
        {
			p=stack[top]  ;										/*将右小孩放入栈*/
			top--;
			Visit(p->data) ;
			if(p->rchild!=NULL)
			{
				top++;
				stack[top]=p->rchild;
			}
			if(p->lchild!=NULL)
			{
				top++;
				stack[top]=p->lchild;
			}
		}
	}
	printf("\n");
}



// 中序递归遍历T,对每个结点调用函数Visit一次且仅一次
void st_btree_midorder_traverse(ST_BTREE T, VisitFunc Visit)
{
	if(NULL != T)
	{	
		st_btree_midorder_traverse(T->lchild, Visit) ;			// 先中序遍历左子树 
		Visit(T->data); 										// 再访问根结点 
		st_btree_midorder_traverse(T->rchild, Visit) ;			// 最后中序遍历右子树 
	}
}

/*按照中序非递归遍历二叉树*/
void st_btree_midorder_traverse_iteration(ST_BTREE T, VisitFunc Visit)
{
	ST_BTREE p ;
	SElemType stack[100];
	stint top=0;
	p=T;
	do
	{
		while(p!=NULL)
		{
			top++;
			stack[top]=p;
			p=p->lchild;
		}
		if(top>0)
		{
			p=stack[top];						/*p所指的节点为无左子树或其左子树已经遍历过*/
			top--;
			Visit(p->data);
			p=p->rchild;
		}
	}while(p!=NULL||top!=0);
	printf("\n");
}




//	构造一个空栈S。
static stint InitStack(SqStack *S)
{
	// 为栈底分配一个指定大小的存储空间
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if( !(*S).base )
		exit(0);		// 存储分配失败 
	(*S).top = (*S).base;	// 栈底与栈顶相同表示一个空栈
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

// 若栈S为空栈（栈顶与栈底相同的），则返回1，否则返回0。
static stint StackEmpty(SqStack S)
{
	if(S.top == S.base)
		return 1;
	else
		return 0;
}

//	若栈不空，则用e返回S的栈顶元素，并返回1；否则返回0。
static stint GetTop(SqStack S,SElemType *e)
{
	if(S.top > S.base)
	{
		*e = *(S.top-1);	// 栈顶指针的下一个位置为栈顶元素
		return 1;
	}
	else
		return 0;
}

//	插入元素e为新的栈顶元素。
static stint Push(SqStack *S, SElemType e)
{
	if((*S).top - (*S).base >= (*S).stacksize)	// 栈满，追加存储空间 
	{
		(*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if( !(*S).base )
			exit(0); // 存储分配失败 
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++=e;
	// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

//	若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0。
static stint Pop(SqStack *S,SElemType *e)
{
	if((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

// 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。 
// 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit 
stint st_btree_midorder_iter_traverse(ST_BTREE T, VisitFunc Visit)
{
	SqStack S;
	InitStack(&S);

	while((NULL != T) || !StackEmpty(S))
	{
		if(T)												// 根指针进栈,遍历左子树 
		{ 	
			Push(&S,T);
			T = T->lchild;
		}
		else												// 根指针退栈,访问根结点,遍历右子树 
		{ 	
			Pop(&S,&T);
			if(!Visit(T->data))
				return 0;
			T = T->rchild;
		}
	}
	printf("\n");
	return 1;
}




// 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。 
// 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit 
stint st_btree_midorder_iter_traverse2(ST_BTREE T, VisitFunc Visit)
{
	SqStack S;
	ST_BTREE p;
	InitStack(&S);
	Push(&S,T); 											// 根指针进栈 
	
	while(!StackEmpty(S))
	{
		while(GetTop(S,&p)&&p)
			Push(&S,p->lchild); 							// 向左走到尽头 
		Pop(&S,&p); 										// 空指针退栈 
		if(!StackEmpty(S))									// 访问结点,向右一步 
		{ 
			Pop(&S,&p);
			if(!Visit(p->data))
				return 0;
			Push(&S,p->rchild);
		}
	}
	printf("\n");
	return 1;	
}



// 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 
void st_btree_posorder_traverse(ST_BTREE T, VisitFunc Visit)
{
	if(NULL != T)
	{
		st_btree_posorder_traverse(T->lchild, Visit);
		st_btree_posorder_traverse(T->rchild, Visit);
		Visit(T->data) ;
	}
}

/*按照后序非递归遍历二叉树*/
void st_btree_posorder_traverse_iteration(ST_BTREE T, VisitFunc Visit)
{
	ST_BTREE p ;
	SElemType s[100];
    stint top=-1;
    stint flag[100];

	p = T ;
    while(p != NULL || top != -1)
    {
        while(p)
        {
            top++;
            flag[top] = 0;
            s[top] = p;
            p = p->lchild;
 
        }
        while(top >= 0 && flag[top] == 1)
        {
            p = s[top];
            Visit(p->data) ;
            top--;
        }
        if(top>=0)
        {
            p = s[top];
            flag[top] = 1;
            p = p->rchild;
        }
        else
        {
            p = NULL;
        }
    }
 	printf("\n");
}


// 层序递归遍历T(利用队列),对每个结点调用函数Visit一次且仅一次
void st_btree_level_order_traverse(ST_BTREE T, VisitFunc Visit)
{
	QElemType a;
	STQueue	*q ;
	q = st_queue_new() ;
	
	if(T)
	{
		st_queue_init(q) ;
		st_queue_push_tail(q, (stpointer)T);
		while(!st_queue_is_empty(q))
		{
			a = (QElemType)st_queue_pop_head(q) ;
			Visit(a->data);
			if(a->lchild!=NULL)
				st_queue_push_tail(q, (stpointer)a->lchild);
			if(a->rchild!=NULL)
				st_queue_push_tail(q, (stpointer)a->rchild);
		}
		printf("\n");
	}
}

/*递归法将二叉树的左右子树互换*/
void st_btree_exchange_LR(ST_BTREE T)
{
    ST_BTREE temp;
    if(T)
    {
        st_btree_exchange_LR(T->lchild);
        st_btree_exchange_LR(T->rchild);
        temp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = temp;
    }
}


/*非递归法将二叉树的左右子树互换*/
void st_btree_iteration_exchange_LR(ST_BTREE T)
{
    ST_BTREE temp;
    SElemType s[100];
    stint top=0;
	
    while(T || top)
    {
        if(T)
        {
            s[top++] = T;
            temp = T->lchild;
            T->lchild = T->rchild;
            T->rchild = temp;
            T = T->lchild;
        }
        else
        {
            T = s[--top]->rchild;
        }
    }
}


/*递归法求叶子结点个数*/
stint st_btree_leaves_num(ST_BTREE T)
{
    if(T)
    {
        if(T->lchild == NULL && T->rchild == NULL)
        {
            return 1;
        }
        return (st_btree_leaves_num(T->lchild) + st_btree_leaves_num(T->rchild));
    }
   	else 
	{
   		return 0;
	}
}

/*非递归法求叶子结点个数*/
stint st_btree_leaves_num_iteration(ST_BTREE T, VisitFunc Visit)
{
    SElemType s[100];
    stint count=0,top=0;
	
    while(T || top>0)
    {
        if(T)
        {
             s[top++] = T;
             if(T->lchild == NULL && T->rchild == NULL)
             {
                count++;
              	Visit(T->data);					/*输出叶子结点*/
             }
             T = T->lchild;
         }
        else
         {
            T=s[--top]->rchild;
         }
    }
    return count;
}





///////////////////////////////////////////////////////
//                	  二叉树查找树	                 //
///////////////////////////////////////////////////////


// 构造一个空的动态查找表DT 
stint st_bstree_init(BSTree *DT) 
{
	*DT = NULL ;
	return 1 ;
}


//  销毁动态查找表DT 
void st_bstree_destroy(BSTree *DT)
{
	if(NULL != *DT)
	{	
		if(NULL != (*DT)->lchild)						// 有左孩子 
			st_bstree_destroy(&(*DT)->lchild) ;			// 销毁左孩子子树 
		if(NULL != (*DT)->rchild)						// 有右孩子 
			st_bstree_destroy(&(*DT)->rchild) ;			// 销毁右孩子子树 
		free(*DT) ;										// 递归到最后节点*DT都没有左右子树了，进行释放
		*DT = NULL ;									// 空指针赋0 
	}
}



// 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， 
// 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。
BSTree st_bstree_search(BSTree T,BSTKeyType key)
{
	if((NULL == T) || (key == T->data.key))				// 如果为空，或者根节点是要找的点
		return T; 										// 查找结束 
	else if(key < T->data.key) 							// 在左子树中继续查找 
		return st_bstree_search(T->lchild,key);
	else
		return st_bstree_search(T->rchild,key); 		// 在右子树中继续查找 
}




// 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找 
// 成功，则指针p指向该数据元素结点，并返回1，否则指针p指向查找路径上 
// 访问的最后一个结点并返回0,指针f指向T的双亲，其初始调用值为NULL 
void st_bstree_search1(BSTree *T, BSTKeyType key, BSTree f, BSTree *p, stint *flag) 
{
	if(NULL == (*T)) 											// 查找不成功 
	{
		*p = f;
		*flag = 0;												// 查找不成功
	}
	else if(key == (*T)->data.key) 								// 查找成功 
	{
		*p = *T;												// 指针p指向该数据元素结点
		*flag = 1;												// 查找成功
	}
	else if(key < (*T)->data.key)
		st_bstree_search1(&(*T)->lchild, key, *T, p, flag); 	// 在左子树中继续查找 
	else
		st_bstree_search1(&(*T)->rchild, key, *T, p, flag); 	// 在右子树中继续查找 	
}



// 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回1， 
// 否则返回0。关键如何保持查找树的形态，因为每个点的插入都插到叶节点
// 所以很好插入
stint st_bstree_insert(BSTree *T, BSTElemType e)
{
	BSTree p,s;
	stint flag;
	
	st_bstree_search1(T, e.key, NULL, &p, &flag);
	if(!flag) 										// 查找不成功 
	{
		s=(BSTree)malloc(sizeof(BSTNode));			// 初始化一颗树节点
		s->data=e;
		s->lchild=s->rchild=NULL;
		
		if(NULL == p)
			*T = s; 								// 被插结点*s为新的根结点 
		else if(e.key < p->data.key)
			p->lchild = s; 							// 被插结点*s为左孩子,值小的在左边 
		else
			p->rchild = s; 							// 被插结点*s为右孩子,值大的在右边 
		return 1;
	}
	else
		return 0; 									// 树中已有关键字相同的结点，不再插入 
}



// 从二叉排序树中删除结点p，并重接它的左或右子树。
// 将p的左子树最大的接上来，或者将右子树最小得接上来
void st_bstree_delete_node(BSTree *p)
{
	BSTree q, s;
	
	// 右子树空则只需重接它的左子树（待删结点是叶子也走此分支）
	if(NULL == (*p)->rchild) 
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if(NULL == (*p)->lchild) 					// 只需重接它的右子树 
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else 											// 左右子树均不空 
	{
		q = *p;
		s = (*p)->lchild;
		while(s->rchild) 							// 转左，然后向右到尽头（找待删结点的前驱） 
		{
			q = s;									// 临时保存s节点
			s = s->rchild;
		}
		// s指向被删结点的＂前驱＂（将被删结点前驱的值取代被删结点的值）
		(*p)->data = s->data; 
		if(q != *p)
			q->rchild = s->lchild; 					// 重接*q的右子树 
		else
			q->lchild = s->lchild; 					// 重接*q的左子树 
		free(s);
		s->lchild = s->rchild = NULL ;
		s = NULL ;
	}
}



// 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点， 
// 并返回1；否则返回0。 
stint st_bstree_delete_key(BSTree *T,BSTKeyType key)
{
	if(NULL == *T) 											// 不存在关键字等于key的数据元素 
		return 0;
	else
	{
		if(key == (*T)->data.key) 							// 找到关键字等于key的数据元素 
			st_bstree_delete_node(T);
		else if(key < (*T)->data.key)
			st_bstree_delete_key(&(*T)->lchild,key);
		else
			st_bstree_delete_key(&(*T)->rchild,key);
		return 1;
	}	
}




// 按关键字的顺序对DT的每个结点调用函数Visit()一次
void st_bstree_delete_traverse(BSTree DT,VisitBST Visit)
{
	if(NULL != DT)
	{
		// 像这样先序遍历，最后结果是个非递减顺序
		st_bstree_delete_traverse(DT->lchild,Visit); 	// 先中序遍历左子树 
		Visit(DT->data); 								// 再访问根结点 
		st_bstree_delete_traverse(DT->rchild,Visit); 	// 最后中序遍历右子树 
	}
}


