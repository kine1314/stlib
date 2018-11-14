#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "st_btree.h"
#include "st_log.h"


TElemType SPACE = ' ';							// �ַ����Կո��Ϊ�� 

// ����ն�����T 
stint st_btree_init(ST_BTREE *T) 
{
	*T = NULL ;
	return 1 ;
}


// ���ٶ�����T 
void st_btree_destroy(ST_BTREE *T)
{
	if(*T) 										// �ǿ��� 
	{
		if((*T)->lchild) 						// ������ 
			st_btree_destroy(&(*T)->lchild); 	// ������������ 
		if((*T)->rchild) 						// ���Һ��� 
			st_btree_destroy(&(*T)->rchild); 	// �����Һ������� 
		free(*T); 								// �ͷŸ���� 
		*T=NULL; 								// ��ָ�븳0 
	}
}



// �������������������н���ֵ��������������ʾ�Ķ�����T
// ����Nil��ʾ�գ��ӣ����� 
void st_btree_create(ST_BTREE *T)
{
	TElemType ch;
	scanf("%c",&ch);							// ������϶��������ַ���

	/* ����������ַ����ݹ鴴���� */
	if(SPACE == ch)								// ����ַ�Ϊ�ո�
	{
		*T = NULL ;
	}
	else										// ����ݹ鴴����
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



// ��TΪ�ն�����,�򷵻�1,����0 
stint st_btree_empty(ST_BTREE T)
{
	if(NULL != T)
		return 0 ;
	else
		return 1 ;
}



// ����T����� 
stint st_btree_depth(ST_BTREE T)
{
	stint r ; 								// �����������
	stint l ;								// �����������

	if(NULL == T)
		return 0 ;
	if(NULL != T->lchild)
		l = st_btree_depth(T->lchild) ;		// �ݹ������������
	else
		l = 0 ;

	if(NULL != T->rchild)
		r = st_btree_depth(T->rchild) ;		// �ݹ������������
	else
		r = 0 ;

	return l > r ? l+1 : r+1 ;				
}



// ����T�ĸ� 
TElemType st_btree_root(ST_BTREE T)
{
	if(st_btree_empty(T))
		return SPACE ;
	else
		return T->data ;
}




// ����p��ָ����ֵ
TElemType st_btree_value(ST_BTREE p)
{
	return p->data ;
}


// ��p��ָ��㸳ֵΪvalue
void st_btree_assign(ST_BTREE p,TElemType value)
{
	p->data = value ;
}

#if 0			/* beacuse use st queue */
// ����һ���ն���Q 
static stint InitQueue(LinkQueue *Q)
{
	//��̬����һ���ռ�
	(*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front)
		exit(0);
	//��ͷָ��ָ��գ�������������������һ���ն���
	(*Q).front->next=NULL;
	return 1;
}

// ����Ԫ��eΪQ���µĶ�βԪ��
static stint EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) // �洢����ʧ�� 
		exit(0);
	//����һ����ΪeΪ������Ķ���Ԫ��
	p->data=e;
	p->next=NULL;
	//�����¶���Ԫ�ؽ��ڶ�β�ĺ���
	(*Q).rear->next=p;
	(*Q).rear=p;
	return 1;
}

// �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������1,���򷵻�0
static stint DeQueue(LinkQueue *Q,QElemType *e)
{ 
	QueuePtr p;
	if((*Q).front==(*Q).rear)
		return 0;
	p=(*Q).front->next;	//��ͷԪ��
	*e=p->data;
	(*Q).front->next=p->next;
	if((*Q).rear==p)
		(*Q).rear=(*Q).front;
	free(p);
	return 1;
}

// ��QΪ�ն���,�򷵻�1,���򷵻�0
static stint QueueEmpty(LinkQueue Q)
{ 
	if(Q.front==Q.rear)
		return 1;
	else
		return 0;
}
#endif


// ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ�
TElemType st_btree_parent(ST_BTREE T,TElemType e)
{						
	QElemType a;											// ����Ԫ��
	STQueue	*q ;											// ����
	q = st_queue_new() ;

	if(NULL != T)
	{
		st_queue_init(q) ;
		st_queue_push_tail(q, (stpointer)T);		
		while(!st_queue_is_empty(q))						// ���зǿ�
		{
			a = (QElemType)st_queue_pop_head(q) ;			// ����,����Ԫ�ظ���a 
			if((a->lchild) && (a->lchild->data==e) ||	\
				(a->rchild) && (a->rchild->data==e))		// �ж��Ƿ�e�ĸ��ڵ������
			{
				return a->data ;
			}
			else 											// û�ҵ�e,����������Һ���ָ��(����ǿ�) 
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





// ���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣
ST_BTREE st_btree_point(ST_BTREE T,TElemType s)
{
	QElemType a;
	STQueue	*q ;
	q = st_queue_new() ;

	if(NULL != T)
	{				
		st_queue_init(q) ;										// ��ʼ������ 
		st_queue_push_tail(q, (stpointer)T);					// �������� 

		while(!st_queue_is_empty(q))
		{				 
			a = (QElemType)st_queue_pop_head(q) ;				// ����,����Ԫ�ظ���a
			if(a->data == s)	
				return a;
			if(a->lchild) 										// ������ 
				st_queue_push_tail(q, (stpointer)a->lchild);	// �������
			if(a->rchild) 										// ���Һ��� 
				st_queue_push_tail(q, (stpointer)a->rchild);	// ����Һ��� 	
		}
	}

	return NULL ;
}



// ����e�����ӡ���e������,�򷵻أ��գ�
TElemType st_btree_left_child(ST_BTREE T,TElemType e)
{
	ST_BTREE a ;

	if(NULL != T)
	{
		a = st_btree_point(T, e) ;							// �ҵ��ڵ�
		if(a && a->lchild)
			return a->lchild->data ;
	}

	return SPACE ;
}



// ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ�
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




// ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ�
TElemType st_btree_left_sibling(ST_BTREE T,TElemType e)
{
	TElemType a;
	ST_BTREE p;

	if(NULL != T)											// �ǿ��� 
	{
		a = st_btree_parent(T, e) ;							// �ҵ��ڵ�e�ĸ���
		if(SPACE == a)										// ����Ǹ��ڵ�
			return SPACE ;
		p = st_btree_point(T, a);							// �ҵ��ڵ�a
		if(p->lchild && p->rchild && p->rchild->data == e)
			return p->lchild->data ;						// ����p������(e�����ֵ�)	
		
	}

	return SPACE ;
}



// ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ�
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




//������LRΪ0��1,����cΪT��p��ָ���������������p��ָ���� 
//��ԭ��������������Ϊc�������� 
stint st_btree_insert_child(ST_BTREE p, stint LR,ST_BTREE c) // �β�T����,c��һ�������������� 
{
	if(NULL != p)									// p���� 
	{
		if(0 == LR)									// ����Ϊ������
		{
			c->rchild = p->lchild;
			p->lchild = c;
		}
		else										// ����Ϊ������
		{
			c->rchild=p->rchild;
			p->rchild=c;
		}
		return 1 ;
	}

	return 0 ;
}



// ����LRΪ0��1,ɾ��T��p��ָ������������� 
stint st_btree_delete_child(ST_BTREE p, stint LR) 
{
	if(NULL != p)
	{
		if(0 == LR)									// ɾ��������
		{
			STClearBtree(&p->lchild);
		}
		else										// ɾ��������
		{
			STClearBtree(&p->rchild);
		}
		return 1 ;
	}

	return 0 ;
}


// ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ��
void st_btree_preorder_traverse(ST_BTREE T, VisitFunc Visit)
{
	if(NULL != T) 												// T���� 
	{
		Visit(T->data); 										// �ȷ��ʸ���� 
		st_btree_preorder_traverse(T->lchild, Visit); 			// ��������������� 
		st_btree_preorder_traverse(T->rchild, Visit); 			// ���������������� 
	}	
}

// ����ǵݹ����T
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
			p=stack[top]  ;										/*����С������ջ*/
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



// ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ��
void st_btree_midorder_traverse(ST_BTREE T, VisitFunc Visit)
{
	if(NULL != T)
	{	
		st_btree_midorder_traverse(T->lchild, Visit) ;			// ��������������� 
		Visit(T->data); 										// �ٷ��ʸ���� 
		st_btree_midorder_traverse(T->rchild, Visit) ;			// ���������������� 
	}
}

/*��������ǵݹ����������*/
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
			p=stack[top];						/*p��ָ�Ľڵ�Ϊ�������������������Ѿ�������*/
			top--;
			Visit(p->data);
			p=p->rchild;
		}
	}while(p!=NULL||top!=0);
	printf("\n");
}




//	����һ����ջS��
static stint InitStack(SqStack *S)
{
	// Ϊջ�׷���һ��ָ����С�Ĵ洢�ռ�
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if( !(*S).base )
		exit(0);		// �洢����ʧ�� 
	(*S).top = (*S).base;	// ջ����ջ����ͬ��ʾһ����ջ
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

// ��ջSΪ��ջ��ջ����ջ����ͬ�ģ����򷵻�1�����򷵻�0��
static stint StackEmpty(SqStack S)
{
	if(S.top == S.base)
		return 1;
	else
		return 0;
}

//	��ջ���գ�����e����S��ջ��Ԫ�أ�������1�����򷵻�0��
static stint GetTop(SqStack S,SElemType *e)
{
	if(S.top > S.base)
	{
		*e = *(S.top-1);	// ջ��ָ�����һ��λ��Ϊջ��Ԫ��
		return 1;
	}
	else
		return 0;
}

//	����Ԫ��eΪ�µ�ջ��Ԫ�ء�
static stint Push(SqStack *S, SElemType e)
{
	if((*S).top - (*S).base >= (*S).stacksize)	// ջ����׷�Ӵ洢�ռ� 
	{
		(*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if( !(*S).base )
			exit(0); // �洢����ʧ�� 
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++=e;
	// �����ʽ��++ * ���ȼ���ͬ���������ǵ����㷽ʽ������������
	return 1;
}

//	��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0��
static stint Pop(SqStack *S,SElemType *e)
{
	if((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	// �����ʽ��++ * ���ȼ���ͬ���������ǵ����㷽ʽ������������
	return 1;
}

// ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú����� 
// �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit 
stint st_btree_midorder_iter_traverse(ST_BTREE T, VisitFunc Visit)
{
	SqStack S;
	InitStack(&S);

	while((NULL != T) || !StackEmpty(S))
	{
		if(T)												// ��ָ���ջ,���������� 
		{ 	
			Push(&S,T);
			T = T->lchild;
		}
		else												// ��ָ����ջ,���ʸ����,���������� 
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




// ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú����� 
// �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit 
stint st_btree_midorder_iter_traverse2(ST_BTREE T, VisitFunc Visit)
{
	SqStack S;
	ST_BTREE p;
	InitStack(&S);
	Push(&S,T); 											// ��ָ���ջ 
	
	while(!StackEmpty(S))
	{
		while(GetTop(S,&p)&&p)
			Push(&S,p->lchild); 							// �����ߵ���ͷ 
		Pop(&S,&p); 										// ��ָ����ջ 
		if(!StackEmpty(S))									// ���ʽ��,����һ�� 
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



// ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� 
void st_btree_posorder_traverse(ST_BTREE T, VisitFunc Visit)
{
	if(NULL != T)
	{
		st_btree_posorder_traverse(T->lchild, Visit);
		st_btree_posorder_traverse(T->rchild, Visit);
		Visit(T->data) ;
	}
}

/*���պ���ǵݹ����������*/
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


// ����ݹ����T(���ö���),��ÿ�������ú���Visitһ���ҽ�һ��
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

/*�ݹ鷨����������������������*/
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


/*�ǵݹ鷨����������������������*/
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


/*�ݹ鷨��Ҷ�ӽ�����*/
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

/*�ǵݹ鷨��Ҷ�ӽ�����*/
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
              	Visit(T->data);					/*���Ҷ�ӽ��*/
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
//                	  ������������	                 //
///////////////////////////////////////////////////////


// ����һ���յĶ�̬���ұ�DT 
stint st_bstree_init(BSTree *DT) 
{
	*DT = NULL ;
	return 1 ;
}


//  ���ٶ�̬���ұ�DT 
void st_bstree_destroy(BSTree *DT)
{
	if(NULL != *DT)
	{	
		if(NULL != (*DT)->lchild)						// ������ 
			st_bstree_destroy(&(*DT)->lchild) ;			// ������������ 
		if(NULL != (*DT)->rchild)						// ���Һ��� 
			st_bstree_destroy(&(*DT)->rchild) ;			// �����Һ������� 
		free(*DT) ;										// �ݹ鵽���ڵ�*DT��û�����������ˣ������ͷ�
		*DT = NULL ;									// ��ָ�븳0 
	}
}



// �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ� 
// �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ�롣
BSTree st_bstree_search(BSTree T,BSTKeyType key)
{
	if((NULL == T) || (key == T->data.key))				// ���Ϊ�գ����߸��ڵ���Ҫ�ҵĵ�
		return T; 										// ���ҽ��� 
	else if(key < T->data.key) 							// ���������м������� 
		return st_bstree_search(T->lchild,key);
	else
		return st_bstree_search(T->rchild,key); 		// ���������м������� 
}




// �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������� 
// �ɹ�����ָ��pָ�������Ԫ�ؽ�㣬������1������ָ��pָ�����·���� 
// ���ʵ����һ����㲢����0,ָ��fָ��T��˫�ף����ʼ����ֵΪNULL 
void st_bstree_search1(BSTree *T, BSTKeyType key, BSTree f, BSTree *p, stint *flag) 
{
	if(NULL == (*T)) 											// ���Ҳ��ɹ� 
	{
		*p = f;
		*flag = 0;												// ���Ҳ��ɹ�
	}
	else if(key == (*T)->data.key) 								// ���ҳɹ� 
	{
		*p = *T;												// ָ��pָ�������Ԫ�ؽ��
		*flag = 1;												// ���ҳɹ�
	}
	else if(key < (*T)->data.key)
		st_bstree_search1(&(*T)->lchild, key, *T, p, flag); 	// ���������м������� 
	else
		st_bstree_search1(&(*T)->rchild, key, *T, p, flag); 	// ���������м������� 	
}



// ������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������1�� 
// ���򷵻�0���ؼ���α��ֲ���������̬����Ϊÿ����Ĳ��붼�嵽Ҷ�ڵ�
// ���Ժܺò���
stint st_bstree_insert(BSTree *T, BSTElemType e)
{
	BSTree p,s;
	stint flag;
	
	st_bstree_search1(T, e.key, NULL, &p, &flag);
	if(!flag) 										// ���Ҳ��ɹ� 
	{
		s=(BSTree)malloc(sizeof(BSTNode));			// ��ʼ��һ�����ڵ�
		s->data=e;
		s->lchild=s->rchild=NULL;
		
		if(NULL == p)
			*T = s; 								// ������*sΪ�µĸ���� 
		else if(e.key < p->data.key)
			p->lchild = s; 							// ������*sΪ����,ֵС������� 
		else
			p->rchild = s; 							// ������*sΪ�Һ���,ֵ������ұ� 
		return 1;
	}
	else
		return 0; 									// �������йؼ�����ͬ�Ľ�㣬���ٲ��� 
}



// �Ӷ�����������ɾ�����p�����ؽ����������������
// ��p�����������Ľ����������߽���������С�ý�����
void st_bstree_delete_node(BSTree *p)
{
	BSTree q, s;
	
	// ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧��
	if(NULL == (*p)->rchild) 
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if(NULL == (*p)->lchild) 					// ֻ���ؽ����������� 
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else 											// �������������� 
	{
		q = *p;
		s = (*p)->lchild;
		while(s->rchild) 							// ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� 
		{
			q = s;									// ��ʱ����s�ڵ�
			s = s->rchild;
		}
		// sָ��ɾ���ģ�ǰ����������ɾ���ǰ����ֵȡ����ɾ����ֵ��
		(*p)->data = s->data; 
		if(q != *p)
			q->rchild = s->lchild; 					// �ؽ�*q�������� 
		else
			q->lchild = s->lchild; 					// �ؽ�*q�������� 
		free(s);
		s->lchild = s->rchild = NULL ;
		s = NULL ;
	}
}



// ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬 
// ������1�����򷵻�0�� 
stint st_bstree_delete_key(BSTree *T,BSTKeyType key)
{
	if(NULL == *T) 											// �����ڹؼ��ֵ���key������Ԫ�� 
		return 0;
	else
	{
		if(key == (*T)->data.key) 							// �ҵ��ؼ��ֵ���key������Ԫ�� 
			st_bstree_delete_node(T);
		else if(key < (*T)->data.key)
			st_bstree_delete_key(&(*T)->lchild,key);
		else
			st_bstree_delete_key(&(*T)->rchild,key);
		return 1;
	}	
}




// ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��
void st_bstree_delete_traverse(BSTree DT,VisitBST Visit)
{
	if(NULL != DT)
	{
		// ���������������������Ǹ��ǵݼ�˳��
		st_bstree_delete_traverse(DT->lchild,Visit); 	// ��������������� 
		Visit(DT->data); 								// �ٷ��ʸ���� 
		st_bstree_delete_traverse(DT->rchild,Visit); 	// ���������������� 
	}
}


