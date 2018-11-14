#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

/* �����Լ�д�˸��ǵݹ��ԭ�ع鲢ʵ�� */
#ifndef bool 
#define bool 	int 
#endif 
#ifndef true 
#define true 	1 
#endif 
#ifndef false 
#define false 	0 
#endif 

//template<class T>
typedef struct _Node
{
    int data;
    struct _Node *next;
}Node;

typedef bool (*CmpFunc)(int a, int b) ;

/*inline*/ bool IntCmp( int a, int b )
{
    return a>b;
}

//template<class  T>
Node * GetTailNode( Node *startNode, int length )
    //�������ҵ�β�ڵ�
{
    while(length-- && startNode->next != NULL)
    {
        startNode = startNode->next;
    }
    return startNode;
}

//template<class T, class CmpFunc>
Node * Merge( Node *startNode, int currBlockLen, CmpFunc cmp )
    //��startNode��ʼ����currBlockLen���֣����й鲢����
{
	int i ;
    bool canMerge = true;
    Node *leftBlock = startNode; 
    Node *rightBlock = startNode;

    // �ҵ�rightBlock��ͷ�ڵ�
    for(i = 0; i<currBlockLen; ++i)
    {
        rightBlock = rightBlock->next;
        if(rightBlock == NULL)
        {
            canMerge = false;
            break;
        }
    }

    if(!canMerge)
        return NULL;

    Node *currSortedNode;                //�������ĵ�ǰ�ڵ�
    Node *currTailNode = NULL;        //��������β�ڵ㣬�����������������һ��������������
    int leftCount = 0, rightCount = 0;

    //��ʼ��currSortedNode
    if( cmp(leftBlock->data, rightBlock->data) )
    {
        ++rightCount;
        currSortedNode = startNode = rightBlock;
        rightBlock = rightBlock ->next;
    }
    else
    {
        ++leftCount;
        currSortedNode = leftBlock;
        leftBlock = leftBlock ->next;
    }

    while(true)
    {
        if(leftCount == currBlockLen || leftBlock == NULL )
            //��leftBlock�������ʱ��leftBlockβ�ڵ㼴ΪcurrSortedNode
        {
            currSortedNode->next = rightBlock;            //ʣ�µ�rightBlock����������ֱ�Ӽ�������
            currTailNode = GetTailNode( currSortedNode, currBlockLen-rightCount );            //�ҵ������β�ڵ�
            break;
        }
        else if(rightCount == currBlockLen || rightBlock == NULL )
            //����Block������򣬴�ʱ��Block��β�ڵ㼴ΪcurrSortedNode
        {
            Node *tmpNode = currSortedNode->next;            //������һ�������ͷ�ڵ�

            currSortedNode->next = leftBlock;
            currTailNode = GetTailNode( currSortedNode, currBlockLen-leftCount );
            currTailNode->next = tmpNode;                    //�������������һ������������
            break;
        }
        else
            //��ͨ�Ĺ鲢����
        {
            if(cmp(leftBlock->data, rightBlock->data))
            {
                ++rightCount;
                currSortedNode->next = rightBlock;
                rightBlock = rightBlock->next;
            }
            else
            {
                ++leftCount;
                currSortedNode->next = leftBlock;
                leftBlock = leftBlock->next;
            }
            currSortedNode = currSortedNode->next;
        }
    }
    return currTailNode->next != NULL ? currTailNode : NULL;                //����NULL��ζ��һ�ֹ鲢�Ľ���
}

//template<class T, class CmpFunc>
void MergeSort( Node* dataLink, CmpFunc cmp )
{
    int currBlockLen = 1;
    Node *lastTailNode;
    while( true )
    {
        lastTailNode = Merge( dataLink, currBlockLen, cmp );
        if(lastTailNode != NULL)
        {
            do 
            {
                lastTailNode = Merge( lastTailNode->next, currBlockLen, cmp );
            } 
            while ( lastTailNode != NULL );
            currBlockLen *= 2;
        }
        else
            break;
    }
}



Node *BuildLink( int *data, int len )
{
	int i ;
    Node *header = (Node *)malloc(sizeof(Node));
    header->data = data[0];
    Node* currNode = header;
    for(i = 1; i<len; ++i)
    {
        currNode->next = (Node *)malloc(sizeof(Node));
        currNode->next->data = data[i] ;
        currNode = currNode->next;
    }
    return header;
}




//using namespace std;
int main()
{
	int i ;
    srand(time(0));
    int dataLen = 10;
    //int *data = new int[dataLen];
    int data[10] = {0} ;
    for(i = 0; i<dataLen; ++i)
    {
        data[i] = rand()%10;
    }

    Node*link = BuildLink(data,dataLen);

	Node *link1 = link ;
	while(link1 != NULL)
    {
        printf("%d ", link1->data);
        link1 = link1->next;
    }

	printf("\n");

    MergeSort(link, IntCmp);

    while(link != NULL)
    {
        printf("%d ", link->data);
        link = link->next;
    }
    printf("\n");
}
