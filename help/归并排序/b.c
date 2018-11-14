#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>



/* 合并两个无序的链表 */
typedef struct Node
{
    int num;
    struct Node * next;
}Node;
Node * createTail()
{
    int x;
    Node *head = NULL, *p = NULL, *tail = NULL;
    puts("\nplease enter some digits(end of '.'):");
    while( 1 == scanf("%d",&x) )
    {
        p = (Node *)malloc(sizeof(Node));
        p->num = x;
        p->next = NULL;
        if( NULL == head )
        {
            tail = p;
            head = tail;
        }
        else
        {
            tail->next = p;
            tail = p;
        }
    }
    getchar();
    return head;
}
Node * CombinationNode(Node* head1, Node* head2)
{
    Node *head,*tail,*p = head1,*q = head2,*s;

    if( NULL == p )
        return q;
    if( NULL == q )
        return p;

    tail = p;
    if( p->num > q->num) 
        tail = q;
    head = tail;

    while( NULL != p && NULL != q )
    {
        if(p->num <= q->num ) 
            //如果p所指元素<q所指元素，那么把p所指元素，率先拉入合并后的链表中，
            //p赋给s，并从p的下一个元素p->next查找。
            //直到发现p所指 不再 < q，而是p > q了 即转至下述代码的else部分。
        {
            s = p; 
            p = p->next;
        }
        else
        {
            s = q;
            q = q->next;
        }
        tail->next = s;
        tail = s;
    }

    if( NULL == p )
        p = q;
    s = p;
    tail->next = s;

    return head;
}
void printHead(Node *head)
{
    if( NULL == head )
        return;
    printf("List: ");
    while(head)
    {
        printf("%d->",head->num);
        head = head->next;
    }
    puts("NUL");
}
void main( void )
{
    Node* head1;
    Node* head2;
    Node* head;

    head1 = createTail();
    printHead(head1);

    head2 = createTail();
    printHead(head2);

    head = CombinationNode(head1,head2);
    printHead(head);
}
