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
	 printf("����������Ҫ���㷨;\n");
	 printf("1.KMP�㷨ƥ���㷨;\n");
	 printf("2.�����������㷨;\n");
	 printf("3.�ɱ������лָ�������;\n");
     printf("4.Prim�㷨;\n");
	 printf("5.Kruskal�㷨;\n");
	 printf("6.Floyd�㷨;\n");
	 printf("7.Dijkstra�㷨;\n");
     printf("8.�ؼ�·���㷨;\n");
	 printf("9.���������������㷨;\n");
	 printf("10.��ϣ�����ɼ���ϣ�����㷨;\n");
     printf("11.ϣ������;\n");
	 printf("12.���������㷨;\n");
	 printf("13.�������㷨;\n");
	 printf("14.�鲢�����㷨;\n");
	 printf("15.���������㷨;\n");
	 printf("16.������ʽ�����㷨;\n");
     printf("17.����.\n");
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

		    
