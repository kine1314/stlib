#define MAX  10 // ���9��Ԫ�� 
#define NULL -1 //ʧ�ܱ�־

typedef struct
{ 
	int   	d[MAX] ;  //��������Ϊ���еĴ���ռ�
	int    	front,rear ; //ָʾ��ͷλ�úͶ�βλ�õı���
} SEQUEUE ;  //˳��������Ͷ���
SEQUEUE sq ;  //����˳�����

void INITQUEUE ( ) //��ʼ��˳��ѭ������
{ 
	sq.front = sq.rear = -1;			//��ʼ���ն�
}

int ENQUEUE (int x) //˳��ѭ�����е�����㷨
{ 
	if ( sq.front == (sq.rear+1) % MAX ) //���ӣ����ʧ��
	{
		return NULL;
	}
	else 
	{ 
		if(sq.rear == -1)
			sq.front = sq.rear = 0 ;
		else
			sq.rear = (sq.rear+1) % MAX; //������β����
			
		sq.d[sq.rear] = x ;  //�������
		return 1 ; 
	} //��ӳɹ�
}

int DEQUEUE ( )//ѭ�����еĳ����㷨
{ 
	if (-1 == sq.rear)  //�նӣ�����ʧ��
	{
		return NULL;
	}
	else 
	{ 
		int data = sq.d[sq.front] ;
		if(sq.front == sq.rear)
			sq.front = sq.rear = -1;
		else
			sq.front = ( sq.front+1) % MAX ; //�������ױ���
		return data ;
	}  //���ض���Ԫ��
}

void main ( )
{
	int x;
	INITQUEUE ( ); //��ʼ���ն�
	ENQUEUE (45);  //��������㷨,45���
	ENQUEUE (67);  //��������㷨,67���
	ENQUEUE (29);  //��������㷨,29���
	x = DEQUEUE (); //���ó����㷨,x=45
	ENQUEUE (44);  //��������㷨,44���
	x = DEQUEUE (); //���ó����㷨,x=67
	ENQUEUE (37);  //��������㷨,37���
	x = DEQUEUE (); //���ó����㷨,x=29
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	ENQUEUE (89);  //��������㷨,89���
	x = DEQUEUE (); //���ó����㷨,x=44
	x = DEQUEUE (); //���ó����㷨,x=37
	x = DEQUEUE (); //���ó����㷨,x=89
	while (1) ; //����һ�����öϵ�,��ֹ��������,�Ա�۲�������еĽ�� 
}
