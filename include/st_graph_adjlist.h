#ifndef	__ST_GRAPH_ADJLIST_H__
#define	__ST_GRAPH_ADJLIST_H__

#include "stlib.h"


ST_BEGIN_DECLS ;

 // ���Ķ�������(���ӣ��ֵ�)�洢��ʾ 


// ͼ���ڽӱ�洢��ʾ 
#define MAX_NAME 3						// �����ַ�������󳤶�+1 
#define MAX_VERTEX_NUM 20
typedef int InfoType;					// �������Ȩֵ 
typedef char VertexType[MAX_NAME];		// �ַ������� 
typedef enum{DG,DN,AG,AN}GraphKind; 	// {����ͼ,������,����ͼ,������} 

// �������������
typedef char GElemType[MAX_NAME];
typedef GElemType GTElemType;
typedef struct _CSNode
{
	GTElemType data;
	struct _CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

typedef struct ArcNode
{
	int adjvex;							// �û���ָ��Ķ����λ�� 
	struct ArcNode *nextarc;			// ָ����һ������ָ�� 
	InfoType *info;						// ����Ȩֵָ�룩 
}ArcNode;	// ���� 

typedef struct VNode
{
	VertexType data;					// ������Ϣ 
	ArcNode *firstarc;					// ��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ�� 
 }VNode,AdjList[MAX_VERTEX_NUM];		// ͷ��� 

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;					// ͼ�ĵ�ǰ�������ͻ��� 
	int kind;							// ͼ�������־ 
}ALGraph;



// �ⲿ�ӿ�����
// �ڽӱ�洢ͼ
int		CreateGraph(ALGraph *G);
void	DestroyGraph(ALGraph *G);
void 	InsertVex(ALGraph *G, VertexType v);
int 	DeleteVex(ALGraph *G, VertexType v);
int 	InsertArc(ALGraph *G, VertexType v, VertexType w);
int 	DeleteArc(ALGraph *G, VertexType v, VertexType w);
void 	DFSTraverse(ALGraph G, void(*Visit)(char*));
void 	BFSTraverse(ALGraph G, void(*Visit)(char*));
void 	G_Display(ALGraph G);
int 	PutVex(ALGraph *G,VertexType v,VertexType value);
// ��������
int 	TopologicalSort(ALGraph G);
// �ؽڵ�
void 	FindArticul(ALGraph G);
// �ؼ�·��
int 	CriticalPath(ALGraph G) ;
// ����ͼ���������������
// ��������ͼG�������������ɭ�ֵ�(����)����(��)�ֵ�����T��
void 	DFSForest(ALGraph G,CSTree *T);
// �ȸ��������ӣ��ֵܶ�������ṹ����T
void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))

ST_END_DECLS;
#endif	/* __ST_GRAPH_ADJLIST_H__ */

