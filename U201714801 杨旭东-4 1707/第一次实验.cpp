#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType;
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 10
#define MAXSIZE 10
typedef struct
{
	ElemType *elem;
	int length;
	int listsize;
	int flag;                 //用于标记表初始化状态
}SqList;
typedef struct                //用于保存多个线性表的结构
{
	SqList* Sq;               //顺序表指针
	int length;
	int listsize;
}M_List;
status ListDelete(SqList &L, int i, ElemType &e);
status ListTrabverse(SqList L);
status IntiaList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L,ElemType &e);
status GetElem(SqList &L, int i, ElemType &e); 
status LocateElem(SqList L,ElemType e); 
status PriorElem(SqList L,ElemType cur,ElemType &pre_e);
status NextElem(SqList L,ElemType cur,ElemType &next_e);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListSave(SqList &L);
status List_Load_from_File(SqList&L);
status Init_ManyList(M_List &M);
status Add_List(M_List &M);
status Change_List(M_List &M,SqList &L);
status Delete_List(M_List &M,int &i);

int main()
{
	int count = 0;             //用来计算当前表的序号
	M_List M;
	Init_ManyList(M);
	SqList &L=M.Sq[count];
	int op=1;
	while (op)
	{
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("		1. IntiaList	10. ListInsert\n");
		printf("		2. DestroyList	11. ListDelete\n");
		printf("		3. ClearList    12. ListTrabverse\n");
		printf("		4. ListEmpty    13. ListSave\n");
		printf("		5. ListLength   14. List_Load_from_File\n");
		printf("		6. GetElem      15. Add_List\n");
		printf("		7. LocateElem   16. Change_List\n ");
		printf("		8. PriorElem    17.List_Delete\n  ");
		printf("		9. NextElem     0. Exit\n");
		printf("    当前操作对象是表%d\n", count+1);
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~14]:");
		scanf("%d", &op);
		int i, j, k, e;
		switch (op)
		{
		case 1:{
				   if (IntiaList(M.Sq[count]) == -1) printf("已经初始化，请勿重复操作\n");
				   else if (IntiaList(M.Sq[count]))printf("线性表创建成功\n");
			   else printf("线性表创建失败\n"); system("pause"); }
			break;
		case 2:
			i = DestroyList(M.Sq[count]);
			if (i==OK)
				printf("\n已经成功销毁顺序表\n");
			if (i == -1)
				printf("还没有初始化\n");
			system("pause");
			break;
		case 3:
			if (ClearList(M.Sq[count]) == -1)printf("\n请先初始化操作\n");
			else
				printf("\n表已经清空\n");
			system("pause");
			break;
		case 4:
			i = ListEmpty(M.Sq[count]);
			if (i)printf("\n表非空\n");
			else if (i == -1)
				printf("还没有初始化");
			else
				printf("\n表为空\n");
			system("pause");
			break;
		case 5:
			i = ListLength(L,e);
			if (i==-1)printf("\n请先初始化表\n");
			else
				printf("\n表的长度为%d\n",e);
			system("pause");
			break;
		case 6:
			printf("请输入需要获取的元素的位置\n");
			scanf("%d", &i);
			j = GetElem(M.Sq[count], i, e);
			if (j == -1)
			{
				printf("还没有初始化\n");
				break;
			}
			if (j==1)
				printf("\n第%d个元素为%d\n",i,e);
			else
				printf("\n输入错误或者是还没有初始化表\n");
			system("pause");
			break;
		case 7:
			printf("请输入元素\n");
			scanf("%d", &e);
			j = LocateElem(M.Sq[count], e);
			if (j == -1)
				printf("还没有初始化\n");
			if (!j)printf("元素不存在\n");
			else
				printf("\n元素%d表中第%d位置\n",e,j);
			system("pause");
			break;
		case 8:
			printf("请输入元素\n");
			scanf("%d", &j);
			i = PriorElem(M.Sq[count], j, k);
			if (i == -1)
			{
				printf("还没有初始化"); break;
			}
			if (i == 0)printf("请先初始化\n");
			else if (i == 2)printf("元素不存在或没有前驱\n");
			else
				printf("\n%d的前驱元素为%d\n",j,k);
			system("pause");
			break;
		case 9:
			printf("请输入元素\n");
			scanf("%d", &j);
			i = NextElem(M.Sq[count], j, k);
			if (i == -1){ printf("请先初始化\n"); }
			else if (i == 2)printf("元素不存在或没有后继\n");
			else
				printf("\n%d的后继元素为%d\n", j, k);
			system("pause");
			break;
		case 10:
			printf("\n请输入需要插入的元素位置\n");
			scanf("%d", &j);
			printf("请输入需要插入元素\n");
			scanf("%d", &k);
			i = ListInsert(M.Sq[count], j, k);
			if (i == -1)
			{
				printf("还没有初始化\n"); break;
			}
			if (i == 0)printf("输入错误\n");
			else
				printf("\n插入成功\n", k);
			system("pause");
			break;
		case 11:
			printf("请输入需要删除元素位置\n");
			scanf("%d", &j);
			i = ListDelete(M.Sq[count], j, k);
			if (i == -1)
			{
				printf("还没有初始化\n"); break;
			}
			if (i == 0)printf("输入错误\n");
			else
				printf("\n删除成功,删除元素为%d\n",k);
			system("pause");
			break;
		case 12:  
			i = ListTrabverse(M.Sq[count]);
			if (i == -1){ printf("还没有初始化\n");}
			if (i==0) printf("线性表是空表！\n");
			system("pause");
			break;
		case 13:
			if (ListSave(M.Sq[count]) == -1){ printf("还没有初始化"); break; }
			else printf("保存成功!\n");
			system("pause");
			break;
		case 14:
			i = List_Load_from_File(M.Sq[count]);
			if (i==0){ printf("读入失败!\n"); }
			else{ printf("读入成功!\n");}
			system("pause");
			break;
		case 15:
			Add_List(M);
			printf("添加表%d成功\n",M.length+1);
			count = M.length;
			system("pause");
			break;
		case 16:
			if (M.length == 0){ printf("当前还没有表存在\n"); }
			else{
				if (count < M.length)count++;
				else count =0;
				printf("已经切换至表%d\n", count+1);
			}
			system("pause");
			break;
		case 17:
			if (M.length == 0){ printf("当前还没有表存在\n"); }
			else{
				if (Delete_List(M, count))printf("已经删除表%d\n", count+1);
				else
					printf("删除失败\n");
				count--;
			}
			system("pause");
			break;
		case 0:break;
		}
	}
	printf("欢迎下次使用本系统\n");
}
status IntiaList(SqList &L)
{
	if (L.flag==1)return -1;         //L.flag==1,说明顺序表已经经过初始化，为避免浪费，不应再为其申请，直接返回
	else
	{
		L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
		if (!L.elem)return ERROR;
		L.flag = 1;                  //将flag置为1，标记已经经过初始化
		L.length = 0;
		L.listsize = LIST_INIT_SIZE;
		return OK;
	}
}
status ListInsert(SqList &L, int i, ElemType e)
{
	if (i<1 || i>L.length+1)return ERROR;           //插入位置不正确
	if (L.flag == 0)return -1;
	if (L.length >= L.listsize)                     //表满，为其动态增加空间
	{
		L.elem = (ElemType*)realloc(L.elem, (LISTINCREMENT + L.listsize)*sizeof(ElemType));
		if (!L.elem)return ERROR;
		L.listsize += LISTINCREMENT;
	}
	++L.length;
	int j = L.length;
	for (; j >= i; j--)L.elem[j] = L.elem[j - 1];   //遍历表，找到插入位置
	L.elem[i - 1] = e;                              //完成插入
	return OK;
}
status DestroyList(SqList &L)
{
	if (L.flag == 0)return -1;      //flag为0，说明表不存在
	else
	{
		L.flag = 0;                 //释放空间，并将标志置为0
		free(L.elem);
		return OK;
	}
	
}
status ClearList(SqList &L)
{
	if (L.flag==0)return -1;
	else L.length = 0;             //表长置为0，清空表
	return OK;
}
int ListLength(SqList L,ElemType &e)
{
	if (L.flag==0)return -1;        //先判断表是否存在
	e = L.length;
	return OK;
}
status ListEmpty(SqList L)
{
	if (L.flag==0)return -1;         //先判断表是否存在
	if (L.length == 0)return 0;		 //表长为0，说明表为空
	else return 1;
}
status GetElem(SqList &L, int i, ElemType &e)
{
	if (L.flag==0)return -1;			 //先判断表是否存在
	if (i<1 || i>L.length)return ERROR; //获取元素的位置不正确
	e = L.elem[i-1];
	return OK;
}
status LocateElem(SqList L, ElemType e)
{
	int i = 1,j=0;
	if (L.flag == 0)return -1;          //先判断表是否存在
	while (i <= L.length&&L.elem[j++]!=e)i++;    //查找元素
	if (i <= L.length)return i;
	else return 0;
}
status PriorElem(SqList L, ElemType cur, ElemType &pre_e)
{
	if (L.flag == 0)return -1;           //先判断表是否存在
	int i = 0;
	while (L.elem[i] != cur)i++;         //查找元素位置
	if (i == 0)return 2;                 //第一个元素，没有前驱
	else
		pre_e = L.elem[i - 1];           //返回元素
	return OK;
}
status NextElem(SqList L, ElemType cur, ElemType &next_e)
{
	if (L.flag==0)return -1;             //先判断表是否存在
	int i=0;
	while (L.elem[i] != cur&&i<L.length)i++;
	if (i == L.length-1)return 2;              //表尾元素没有后继
	else if (L.elem[i] != cur)return 2;        //元素没有找到
	else 
		next_e = L.elem[i + 1];
	return OK;
}
status ListDelete(SqList &L, int i, ElemType &e)
{
	if (L.flag == 0)return -1;
	if ((i<1 )||( i>L.length))return ERROR;          //元素位置错误
	int j = i - 1;
	e = L.elem[i - 1];
	for (; j <= L.length - 2; j++)L.elem[j] = L.elem[j + 1];
	L.length--;
	return OK;
}
status Delete_List(M_List &M, int &i)
{
	if (M.length == 0 || i<0 || i>M.length)return ERROR;
	int j = i;
	while (j < M.length-1)M.Sq[j] = M.Sq[j + 1];
	M.length--;
	return OK;
}
status ListTrabverse(SqList L)
{
	if (L.flag == 0)return -1;              //先判断表是否存在
	if (L.length==0)return ERROR;
	int i = 0;
	while (i <= L.length-1)printf("\n%d\t", L.elem[i++]);  //遍历顺序表
	printf("\n");
	return OK;
}
status ListSave(SqList &L)
{
	if (L.flag == 0)return -1;
	FILE *fout;
	fout = fopen("D://abc.txt", "w");
	for (int i = 0; i < L.length; i++)
		fwrite(&L.elem[i], sizeof(int), 1, fout);//把表中的数据写入到文件中保存
	fclose(fout);
	return OK;
}
status List_Load_from_File(SqList&L)
{
	printf("1. 清空当前表并加载    2. 加载到当前表后部\n");
	int op,flag=1;
	scanf("%d", &op);
	switch (op)
	{
	case 1:
	{	IntiaList(L);
		FILE *fin;
		fin = fopen("D://abc.txt", "r");
		if (!fin)return ERROR;
		int i = 0, temp;
		for (i; !feof(fin); i++)
		{
			fread(&temp, sizeof(int), 1, fin);
			if (!feof(fin))
			{
				ListInsert(L, 1, temp);
			}
		}
		fclose(fin);
	}break;
	case 2:
	{
		if (L.flag == 0){ printf("当前表不存在!\n"); flag = 0; }
		else{
			FILE *fin;
			fin = fopen("D://abc.txt", "r");
			if (!fin)return ERROR;
			int i = 0, temp;
			for (i; !feof(fin); i++)
			{
				fread(&temp, sizeof(int), 1, fin);
				if (!feof(fin))
				{
					ListInsert(L, L.length, temp);
				}
			}
			fclose(fin);
		}
	}break;
	default:
		printf("输入错误\n");
		break;
	}
	if (flag == 0)return 0;
	return OK;
}
status Init_ManyList(M_List &M)
{
	M.Sq = (SqList*)malloc(MAXSIZE*sizeof(SqList));
	if (!M.Sq) exit(-1);
	M.length = 0;
	M.listsize = MAXSIZE;
	return OK;
}
status Add_List(M_List &M)
{
	if (M.length >= MAXSIZE)
	{
		M.Sq = (SqList*)realloc(M.Sq, (M.listsize + LISTINCREMENT)*sizeof(SqList));
		if (!M.Sq)return ERROR;
	}
	M.listsize += LISTINCREMENT;
	M.length++;
	return OK;
}
