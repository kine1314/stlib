#include<malloc.h>
#include<stdio.h>

/*���ڽӱ�ʵ�ֹؼ�·������*/

#define MAX 20 /*ͷ�������ֵ*/
#define NUNUM 20

struct node1 /*�ڽӵ㶨��*/
{
    int adjvex; /*������Ϣ�����*/
    int dut; /*Ȩֵ*/
    struct node1 *next;
};


struct vnode1 /*ͷ��㶨��*/
{
    int vertex; /*������Ϣ�����*/
    int id; /*�������*/
    struct node1 *link; /*ͷ��������ָ������ڽӵ�*/
}Adjlist[MAX];


void CreateGraph(struct vnode1 Adjlist[MAX],int n,int e)/*����ͼ*/
{
    /*nΪ������,eΪͼ�ı���*/
    int i,j,k,l;
    struct node1 * p;/*�����µ��ڽӵ����õ�ָ�����ͱ���*/
    

    for(i=1;i<=n;i++)
    {
        /*���������*/
        
        Adjlist[i].vertex=i;
        Adjlist[i].id=0;
        Adjlist[i].link=NULL;
     }
   

     for(k=1;k<=e;k++)
     {
        /*�ڽӱ�����*/
        printf("\n������ߵ�ͷ��� β��� Ȩֵ���м��Կո���:");
        scanf("%d",&i);
        scanf("%d",&j);
   
        scanf("%d",&l);
        p=(struct node1 *)malloc(sizeof(struct node1));/*�����µı߱���*/
        p->adjvex=j; /*���ڽӵ���Ÿ�ֵ���½��Ķ�����Ϣ��*/
        p->dut=l; /*Ȩֵ*/
        p->next=Adjlist[i].link;
        Adjlist[i].link=p; /*���½����뵽����Vi�ı߱�ͷ��*/
     }
     
     for(i=1;i<=n;i++)
     {
     p=Adjlist[i].link;
     while(p!=NULL)
     {
            k=p->adjvex;
            Adjlist[k].id=Adjlist[k].id+1;
         p=p->next;
     }
     
     }

}


void CriticalPath(struct vnode1 Adjlist[MAX],int n)
{
    int i,j,m,front,rear;
    int k=0;

    int ve[NUNUM],vl[NUNUM],e[NUNUM],l[NUNUM];
    int tpord[NUNUM];

    struct node1 *p;

    for(i=1;i<=n;i++) /*������������ٷ���ʱ�䣬��ʼ��Ϊ0*/
    {
        ve[i]=0; /*���緢��ʱ��*/
        vl[i]=0; /*��ٷ���ʱ��*/
    }
    front=0; /*���ڶ�ջ���ñ��� front������������ж��Ƿ��ջ�еĽ�������Ƿ��Ѿ�ȫ����������rear�ĳ�ʼ��Ϊ0*/
    rear=0; /*��ջʱ���õı�����������tpord����ϵ*/

    for(i=1;i<=n;i++) /*���ȣ������ڽӱ�ı�ͷ���������Ϊ0�Ķ��㣬�������ջ����tpord��*/
    {
        if(Adjlist[i].id==0)
        {
            rear++;
            tpord[rear]=i; /*ͷ������Ϊ0�ĵ���ջ������tpord[]���ӵ͵��ߵ�˳�����*/
        }
    }

    m=0; /*������ʼ�����˱���Ϊ��������ı���m���佫��Ϊ�ж�ͼ�Ƿ��л�·ʹ��*/
    while(front!=rear) /*ջ����ʱ*/
    {
        front++; /*�ӵ͵��ߵ�˳��ȥ�Զ�ջ���в���*/
        j=tpord[front];/*ÿ��ȡһ�����Ϊ0�Ķ��㣬������������²���*/
        m++; /*ÿȡһ����㣬��M���м�1����*/

        p=Adjlist[j].link;/*������ָ���򴫸�p*/
        while(p!=NULL)/*����p�Խ��ĺ���������ѭ������*/
        {
            k=p->adjvex;/*ȡһ���ڽӵ���Ϣ�����*/
            Adjlist[k].id=Adjlist[k].id-1; /*�������ڽӵ���ȼ�ȥ1*/

            if(ve[j]+(p->dut)>ve[k])
                ve[k]=ve[j]+(p->dut); /*��������緢��ʱ�䣬��ȡ���ֵ*/

             if(Adjlist[k].id==0) /*Ȼ���жϣ����˺����ڽӵ����Ϊ0������ջtpord*/
            {
                rear++;
                tpord[rear]=k; /*��ԭ������Ļ����Ͻ��в���������ִ��*/
            }
            p=p->next;/*������һ���ڽӵ����ͬ���Ĳ���������ȼ�1�������緢��ʱ��Ĺ�����Ȼ���ж��Ƿ���ջ������Ƿ�Ϊ0��*/
        }
    }

    
    if(m<n) /*nΪ�ܽ������mΪ����ʱ���õļ�������ÿ����һ�����������м�1����*/
    {
      printf("\n���󣡣���\nͼ���л�·���޷�������������");/*ͼ���Ƿ��л�·*/
      return;
    }

    
    for(i=1;i<=n;i++)
        vl[i]=ve[n]; /*�����ý������緢��ʱ�����ݸ�ֵ����ٷ���ʱ������*/

    
    for(i=n-1;i>=1;i--) /*�������������򣬴Ӷ�ջ���ݵ����λ��ʼ*/
    {
        j=tpord[i]; /*ȡ����*/
        p=Adjlist[j].link; /*ȡ���ĺ����ڽӵ��ָ����*/
        while(p!=NULL) /*�Դ˽����ڽӵ���в���*/
        {
            k=p->adjvex; /*ȡ �ڽӵ���Ϣ�������*/
            if((vl[k]-p->dut)<vl[j]) /*�ڻ<j,k>�Ͻ��в�����ȷ���¼�j����ٷ���ʱ��*/
                vl[j]=vl[k]-(p->dut);
             p=p->next; /*������һ���ڽӵ����ͬ���Ĳ���*/
        }
        
    } /*�������������*/

   
    i=0; /*ѭ���ж�ȷ�� ÿ���������緢��ʱ�� ����ٷ���ʱ���Ƿ����*/
    
    for(j=1;j<=n;j++)
    {
        p=Adjlist[j].link;/*ȡͷ�����ڽӵ��ָ���򣬸�ֵ��p*/
        while(p!=NULL)
        {
            k=p->adjvex; /*����ڽӵ����ţ���λ��*/
            i++; /*i++����*/

            e[i]=ve[j]; /*�¼�j�����緢��ʱ��������i�����緢��ʱ��*/
            l[i]=vl[k]-(p->dut);/*<j--ai--k>�ai����ٷ���ʱ��=vl[k]-(p->dut)*/

            printf("\n <%d ,%d>:",Adjlist[j].vertex,Adjlist[k].vertex);
            if(l[i]==e[i]) /*�ж��Ƿ�ai�����緢��ʱ��=��ٷ���ʱ�䣿����ȣ���˻Ϊ�ؼ����*/
            {
                printf("�ǹؼ�·��!\n");
                printf("ȨֵΪ:%d",p->dut);
                
            }
            else
            {
                printf("���ǹؼ�·��!");
          
            }
            p=p->next;
        }
    }
    

}


void guanjianlujing()
{
    int n,e;
	printf("-----------------------�ؼ�·���㷨��ʾ-----------------------");
	printf("��д�ˣ����ƴ�         ѧ�ţ�20082556");
    printf("\n�����붥����:");
    scanf("%d",&n);
    printf("\n���������: ");
    scanf("%d",&e);


    CreateGraph(Adjlist,n,e);
    CriticalPath(Adjlist,n);
   // getch();

}

int main(void)
{
	guanjianlujing();
	return 1 ;
}

