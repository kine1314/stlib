#include <stdio.h>
#include <malloc.h>
#include<stdlib.h>
#define EQ(a,b) ((a)==(b))
#define LT(a,b)  ((a)<(b))
#define LQ(a,b)  ((a)>(b))
#define LH +1     
#define EH 0      
#define RH -1    
#define NULL 0

typedef struct BSTNode
{
	int data;
	int bf;                        
	struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

void R_Rotate(BSTree &p);   
void L_Rotate(BSTree &p);   
void LeftBalance(BSTree &T); 
void RightBalance(BSTree &T);
void PrintBST(BSTree T,int m);
void CreatBST(BSTree &T);   

void erchapaixushu()
{ 
	BSTree T;
	T=(BSTree)malloc(sizeof(BSTNode));
	printf("              *****�����Ƕ��������������㷨����ƽ�⻯����ʾ*****\n");
	printf("\n");
	printf("��д�ˣ���ΰΰ      ѧ�ţ�20082547\n");
	CreatBST(T); 
}

void R_Rotate(BSTree &p) 
{
	BSTree lc;             
	lc = p->lchild;         
	p->lchild = lc->rchild; 
	lc->rchild = p; p = lc;
}

void L_Rotate(BSTree &p) 
{
	BSTree rc;             
	rc = p->rchild;         
	p->rchild = rc->lchild; 
	rc->lchild = p; p = rc; 
}

void LeftBalance(BSTree &T)
{
	BSTree lc,rd;
	lc = T->lchild;          
	switch(lc->bf)           
	{
		case LH:                
			T->bf = lc->bf = EH;
			R_Rotate(T);  
			break;
		case RH:                
			rd = lc->rchild;     
			switch(rd->bf)       
			{
				case LH:
					T->bf = RH; lc->bf = EH; 
					break;
				case EH:
					T->bf = lc->bf = EH; 
					break;
				case RH:
					T->bf = EH; lc->bf = LH; 
					break;
			}
			rd->bf = EH;
			L_Rotate(T->lchild); 
			R_Rotate(T);       
	}
}

void RightBalance(BSTree &T)
{
	BSTree rc,ld;
	rc = T->rchild;        
	switch(rc->bf)          
	{
		case RH:                
			T->bf = rc->bf =EH;
			L_Rotate(T); 
			break;
		case LH:                
			ld = rc->lchild;    
			switch(ld->bf)      
			{
				case LH: 
					T->bf = EH; rc->bf = RH; 
					break;
				case EH: 
					T->bf = rc->bf =EH; 
					break;
				case RH: 
					T->bf = LH; rc->bf = EH; 
					break;
			}
			ld->bf = EH;
			R_Rotate(T->rchild);
			L_Rotate(T);       
	}
}

bool InsertAVL(BSTree &T,int e,bool &taller)
{
	if(!T)
	{
		T = (BSTree)malloc(sizeof(BSTNode)); 
		T->data = e;
		T->lchild = T->rchild =NULL;
		T->bf = EH; taller = true;
	}
	else
	{
		if(EQ(e,T->data))                
		{ 
			taller = false;
			printf("������ͬ�ؼ��ֵĽ�㣡\n"); 
			return 0; 
		}

		if(LT(e,T->data))                
		{
			if(!InsertAVL(T->lchild,e,taller)) 
			{
				return 0;
			}
			if(taller)
			{
				switch(T->bf)             
				{
					case LH:               
						LeftBalance(T); 
						taller = false; 
						break;
					case EH:               
						T->bf = LH; 
						taller = true; 
						break;
					case RH:               
						T->bf = EH; 
						taller = false; 
						break;
				}
			}
		}
		else                           
		{
			if(!InsertAVL(T->rchild,e,taller)) 
			{
				return 0;
			}
			if(taller)
			{
				switch(T->bf)             
				{
					case LH:               
						T->bf = EH; 
						taller = false; 
						break;
					case EH:            
						T->bf = RH; 
						taller = true; 
						break; 
					case RH:              
						RightBalance(T); 
						taller = false; 
						break;
				}
			}
		}
	}
	return 1;
}

void PrintBST(BSTree T,int m)
{
	int i;
	if(T->rchild) 
	{
		PrintBST(T->rchild,m+1);
	}
	for(i = 1; i<=m; i++)  
	{
		printf("     ");
	}
	printf("%d\n",T->data);
	if(T->lchild) 
	{
		PrintBST(T->lchild,m+1);   
	}
}

void CreatBST(BSTree &T)
{
	int e,m;
	bool taller=false;
	T = NULL;
	printf("\n������ؼ���(�ؼ��ּ��ÿո��������-1����):");
	scanf("%d",&e);
	getchar();
	while(e !=-1)
	{
		InsertAVL(T,e,taller);        
		scanf("%d",&e);
		getchar();
		taller=false;
	}
	m=0;
	printf("\n");
	printf("�����ӡ����������������״(�����Ϊ���ڵ㣬�����²���Ϊ�����������ϲ���Ϊ������)��\n");
	if(T)  
	{
		PrintBST(T,m);
	}
	else  
	{
		printf("����һ�ÿ���.\n");
	}
}

int main(void)
{
	erchapaixushu();
	return 1 ;
}



