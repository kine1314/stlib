/*
 * st_b+_tree.cpp
 *
 *  Created on: 2011-12-5
 *      Author: kine
 */
#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<time.h>
#include<stdio.h>

#include "st_b+_tree_cpp.h"

using namespace std;

int BTree::number=4;			// 定义btree的阶值是4
int BTree::deep=0;
BTree *BTree::root=NULL;

/* btree 类的构造函数 */
BTree::BTree()             				//创建一个节点
{
	data = new int[number];				// 默认是this的赋值
	down = new BTree*[number];
	for(int i=0;i<number;i++)
	{
		data[i]=0;
		down[i]=NULL;
	}
	father = NULL;
	n = 0;
}

/* 返回btree */
BTree* BTree::searchdel(int t)			// 搜索要删除的节点
{
	BTree *p;
	p=root;
	while(p->down[0] != NULL)
	{
		int i;
		for(i=0 ; i < p->n && t> p->data[i] ; i++);
		if(t == p->data[i])
			goto loop;     				//要改父节点的值
		p=p->down[i];
	}
	return p;
loop:
	int y=0;
	while(p->data[y]!=t)y++;			//查找所在的结点

	BTree *q=p->down[y];
	while(q->down[0]!=NULL)
	{
		q=q->down[q->n-1];
	}
	int a=q->data[q->n-2];  			//q到达底端
	p->data[y]=a;
	p=p->down[y];
	while(p->down[0]!=NULL)
	{
		p->data[p->n-1]=a;
		p=p->down[p->n-1];
	}
	return p;
}

/* 删除查找到的节点 */
void BTree::delpoint(int t)						//在this处删除t
{
	int i;
	for(i=0 ; i < n && t > data[i] ; i++);
	if(t!=data[i])
	{
		cout<<"无该元素"<<endl;
		return ;   								//无该元素，结束;
	}
	for(;i<n-1;i++)
	{
		data[i]=data[i+1];
		down[i]=down[i+1];
	}
	n--;
	if(n<(number+1)/2)
	{
		combine();
	}
}

/* 删除tree的节点 */
void BTree::treedel(int t)						// 删除树
{
	if(root==NULL)
	{
		cout<<"空树"<<endl;
		return ;
	}
	if(t>root->data[root->n-1])
	{
		cout<<"无该元素"<<endl;
		return ;
	}
	searchdel(t)->delpoint(t);

}

/* 合并节点 */
void BTree::combine()  //1号结点找第二个，其他的找前一个
{
	int i;

	if(this==root)
	{
		if(root->n==0)
		{
			deep--;
			BTree *p=root;
			root=NULL;
			delete p;
		}
		else
		{
				if(root->n==1&&root->down[0]!=NULL)
			{
					BTree *p=root;
					root=root->down[0];
					delete p;
					deep--;
			}
		}

		return;
	}

	for(i=0;i<father->n;i++)
	{
		if(father->down[i]==this)
			break;
	}
	if(0==i)
	{
		BTree *p;
		int j;
		p=father->down[1];
		if(p->n==(number+1)/2)
		{
			int a;
			a=data[n-1];
			for(j=0;j<p->n;j++)
			{
				data[n]=p->data[j];
				down[n++]=p->down[j];
				if(p->down[j]!=NULL)
					p->down[j]->father=this;
			}
			father->down[1]=this;
			father->delpoint(a);
			delete p;
		}
		else
		{
			father->data[0]=p->data[0];
			data[n]=p->data[0];
			down[n++]=p->down[0];
			if(p->down[0]!=NULL)p->down[0]->father=this;
			for(j=0;j<p->n-1;j++)
			{
				p->data[j]=p->data[j+1];
				p->down[j]=p->down[j+1]	;
			}
			p->n--;
		}
	}
	else
	{
		BTree *p;
		int j;
		p=father->down[i-1];
		if(p->n==(number+1)/2)
		{
			int a;
			a=p->data[p->n-1];
			for(j=0;j<n;j++)
			{
				p->data[p->n]=data[j];
				p->down[p->n++]=down[j];
				if(down[j]!=NULL)
					down[j]->father=p;
			}
			father->down[i]=p;
			father->delpoint(a);
			delete this;
		}
		else
		{
			father->data[i-1]=p->data[p->n-2];
			p->n--;
			for(j=n;j>0;j--)
			{
				data[j]=data[j-1];
			}
			n++;
			data[0]=p->data[p->n];
		}
	}
}


//搜索t的该插入的位置，返回指针
BTree* BTree::searchinsert(int t)
{
	BTree *p;

	if(root==NULL)
	{
		root=new BTree;
		deep=1;
		return root;
	}

	p=root;
	if(t>root->data[root->n-1])  //大于最大关键字要改父节点的关键字
	{
		while(p->down[0]!=NULL)
		{
			p->data[p->n-1]=t;
			p=p->down[p->n-1];
		}
		return p;
	}
	while(p->down[0]!=NULL)
	{
		int i;
		for(i=0;i<p->n&&t>p->data[i];i++);
		p=p->down[i];
	}
	return p;
}

//将t插入树中
bool BTree:: inserttree(int t)
{
	BTree *p=BTree::searchinsert(t);
	if(1 == p->insertpoint(t,NULL))
		return 1;
	else
		return 0;
}

//把元素t和它所指的子树插入this结点中
bool BTree::insertpoint(int t,BTree *p)
{

	int i,j;
	for(i=n-1 ; i >= 0 && data[i] > t ; i--);

	if(i >= 0 && t == data[i])
		return 0;  			//相同不做操作

	if(n+1>number)
	{
		split(t,p);			// 分裂节点
		return 1 ;
	}

	for(j=n-1;j>i;j--)      //插入元素和指针
	{
		data[j+1]=data[j];
		down[j+1]=down[j];
	}
	data[i+1]=t;
	down[i+1]=p;
	if(p!=NULL)
		p->father=this;
	n++;
	return 1;
}

//t,p分别是多余的节点地址，关键字，分裂this节点
void BTree::split(int t,BTree *p)
{

	int i,j;
	if(this==root)
	{
		deep++;
		root=new BTree;
		BTree *pt=new BTree;
		for(i=0,j=0 ; i < (number+1)/2 ; i++)		//找到前(number+1)/2个给pt
		{
			if(t>data[j])
			{
				pt->data[i]=data[j];
				if(down[i]!=NULL)
					down[i]->father=pt;

				pt->down[i]=down[j];
				j++;
			}
			else
			{
				pt->data[i]=t;
				t=99999999;
				if(p!=NULL)
					p->father=pt;
				pt->down[i]=p;
			}

		}
		pt->father=root;
		pt->n=(number+1)/2;
		root->data[0]=pt->data[(number+1)/2-1];
		root->down[0]=pt;
		for(i=0 ; i < number-(number+1)/2+1 ; i++)
		{
			if(j==number)
			{
				data[i]=t;
				down[i]=p;
				break;
			}
			if(t>data[j])
			{
				data[i]=data[j];
				down[i]=down[j];
				j++;
			}
			else
			{
				data[i]=t;
				down[i]=p;
				t=99999999;
			}
		}
		father=root;
		n=number-(number+1)/2+1;
		root->n=2;
		root->data[1]=data[number-(number+1)/2];
		root->down[1]=this;
		}
	else
	{
		BTree *pt=new BTree;
		for(i=0,j=0;i<(number+1)/2;i++)
		{
			if(t>data[j])
			{
				pt->data[i]=data[j];
				if(down[j]!=NULL)down[j]->father=pt;
				pt->down[i]=down[j];
				j++;
			}
			else
			{
				pt->data[i]=t;
				t=99999999;
				if(p!=NULL)p->father=pt;
				pt->down[i]=p;
			}

		}
		pt->father=father;
		pt->n=(number+1)/2;
		for(i=0;i<number-(number+1)/2+1;i++)
		{
			if(j==number){data[i]=t;down[i]=p;break;}
			if(t>data[j])
			{
				data[i]=data[j];
				down[i]=down[j];
				j++;
			}
			else
			{
				data[i]=t;
				t=99999999;
				down[i]=p;
			}
		}
		n=number-(number+1)/2+1;
		father->insertpoint(pt->data[pt->n-1],pt);
	}

}


dui qu;
int *x;    				//各层的结点数
node *head=NULL;				// 链表的头指针

BTree* dui::pop()				//出队
{
	int t;
	t=tp;
	tp=(tp+1)%200;
	if(num[t]!=BTree::deep-1)//不为叶子节点
	{
		for(int i=0;i<data[t]->n;i++)
		{
			push(data[t]->down[i],num[t]+1);
		}
	}
	return data[t];
}

void dui::push(BTree *i,int j)
{
	data[tl]=i;
	num[tl]=j;
	tl=(tl+1)%200;
	x[j]++;
}
bool dui::empty()
{
	if(tp==tl)
		return 1;
	else
		return 0;
}

void bbprint(BTree *p)
{

	for (int i=0; i <p->n; i++)
		cout<<setw(4)<<p->data[i];
	cout<<" | ";
}

void bbprinttree(BTree *q)
{
	if(q==NULL)
	{
		cout<<"空树"<<endl;
		return;
	}
	int i,j;
	for(i=0;i<BTree::deep;i++)
	{
		x[i]=0;
	}
	qu.push(q,0);
	for(i=0;i<BTree::deep;i++)
	{
		cout<<"第"<<i+1<<"层:"<<endl;
		for(j=0;j<x[i];j++)
		{

			bbprint(qu.pop());

		}
		cout<<endl;
	}
}

void BTree::deletetree()
{
	if(root!=NULL)
	{
		deep=1;
		qu.push(root,0);
	}
	while(!qu.empty())
	{
		delete(qu.pop());
	}
	node *p;
	while(head!=NULL)
	{
		p=head;
		head=head->next;
		delete(p);
	}

}
void Createlink(BTree* p)
{
	qu.push(p,0);
	BTree *tree;
	do
	{
		tree=qu.pop();
	}while(tree->down[0]!=NULL);
	node *p1,*p2;
	head=p1=new node;
	p1->q=tree;
	while(!qu.empty())
	{
		p2=new node;
		p2->q=qu.pop();
		p1->next=p2;
		p1=p2;
	}
	p1->next=NULL;
}

void Create(int m)
{
	BTree::deletetree();
	srand((unsigned)time(NULL));
	for(int i=0;i<m;i++)
	{
		BTree::inserttree(rand()%999+1);
	}
	x=new int[BTree::deep];
 	Createlink(BTree::root);

}
void searchroot(int t)
{
	int i ;
	if(BTree::root==NULL)
	{
		cout<<"空树"<<endl;
		return;
	}
	if(t>BTree::root->data[BTree::root->n-1])
	{
		cout<<"无改结点值"<<endl;
		return;
	}
	BTree *p=BTree::root;
	while(p->down[0]!=NULL)
	{
		for(i=0 ; i < p->n&&t>p->data[i] ; i++);
			p=p->down[i];
	}
	for(i=0;i<p->n&&t>p->data[i];i++);
	{
		if(t==p->data[i])
			cout<<"success!~~存在该结点值"<<endl;
		else
			cout<<"fail!~~~不存在该结点值！~~"<<endl;
	}
}
void searchlink(int t)
{
	if(head==NULL)
	{
		cout<<"空树"<<endl;
		return;
	}
	node *p=head;
	int n=0;
	int i ;
	while(p!=NULL)
	{
		n++;
		for(i=0;i<p->q->n&&t>p->q->data[i];i++);
		if(t==p->q->data[i]){cout<<"success!~它在第"<<BTree::deep<<"层的第"<<n<<"个结点里"<<endl;break;}
		else
			if(t<p->q->data[i])
		{
			cout<<"fail!~无该结点值"<<endl;
			break;
		}
		p=p->next;
	}
	if(p==NULL)cout<<"fail!~无该结点值"<<endl;
}












