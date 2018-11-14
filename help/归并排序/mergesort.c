#include <stdio.h>
#include <stdlib.h>
#define N 8

struct nature_num {
    int num;
    struct nature_num *next; 
};

void merge(struct nature_num *p, struct nature_num *q)
{
    printf("p->next:%d,q->next:%d\n", p->next, q->next);
    struct nature_num *r, *ptr1, *ptr2;
    ptr1 = p;
    ptr2 = q;
    while(((ptr1->next) != NULL) && (ptr2->next != NULL)){
        if(((ptr1->next)->num) > ((ptr2->next)->num)){
            r = ptr2->next;
            ptr2->next = (ptr2->next)->next;
            r->next = ptr1->next;
            ptr1->next = r; 
            ptr1 = r;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr2->next != NULL){
        r = ptr2->next;
                ptr2->next = (ptr2->next)->next;
                r->next = NULL;
                ptr1->next = r;
                ptr1 = r;
    }
    for(r = p->next; r != NULL; r = r->next){
        printf("%4d", r->num);
    }
    printf("\n");
}

void mergepass(struct nature_num *p)
{
    int i = 0, t, s;
    struct nature_num *q, *r, *head, *m[N] = {NULL};
    head = p;
    m[0] = head;
    printf("m[0]->next:%d\n", m[0]->next->num);
    while((r->next) != NULL){
        q = head->next;
        r = q->next;
        if(q->num > r->num){
            head = (struct nature_num *)malloc(sizeof(struct nature_num));
            head->next = r;
            q->next = NULL;
            m[++i] = head;
            printf("m[++i]->next:%d\n", m[i]->next->num);
        }
        else {
            head = q;
        }
    }

    for(s = 1; s < (i+1); s = s*2){
        for(t = 0; s*(t+1) <= i; t = t+2){
            merge(m[s*t],m[s*(t+1)]);
        }
    }
    for(q = m[0]->next; q != NULL; q = q->next){
        printf("%4d", q->num);
    }
    printf("\n");
}

int main()
{
    int i;
    struct nature_num *p,  *new, *head;

    head = (struct nature_num *)malloc(sizeof(struct nature_num));
    head->next = NULL;

    p = head;
    printf("please input the %d numbers:\n",N);
    for(i = 0; i < N; i++){
        new = (struct nature_num *)malloc(sizeof(struct nature_num));
        if(new == NULL){
            printf("requiring memory error!\n");
            exit(0);
        }
        scanf("%d", &(new->num));
        p->next = new;
        p = new;
    }
    p->next = NULL;

    mergepass(head);

    for(p = head->next; p != NULL; p = p->next){
        printf("%4d", p->num);
    }
    printf("\n");

    for(p = head; p != NULL; p = p->next){
        free(p);
    }
    return 0;
}