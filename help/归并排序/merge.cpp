#include <stdlib.h>
#include <time.h>

/* 于是自己写了个非递归的原地归并实现 */

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
    //按长度找到尾节点
{
    while(length-- && startNode->next != NULL)
    {
        startNode = startNode->next;
    }
    return startNode;
}

template<class T, class CmpFunc>
Node<T> * Merge( Node<T> *&startNode, int currBlockLen, CmpFunc cmp )
    //从startNode开始，按currBlockLen二分，进行归并操作
{
    bool canMerge = true;
    Node<int> *leftBlock = startNode, *rightBlock = startNode;

    // 找到rightBlock的头节点
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

    Node<int> *currSortedNode;                //排序结果的当前节点
    Node<int> *currTailNode = NULL;        //排序结果的尾节点，用于最后将排序结果与下一段链表数据连接
    int leftCount = 0, rightCount = 0;

    //初始化currSortedNode
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
            //当leftBlock完成排序时，leftBlock尾节点即为currSortedNode
        {
            currSortedNode->next = rightBlock;            //剩下的rightBlock无需再排序，直接加入结果链
            currTailNode = GetTailNode( currSortedNode, currBlockLen-rightCount );            //找到结果的尾节点
            break;
        }
        else if(rightCount == currBlockLen || rightBlock == NULL )
            //当右Block完成排序，此时右Block的尾节点即为currSortedNode
        {
            Node<T> *tmpNode = currSortedNode->next;            //记下下一段链表的头节点

            currSortedNode->next = leftBlock;
            currTailNode = GetTailNode( currSortedNode, currBlockLen-leftCount );
            currTailNode->next = tmpNode;                    //将结果链表与下一段链表连起来
            break;
        }
        else
            //普通的归并操作
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
    return currTailNode->next != NULL ? currTailNode : NULL;                //返回NULL意味着一轮归并的结束
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