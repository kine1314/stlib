#include<stdio.h>
#include<malloc.h>
#define NULL 0

typedef struct node
{
	char date;
	struct node *next;
}SNode;

SNode *InitStack()
{
	SNode *top;
	top=(SNode *)malloc(sizeof(SNode));
	top->next=NULL;
	return top;
}

void PushOptr(SNode *top,char x)
{
	SNode *p;
	p=(SNode *)malloc(sizeof(SNode));
	p->date=x;
	p->next=top->next;
	top->next=p;

}

char PopOptr(SNode *top)
{
	SNode *p;
	char x;
	if(top==NULL)
	{
		return NULL;
	}
	p=top->next;
	x=p->date;
	top->next=p->next;
	free(p);
	return x;
}

void PushOpnd(SNode *top,char x)
{
	SNode *p;
	p=(SNode *)malloc(sizeof(SNode));
	p->date=x;
	p->next=top->next;
	top->next=p;
}


char PopOpnd(SNode *top)
{
	SNode *p;
	char x;
	if(top==NULL)
	{
		return NULL;
	}
	p=top->next;
	x=p->date;
	top->next=p->next;
	free(p);
	return x;
}

char GetTop(SNode *top)
{
	return (top->next)->date;
}

int In(char c)
{
	int n;
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '#':
			n=1;
			break;
		default:
			n=0;
			break;
	}
	return n;
}


char Precede(char x,char y)//�������ȼ�
{
	int i,j;
	int form[7][7]={{1,1,-1,-1,-1,1,1},{1,1,-1,-1,-1,1,1},{1,1,1,1,-1,1,1},{1,1,1,1,-1,1,1},{-1,-1,-1,-1,-1,0,2},{1,1,1,1,2,1,1},{-1,-1,-1,-1,-1,2,0}}; 
	switch(x)
	{
		case '+':i=0;break;
		case '-':i=1;break;
		case '*':i=2;break;
		case '/':i=3;break;
		case '(':i=4;break;
		case ')':i=5;break;
		case '#':i=6;break; 
	}
	switch(y)
	{
		case '+':j=0;break;
		case '-':j=1;break;
		case '*':j=2;break;
		case '/':j=3;break;
		case '(':j=4;break;
		case ')':j=5;break;
		case '#':j=6;break; 
	}
	if(form[i][j]==1)
	{
		return '>';
	}
	else if(form[i][j]==-1)
	{
		return '<';
	}
	else 
	{
		return '=';
	}
}

int Operate(char x,char z,char y)
{
	int a=x-'0',b=y-'0';
	switch(z)
	{
		case '+':return a+b;
		case '-':return a-b;
		case '*':return a*b;
		case '/':return a/b;
	}
}

char Eval_Exp()
{
	char a,b,c,r,f,z;
	int result;
	SNode *top[2];
	top[0]=InitStack();
	PushOptr(top[0],'#');
	top[1]=InitStack();
	printf("#");
	c=getchar();
	while(c!='#'||(GetTop(top[0]))!='#')
	{
		if(!In(c))//���cΪ����,ѹջ
		{
			PushOpnd(top[1],c);
			printf("%c",c);
			c=getchar();
		}
		else //���Ϊ�ַ�
		{
			r=Precede(GetTop(top[0]),c);
			switch(r)
			{
			case '<':
				PushOptr(top[0],c);
				c=getchar();
				break;
			case '=':
				PopOptr(top[0]);
				c=getchar();
				break;
			case '>':
				b=PopOptr(top[0]);
				printf("%c",b);
				a=PopOpnd(top[1]);
				z=PopOpnd(top[1]);
				result=Operate(z,b,a);
				f=result+'0';
				PushOpnd(top[1],f);
				break;
			}
		}
	}
	printf("  ��====��׺���ʽ\n");
	return f;
}

int biaodashiqiuzhi()
{
	char result;
	char y='y';
	printf("-----------------------���ʽ��ֵ-----------------------\n");
	printf("��д�ˣ����ƴ�         ѧ�ţ�20082556");
	while(y='y')
	{	
		y=getchar();
		if(y=='n')
		{
		break;
		}
		printf("\n������������ʽ����#���������磺5+6#���������뷶Χ0-9�����ʽ�ڲ��ܴ��ڿո�\n");
		result=Eval_Exp();
		printf("���ʽ�Ľ��Ϊ��%d\n",result-'0');

		printf("�Ƿ������y/n:");
		y=getchar();
		if(y=='n')
		{
			break;
		}
	}
	return 0;

}



int main(void)
{
	biaodashiqiuzhi();
	return 1 ;
}


