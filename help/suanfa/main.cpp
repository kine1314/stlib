#include"hfm.c"
#include"kmp.c"
#include"kruskal.cpp"
#include"erchapaixushu.cpp"
#include"dui.c"
#include"prim.cpp"
#include"guibing.c"
#include"biaodashiqiuzhi.c"
#include"quicksort.c"
#include"hash.c"
#include"floyd.c"
#include"xierpaixu11.c"
#include"jishupaixu15.c"
#include"Dijkstra7.c"
#include"guanjianlujing.cpp"
#include"erchashu3.c"




void main()
{

flag:;printf("\n\n\n\n");
	 printf("请输入您想要的算法;\n");
	 printf("1.KMP算法匹配算法;\n");
	 printf("2.哈夫曼编码算法;\n");
	 printf("3.由遍历序列恢复二叉树;\n");
     printf("4.Prim算法;\n");
	 printf("5.Kruskal算法;\n");
	 printf("6.Floyd算法;\n");
	 printf("7.Dijkstra算法;\n");
     printf("8.关键路径算法;\n");
	 printf("9.二叉排序树生成算法;\n");
	 printf("10.哈希表生成及哈希查找算法;\n");
     printf("11.希尔排序;\n");
	 printf("12.快速排序算法;\n");
	 printf("13.堆排序算法;\n");
	 printf("14.归并排序算法;\n");
	 printf("15.基数排序算法;\n");
	 printf("16.四则表达式计算算法;\n");
     printf("17.返回.\n");
	 	int n;
	 



	 scanf("%d",&n);
	 switch(n)
	 {
	 case 1:kmp();
		   goto flag; break;
     case 2:hfm();
		    goto flag; break;
	 case 3:erchashu3();
		    goto flag; break;
	 case 4:prim();
		    goto flag; break;
	 case 5:kruskal();
		    goto flag; break;
	 case 6:floyd();
		    goto flag; break;
	 case 7:Dijkstra7();
		    goto flag; break;
	 case 8:guanjianlujing();
		    goto flag; break;
	 case 9:erchapaixushu();
		   goto flag; break;
	 case 10:hash();
		    goto flag; break;
     case 11:xierpaixu11();
		    goto flag; break;
	 case 12:quicksort();
		    goto flag; break;
	case 13:dui();
		    goto flag; break;
	 case 14:guibing();
		    goto flag; break;
	 case 15:jishupaixu15();
		    goto flag; break;
	 case 16:biaodashiqiuzhi();
		    goto flag; break;
	 case 17:break;
	 }
}

		    
