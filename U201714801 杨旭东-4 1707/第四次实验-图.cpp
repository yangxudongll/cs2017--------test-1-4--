#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include<string.h>
#include<io.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int InfoType;
#define MAXSIZE 100
#define MAX_VERTEX_NUM 20
typedef int KeyType;

int ID[100],num;                        //用来存储唯一ID，防止重复
bool visited[MAX_VERTEX_NUM];            //访问标志数组

typedef struct
{
	char localName[20];          //地点名称
	int ID;                     //唯一标识ID
}province;

typedef struct ArcNode
{
	int adjvex;               //该弧所指向的顶点的位置
	struct ArcNode *nextarc;  //指向下一条弧的指针
	InfoType info;            //该弧相关信息的指针
}ArcNode;

typedef struct VNode
{
	province* data;                  //顶点信息
	ArcNode *firstarc;          //指向第一条依附于该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertice;
	int vexnum, arcnum;          //弧的当前顶点数和弧度数
	int kind;                    //图的种类标志
}ALGraph;

//邻接关系矩阵
typedef struct
{
	int relation[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}rela;
//顶点信息
typedef struct
{
	char Vnode[MAX_VERTEX_NUM][20];
}Vnodes;
//多表结构，用于保存多个图
typedef struct Sq
{
	ALGraph* G;        //图
	rela* Mtrix;       //关系矩阵
	char name[20];     //图的名字
	struct Sq *next;
}SqNode,*SqList;

//销毁图
status DestoryGraph(ALGraph* G);
status(*VisitedFunc)(VNode V);             //函数变量
//检查ID是否重复
status Inpect(int t);
//创建关系集,用一个一维数组保存
status CreateRela(int vexnum, int arcnum);
//查找节点,根据ID
status LocateVex(ALGraph *G, int u);
//查找节点，根据地名
status LocateVex(ALGraph *G, char* name);
//插入弧
status InsertArc(ALGraph *G,KeyType v,KeyType w);
//创建顶点集
status CreateNode(Vnodes* &V, int vexnum);
//创建图
status CreateCraph(ALGraph* &G,Vnodes *V,rela *VR);
//插入顶点
status InsertVex(ALGraph* &G, VNode* v);
//获得第一个邻接点
ArcNode* FirstAdjVex(ALGraph *G, KeyType v);
status Visit(VNode V)
{
	printf("ID:%d\n", V.data->ID);
	printf("名字：%s\n", V.data->localName);
	return OK;
}
//删除顶点
status DeleteVex(ALGraph* &G, KeyType v);
//深度优先遍历
void DFSTraverse(ALGraph* G, status(*Visit)(VNode V));
void DFS(ALGraph* G, int v);
//广度优先搜索
void BFSTraverse(ALGraph *G, status(*Visit)(VNode V));
//获得顶点值
status GetVex(ALGraph *G,int v);
//顶点赋值
status PutVex(ALGraph* G, int v, province* value);
//删除弧
status DeleteArc(status &G,int v,int w);
//创建关系集,用一个一维数组保存
status CreateRela(int vexnum, int arcnum, rela* &relation);
//保存图
status SaveGraph(ALGraph* G,rela* VR);
//加载图
status LoadGraph(ALGraph* &G);
//根据ID查找顶点位置
int search(ALGraph *G, int id);
//删除弧
status DeleteArc(ALGraph* G, KeyType v, KeyType w);
//初始化多表
status InitSqList(SqList &L);
//获得下一邻接
ArcNode* NextAdjVex(ALGraph *G, KeyType v, KeyType w);
//更新关系矩阵
status RenewMtrix(SqList L);
//添加一个新图
SqList AddGraph(SqList &L);
//切换图
SqList ChangeGraph(SqList L, char* name);
//删除图
status DeleteGraph(SqList &L, char *name);
//清空ID
void ClearArray();
int main()
{
	Vnodes* V=NULL;         //顶点集
	num = 0;
	ALGraph* G=NULL;
	G = (ALGraph*)malloc(sizeof(ALGraph));
	int op = 1,a,b;
	KeyType v, w;
	SqList L = NULL,p=NULL,q=NULL;
	InitSqList(L);
	p = L;
	ArcNode *A=NULL;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("1、CreateCraph            18、DeleteGraph\n");
		printf("2、DFSTraverse            10、DeleteArc\n");
		printf("3、BFSTraverse            11、FirstArcNode\n");
		printf("4、LocateVex              12、NextAdjVex\n");
		printf("5、GetVex                 13、DestoryGraph\n");
		printf("6、PutVex                 14、InsertArc\n");
		printf("7、InsertVex              15、AddGraph\n");
		printf("8、SaveGraph              16、DeleteVex\n");
		printf("9、LoadGraph              17、ChangeGraph\n");
		printf("0、exit\n");
		printf("-------------------------------------------------\n");
		if (p == NULL)InitSqList(p);
		if (p->G->kind == 1)
			printf("当前操作的图是：%s\n", p->name);
		printf("请输入命令[1`18]\n");
		scanf("%d", &op);
		if (p == NULL)	InitSqList(p);
		switch (op)
		{
		case 1:
			printf("请输入顶点数和弧数\n");
			scanf("%d %d", &a, &b);
			if (a <= 0 || a > MAX_VERTEX_NUM || b <= 0 || b > MAX_VERTEX_NUM)
			{
				printf("输入错误\n");
			}
			else
			{
				p->G = (ALGraph*)malloc(sizeof(ALGraph));
				p->G->vexnum = a; p->G->arcnum = b;
				CreateRela(p->G->vexnum, p->G->arcnum, p->Mtrix);
				CreateNode(V, p->G->vexnum);
				CreateCraph(p->G, V, p->Mtrix);
				printf("请主人为小图取个名字吧\n");
				scanf("%s", &p->name);
			}
			system("pause");
			break;
		case 2:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				DFSTraverse(p->G, Visit);
			}

			system("pause");
			break;
		case 3:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
				BFSTraverse(p->G, Visit);
			system("pause");
			break;
		case 4:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				char name[20];
				int id;
				printf("1、根据ID查找   2、根据名字查找\n");
				scanf("%d", &id);
				if (id == 1)
				{
					printf("请输入需要查找的ID\n");
					scanf("%d", &id);
					if (LocateVex(p->G, id) == ERROR)
						printf("没有找到\n");
				}
				else if (id == 2)
				{
					printf("请输入需要查找的名字\n");
					scanf("%s", &name);
					if (!LocateVex(p->G, name))
						printf("没有找到\n");
				}
				else
					printf("输入错误\n");
			}
			system("pause");
			break;
		case 5:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("请输入需要查找的顶点ID\n");
				scanf("%d", &a);
				if (GetVex(p->G, a)==ERROR)
					printf("输入错误\n");
			}
			system("pause");
			break;
		case 6:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("输入结点ID\n");
				scanf("%d", &a);
				b = search(p->G, a);
				if (b == -1)
				{
					printf("不存在的ID\n");
				}
				else
				{
					province* po = (province*)malloc(sizeof(province));
				loop5:
					printf("请输入修改后的ID\n");
					int th;
					scanf("%d", &th);
					if (Inpect(th))
					{
						po->ID = th;
						printf("请输入修改后的名字\n");
						scanf("%s", &po->localName);
						if (PutVex(p->G, b, po))
							printf("修改成功\n");
						else
							printf("修改失败\n");
					}
					else
					{
						printf("ID重复，重新输入\n");
						goto loop5;
					}
					free(po);
				}
			}
			system("pause");
			break;
		case 7:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				VNode *node = NULL;
				node = (VNode*)malloc(sizeof(VNode));
				node->data = (province*)malloc(sizeof(province));
				printf("请输入要插入顶点名字：\n");
				scanf("%s", &node->data->localName);
				printf("请输入顶点%s的ID:\n", node->data->localName);
				int m;
			loop4:scanf("%d", &m);
				if (Inpect(m) == OK)
				{
					node->data->ID = m;
				}
				else
				{
					printf("ID重复，重新输入\n");
					goto loop4;
				}
				if (InsertVex(p->G, node))printf("插入成功\n");
				else printf("插入失败");
			}
			system("pause");
			break;
		case 8:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				if (SaveGraph(p->G, p->Mtrix))
					printf("保存成功\n");
			}
			system("pause");
			break;
		case 9:
			if (p->G == NULL)
			{
				p->G = (ALGraph*)malloc(sizeof(ALGraph));
				if (LoadGraph(p->G))printf("加载成功\n");
				else printf("加载失败\n");
			}
			else
			{
				printf("继续操作会失去当前图中的信息,继续吗？(回车继续)\n");
				char ch;
				getchar();
				ch = getchar();
				if (ch == '\n'){
					if (LoadGraph(p->G))
					{
						printf("加载成功\n");
						RenewMtrix(p);
						printf("这张新图的名字叫什么呀?\n");
						scanf("%s", &p->name);
						ClearArray();;
					}
					else printf("加载失败\n");
				}

			}
			system("pause");
			break;
		case 10:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("请输入顶点的id，中间用空格隔开\n");
				scanf("%d %d", &v, &w);
				if (DeleteArc(p->G, v, w))
					printf("删除成功\n");
				RenewMtrix(p);
			}
			system("pause");
			break;
		case 11:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("输入需要查找的ID\n");
				scanf("%d", &v);
				A = FirstAdjVex(p->G, v);
				if (A == NULL)
					printf("顶点不存在或者没有邻接点\n");
				else
				{
					printf("第一邻接点信息为:\n");
					printf("ID:%d\n", p->G->vertice[A->adjvex].data->ID);
					printf("名字:%s\n", p->G->vertice[A->adjvex].data->localName);
				}
			}
			system("pause");
			break;
		case 12:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("请输入需要查找的顶点，中间用空格隔开\n");
				scanf("%d %d", &v, &w);
				A = NextAdjVex(p->G, v, w);
				if (A != NULL)
					Visit(p->G->vertice[A->adjvex]);
				else
					printf("NULL\n");
			}
			system("pause");
			break;
		case 13:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				if (DestoryGraph(p->G))printf("销毁成功\n");
			}
			system("pause");
			break;
		case 14:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("请输入需要插入的弧的两端顶点ID\n");
				scanf("%d %d", &v, &w);
				if (InsertArc(p->G, v, w))
					printf("插入成功\n");
				else
					printf("插入失败\n");
				RenewMtrix(p);
			}
			system("pause");
			break;
		case 15:
			q = AddGraph(L);
			if (q)
				p = q;
			else
				printf("添加失败\n");
			system("pause");
			break;
		case 16:
			if (p->G->kind != 1)
			{
				printf("还没有创建\n");
			}
			else
			{
				printf("请输入需要删除的顶点的ID\n");
				scanf("%d", &v);
				if (search(p->G, v) == -1)
					printf("ID不存在\n");
				else
				{
					if (DeleteVex(p->G, v) == OK)
						printf("删除成功\n");
					else
						printf("删除失败\n");
					RenewMtrix(p);
				}
			}
			system("pause");
			break;
		case 17:
			printf("请输入需要切换到的图的名字\n");
			char Graphname[20];
			scanf("%s", &Graphname);
			q = ChangeGraph(L, Graphname);
			if (q == NULL)
				printf("不存在\n");
			else
			{
				p = q;
				printf("切换成功\n");
				ClearArray();;
			}
			system("pause");
			break;
		case 18:
			printf("请输入需要删除的图的名字\n");
			getchar();
			gets(Graphname);
			if (DeleteGraph(L, Graphname))
			{
				printf("删除成功\n");
				ClearArray();;
			}
			else
				printf("图不存在\n");
			system("pause");
			break;
		case 0:
			break;
		default:
			system("pause");
			break;
		}
	}
	return 0;
}
//创建顶点集
status CreateNode(Vnodes* &V,int vexnum)
{
	V = (Vnodes*)malloc(sizeof(Vnodes));
	for (int i = 0; i < vexnum; i++)              //num表示顶点数目，依次为每个顶点赋值
	{
		printf("请输入第%d个节点的地名\n", i + 1);
		scanf("%s", &V->Vnode[i]);
	}
	return OK;
}
//创建关系集,用一个一维数组保存
status CreateRela(int vexnum,int arcnum,rela* &realtion)
{	
	int m, n,t=0;
	realtion = (rela*)malloc(sizeof(rela));
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		memset(&realtion->relation[i], 0, MAX_VERTEX_NUM);
	printf("请输入两个节点的序号表示它们之间有关系，中间以空格隔开\n");
	char ch = '*';
	while (t<arcnum)
	{
		loop6:
		scanf("%d %d", &m, &n);
		if (m<0 || m>vexnum || n < 0 || n > vexnum||m==n)
		{
			printf("输入错误，重新输入\n");
			goto loop6;
		}
		else
		{
			ch = getchar();
			realtion->relation[m-1][n-1] = 1;
		}
		t++;
	}
	return OK;
}
//检查ID是否重复
status Inpect(int t)
{
	for (int i = 0; i < num; i++)
	{
		if (ID[i] == t)
		{
			printf("ID重复\n");
			return ERROR;
		}
	}
	ID[num++] = t;
	return OK;
}
//创建图
status CreateCraph(ALGraph* &G, Vnodes* V, rela *VR)
{
	if (!G)return ERROR;
	for (int i = 0; i < G->vexnum; i++)   //把顶级集中的顶点信息拷贝到图中
	{
		G->vertice[i].data = (province*)malloc(sizeof(province));
		strcpy(G->vertice[i].data->localName, V->Vnode[i]);
		G->vertice[i].firstarc = NULL;
	}
	for (int i = 0; i < G->vexnum; i++)          //输入每个顶点ID
	{
		printf("请输入顶点%s的ID:\n",G->vertice[i].data->localName);
		int m;
		it:scanf("%d", &m);
		if (Inpect(m) == OK)
		{
			G->vertice[i].data->ID = m;
		}
		else
		{
			printf("ID重复，重新输入\n");
			goto it;
		}
	}
	ArcNode* p = NULL;
	for (int i = 0; i < G->vexnum;i++)
	for (int j = 0; j < G->vexnum; j++)
	{
		if (VR->relation[i][j] == 1)
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->nextarc = NULL;
			p->adjvex = j;
			p->nextarc = G->vertice[i].firstarc;
			G->vertice[i].firstarc = p;
		}
	}
	G->kind = 1;
	return OK;
}
//深度优先搜索
void DFSTraverse(ALGraph* G, status(*Visit)(VNode V))
{
	for (int v = 0; v < G->vexnum; v++)       //访问数组初始化
		visited[v] = FALSE;
	for (int v = 0; v < G->vexnum; v++)
	if (!visited[v])
		DFS(G, v);                        //对尚未访问的节点调用DFS
}
void DFS(ALGraph* G, int v)
{
	visited[v] = TRUE;                  
	Visit(G->vertice[v]);                //访问第v个顶点
	for (ArcNode *p = G->vertice[v].firstarc; p != NULL; p = p->nextarc)
	{
		if (!visited[p->adjvex])DFS(G, p->adjvex);
	}
}
//广度优先搜索
void BFSTraverse(ALGraph *G, status(*Visit)(VNode V))
{
	int v;
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	int array[MAX_VERTEX_NUM*20], first = 0, tail = 0,temp;    //作为辅助队列
	for (v = 0; v < G->vexnum;v++)
	if (!visited[v])
	{
		visited[v] = TRUE;
		Visit(G->vertice[v]);
		array[tail++] = v;
		while (first < tail)
		{
			temp = array[first++];
			for (ArcNode *p = G->vertice[temp].firstarc; p != NULL; p = p->nextarc)
			{
				if (!visited[p->adjvex])
				{
					visited[p->adjvex] = TRUE;
					Visit(G->vertice[p->adjvex]);
					array[tail++] = p->adjvex;
				}
			}
		}
	}
	
}
//根据ID查找
status LocateVex(ALGraph *G, int u)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist=0, tail=0,temp;      //辅助对列
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum;v++)                        //广度优先搜索查找
	if (!visited[v])
	{
		if (G->vertice[v].data->ID == u)
		{
			printf("%d是图中的第%d个顶点\n", u, v+1);
			Visit(G->vertice[v]);
			return OK;
		}
		visited[v] = TRUE;
		array[tail++] = v;
		while (frist < tail)
		{
			temp = array[frist++];
			for (ArcNode *p = G->vertice[temp].firstarc; p != NULL; p = p->nextarc)
			{
				if (!visited[p->adjvex])
				{
					visited[p->adjvex] = TRUE;
					if (G->vertice[p->adjvex].data->ID == u)
					{
						printf("%d是图中的第%d个顶点\n", u, p->adjvex+1);
						Visit(G->vertice[p->adjvex]);
						return OK;
					}	array[tail++] = p->adjvex;
				}
			}
		}
	}
	return ERROR;
}
//查找节点，根据地名
status LocateVex(ALGraph *G, char* name)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist = 0, tail = 0, temp;      //辅助对列
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum; v++)                        //广度优先搜索查找
	if (!visited[v])
	{
		if (!strcmp(name,G->vertice[v].data->localName))
		{
			printf("%s是图中的第%d个顶点\n", name, v+1);
			Visit(G->vertice[v]);
			return OK;
		}
		visited[v] = TRUE;
		array[tail++] = v;
		while (frist < tail)
		{
			temp = array[frist++];
			for (ArcNode *p = G->vertice[temp].firstarc; p != NULL; p = p->nextarc)
			{
				if (!visited[p->adjvex])
				{
					visited[p->adjvex] = TRUE;
					if (!strcmp(name, G->vertice[p->adjvex].data->localName))
					{
						printf("%s是图中的第%d个顶点\n", name, p->adjvex+1);
						Visit(G->vertice[p->adjvex]);
						return OK;
					}
					array[tail++] = p->adjvex;
				}
			}
		}
	}
	return ERROR;
}
//获得顶点值
status GetVex(ALGraph* G, int vn)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist = 0, tail = 0, temp;      //辅助对列
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum; v++)                        //广度优先搜索查找
	if (!visited[v])
	{
		if (G->vertice[v].data->ID == vn)
		{
			Visit(G->vertice[v]);
			return OK;
		}
		visited[v] = TRUE;
		array[tail++] = v;
		while (frist < tail)
		{
			temp = array[frist++];
			for (ArcNode *p = G->vertice[temp].firstarc; p != NULL; p = p->nextarc)
			{
				if (!visited[p->adjvex])
				{
					visited[p->adjvex] = TRUE;
					if (G->vertice[p->adjvex].data->ID == vn)
					{
						Visit(G->vertice[p->adjvex]);
						return OK;
					}	array[tail++] = p->adjvex;
				}
			}
		}
	}
	return ERROR;
}
//顶点赋值
status PutVex(ALGraph* G, int vn,province* value )
{
	if (!G || G->kind != 1)
		return ERROR;
	G->vertice[vn].data->ID = value->ID;
	strcpy(G->vertice[vn].data->localName, value->localName);
	return OK;
}
//插入顶点
status InsertVex(ALGraph* &G, VNode* v)
{
	if (G == NULL || G->kind != 1)return ERROR;
	if (G->vexnum >= MAXSIZE - 1)return ERROR;      //结构数组已满
	G->vexnum++;                //顶点数加一
	G->vertice[G->vexnum-1].data = (province*)malloc(sizeof(province));
	strcpy(G->vertice[G->vexnum-1].data->localName, v->data->localName);
	G->vertice[G->vexnum-1].data->ID = v->data->ID;
	G->vertice[G->vexnum - 1].firstarc = NULL;
	return OK;
}
//保存图
status SaveGraph(ALGraph* G,rela* VR)
{
	FILE* fp;
	char fupan[50] = "D://";
	char tail[10] = ".txt";
	char name[20];
	printf("输入需要保存的文件名字\n");
	scanf("%s", &name);
	strcat(fupan, name);
	strcat(fupan, tail);          //拼接成一个完整的文件路径
	fp = fopen(fupan,"w");
	if (!fp)exit(-1);
	fwrite(&G->vexnum, 1, sizeof(int), fp);
	for (int i = 0; i < G->vexnum; i++)                       //保存顶点数目
	{
		fwrite(&G->vertice[i].data->localName,20, sizeof(char), fp);
		fwrite(&G->vertice[i].data->ID, 1, sizeof(int), fp);
	}
	for (int i = 0; i < G->vexnum; i++)
	for (int j = 0; j < G->vexnum; j++)
	{
		fwrite(&VR->relation[i][j], 1, sizeof(int), fp);     //保存关系矩阵
	}
	fclose(fp);
	return OK;
}
//根据ID查找顶点位置
int search(ALGraph* G, int id)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist = 0, tail = 0, temp;      //辅助对列
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum; v++)                        //广度优先搜索查找
	if (!visited[v])
	{
		if (G->vertice[v].data->ID == id)
		{
			return v;
		}
		visited[v] = TRUE;
		array[tail++] = v;
		while (frist < tail)
		{
			temp = array[frist++];
			for (ArcNode *p = G->vertice[temp].firstarc; p != NULL; p = p->nextarc)
			{
				if (!visited[p->adjvex])
				{
					visited[p->adjvex] = TRUE;
					if (G->vertice[p->adjvex].data->ID == id)
					{
						return p->adjvex;
					}
					array[tail++] = p->adjvex;
				}
			}
		}
	}
	return -1;          //没有找到
}
//加载图
status LoadGraph(ALGraph* &G)
{
	Vnodes* V=NULL;        // 保存顶点信息
	rela* VR;              //保存关系矩阵
	V = (Vnodes*)malloc(sizeof(Vnodes));
	VR = (rela*)malloc(sizeof(rela));
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		memset(&VR->relation[i], 0, MAX_VERTEX_NUM);
	FILE* fp;
	char filepath[30];
	printf("请输入文件名称\n");
	file:gets(filepath);
	if (_access(filepath, 0) == -1)
	{
		printf("文件不存在，从新输入\n");
		goto file;
	}
	G = (ALGraph*)malloc(sizeof(ALGraph));
	fp = fopen(filepath,"r");
	int m;
	while (!feof(fp))
	{
		fread(&m, 1, sizeof(int), fp);   //读取顶点个数
		if (!feof(fp))
			G->vexnum = m;
		for (int i = 0; i < G->vexnum; i++)
		{
			if (!feof(fp))
			{
				G->vertice[i].data = (province*)malloc(sizeof(province));
				fread(&G->vertice[i].data->localName, 20, sizeof(char), fp);      //读取顶点信息
				fread(&G->vertice[i].data->ID, 1, sizeof(int), fp);
				G->vertice[i].firstarc = NULL;
			}
		}
		for (int i = 0; i < G->vexnum; i++)
		for (int j = 0; j < G->vexnum; j++)
		{
			fread(&m, 1, sizeof(int), fp);         //读取关系矩阵
			if (!feof(fp))
				VR->relation[i][j] = m;
		}
	}
	ArcNode* p = NULL;
	for (int i = 0; i < G->vexnum; i++)           //根据关系矩阵建立邻接表
	for (int j = 0; j < G->vexnum; j++)
	{
		if (VR->relation[i][j] == 1)
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->nextarc = NULL;
			p->adjvex = j;
			p->nextarc = G->vertice[i].firstarc;
			G->vertice[i].firstarc = p;
		}
	}
	G->kind = 1;
	fclose(fp);
	return OK;
}
//插入弧
status InsertArc(ALGraph *G, KeyType v, KeyType w)
{
	int m = search(G, v);             //找到顶点在图中的位置
	int n = search(G, w);
	if (m == -1 || n == -1)      //输入的ID不存在
	{	printf("不存在的ID\n");
	    return ERROR;
	}
	else
	{
		ArcNode* p = NULL;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->nextarc = NULL;
		p->adjvex = n;
		p->nextarc = G->vertice[m].firstarc;
		G->vertice[m].firstarc = p;
		return OK;
	}


}
//删除弧
status DeleteArc(ALGraph* G, KeyType v, KeyType w)
{
	int m = search(G, v);                //找到顶点在邻接表中的序号
	int n = search(G, w);
	if (m == -1 || n == -1)
	{
		printf("ID不存在\n");
		return ERROR;
	}
	ArcNode* p = NULL,*q=NULL;
	if (G->vertice[m].firstarc == NULL)
	{
		printf("%d和%d之间没有弧\n", v, w);
		return ERROR;
	}
	if (G->vertice[m].firstarc->adjvex == n)    //对第一个邻接点特殊处理
	{
		p = G->vertice[m].firstarc;
		G->vertice[m].firstarc = p->nextarc;
		free(p);
		return OK;
	}
	for (p = G->vertice[m].firstarc; p != NULL;)
	{
		q = p;
		p = p->nextarc;
		if (p == NULL)break;
		if (p->adjvex == n)
		{
			q->nextarc = p->nextarc;
			free(p);
			return OK;
		}
	}
	printf("%d和%d之间没有弧\n", v, w);
	return ERROR;
}
//初始化多表
status InitSqList(SqList &L)
{
	L = (SqList)malloc(sizeof(SqNode));
	if (!L)return ERROR;
	L->next = NULL;
	L->G = (ALGraph*)malloc(sizeof(ALGraph));
	L->G->kind = 0;
	L->Mtrix = (rela*)malloc(sizeof(rela));
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		memset(&L->Mtrix->relation[i], 0, MAX_VERTEX_NUM);
	return OK;
}
//获得第一个邻接点
ArcNode* FirstAdjVex(ALGraph *G, KeyType v)
{
	int m = search(G, v);
	if (m == -1)return NULL;       //顶点不存在
	if (G->vertice[m].firstarc == NULL)return NULL;     //没有邻接顶点
	else
		return G->vertice[m].firstarc;
}
//获得下一邻接
ArcNode* NextAdjVex(ALGraph *G, KeyType v, KeyType w)
{
	int m = search(G, v);      //找到v和w的位置
	int n = search(G, w);
	if (m == -1 || n == -1)
	{	
		printf("顶点不存在\n");   //顶点不存在
		return NULL;
	}
	ArcNode *p = G->vertice[m].firstarc;
	for (p; p != NULL; p = p->nextarc)
	{
		if (p->adjvex == n&&p->nextarc != NULL)      //找到顶点
			return p->nextarc;
	}
	return NULL;
}
//更新关系矩阵
status RenewMtrix(SqList L)
{
	for (int i = 0; i < L->G->vexnum;i++)
	for (ArcNode* p = L->G->vertice[i].firstarc; p != NULL; p = p->nextarc)
		L->Mtrix->relation[i][p->adjvex] = 1;
	//for (int i = 0; i < L->G->vexnum;i++)
	//for (int j = 0; j < L->G->vexnum; j++)
	//	printf("%d\t", L->Mtrix->relation[i][j]);
	return OK;
}
//添加一个新图
SqList AddGraph(SqList &L)
{
	SqList p = L,q=NULL;
	if (L->G->kind != 1)
	{
		printf("请输入名字\n");
		scanf("%s", &L->name);
		printf("添加成功\n");
		return L;
	}
	InitSqList(q);
	q->next = L->next;
	L->next = q;
	printf("请输入名字\n");
	scanf("%s", &q->name);
	return q;
}
//切换图
SqList ChangeGraph(SqList L, char* name)
{

	if (strcmp(name, L->name) == 0)
		return L;
	if (L->next == NULL)
	{
		return ERROR;
	}
	if (L->G->kind != 1)return ERROR;
	SqList p = L;
	for (p; p != NULL&&p->G->kind==1;p=p->next)
	if (strcmp(name, p->name) == 0)
		return p;
	return NULL;
}
//删除图
status DeleteGraph(SqList &L, char *name)
{
	SqList p = L, q;
	if (L == NULL)return ERROR;
	if (L->G->kind != 1)return ERROR;
	if (strcmp(L->name, name) == 0)
	{
		L = L->next;
		free(p);
		return OK;
	}
	q = p;
	for (p; p != NULL; p = p->next)
	{
		if (strcmp(p->name, name) == 0)
		{
			q->next = p->next;
			free(p);
			return OK;
		}
		q = p;
	}
	return ERROR;
}
//销毁图
status DestoryGraph(ALGraph* G)
{
	free(G->vertice);
	G->kind = 0;
	return OK;
}
//删除顶点
status DeleteVex(ALGraph* &G, KeyType v)
{
	int m = search(G, v);          //找到v在邻接表中的位置
	ArcNode*p = NULL, *q = NULL;
	for (int i = 0; i < G->vexnum; i++)
	{
		q=p = G->vertice[i].firstarc;        //遍历整个邻接表，删除每个顶点与v相关的弧
		if (G->vertice[i].firstarc!=NULL&&G->vertice[i].firstarc->adjvex == m)                    //对第一个邻接点单独处理
		{
			G->vertice[i].firstarc = p->nextarc;
			free(p);
		}
		else
			for (p; p != NULL; p = p->nextarc)
			{
				if (p->adjvex == m)
				{
					q->nextarc = p->nextarc;
					free(p);
					break;
				}
				q = p;
			}
	}
	for (int i = m; i < G->vexnum-1; i++)          //将m后面的表都往前移动
		G->vertice[i] = G->vertice[i + 1];
	G->vexnum--;                                   //顶点数目减1
	return OK;
}
//清空ID
void ClearArray()
{
	for (int i = 0; i < num; i++)
	{
		ID[i] = -1;
	}
	num = 0;
}