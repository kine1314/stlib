#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>

#define  MAX 5

typedef struct node
{
	void*		k;
	struct node *next;
}*lnode;

lnode my_input(int *d)
{
	lnode head,temp,terminal;
	char s[MAX+1];

	printf("input the records ('0' to end input):\n");
	scanf("%s",s);
	head=NULL;
	*d=0;
	terminal=NULL;

	while (s[0]!='0')
	{
		temp=(lnode)malloc(sizeof(struct node));

		if (strlen(s) > (unsigned int)*d)
		{
			*d=strlen(s);
		}
		(int)temp->k=atoi(s);
		if (head==NULL)
		{
			head=temp;
			terminal=temp;
		}
		else
		{
			terminal->next=temp;
			terminal=temp;//做程序以防后面要用到的链接
		}
		scanf("%s",s);
	}
	terminal->next=NULL;
	return head;
}


void my_output(lnode h)
{
	lnode t=h;

	printf("\n");
	while (h!=NULL)
	{
		printf("%d",h->k);
		h=h->next;
	}
	h=t;
}


lnode radix_sort(lnode head,int d)
{
	lnode p,q,h,t;
	int i,j,x,radix=1;

	h=(lnode)malloc(sizeof(struct node));
	t=(lnode)malloc(sizeof(struct node));

	for (i=d;i>=1;i--)//数组里元素的位数
	{
		for (j=0;j<=9;j++)
		{
			h[j].next=NULL;
			t[j].next=NULL;
		}

		p=head;
		while (p!=NULL)
		{
			x=((int)(p->k)/radix)%10;
			if (h[x].next==NULL)
			{
				h[x].next=p;
				t[x].next=p;
			}
			else
			{
				q=t[x].next;
				q->next=p;
				t[x].next=p;//q是指另一个队列的头指针，P是另一个队列的尾指针
			}
			p=p->next;
		}

		j=0;
		while (h[j].next==NULL)
		{
			j++;
		}

		head=h[j].next;
		q=t[j].next;

		for (x=j+1;x<=9;x++)
		{
			if (h[x].next!=NULL)
			{
				q->next=h[x].next;//把一个队列的尾部，指向另一个队列的头
				q=t[x].next;
			}
		}
		q->next=NULL;
		radix*=10;
		printf("\n--------------------------\n");
	}

	return head;
}


void my_free(lnode h)
{
	lnode temp=h;
	while (temp)
	{
		h=temp->next;
		free(temp);
		temp=h;//好几个队列要把空间释放掉；
	}
}

int main(void)
{
	lnode h;
	int d;

	h=my_input(&d);
	puts("the sequence you input is:");
	my_output(h);

	h=radix_sort(h,d);
	puts("\n the sequence after radix_sort is:");

	my_output(h);
	my_free(h);

	puts("\n press any key to  quit");
	getchar();
}
