

/*Dijkstra算法的基本思路是：假设每个点都有一对标号 (dj, pj)，其中dj是从起源点s到点j的最短路径的长度 (从顶点到其本身的最短路径是零路(没有弧的路)，其长度等于零)；pj则是从s到j的最短路径中j点的前一点。求解从起源点s到点j的最短路径算法的基本过程如下：
　　1) 初始化。起源点设置为：① ds=0, ps为空;② 所有其他点: di=∞, pi=?;③ 标记起源点s，记k=s,其他所有点设为未标记的。
　　2) 检验从所有已标记的点k到其直接连接的未标记的点j的距离，并设置：
dj=min［dj, dk+lkj］
式中，lkj是从点k到j的直接连接距离。
　　3) 选取下一个点。从所有未标记的结点中，选取dj 中最小的一个i：
di=min［dj, 所有未标记的点j］
点i就被选为最短路径中的一点，并设为已标记的。
　　4) 找到点i的前一点。从已标记的点中找到直接连接到点i的点j*，作为前一点,设置：
i=j*
　　5) 标记点i。如果所有点已标记，则算法完全推出，否则，记k=i，转到2) 再继续。*/

#include <stdio.h>
#define true  1
#define false 0
#define I  9999                                /* 无穷大        */
#define N  10                                  /* 城市顶点的数目 */

int cost[N][N] = {
{0,3,I,I,I,1,I,I,I,I},
{3,0,5,I,I,I,6,I,I,I},
{I,5,0,4,I,I,I,1,I,I},
{I,I,4,0,2,I,I,I,6,I},
{I,I,I,2,0,I,I,I,I,7},
{1,I,I,I,I,0,1,I,I,I},
{I,6,I,I,I,1,0,6,I,I},
{I,I,1,I,I,I,6,0,2,I},
{I,I,I,6,I,I,I,2,0,8},
{I,I,I,I,7,I,I,I,8,0}

};
int dist[N];                                          /* 存储当前最短路径长度 */




void mj(char ch)
{  
	int final[N], i1, v1,w1,min1;
	int v0=ch-65; 
	/* 初始化最短路径长度数据，所有数据都不是最终数据 */
	for (v1 = 0; v1 < N; v1++) 
	{
		final[v1] = false;
		dist[v1] = cost[v0][v1];
	}


	/* 首先选v0到v0的距离一定最短，最终数据 */
	final[v0] = true;

	/* 寻找另外 N-1 个结点 */
	for (i1 = 0; i1 < N-1; i1++) 
	{
		min1 = I;                                      /* 初始最短长度无穷大  */

		/* 寻找最短的边 */
		for (w1 = 0; w1 < N; w1++) 
		{
			if (!final[w1] && dist[w1] < min1) 
			{
				min1 = dist[w1];
				v1 = w1;
			}
		}
		final[v1] = true;                              /* 加入新边          */

		for (w1 = 0; w1 < N; w1++) 
		{                      /* 更新 dist[] 数据  */
			if (!final[w1] && dist[v1] + cost[v1][w1] < dist[w1]) 
			{
				dist[w1] = dist[v1] + cost[v1][w1];
			}
		}
	}
	for (i1 = 0; i1< N; i1++) 
	{                          /* 显示到监视器      */
		printf("%c->%c: %2d\t", v0 + 65, i1 + 65, dist[i1]);
	}
}


//主函数
void Dijkstra7()
{   
	int i ,j;
	char ch1,ch2;
	printf("---------------------------------Dijkstra算法演示程序--------------------------\n");
	printf("\n制作人： 马静           学号： 20082554            班级：计0801-3班\n");
	printf("\n排序说明：\n");
	printf("结点为A~J(为10个大写字母)\n");
	printf("\n下面是节点间距离信息的矩阵：\n");	
	for(i=0;i<N;i++)
	{
		for( j=0;j<N;j++)
		{
			printf("%d ",cost[i][j]);
			if(j==N-1)
			printf("\n");
		}
	}

	printf("\n\n");
	printf("请输入起始结点：\n");
	loop1: ch1=getchar();
	if(ch1!='A')
	{
		printf("你输入的不是起始结点，请重新输入！\n");

		goto loop1;
	}
	printf("该结点到其他结点的最短路径如下\n：\n");
	mj(ch1);
	printf("请输入任意结点：\n");

	getchar();
	loop2: ch2=getchar();
	if(ch2<'A'||ch2>'J')
	{
		printf("你的输入超出了范围，请重新输入！\n");
		goto loop2;
	}
	printf("该结点到其他结点的最短路径如下\n：\n");

	mj(ch2);

	printf("\n");
}


int main(void)
{
	Dijkstra7();
	return 1 ;
}
