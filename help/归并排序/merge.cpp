#include <stdlib.h>
#include <time.h>

/* �����Լ�д�˸��ǵݹ��ԭ�ع鲢ʵ�� */

template<class T>
struct Node
{
    Node(T d)
    {
        data = d;
        next = NULL;
    }
    T data;
    Node *next;
};

template<class  T>
Node<T> * GetTailNode( Node<T> *startNode, int length )
    //�������ҵ�β�ڵ�
{
    while(length-- && startNode->next != NULL)
    {
        startNode = startNode->next;
    }
    return startNode;
}

template<class T, class CmpFunc>
Node<T> * Merge( Node<T> *&startNode, int currBlockLen, CmpFunc cmp )
    //��startNode��ʼ����currBlockLen���֣����й鲢����
{
    bool canMerge = true;
    Node<int> *leftBlock = startNode, *rightBlock = startNode;

    // �ҵ�rightBlock��ͷ�ڵ�
    for(int i = 0; i<currBlockLen; ++i)
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

    Node<int> *currSortedNode;                //�������ĵ�ǰ�ڵ�
    Node<int> *currTailNode = NULL;        //��������β�ڵ㣬�����������������һ��������������
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
            Node<T> *tmpNode = currSortedNode->next;            //������һ�������ͷ�ڵ�

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

template<class T, class CmpFunc>
void MergeSort( Node<T>* &dataLink, CmpFunc cmp )
{
    int currBlockLen = 1;
    Node<T> *lastTailNode;
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



Node<int> *BuildLink( int *data, int len )
{
    Node<int> *header = new Node<int>(data[0]);
    Node<int> *currNode = header;
    for(int i = 1; i<len; ++i)
    {
        currNode->next = new Node<int>( data[i] );
        currNode = currNode->next;
    }
    return header;
}

inline bool IntCmp( int &a, int &b )
{
    return a>b;
}

#include <time.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
    srand(time(0));
    int dataLen = 10;
    int *data = new int[dataLen];
    for(int i = 0; i<dataLen; ++i)
    {
        data[i] = rand();
    }

    Node<int> *link = BuildLink(data,dataLen);

	Node<int> *link1 = link ;
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
}