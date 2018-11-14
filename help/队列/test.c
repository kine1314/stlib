#define MAX  10 // 最多9个元素 
#define NULL -1 //失败标志

typedef struct
{ 
	int   	d[MAX] ;  //用数组作为队列的储存空间
	int    	front,rear ; //指示队头位置和队尾位置的变量
} SEQUEUE ;  //顺序队列类型定义
SEQUEUE sq ;  //定义顺序队列

void INITQUEUE ( ) //初始化顺序循环队列
{ 
	sq.front = sq.rear = -1;			//初始化空队
}

int ENQUEUE (int x) //顺序循环队列的入队算法
{ 
	if ( sq.front == (sq.rear+1) % MAX ) //满队，入队失败
	{
		return NULL;
	}
	else 
	{ 
		if(sq.rear == -1)
			sq.front = sq.rear = 0 ;
		else
			sq.rear = (sq.rear+1) % MAX; //调整队尾变量
			
		sq.d[sq.rear] = x ;  //数据入队
		return 1 ; 
	} //入队成功
}

int DEQUEUE ( )//循环队列的出队算法
{ 
	if (-1 == sq.rear)  //空队，出队失败
	{
		return NULL;
	}
	else 
	{ 
		int data = sq.d[sq.front] ;
		if(sq.front == sq.rear)
			sq.front = sq.rear = -1;
		else
			sq.front = ( sq.front+1) % MAX ; //调整队首变量
		return data ;
	}  //返回队首元素
}

void main ( )
{
	int x;
	INITQUEUE ( ); //初始化空队
	ENQUEUE (45);  //调用入队算法,45入队
	ENQUEUE (67);  //调用入队算法,67入队
	ENQUEUE (29);  //调用入队算法,29入队
	x = DEQUEUE (); //调用出队算法,x=45
	ENQUEUE (44);  //调用入队算法,44入队
	x = DEQUEUE (); //调用出队算法,x=67
	ENQUEUE (37);  //调用入队算法,37入队
	x = DEQUEUE (); //调用出队算法,x=29
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	ENQUEUE (89);  //调用入队算法,89入队
	x = DEQUEUE (); //调用出队算法,x=44
	x = DEQUEUE (); //调用出队算法,x=37
	x = DEQUEUE (); //调用出队算法,x=89
	while (1) ; //在这一行设置断点,中止程序运行,以便观察程序运行的结果 
}
