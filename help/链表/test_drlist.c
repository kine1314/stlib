#include <stdio.h>
#include "list.h"

struct test{
	int a;
	char b;
};
struct ts_hlist{
	struct list_head member1;
	int member2;
	char member3;
	double member4;
};

LIST_HEAD(hellolist);
struct ts_hlist hellots;
struct ts_hlist * rs;

int main(void){

	struct test t1;
	t1.a=8;
	t1.b='z';
	char *pchar="testok";
	int i=0;
	printf("length of int:%d char:%d double:%d long:%d\n",sizeof(int),sizeof(char),sizeof(double),sizeof(long));
	printf("Address of t1 is:%p\nddd member of a is:%d\n member of b is:%c\n",&t1,t1.a,t1.b);
	printf("Address of pchar is:%p\nvalue of pchar is:%s\n",pchar,pchar);
	for(;i<strlen(pchar);i++)
	{
	  printf("Address of member of pchar in pos %d is %p  ,value of pchar in pos%d is:%c\n",i,pchar+i,i,pchar[i]);
	}
	printf("address base=0\n,than the address of a:%d\naddress of b:%d\n", &((struct test *)0)->a,&((struct test *)0)->b) ;


	printf("If the NULL struct as 0 of ts_hlist is given,then the size of 0based willbe:like this:\n\n\n\n");
	printf("   struct ts_hlist as NULL \n");
	printf("%u --->|__________|\n",&( ((struct ts_hlist *)0)->member1)  );
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");  
	printf("%u --->|__________|\n",&( ((struct ts_hlist *)0)->member2) );
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("%u--->|__________|\n",&( ((struct ts_hlist *)0)->member3) );
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("%u--->|__________|\n",&( ((struct ts_hlist *)0)->member4) );
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");
	printf("      |__________|\n");

	printf("                          \n\n");
	printf("  struct ts_hlist as allocate space\n");
	int j=0;

	printf(" size of  ts_hlist struct is %d\n",sizeof(struct ts_hlist));
	for(;j<sizeof(struct ts_hlist);j++)
	{
	  printf("     |__________|<--%p\n",&hellots+(unsigned long)j);
	}
	printf(" the address of head(type of head_list) is:%p\n",hellolist);

	hellots.member2=3;
	hellots.member3='A';
	hellots.member4=44.33;
	list_add_tail(&hellots.member1,&hellolist);
	rs=list_entry(&hellots.member1,struct ts_hlist,member1);
	printf("  the address of member1 is: %p\n",&hellots+(unsigned long)&( ((struct ts_hlist *)0)->member1) );
	printf("  the address of member2 is: %p\n",&hellots+(unsigned long)&( ((struct ts_hlist *)0)->member2) );
	printf("  the address of member3 is: %p\n",&hellots+(unsigned long)&( ((struct ts_hlist *)0)->member3) );
	printf("  the address of member4 is: %p\n",&hellots+(unsigned long)&( ((struct ts_hlist *)0)->member4) );
	printf(" Now we'll test the value area of ts_hlist>>>>>\n");
	printf("  member2 of rs is:%d\n", rs->member2);
	printf("  member3 of rs is:%c\n", rs->member3);
	printf("  member4 of rs is:%g\n", rs->member4);
}