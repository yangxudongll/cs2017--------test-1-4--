/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 10
typedef int status;
typedef int ElemType;                //数据元素类型定义
#define MAXSIZE 20
//学生信息结构体
typedef struct student
{
	char name[MAXSIZE];
	int number;
}Student;

typedef struct SqList
{
	Student* Stu;
	struct SqList*next;
	int flag;
}SqList, *LinkList;
typedef struct                //用于保存多个线性表的结构
{
	SqList *elem;               //顺序表指针
	int length;
	int listsize;
}M_List;


status IntiaList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList &L);
status GetElem(SqList &L, int i, LinkList& e);
status LocateElem(SqList& L, ElemType e, int &loc);
status ListInsert(SqList &L, int i);
status ListDelete(SqList &L, int i, LinkList &e);
status ListTrabverse(SqList L);
status Init_MList(M_List &M);
status Add_List(M_List &M);
status Save_List(SqList L);
//从文件加载到尾部
status load_List(SqList &L);
//查找前驱
status PriorElem(SqList L,int cur, LinkList& pre_e);
//查找后继
status NextElem(SqList L,int cur, LinkList& next_e);

/*--------------------------------------------*/
void main(void){
	M_List M;
	LinkList next_e, pre_e,temp=NULL;
	int op = 1;
	int i, j, k;
	int count = 0;
	int cur;
	Init_MList(M);
	while (op){
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. IntiaList       10. ListInsert\n");
		printf("    	  2. DestroyList     11. ListDelete\n");
		printf("    	  3. ClearList       12. ListTrabverse\n");
		printf("    	  4. ListEmpty       13. SavetoFile\n");
		printf("    	  5. ListLength      14. LoadfromFile\n");
		printf("    	  6. GetElem         15. AddList\n");
		printf("          7. LocateElem      16. ChangeList\n");
		printf("          8. PriorElem       0. exit\n");
		printf("          9. NextElem        \n");
		printf("当前操作对象为表%d\n", count + 1);
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~16]:");
		scanf("%d", &op);
		switch (op){
		case 1:
			if (IntiaList(M.elem[count]) == OK) printf("线性表创建成功！\n");
			else printf("线性表已经存在，请勿重新创建！\n");
			system("pause");
			break;
		case 2:
			i = DestroyList(M.elem[count]);
			if (i == OK)
			{
				printf("链表已经销毁\n");
				if (count < M.length - 1)count++;
				else count = 0;
			}
				
			else
				printf("链表不存在\n");
			system("pause");
			break;
		case 3:
			if (M.elem[count].flag != 1)
				printf("表不存在\n");
			else
			{
				ClearList(M.elem[count]);
				printf("表已经清空\n");
			}
				
			system("pause");
			break;
		case 4:
			j = ListEmpty(M.elem[count]);
			if (j == FALSE)
				printf("\n表不存在\n");
			else if (j == OK)
				printf("表为空\n");
			else
				printf("表不为空\n");
			system("pause");
			break;
		case 5:
			j = ListLength(M.elem[count]);
			if (j == -1)
				printf("表不存在\n");
			else
				printf("表长为%d\n",j);
			system("pause");
			break;
		case 6:
			if (M.elem[count].flag!=1)
				printf("表不存在\n");
			else
			{
				printf("请输入元素位置\n");
				scanf("%d", &i);
				if (GetElem(M.elem[count], i, temp))
				{
					printf("第i个学生：\n");
					printf("%s\n", temp->Stu->name);
					printf("%d\n", temp->Stu->number);
				}
				else
					printf("位置不对\n");
			}
			system("pause");
			break;
		case 7:
			printf("请输入需要查找的学号\n");
			scanf("%d", &i);
			j = LocateElem(M.elem[count], i, k);
			if (j == FALSE)
				printf("链表不存在\n");
			else if (j == ERROR)
				printf("没有找到\n");
			else
				printf("%d在第%d个位置\n", i, k);
			system("pause");
			break;
		case 8:
			if (M.elem[count].flag != 1)
				printf("\n表不存在\n");
			else
			{
				
				printf("请输入要查找的学号\n");
				scanf("%d", &cur);
				i = PriorElem(M.elem[count],cur,pre_e);
				if (i == ERROR)
					printf("元素没有前驱\n");
				else
				{
					printf("前一个学生为：\n");
					printf("%s\n", pre_e->Stu->name);
					printf("%d\n", pre_e->Stu->number);
				}
			}
			system("pause");
			break;
		case 9:
			if (M.elem[count].flag != 1)
				printf("\n表不存在\n");
			else
			{
				printf("请输入要查找的学号\n");
				scanf("%d", &cur);
				i = NextElem(M.elem[count],cur, next_e);
				if (i == ERROR)
					printf("元素没有后继\n");
				else
				{
					printf("后一个学生为：\n");
					printf("%s\n", next_e->Stu->name);
					printf("%d\n", next_e->Stu->number);
				}
			}
			system("pause");
			break;
		case 10:
			printf("\n请输入元素位置\n");
			scanf("%d", &i);
			j = ListInsert(M.elem[count], i);
			if (j == OK)
				printf("插入成功\n");
			else if (j == FALSE)
				printf("表不存在\n");
			else 
				printf("插入失败");
			system("pause");
			break;
		case 11:
			if (M.elem[count].flag != 1)
				printf("\n表不存在\n");
			else
			{
				printf("请输入需要删除元素位置\n");
				scanf("%d", &i);
				j = ListDelete(M.elem[count], i, temp);
				if (!j)
					printf("位置输入不对\n");
				else
				{
					printf("删除的学生为:\n");
					printf("%s\n", temp->Stu->name);
					printf("%d\n", temp->Stu->number);
				}
			}
			system("pause");
			break;
		case 12:
			if (!ListTrabverse(M.elem[count])) printf("链表不存在！\n");
			system("pause");
			break;
		case 13:
			if (M.elem[count].flag != 1)printf("链表不存在\n");
			else
			{
				Save_List(M.elem[count]);
				printf("保存成功\n");
			}
			system("pause");
			break;
		case 14:
			if (M.elem[count].flag != 1)
				printf("链表不存在!\n");
			else
			{
				load_List(M.elem[count]);
				printf("加载成功\n");
			}
			system("pause");
			break;
		case 15:
			Add_List(M);
			count++;
			printf("已经添加新表%d\n", M.length);
			system("pause");
			break;
		case 16:
			if (count < M.length-1)count++;
			else count = 0;
			printf("已经切换至表%d\n", count + 1);
			system("pause");
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}
status IntiaList(SqList& L)
{
	if (L.flag == 1)return FALSE;
	L.Stu = (Student*)malloc(MAXSIZE*sizeof(Student));
	L.Stu->number = 0;
	L.next = NULL;
	L.flag = 1;
	return OK;
}
status ListTrabverse(SqList L){
	if (L.flag != 1)return ERROR;
	LinkList p = L.next;
	printf("-------------------------------------------------\n");
	while (p){
		printf("姓名:%s\n", p->Stu->name);
		printf("学号:%d\n", p->Stu->number);
		printf("-------------------------------------------------\n");
		p = p->next;
	}
	return OK;
}
status ListEmpty(SqList L)
{
	if (L.flag != 1)return FALSE;           //表不存在
	if (L.next == NULL)return OK;           //表为空，返回OK
	return ERROR;
}
status Init_MList(M_List &M)
{
	//为顺序表申请空间
	M.elem = (LinkList)malloc(LIST_INIT_SIZE*sizeof(SqList));
	if (!M.elem)return ERROR;
	M.length = 1;								//初始化为1，表示表中默认开始有一张表
	M.listsize = LIST_INIT_SIZE;
	return OK;
}
status Add_List(M_List &M)
{
	//储存空间已满
	if (M.length >= MAXSIZE)
	{
		M.elem = (SqList*)realloc(M.elem, (M.listsize + LISTINCREMENT)*sizeof(SqList));
		if (!M.elem)return ERROR;
	}
	M.listsize += LISTINCREMENT;
	M.length++;
	return OK;
}
status ListInsert(SqList &L, int i)
{
	if (L.flag != 1)return FALSE;
	if (i<1||i > ListLength(L)+1)return ERROR;          //位置不对
	int j = 1;
	LinkList p = L.next, q = NULL;
	while (j < i&&p)
	{
		j++;
		p = p->next;
	}
	if (j < i)return ERROR;
	q = (LinkList)malloc(sizeof(SqList));
	q->Stu = (Student*)malloc(sizeof(Student));
	printf("请输入姓名:\n");
	scanf("%s", &q->Stu->name);
	printf("请输入学号:\n");
	scanf("%d", &q->Stu->number);
	if (p == NULL)
	{
		L.next = q;
		q->next = NULL;
	}
	else
	{
		q->next = p->next;
		p->next = q;
	}
	return OK;
}
status LocateElem(SqList& L, ElemType e, int &loc)
{
	if (L.flag != 1)return FALSE;          //表不存在
	LinkList p = L.next;
	int j = 1;
	while (p&&(p->Stu->number != e))              //根据学号查找
	{
		j++;
		p = p->next;
	}
	if (!p)return ERROR;                  //没有找到
	loc = j;                            //返回找到位置
	return OK;
}
int ListLength(SqList &L)
{
	if (L.flag != 1)return FALSE;
	int j = 0;
	LinkList p = L.next;
	while (p!=NULL)
	{
		j++;
		p = p->next;
	}
	return j;
}
status PriorElem(SqList L,int cur,LinkList& pre_e)
{
	if (L.flag != 1)return FALSE;
	LinkList p = L.next;
	if (p->Stu->number == cur)return ERROR;      //第一个元素没有前驱
	while ((p->next)&&(p->next->Stu->number != cur))p = p->next;
	if (p!=NULL)pre_e = p;
	else return ERROR;
	return OK;
}
status NextElem(SqList L,int cur,LinkList& next_e)
{
	if (L.flag != 1)return FALSE;
	LinkList p = L.next;
	while (p&&p->Stu->number != cur)p = p->next;
	if (!p || p->next == NULL)return ERROR;           //元素不存在后者是最后一个元素没有后继
	next_e = p->next;
	return OK;
}
status DestroyList(SqList &L)
{
	if (L.flag != 1)return FALSE;
	LinkList p = L.next,q;
	q = p;
	while (q!=NULL&&(q->next!=NULL))
	{
		p = q->next;
		free(q);
		q = p;
	}
	L.next = NULL;
	L.flag = 0;                        //标志置为0,表示表不存在了
	return OK;
}
status ListDelete(SqList &L, int i, LinkList &e)
{
	if (i <= 0 || i > ListLength(L))
		return ERROR;
	LinkList p = L.next,q;
	int count = 1;
	if (i == 1)
	{
		e = L.next;
		L.next = p->next;
		return OK;
	}
	while (p->next&&count < i-1)
	{
		p = p->next;
		++count;
	}
	if (!(p->next))return ERROR;
	q = p->next;
	p->next = q->next;
	e = q;
	return OK;
}
status Save_List(SqList L)
{
	LinkList p=L.next;
	FILE *fp,*fp1;
	//姓名和学号分别保存在两个文件中，如果打开失败，退出程序
	fp = fopen("D://number.txt", "w");
	if (!fp)exit(-1);
	fp1 = fopen("D://name.txt", "w");
	if (!fp1)exit(-1);
	int i;
	while (p)
	{
		char *temp =  p->Stu->name ;
		i = 0;
		//名字中含有多个字节，逐一遍历然后保存
		while (temp[i] != '\0')
		{
			fwrite(&temp[i], sizeof(char), 1, fp1);
			i++;
		}
		fwrite(&temp[i], sizeof(char), 1, fp1);
		fwrite(&p->Stu->number, sizeof(int), 1, fp);
		p = p->next;
	}
	fclose(fp);
	fclose(fp1);
	return OK;
}
status load_List(SqList &L)
{
	LinkList p=L.next,q=NULL;
	if (p)								//找到表尾进行加载
		while (p->next)p = p->next;
	FILE *fp1, *fp2;
	fp1 = fopen("D://name.txt", "r");
	if (!fp1)exit(-1);
	fp2 = fopen("D://number.txt", "r");
	if (!fp2)exit(-1);
	int i = 0,temp,t;
	char ch;
	for (i; (!feof(fp2))&&(!feof(fp1)); i++)
	{
		t = 0;
		fread(&temp, sizeof(int), 1, fp2);
		fread(&ch, sizeof(char), 1, fp1);
		if (!feof(fp2))				//再次判断是否到达文件尾，非常重要
		{
			//如果还有元素，继续增加结点
			q = (LinkList)malloc(sizeof(SqList));
			q->Stu = (Student*)malloc(sizeof(Student));
			q->Stu->number = temp;
		}
		else
			break;
		while (ch != '\0')				//当读到一个字符串尾部，表示一个名字结束
		{
			if (!feof(fp1))
				q->Stu->name[t++] = ch;
			fread(&ch, sizeof(char), 1, fp1);
		}
		q->Stu->name[t] = '\0';         //对保存名字的字符串末尾添加结尾符，否则遍历会出错
		if (L.next == NULL)
		{
			L.next = q;
			p = L.next;
			p->next = NULL;
			q = NULL;
		}
		else
		{
			p->next = q;
			p = p->next;
			p->next = NULL;
			q = NULL;
		}
	}
	fclose(fp2);
	fclose(fp1);
	return OK;
}
status GetElem(SqList &L, int i, LinkList& e)
{
	if (i<1 || i>ListLength(L))return ERROR;
	LinkList p = L.next;
	int j=1;
	while (p&&j < i)
	{
		p = p->next;
		++j;
	}
	e = p;
	return OK;
}
status ClearList(SqList &L)
{
	LinkList p = L.next,q;
	//依次释放结点空间，只保留头结点
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	L.next = NULL;
	return OK;
}