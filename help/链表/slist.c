/*
===============================================
作者：rerli
时间：2003-12-05
目的：学习单向链表的创建、删除、
  插入（无序、有序）、输出、
  排序（选择、插入、冒泡）、反序

说明：编译没有任何错误，能生成EXE文件。
  这个程序TC2.0中编译生成的EXE文件，
  在运行输入节点时出现以下错误(TC2.01中没有任何错误)：
  scanf : floating point formats not linked
  Abnormal program termination
  即：struct student中float score字段在输入时，
  它不认float数格式，而改为long score却可以正常运行。
  但是在TC2.01中float score重新编译、链接、运行很正常。
   因此，我认为这是TC2.0在结构类型中的Bug.
================================================
*/

/*
单向链表的图示：
---->[NULL]
head

图1：空链表
      
---->[p1]---->[p2]...---->[pn]---->[NULL]
head   p1->next  p2->next   pn->next

图2：有N个节点的链表
*/

#include <stdlib.h>
#include <stdio.h>
#define NULL 0
#define LEN sizeof(struct student)

struct student
{
 long num; /*学号*/
 float score; /*分数，其他信息可以继续在下面增加字段*/
 struct student *next; /*指向下一节点的指针*/
};

int n; /*节点总数*/

/*
==========================
 功能：创建节点
 返回：指向链表表头的指针
==========================
*/
struct student *Create()
{
 struct student *head; /*头节点*/
 struct student *p1=NULL; /*p1保存创建的新节点的地址*/
 struct student *p2=NULL; /*p2保存原链表最后一个节点的地址*/

 n = 0; /*创建前链表的节点总数为0：空链表*/
 p1 = (struct student *)malloc(LEN); /*开辟一个新节点*/
 p2 = p1; /*如果节点开辟成功，则p2先把它的指针保存下来以备后用*/

 if (p1 == NULL) /*节点开辟不成功*/
 {
  printf("/nCann't create it, try it again in a moment!/n");
  return NULL;
 }
 else /*节点开辟成功*/
 {
  head = NULL; /*开始head指向NULL*/

  printf("Please input %d node -- num,score: ",n+1);
  scanf("%ld,%f",&(p1->num),&(p1->score)); /*录入数据*/
 }
 
 // 循环创建节点
 while(p1->num != 0) /*只要学号不为0，就继续录入下一个节点*/
 {
  n += 1; /*节点总数增加1个*/

  if (n==1) /*如果节点总数是1，则head指向刚创建的节点p1*/
  {
   head = p1;
   /*
   注意：
   此时的p2就是p1,也就是p1->next指向NULL。
   这样写目的是与下面else保持一致。
   */
   p2->next = NULL; 
  }
  else
  {
   p2->next = p1; /*指向上次下面刚开辟的节点*/
  }

  p2 = p1; /*把p1的地址给p2保留，然后p1去产生新节点*/ 
  
  p1 = (struct student *)malloc(LEN);
  printf("Please input %d node -- num,score: ",n+1);
  scanf("%ld,%f",&(p1->num),&(p1->score));
 }

 p2->next = NULL; /*此句就是根据单向链表的最后一个节点要指向NULL*/
 
 free(p1); /*释放p1。用malloc()、calloc()的变量都要free()*/
 p1 = NULL; /*特别不要忘记把释放的变量清空置为NULL,否则就变成"野指针"，即地址不确定的指针。*/
 return head; /*返回创建链表的头指针*/
}


/*
===========================
 功能：输出节点
 返回： void
===========================
*/
void Print(struct student *head)
{
 struct student *p;

 printf("/nNow , These %d records are:/n",n);
 p = head;		// protect the head point
 if(head != NULL) /*只要不是空链表，就输出链表中所有节点*/
 {
  printf("head is %o/n", head); /*输出头指针指向的地址*/
  do 
  { 
   /*
   输出相应的值：当前节点地址、各字段值、当前节点的下一节点地址。
   这样输出便于读者形象看到一个单向链表在计算机中的存储结构，和我们
   设计的图示是一模一样的。   
   */
   printf("%o   %ld   %5.1f   %o/n", p, p->num, p->score, p->next);
   p = p->next; /*移到下一个节点*/
  }
  while (p != NULL);
 }
}


/*
==========================
 功能：删除指定节点
  (此例中是删除指定学号的节点)
 返回：指向链表表头的指针
==========================
*/

/*
单向链表的删除图示：
---->[NULL]
head

图3：空链表

从图3可知，空链表显然不能删除


---->[1]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  2->next   n->next

---->[2]...---->[n]---->[NULL]（删除后链表）
head   2->next   n->next

图4：有N个节点的链表，删除第一个节点
结合原链表和删除后的链表，就很容易写出相应的代码。操作方法如下：
1、你要明白head就是第1个节点，head->next就是第2个节点；
2、删除后head指向第2个节点，就是让head=head->next,OK这样就行了。


---->[1]---->[2]---->[3]...---->[n]---->[NULL]（原链表）
head   1->next  2->next  3->next   n->next

---->[1]---->[3]...---->[n]---->[NULL]（删除后链表）
head   1->next  3->next   n->next

图5：有N个节点的链表，删除中间一个（这里图示删除第2个）
结合原链表和删除后的链表，就很容易写出相应的代码。操作方法如下：
1、你要明白head就是第1个节点，1->next就是第2个节点，2->next就是第3个节点；
2、删除后2，1指向第3个节点，就是让1->next=2->next。 
*/
struct student *Del(struct student *head, long num)
{
 struct student *p1;  /*p1保存当前需要检查的节点的地址*/
 struct student *p2;  /*p2保存当前检查过的节点的地址*/
 
 if (head == NULL) /*是空链表（结合图3理解）*/
 {
  printf("/nList is null!/n");
  return head;
 }

 /*定位要删除的节点*/
 p1 = head;
 while (p1->num != num && p1->next != NULL) /*p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找*/
 {
  p2 = p1; /*保存当前节点的地址*/
  p1 = p1->next; /*后移一个节点*/
 } 

 if (num == p1->num) /*找到了。（结合图4、5理解）*/
 {
  if (p1 == head) /*如果要删除的节点是第一个节点*/
  {
   head = p1->next; /*头指针指向第一个节点的后一个节点，也就是第二个节点。这样第一个节点就不在链表中，即删除。*/   
  }
  else /*如果是其它节点，则让原来指向当前节点的指针，指向它的下一个节点，完成删除*/
  {
   p2->next = p1->next;

  }

  free(p1); /*释放当前节点*/
  p1 = NULL;
  printf("/ndelete %ld success!/n",num);
  n -= 1; /*节点总数减1个*/
 }
 else /*没有找到*/
 {
  printf("/n%ld not been found!/n",num);
 }

 return head;
}


/*
==========================
 功能：插入指定节点的后面
  (此例中是指定学号的节点)
 返回：指向链表表头的指针
==========================
*/

/*
单向链表的插入图示：
---->[NULL]（原链表）
head

---->[1]---->[NULL]（插入后的链表）
head   1->next

图7 空链表插入一个节点
结合原链表和插入后的链表，就很容易写出相应的代码。操作方法如下：
1、你要明白空链表head指向NULL就是head=NULL；
2、插入后head指向第1个节点，就是让head=1,1->next=NULL,OK这样就行了。

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（原链表）
head   1->next  2->next  3->next   n->next

---->[1]---->[2]---->[x]---->[3]...---->[n]---->[NULL]（插入后的链表）
head   1->next  2->next  x->next  3->next   n->next

图8：有N个节点的链表，插入一个节点（这里图示插入第2个后面）
结合原链表和插入后的链表，就很容易写出相应的代码。操作方法如下：
1、你要明白原1->next就是节点2，2->next就是节点3；
2、插入后x指向第3个节点,2指向x，就是让x->next=2->next,1->next=x。
*/
struct student *Insert(struct student *head, long num, struct student *node)
{
 struct student *p1;  /*p1保存当前需要检查的节点的地址*/ 

 if (head == NULL) /*（结合图示7理解）*/
 {
  head = node;
  node->next = NULL;
  n += 1;
  return head;
 } 

 p1 = head;
 while (p1->num != num && p1->next != NULL) /*p1指向的节点不是所要查找的，并且它不是最后一个节点，继续往下找*/
 {  
  p1 = p1->next; /*后移一个节点*/
 }
 
 if (num == p1->num) /*找到了（结合图示8理解）*/
 {
  node->next = p1->next; /*显然node的下一节点是原p1的next*/
  p1->next = node; /*插入后，原p1的下一节点就是要插入的node*/
  n += 1; /*节点总数增加1个*/
 }
 else
 {
  printf("/n%ld not been found!/n",num);
 }
 
 return head;
}


/*
==========================
 功能：反序节点
  (链表的头变成链表的尾，链表的尾变成头)
 返回：指向链表表头的指针
==========================
*/

/*
单向链表的反序图示：
---->[1]---->[2]---->[3]...---->[n]---->[NULL]（原链表）
head   1->next  2->next  3->next   n->next

[NULL]<----[1]<----[2]<----[3]<----...[n]<----（反序后的链表）
     1->next  2->next  3->next   n->next  head

图9：有N个节点的链表反序
结合原链表和插入后的链表，就很容易写出相应的代码。操作方法如下：
1、我们需要一个读原链表的指针p2,存反序链表的p1=NULL（刚好最后一个节点的next为NULL）,还有一个临时存储变量p；
2、p2在原链表中读出一个节点，我们就把它放到p1中，p就是用来处理节点放置顺序的问题；
3、比如，现在我们取得一个2,为了我们继续往下取节点，我们必须保存它的next值，由原链表可知p=2->next;
4、然后由反序后的链表可知，反序后2->next要指向1，则2->next=1;
5、好了，现在已经反序一个节点，接着处理下一个节点就需要保存此时的信息：
   p1变成刚刚加入的2，即p1=2;p2要变成它的下一节点，就是上面我们保存的p,即p2=p。
*/
struct student *Reverse(struct student *head)
{
 struct student *p; /*临时存储*/
 struct student *p1; /*存储返回结果*/
 struct student *p2; /*源结果节点一个一个取*/
 
 p1 = NULL; /*开始颠倒时，已颠倒的部分为空*/
 p2 = head; /*p2指向链表的头节点*/
 while (p2 != NULL)
 {
  p = p2->next;
  p2->next = p1;
  p1 = p2;
  p2 = p;
 }
 head = p1;
 return head;
}


/*

接着讲（测试编译时，请把相应的函数及测试代码放到上一讲代码的相关地方）：

排序（选择、插入、冒泡）

插入（有序）

*/

/*
===============================================
作者：rerli
时间：2003-12-08
目的：学习单向链表的创建、修改、删除、
  插入（无序、有序）、输出、
  排序（选择、插入、冒泡）、反序

说明：编译没有任何错误，能生成EXE文件。
  这个程序TC2.0中编译生成的EXE文件，
  在运行输入节点时出现以下错误(TC2.01中没有任何错误)：
  scanf : floating point formats not linked
  Abnormal program termination
  即：struct student中float score字段在输入时，
  它不认float数格式，而改为long score却可以正常运行。
  但是在TC2.01中float score重新编译、链接、运行很正常。
   因此，我认为这是TC2.0在结构类型中的Bug.
================================================
*/

/*
==========================
 功能：选择排序(由小到大)
 返回：指向链表表头的指针
==========================
*/

/*
 选择排序的基本思想就是反复从还未排好序的那些节点中，
 选出键值（就是用它排序的字段，我们取学号num为键值）最小的节点，
 依次重新组合成一个链表。

 我认为写链表这类程序，关键是理解：
 head存储的是第一个节点的地址，head->next存储的是第二个节点的地址；
 任意一个节点p的地址，只能通过它前一个节点的next来求得。

单向链表的选择排序图示：
---->[1]---->[3]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next

---->[NULL]（空链表）
first
tail

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
first   1->next  2->next  3->next   tail->next

图10：有N个节点的链表选择排序

1、先在原链表中找最小的，找到一个后就把它放到另一个空的链表中；
2、空链表中安放第一个进来的节点，产生一个有序链表,并且让它在原链表中分离出来（此时要注意原链表中出来的是第一个节点还是中间其它节点）；
3、继续在原链表中找下一个最小的，找到后把它放入有序链表的尾指针的next,然后它变成其尾指针；
*/
struct student *SelectSort(struct student *head)
{
 struct student *first; /*排列后有序链的表头指针*/
 struct student *tail; /*排列后有序链的表尾指针*/ 
 struct student *p_min; /*保留键值更小的节点的前驱节点的指针*/
 struct student *min; /*存储最小节点*/ 
 struct student *p; /*当前比较的节点*/
 
 first = NULL;
 while (head != NULL) /*在链表中找键值最小的节点。*/
 {
  /*注意：这里for语句就是体现选择排序思想的地方*/
  for (p=head,min=head; p->next!=NULL; p=p->next) /*循环遍历链表中的节点，找出此时最小的节点。*/
  {   
   if (p->next->num < min->num) /*找到一个比当前min小的节点。*/
   {
    p_min = p; /*保存找到节点的前驱节点：显然p->next的前驱节点是p。*/
    min = p->next; /*保存键值更小的节点。*/
   } 
  }
  
  /*上面for语句结束后，就要做两件事；一是把它放入有序链表中；二是根据相应的条件判断，安排它离开原来的链表。*/
  
  /*第一件事添加最小的节点到新有序链表*/
  if (first == NULL) /*如果有序链表目前还是一个空链表*/
  {
   first = min; /*第一次找到键值最小的节点。*/
   tail = min; /*注意：尾指针让它指向最后的一个节点。*/
  }
  else /*有序链表中已经有节点*/
  {
   tail->next = min; /*把刚找到的最小节点放到最后，即让尾指针的next指向它。*/
   tail = min; /*尾指针也要指向它。*/
  }  

  /*第二件事删除原链表节点*/
  if (min == head) /*如果找到的最小节点就是第一个节点*/
  {
   head = head->next; /*显然让head指向原head->next,即第二个节点，就OK*/
  }
  else /*如果不是第一个节点*/
  {
   p_min->next = min->next; /*前次最小节点的next指向当前min的next,这样就让min离开了原链表。*/
  }  
 }

 if (first != NULL) /*循环结束得到有序链表first*/
 {
  tail->next = NULL; /*单向链表的最后一个节点的next应该指向NULL*/ 
 }
 head = first;
 return head;
}


/*
==========================
 功能：直接插入排序(由小到大)
 返回：指向链表表头的指针
==========================
*/

/*
 直接插入排序的基本思想就是假设链表的前面n-1个节点是已经按键值
 （就是用它排序的字段，我们取学号num为键值）排好序的，对于节点n在
 这个序列中找插入位置，使得n插入后新序列仍然有序。按照这种思想，依次
 对链表从头到尾执行一遍，就可以使无序链表变为有序链表。 
 
单向链表的直接插入排序图示：
---->[1]---->[3]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next

---->[1]---->[NULL]（从原链表中取第1个节点作为只有一个节点的有序链表）
head
图11

---->[3]---->[2]...---->[n]---->[NULL]（原链表剩下用于直接插入排序的节点）
first   3->next  2->next   n->next
图12

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
head   1->next  2->next  3->next   n->next

图13：有N个节点的链表直接插入排序

1、先在原链表中以第一个节点为一个有序链表，其余节点为待定节点。
2、从图12链表中取节点，到图11链表中定位插入。
3、上面图示虽说画了两条链表，其实只有一条链表。在排序中，实质只增加了一个用于指向剩下需要排序节点的头指针first罢了。
   这一点请读者务必搞清楚，要不然就可能认为它和上面的选择排序法一样了。
*/
struct student *InsertSort(struct student *head)
{
 struct student *first; /*为原链表剩下用于直接插入排序的节点头指针*/
 struct student *t; /*临时指针变量：插入节点*/
 struct student *p; /*临时指针变量*/
 struct student *q; /*临时指针变量*/
 
 first = head->next; /*原链表剩下用于直接插入排序的节点链表：可根据图12来理解。*/
 head->next = NULL; /*只含有一个节点的链表的有序链表：可根据图11来理解。*/

 while (first != NULL) /*遍历剩下无序的链表*/
 {
  /*注意：这里for语句就是体现直接插入排序思想的地方*/
  for (t=first, q=head; ((q!=NULL) && (q->num < t->num)); p=q, q=q->next); /*无序节点在有序链表中找插入的位置*/
  
  /*退出for循环，就是找到了插入的位置*/
  /*注意：按道理来说，这句话可以放到下面注释了的那个位置也应该对的，但是就是不能。原因：你若理解了上面的第3条，就知道了。*/
  first = first->next; /*无序链表中的节点离开，以便它插入到有序链表中。*/ 
  
  if (q == head) /*插在第一个节点之前*/
  {
   head = t;    
  }
  else /*p是q的前驱*/
  {
   p->next = t;   
  }
  t->next = q; /*完成插入动作*/
  /*first = first->next;*/
 }
 return head;
}


/*
==========================
 功能：冒泡排序(由小到大)
 返回：指向链表表头的指针
==========================
*/

/*
 直接插入排序的基本思想就是对当前还未排好序的范围内的全部节点，
 自上而下对相邻的两个节点依次进行比较和调整，让键值（就是用它排
 序的字段，我们取学号num为键值）较大的节点往下沉，键值较小的往
 上冒。即：每当两相邻的节点比较后发现它们的排序与排序要求相反时，
 就将它们互换。

 
单向链表的冒泡排序图示：
---->[1]---->[3]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next 

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
head   1->next  2->next  3->next   n->next

图14：有N个节点的链表冒泡排序

任意两个相邻节点p、q位置互换图示:
假设p1->next指向p，那么显然p1->next->next就指向q,
p1->next->next->next就指向q的后继节点，我们用p2保存
p1->next->next指针。即：p2=p1->next->next，则有：
[  ]---->[p]---------->[q]---->[  ]（排序前）
  p1->next  p1->next->next  p2->next
图15

[  ]---->[q]---------->[p]---->[  ]（排序后）

图16

1、排序后q节点指向p节点，在调整指向之前，我们要保存原p的指向节点地址，即：p2=p1->next->next；
2、顺着这一步一步往下推,排序后图16中p1->next->next要指的是p2->next,所以p1->next->next=p2->next;
3、在图15中p2->next原是q发出来的指向，排序后图16中q的指向要变为指向p的，而原来p1->next是指向p的，所以p2->next=p1->next;
4、在图15中p1->next原是指向p的，排序后图16中p1->next要指向q,原来p1->next->next（即p2)是指向q的，所以p1->next=p2;
5、至此，我们完成了相邻两节点的顺序交换。
6、下面的程序描述改进了一点就是记录了每次最后一次节点下沉的位置，这样我们不必每次都从头到尾的扫描，只需要扫描到记录点为止。
   因为后面的都已经是排好序的了。
*/
struct student *BubbleSort(struct student *head)
{
 struct student *endpt;		/*控制循环比较*/
 struct student *p;			/*临时指针变量*/
 struct student *p1; 
 struct student *p2; 

 p1 = (struct student *)malloc(LEN);
 p1->next = head;	/*注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址。*/
 head = p1;			/*让head指向p1节点，排序完成后，我们再把p1节点释放掉*/

 for (endpt=NULL; endpt!=head; endpt=p) /*结合第6点理解*/
 {
  for (p=p1=head; p1->next->next!=endpt; p1=p1->next)
  {
   if (p1->next->num > p1->next->next->num) /*如果前面的节点键值比后面节点的键值大，则交换*/
   {
    p2 = p1->next->next; /*结合第1点理解*/
    p1->next->next = p2->next; /*结合第2点理解*/
    p2->next = p1->next; /*结合第3点理解*/
    p1->next = p2; /*结合第4点理解*/
    p = p1->next->next; /*结合第6点理解*/
   }
  }
 }

 p1 = head; /*把p1的信息去掉*/
 head = head->next; /*让head指向排序后的第一个节点*/
 free(p1); /*释放p1*/
 p1 = NULL; /*p1置为NULL，保证不产生“野指针”，即地址不确定的指针变量*/

 return head;
}


/*
==========================
 功能：插入有序链表的某个节点的后面(从小到大)
 返回：指向链表表头的指针
==========================
*/

/*
有序链表插入节点示意图：

---->[NULL]（空有序链表）
head

图18：空有序链表（空有序链表好解决，直接让head指向它就是了。）

以下讨论不为空的有序链表。
---->[1]---->[2]---->[3]...---->[n]---->[NULL]（有序链表）
head   1->next  2->next  3->next   n->next

图18：有N个节点的有序链表

插入node节点的位置有两种情况：一是第一个节点前，二是其它节点前或后。

---->[node]---->[1]---->[2]---->[3]...---->[n]---->[NULL]
head  node->next  1->next  2->next  3->next   n->next

图19：node节点插在第一个节点前

---->[1]---->[2]---->[3]...---->[node]...---->[n]---->[NULL]
head   1->next  2->next  3->next    node->next  n->next

图20：node节点插在其它节点后
*/
struct student *SortInsert(struct student *head, struct student *node)
{
 struct student *p; /*p保存当前需要检查的节点的地址*/ 
 struct student *t; /*临时指针变量*/

 if (head == NULL) /*处理空的有序链表*/
 {
  head = node;
  node->next = NULL;
  n += 1; /*插入完毕，节点总数加1*/
  return head;
 } 

 p = head; /*有序链表不为空*/
 while (p->num < node->num && p != NULL) /*p指向的节点的学号比插入节点的学号小，并且它不等于NULL*/
 {
  t = p; /*保存当前节点的前驱，以便后面判断后处理*/
  p = p->next; /*后移一个节点*/
 }
 
 
 if (p == head)  /*刚好插入第一个节点之前*/
 {
  node->next = p;
  head = node;     
 }
 else /*插入其它节点之后*/
 {  
  t->next = node; /*把node节点加进去*/
  node->next = p;  
 }
 n += 1; /*插入完毕，节点总数加1*/
 
 return head;
}

/*
以上函数的测试程序：
提示：根据测试函数的不同注释相应的程序段，这也是一种测试方法。
*/
main()
{ 
 struct student *head;
 struct student *stu;
 long thenumber;

 /* 测试Create()、Print()*/
 head = Create(); 
 Print(head);
 
 /*测试Del():请编译时去掉注释块*/
 
 /*
 printf("/nWhich one delete: ");
 scanf("%ld",&thenumber);
 head = Del(head,thenumber);
 Print(head);
 */

 /*测试Insert():请编译时去掉注释块*/

 /*
 stu = (struct student *)malloc(LEN);
 printf("/nPlease input insert node -- num,score: ");
 scanf("%ld,%f",&stu->num,&stu->score);
 printf("/nInsert behind num: ");
 scanf("%ld",&thenumber);
 head = Insert(head,thenumber,stu);
 free(stu);
 stu = NULL;
 Print(head);
 */
 
 /*测试Reverse():请编译时去掉注释块*/

 /*
 head = Reverse(head);
 Print(head);
 */

 /*
 
   测试代码如下：
   
 */
 
 /*测试SelectSort():请编译时去掉注释块*/
 
 /*
 head = SelectSort(head);
 Print(head);
 */
 
 /*测试InsertSort():请编译时去掉注释块*/
 
 /*
 head = InsertSort(head);
 Print(head);
 */
 
 /*测试BubbleSort():请编译时去掉注释块*/
 
 /*
 head = BubbleSort(head);
 Print(head);
 */
 
 /*测试SortInsert():上面创建链表，输入节点时请注意学号num从小到大的顺序。请编译时去掉注释块*/
 
 /*
 stu = (struct student *)malloc(LEN);
 printf("/nPlease input insert node -- num,score: ");
 scanf("%ld,%f",&stu->num,&stu->score);
 head = SortInsert(head,stu);
 free(stu);
 stu = NULL;
 Print(head);
 */
 
 printf("/n");
 system("pause");
}

/*
 下次将接着讲
  排序（选择、插入、冒泡）
  插入（有序）
  希望有兴趣的朋友关注
*/