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

int ID[100],num;                        //�����洢ΨһID����ֹ�ظ�
bool visited[MAX_VERTEX_NUM];            //���ʱ�־����

typedef struct
{
	char localName[20];          //�ص�����
	int ID;                     //Ψһ��ʶID
}province;

typedef struct ArcNode
{
	int adjvex;               //�û���ָ��Ķ����λ��
	struct ArcNode *nextarc;  //ָ����һ������ָ��
	InfoType info;            //�û������Ϣ��ָ��
}ArcNode;

typedef struct VNode
{
	province* data;                  //������Ϣ
	ArcNode *firstarc;          //ָ���һ�������ڸö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertice;
	int vexnum, arcnum;          //���ĵ�ǰ�������ͻ�����
	int kind;                    //ͼ�������־
}ALGraph;

//�ڽӹ�ϵ����
typedef struct
{
	int relation[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}rela;
//������Ϣ
typedef struct
{
	char Vnode[MAX_VERTEX_NUM][20];
}Vnodes;
//���ṹ�����ڱ�����ͼ
typedef struct Sq
{
	ALGraph* G;        //ͼ
	rela* Mtrix;       //��ϵ����
	char name[20];     //ͼ������
	struct Sq *next;
}SqNode,*SqList;

//����ͼ
status DestoryGraph(ALGraph* G);
status(*VisitedFunc)(VNode V);             //��������
//���ID�Ƿ��ظ�
status Inpect(int t);
//������ϵ��,��һ��һά���鱣��
status CreateRela(int vexnum, int arcnum);
//���ҽڵ�,����ID
status LocateVex(ALGraph *G, int u);
//���ҽڵ㣬���ݵ���
status LocateVex(ALGraph *G, char* name);
//���뻡
status InsertArc(ALGraph *G,KeyType v,KeyType w);
//�������㼯
status CreateNode(Vnodes* &V, int vexnum);
//����ͼ
status CreateCraph(ALGraph* &G,Vnodes *V,rela *VR);
//���붥��
status InsertVex(ALGraph* &G, VNode* v);
//��õ�һ���ڽӵ�
ArcNode* FirstAdjVex(ALGraph *G, KeyType v);
status Visit(VNode V)
{
	printf("ID:%d\n", V.data->ID);
	printf("���֣�%s\n", V.data->localName);
	return OK;
}
//ɾ������
status DeleteVex(ALGraph* &G, KeyType v);
//������ȱ���
void DFSTraverse(ALGraph* G, status(*Visit)(VNode V));
void DFS(ALGraph* G, int v);
//�����������
void BFSTraverse(ALGraph *G, status(*Visit)(VNode V));
//��ö���ֵ
status GetVex(ALGraph *G,int v);
//���㸳ֵ
status PutVex(ALGraph* G, int v, province* value);
//ɾ����
status DeleteArc(status &G,int v,int w);
//������ϵ��,��һ��һά���鱣��
status CreateRela(int vexnum, int arcnum, rela* &relation);
//����ͼ
status SaveGraph(ALGraph* G,rela* VR);
//����ͼ
status LoadGraph(ALGraph* &G);
//����ID���Ҷ���λ��
int search(ALGraph *G, int id);
//ɾ����
status DeleteArc(ALGraph* G, KeyType v, KeyType w);
//��ʼ�����
status InitSqList(SqList &L);
//�����һ�ڽ�
ArcNode* NextAdjVex(ALGraph *G, KeyType v, KeyType w);
//���¹�ϵ����
status RenewMtrix(SqList L);
//���һ����ͼ
SqList AddGraph(SqList &L);
//�л�ͼ
SqList ChangeGraph(SqList L, char* name);
//ɾ��ͼ
status DeleteGraph(SqList &L, char *name);
//���ID
void ClearArray();
int main()
{
	Vnodes* V=NULL;         //���㼯
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
		printf("1��CreateCraph            18��DeleteGraph\n");
		printf("2��DFSTraverse            10��DeleteArc\n");
		printf("3��BFSTraverse            11��FirstArcNode\n");
		printf("4��LocateVex              12��NextAdjVex\n");
		printf("5��GetVex                 13��DestoryGraph\n");
		printf("6��PutVex                 14��InsertArc\n");
		printf("7��InsertVex              15��AddGraph\n");
		printf("8��SaveGraph              16��DeleteVex\n");
		printf("9��LoadGraph              17��ChangeGraph\n");
		printf("0��exit\n");
		printf("-------------------------------------------------\n");
		if (p == NULL)InitSqList(p);
		if (p->G->kind == 1)
			printf("��ǰ������ͼ�ǣ�%s\n", p->name);
		printf("����������[1`18]\n");
		scanf("%d", &op);
		if (p == NULL)	InitSqList(p);
		switch (op)
		{
		case 1:
			printf("�����붥�����ͻ���\n");
			scanf("%d %d", &a, &b);
			if (a <= 0 || a > MAX_VERTEX_NUM || b <= 0 || b > MAX_VERTEX_NUM)
			{
				printf("�������\n");
			}
			else
			{
				p->G = (ALGraph*)malloc(sizeof(ALGraph));
				p->G->vexnum = a; p->G->arcnum = b;
				CreateRela(p->G->vexnum, p->G->arcnum, p->Mtrix);
				CreateNode(V, p->G->vexnum);
				CreateCraph(p->G, V, p->Mtrix);
				printf("������ΪСͼȡ�����ְ�\n");
				scanf("%s", &p->name);
			}
			system("pause");
			break;
		case 2:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
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
				printf("��û�д���\n");
			}
			else
				BFSTraverse(p->G, Visit);
			system("pause");
			break;
		case 4:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				char name[20];
				int id;
				printf("1������ID����   2���������ֲ���\n");
				scanf("%d", &id);
				if (id == 1)
				{
					printf("��������Ҫ���ҵ�ID\n");
					scanf("%d", &id);
					if (LocateVex(p->G, id) == ERROR)
						printf("û���ҵ�\n");
				}
				else if (id == 2)
				{
					printf("��������Ҫ���ҵ�����\n");
					scanf("%s", &name);
					if (!LocateVex(p->G, name))
						printf("û���ҵ�\n");
				}
				else
					printf("�������\n");
			}
			system("pause");
			break;
		case 5:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("��������Ҫ���ҵĶ���ID\n");
				scanf("%d", &a);
				if (GetVex(p->G, a)==ERROR)
					printf("�������\n");
			}
			system("pause");
			break;
		case 6:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("������ID\n");
				scanf("%d", &a);
				b = search(p->G, a);
				if (b == -1)
				{
					printf("�����ڵ�ID\n");
				}
				else
				{
					province* po = (province*)malloc(sizeof(province));
				loop5:
					printf("�������޸ĺ��ID\n");
					int th;
					scanf("%d", &th);
					if (Inpect(th))
					{
						po->ID = th;
						printf("�������޸ĺ������\n");
						scanf("%s", &po->localName);
						if (PutVex(p->G, b, po))
							printf("�޸ĳɹ�\n");
						else
							printf("�޸�ʧ��\n");
					}
					else
					{
						printf("ID�ظ�����������\n");
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
				printf("��û�д���\n");
			}
			else
			{
				VNode *node = NULL;
				node = (VNode*)malloc(sizeof(VNode));
				node->data = (province*)malloc(sizeof(province));
				printf("������Ҫ���붥�����֣�\n");
				scanf("%s", &node->data->localName);
				printf("�����붥��%s��ID:\n", node->data->localName);
				int m;
			loop4:scanf("%d", &m);
				if (Inpect(m) == OK)
				{
					node->data->ID = m;
				}
				else
				{
					printf("ID�ظ�����������\n");
					goto loop4;
				}
				if (InsertVex(p->G, node))printf("����ɹ�\n");
				else printf("����ʧ��");
			}
			system("pause");
			break;
		case 8:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				if (SaveGraph(p->G, p->Mtrix))
					printf("����ɹ�\n");
			}
			system("pause");
			break;
		case 9:
			if (p->G == NULL)
			{
				p->G = (ALGraph*)malloc(sizeof(ALGraph));
				if (LoadGraph(p->G))printf("���سɹ�\n");
				else printf("����ʧ��\n");
			}
			else
			{
				printf("����������ʧȥ��ǰͼ�е���Ϣ,������(�س�����)\n");
				char ch;
				getchar();
				ch = getchar();
				if (ch == '\n'){
					if (LoadGraph(p->G))
					{
						printf("���سɹ�\n");
						RenewMtrix(p);
						printf("������ͼ�����ֽ�ʲôѽ?\n");
						scanf("%s", &p->name);
						ClearArray();;
					}
					else printf("����ʧ��\n");
				}

			}
			system("pause");
			break;
		case 10:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("�����붥���id���м��ÿո����\n");
				scanf("%d %d", &v, &w);
				if (DeleteArc(p->G, v, w))
					printf("ɾ���ɹ�\n");
				RenewMtrix(p);
			}
			system("pause");
			break;
		case 11:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("������Ҫ���ҵ�ID\n");
				scanf("%d", &v);
				A = FirstAdjVex(p->G, v);
				if (A == NULL)
					printf("���㲻���ڻ���û���ڽӵ�\n");
				else
				{
					printf("��һ�ڽӵ���ϢΪ:\n");
					printf("ID:%d\n", p->G->vertice[A->adjvex].data->ID);
					printf("����:%s\n", p->G->vertice[A->adjvex].data->localName);
				}
			}
			system("pause");
			break;
		case 12:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("��������Ҫ���ҵĶ��㣬�м��ÿո����\n");
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
				printf("��û�д���\n");
			}
			else
			{
				if (DestoryGraph(p->G))printf("���ٳɹ�\n");
			}
			system("pause");
			break;
		case 14:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("��������Ҫ����Ļ������˶���ID\n");
				scanf("%d %d", &v, &w);
				if (InsertArc(p->G, v, w))
					printf("����ɹ�\n");
				else
					printf("����ʧ��\n");
				RenewMtrix(p);
			}
			system("pause");
			break;
		case 15:
			q = AddGraph(L);
			if (q)
				p = q;
			else
				printf("���ʧ��\n");
			system("pause");
			break;
		case 16:
			if (p->G->kind != 1)
			{
				printf("��û�д���\n");
			}
			else
			{
				printf("��������Ҫɾ���Ķ����ID\n");
				scanf("%d", &v);
				if (search(p->G, v) == -1)
					printf("ID������\n");
				else
				{
					if (DeleteVex(p->G, v) == OK)
						printf("ɾ���ɹ�\n");
					else
						printf("ɾ��ʧ��\n");
					RenewMtrix(p);
				}
			}
			system("pause");
			break;
		case 17:
			printf("��������Ҫ�л�����ͼ������\n");
			char Graphname[20];
			scanf("%s", &Graphname);
			q = ChangeGraph(L, Graphname);
			if (q == NULL)
				printf("������\n");
			else
			{
				p = q;
				printf("�л��ɹ�\n");
				ClearArray();;
			}
			system("pause");
			break;
		case 18:
			printf("��������Ҫɾ����ͼ������\n");
			getchar();
			gets(Graphname);
			if (DeleteGraph(L, Graphname))
			{
				printf("ɾ���ɹ�\n");
				ClearArray();;
			}
			else
				printf("ͼ������\n");
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
//�������㼯
status CreateNode(Vnodes* &V,int vexnum)
{
	V = (Vnodes*)malloc(sizeof(Vnodes));
	for (int i = 0; i < vexnum; i++)              //num��ʾ������Ŀ������Ϊÿ�����㸳ֵ
	{
		printf("�������%d���ڵ�ĵ���\n", i + 1);
		scanf("%s", &V->Vnode[i]);
	}
	return OK;
}
//������ϵ��,��һ��һά���鱣��
status CreateRela(int vexnum,int arcnum,rela* &realtion)
{	
	int m, n,t=0;
	realtion = (rela*)malloc(sizeof(rela));
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		memset(&realtion->relation[i], 0, MAX_VERTEX_NUM);
	printf("�����������ڵ����ű�ʾ����֮���й�ϵ���м��Կո����\n");
	char ch = '*';
	while (t<arcnum)
	{
		loop6:
		scanf("%d %d", &m, &n);
		if (m<0 || m>vexnum || n < 0 || n > vexnum||m==n)
		{
			printf("���������������\n");
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
//���ID�Ƿ��ظ�
status Inpect(int t)
{
	for (int i = 0; i < num; i++)
	{
		if (ID[i] == t)
		{
			printf("ID�ظ�\n");
			return ERROR;
		}
	}
	ID[num++] = t;
	return OK;
}
//����ͼ
status CreateCraph(ALGraph* &G, Vnodes* V, rela *VR)
{
	if (!G)return ERROR;
	for (int i = 0; i < G->vexnum; i++)   //�Ѷ������еĶ�����Ϣ������ͼ��
	{
		G->vertice[i].data = (province*)malloc(sizeof(province));
		strcpy(G->vertice[i].data->localName, V->Vnode[i]);
		G->vertice[i].firstarc = NULL;
	}
	for (int i = 0; i < G->vexnum; i++)          //����ÿ������ID
	{
		printf("�����붥��%s��ID:\n",G->vertice[i].data->localName);
		int m;
		it:scanf("%d", &m);
		if (Inpect(m) == OK)
		{
			G->vertice[i].data->ID = m;
		}
		else
		{
			printf("ID�ظ�����������\n");
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
//�����������
void DFSTraverse(ALGraph* G, status(*Visit)(VNode V))
{
	for (int v = 0; v < G->vexnum; v++)       //���������ʼ��
		visited[v] = FALSE;
	for (int v = 0; v < G->vexnum; v++)
	if (!visited[v])
		DFS(G, v);                        //����δ���ʵĽڵ����DFS
}
void DFS(ALGraph* G, int v)
{
	visited[v] = TRUE;                  
	Visit(G->vertice[v]);                //���ʵ�v������
	for (ArcNode *p = G->vertice[v].firstarc; p != NULL; p = p->nextarc)
	{
		if (!visited[p->adjvex])DFS(G, p->adjvex);
	}
}
//�����������
void BFSTraverse(ALGraph *G, status(*Visit)(VNode V))
{
	int v;
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	int array[MAX_VERTEX_NUM*20], first = 0, tail = 0,temp;    //��Ϊ��������
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
//����ID����
status LocateVex(ALGraph *G, int u)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist=0, tail=0,temp;      //��������
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum;v++)                        //���������������
	if (!visited[v])
	{
		if (G->vertice[v].data->ID == u)
		{
			printf("%d��ͼ�еĵ�%d������\n", u, v+1);
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
						printf("%d��ͼ�еĵ�%d������\n", u, p->adjvex+1);
						Visit(G->vertice[p->adjvex]);
						return OK;
					}	array[tail++] = p->adjvex;
				}
			}
		}
	}
	return ERROR;
}
//���ҽڵ㣬���ݵ���
status LocateVex(ALGraph *G, char* name)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist = 0, tail = 0, temp;      //��������
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum; v++)                        //���������������
	if (!visited[v])
	{
		if (!strcmp(name,G->vertice[v].data->localName))
		{
			printf("%s��ͼ�еĵ�%d������\n", name, v+1);
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
						printf("%s��ͼ�еĵ�%d������\n", name, p->adjvex+1);
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
//��ö���ֵ
status GetVex(ALGraph* G, int vn)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist = 0, tail = 0, temp;      //��������
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum; v++)                        //���������������
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
//���㸳ֵ
status PutVex(ALGraph* G, int vn,province* value )
{
	if (!G || G->kind != 1)
		return ERROR;
	G->vertice[vn].data->ID = value->ID;
	strcpy(G->vertice[vn].data->localName, value->localName);
	return OK;
}
//���붥��
status InsertVex(ALGraph* &G, VNode* v)
{
	if (G == NULL || G->kind != 1)return ERROR;
	if (G->vexnum >= MAXSIZE - 1)return ERROR;      //�ṹ��������
	G->vexnum++;                //��������һ
	G->vertice[G->vexnum-1].data = (province*)malloc(sizeof(province));
	strcpy(G->vertice[G->vexnum-1].data->localName, v->data->localName);
	G->vertice[G->vexnum-1].data->ID = v->data->ID;
	G->vertice[G->vexnum - 1].firstarc = NULL;
	return OK;
}
//����ͼ
status SaveGraph(ALGraph* G,rela* VR)
{
	FILE* fp;
	char fupan[50] = "D://";
	char tail[10] = ".txt";
	char name[20];
	printf("������Ҫ������ļ�����\n");
	scanf("%s", &name);
	strcat(fupan, name);
	strcat(fupan, tail);          //ƴ�ӳ�һ���������ļ�·��
	fp = fopen(fupan,"w");
	if (!fp)exit(-1);
	fwrite(&G->vexnum, 1, sizeof(int), fp);
	for (int i = 0; i < G->vexnum; i++)                       //���涥����Ŀ
	{
		fwrite(&G->vertice[i].data->localName,20, sizeof(char), fp);
		fwrite(&G->vertice[i].data->ID, 1, sizeof(int), fp);
	}
	for (int i = 0; i < G->vexnum; i++)
	for (int j = 0; j < G->vexnum; j++)
	{
		fwrite(&VR->relation[i][j], 1, sizeof(int), fp);     //�����ϵ����
	}
	fclose(fp);
	return OK;
}
//����ID���Ҷ���λ��
int search(ALGraph* G, int id)
{
	int v = 0;
	int array[MAX_VERTEX_NUM], frist = 0, tail = 0, temp;      //��������
	for (v = 0; v < G->vexnum; v++)
		visited[v] = FALSE;
	for (v = 0; v < G->vexnum; v++)                        //���������������
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
	return -1;          //û���ҵ�
}
//����ͼ
status LoadGraph(ALGraph* &G)
{
	Vnodes* V=NULL;        // ���涥����Ϣ
	rela* VR;              //�����ϵ����
	V = (Vnodes*)malloc(sizeof(Vnodes));
	VR = (rela*)malloc(sizeof(rela));
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		memset(&VR->relation[i], 0, MAX_VERTEX_NUM);
	FILE* fp;
	char filepath[30];
	printf("�������ļ�����\n");
	file:gets(filepath);
	if (_access(filepath, 0) == -1)
	{
		printf("�ļ������ڣ���������\n");
		goto file;
	}
	G = (ALGraph*)malloc(sizeof(ALGraph));
	fp = fopen(filepath,"r");
	int m;
	while (!feof(fp))
	{
		fread(&m, 1, sizeof(int), fp);   //��ȡ�������
		if (!feof(fp))
			G->vexnum = m;
		for (int i = 0; i < G->vexnum; i++)
		{
			if (!feof(fp))
			{
				G->vertice[i].data = (province*)malloc(sizeof(province));
				fread(&G->vertice[i].data->localName, 20, sizeof(char), fp);      //��ȡ������Ϣ
				fread(&G->vertice[i].data->ID, 1, sizeof(int), fp);
				G->vertice[i].firstarc = NULL;
			}
		}
		for (int i = 0; i < G->vexnum; i++)
		for (int j = 0; j < G->vexnum; j++)
		{
			fread(&m, 1, sizeof(int), fp);         //��ȡ��ϵ����
			if (!feof(fp))
				VR->relation[i][j] = m;
		}
	}
	ArcNode* p = NULL;
	for (int i = 0; i < G->vexnum; i++)           //���ݹ�ϵ�������ڽӱ�
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
//���뻡
status InsertArc(ALGraph *G, KeyType v, KeyType w)
{
	int m = search(G, v);             //�ҵ�������ͼ�е�λ��
	int n = search(G, w);
	if (m == -1 || n == -1)      //�����ID������
	{	printf("�����ڵ�ID\n");
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
//ɾ����
status DeleteArc(ALGraph* G, KeyType v, KeyType w)
{
	int m = search(G, v);                //�ҵ��������ڽӱ��е����
	int n = search(G, w);
	if (m == -1 || n == -1)
	{
		printf("ID������\n");
		return ERROR;
	}
	ArcNode* p = NULL,*q=NULL;
	if (G->vertice[m].firstarc == NULL)
	{
		printf("%d��%d֮��û�л�\n", v, w);
		return ERROR;
	}
	if (G->vertice[m].firstarc->adjvex == n)    //�Ե�һ���ڽӵ����⴦��
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
	printf("%d��%d֮��û�л�\n", v, w);
	return ERROR;
}
//��ʼ�����
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
//��õ�һ���ڽӵ�
ArcNode* FirstAdjVex(ALGraph *G, KeyType v)
{
	int m = search(G, v);
	if (m == -1)return NULL;       //���㲻����
	if (G->vertice[m].firstarc == NULL)return NULL;     //û���ڽӶ���
	else
		return G->vertice[m].firstarc;
}
//�����һ�ڽ�
ArcNode* NextAdjVex(ALGraph *G, KeyType v, KeyType w)
{
	int m = search(G, v);      //�ҵ�v��w��λ��
	int n = search(G, w);
	if (m == -1 || n == -1)
	{	
		printf("���㲻����\n");   //���㲻����
		return NULL;
	}
	ArcNode *p = G->vertice[m].firstarc;
	for (p; p != NULL; p = p->nextarc)
	{
		if (p->adjvex == n&&p->nextarc != NULL)      //�ҵ�����
			return p->nextarc;
	}
	return NULL;
}
//���¹�ϵ����
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
//���һ����ͼ
SqList AddGraph(SqList &L)
{
	SqList p = L,q=NULL;
	if (L->G->kind != 1)
	{
		printf("����������\n");
		scanf("%s", &L->name);
		printf("��ӳɹ�\n");
		return L;
	}
	InitSqList(q);
	q->next = L->next;
	L->next = q;
	printf("����������\n");
	scanf("%s", &q->name);
	return q;
}
//�л�ͼ
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
//ɾ��ͼ
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
//����ͼ
status DestoryGraph(ALGraph* G)
{
	free(G->vertice);
	G->kind = 0;
	return OK;
}
//ɾ������
status DeleteVex(ALGraph* &G, KeyType v)
{
	int m = search(G, v);          //�ҵ�v���ڽӱ��е�λ��
	ArcNode*p = NULL, *q = NULL;
	for (int i = 0; i < G->vexnum; i++)
	{
		q=p = G->vertice[i].firstarc;        //���������ڽӱ�ɾ��ÿ��������v��صĻ�
		if (G->vertice[i].firstarc!=NULL&&G->vertice[i].firstarc->adjvex == m)                    //�Ե�һ���ڽӵ㵥������
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
	for (int i = m; i < G->vexnum-1; i++)          //��m����ı���ǰ�ƶ�
		G->vertice[i] = G->vertice[i + 1];
	G->vexnum--;                                   //������Ŀ��1
	return OK;
}
//���ID
void ClearArray()
{
	for (int i = 0; i < num; i++)
	{
		ID[i] = -1;
	}
	num = 0;
}