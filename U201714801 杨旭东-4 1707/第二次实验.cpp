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
typedef int ElemType;                //����Ԫ�����Ͷ���
#define MAXSIZE 20
//ѧ����Ϣ�ṹ��
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
typedef struct                //���ڱ��������Ա�Ľṹ
{
	SqList *elem;               //˳���ָ��
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
//���ļ����ص�β��
status load_List(SqList &L);
//����ǰ��
status PriorElem(SqList L,int cur, LinkList& pre_e);
//���Һ��
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
		printf("��ǰ��������Ϊ��%d\n", count + 1);
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~16]:");
		scanf("%d", &op);
		switch (op){
		case 1:
			if (IntiaList(M.elem[count]) == OK) printf("���Ա����ɹ���\n");
			else printf("���Ա��Ѿ����ڣ��������´�����\n");
			system("pause");
			break;
		case 2:
			i = DestroyList(M.elem[count]);
			if (i == OK)
			{
				printf("�����Ѿ�����\n");
				if (count < M.length - 1)count++;
				else count = 0;
			}
				
			else
				printf("��������\n");
			system("pause");
			break;
		case 3:
			if (M.elem[count].flag != 1)
				printf("������\n");
			else
			{
				ClearList(M.elem[count]);
				printf("���Ѿ����\n");
			}
				
			system("pause");
			break;
		case 4:
			j = ListEmpty(M.elem[count]);
			if (j == FALSE)
				printf("\n������\n");
			else if (j == OK)
				printf("��Ϊ��\n");
			else
				printf("��Ϊ��\n");
			system("pause");
			break;
		case 5:
			j = ListLength(M.elem[count]);
			if (j == -1)
				printf("������\n");
			else
				printf("��Ϊ%d\n",j);
			system("pause");
			break;
		case 6:
			if (M.elem[count].flag!=1)
				printf("������\n");
			else
			{
				printf("������Ԫ��λ��\n");
				scanf("%d", &i);
				if (GetElem(M.elem[count], i, temp))
				{
					printf("��i��ѧ����\n");
					printf("%s\n", temp->Stu->name);
					printf("%d\n", temp->Stu->number);
				}
				else
					printf("λ�ò���\n");
			}
			system("pause");
			break;
		case 7:
			printf("��������Ҫ���ҵ�ѧ��\n");
			scanf("%d", &i);
			j = LocateElem(M.elem[count], i, k);
			if (j == FALSE)
				printf("��������\n");
			else if (j == ERROR)
				printf("û���ҵ�\n");
			else
				printf("%d�ڵ�%d��λ��\n", i, k);
			system("pause");
			break;
		case 8:
			if (M.elem[count].flag != 1)
				printf("\n������\n");
			else
			{
				
				printf("������Ҫ���ҵ�ѧ��\n");
				scanf("%d", &cur);
				i = PriorElem(M.elem[count],cur,pre_e);
				if (i == ERROR)
					printf("Ԫ��û��ǰ��\n");
				else
				{
					printf("ǰһ��ѧ��Ϊ��\n");
					printf("%s\n", pre_e->Stu->name);
					printf("%d\n", pre_e->Stu->number);
				}
			}
			system("pause");
			break;
		case 9:
			if (M.elem[count].flag != 1)
				printf("\n������\n");
			else
			{
				printf("������Ҫ���ҵ�ѧ��\n");
				scanf("%d", &cur);
				i = NextElem(M.elem[count],cur, next_e);
				if (i == ERROR)
					printf("Ԫ��û�к��\n");
				else
				{
					printf("��һ��ѧ��Ϊ��\n");
					printf("%s\n", next_e->Stu->name);
					printf("%d\n", next_e->Stu->number);
				}
			}
			system("pause");
			break;
		case 10:
			printf("\n������Ԫ��λ��\n");
			scanf("%d", &i);
			j = ListInsert(M.elem[count], i);
			if (j == OK)
				printf("����ɹ�\n");
			else if (j == FALSE)
				printf("������\n");
			else 
				printf("����ʧ��");
			system("pause");
			break;
		case 11:
			if (M.elem[count].flag != 1)
				printf("\n������\n");
			else
			{
				printf("��������Ҫɾ��Ԫ��λ��\n");
				scanf("%d", &i);
				j = ListDelete(M.elem[count], i, temp);
				if (!j)
					printf("λ�����벻��\n");
				else
				{
					printf("ɾ����ѧ��Ϊ:\n");
					printf("%s\n", temp->Stu->name);
					printf("%d\n", temp->Stu->number);
				}
			}
			system("pause");
			break;
		case 12:
			if (!ListTrabverse(M.elem[count])) printf("�������ڣ�\n");
			system("pause");
			break;
		case 13:
			if (M.elem[count].flag != 1)printf("��������\n");
			else
			{
				Save_List(M.elem[count]);
				printf("����ɹ�\n");
			}
			system("pause");
			break;
		case 14:
			if (M.elem[count].flag != 1)
				printf("��������!\n");
			else
			{
				load_List(M.elem[count]);
				printf("���سɹ�\n");
			}
			system("pause");
			break;
		case 15:
			Add_List(M);
			count++;
			printf("�Ѿ�����±�%d\n", M.length);
			system("pause");
			break;
		case 16:
			if (count < M.length-1)count++;
			else count = 0;
			printf("�Ѿ��л�����%d\n", count + 1);
			system("pause");
			break;
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
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
		printf("����:%s\n", p->Stu->name);
		printf("ѧ��:%d\n", p->Stu->number);
		printf("-------------------------------------------------\n");
		p = p->next;
	}
	return OK;
}
status ListEmpty(SqList L)
{
	if (L.flag != 1)return FALSE;           //������
	if (L.next == NULL)return OK;           //��Ϊ�գ�����OK
	return ERROR;
}
status Init_MList(M_List &M)
{
	//Ϊ˳�������ռ�
	M.elem = (LinkList)malloc(LIST_INIT_SIZE*sizeof(SqList));
	if (!M.elem)return ERROR;
	M.length = 1;								//��ʼ��Ϊ1����ʾ����Ĭ�Ͽ�ʼ��һ�ű�
	M.listsize = LIST_INIT_SIZE;
	return OK;
}
status Add_List(M_List &M)
{
	//����ռ�����
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
	if (i<1||i > ListLength(L)+1)return ERROR;          //λ�ò���
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
	printf("����������:\n");
	scanf("%s", &q->Stu->name);
	printf("������ѧ��:\n");
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
	if (L.flag != 1)return FALSE;          //������
	LinkList p = L.next;
	int j = 1;
	while (p&&(p->Stu->number != e))              //����ѧ�Ų���
	{
		j++;
		p = p->next;
	}
	if (!p)return ERROR;                  //û���ҵ�
	loc = j;                            //�����ҵ�λ��
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
	if (p->Stu->number == cur)return ERROR;      //��һ��Ԫ��û��ǰ��
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
	if (!p || p->next == NULL)return ERROR;           //Ԫ�ز����ں��������һ��Ԫ��û�к��
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
	L.flag = 0;                        //��־��Ϊ0,��ʾ��������
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
	//������ѧ�ŷֱ𱣴��������ļ��У������ʧ�ܣ��˳�����
	fp = fopen("D://number.txt", "w");
	if (!fp)exit(-1);
	fp1 = fopen("D://name.txt", "w");
	if (!fp1)exit(-1);
	int i;
	while (p)
	{
		char *temp =  p->Stu->name ;
		i = 0;
		//�����к��ж���ֽڣ���һ����Ȼ�󱣴�
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
	if (p)								//�ҵ���β���м���
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
		if (!feof(fp2))				//�ٴ��ж��Ƿ񵽴��ļ�β���ǳ���Ҫ
		{
			//�������Ԫ�أ��������ӽ��
			q = (LinkList)malloc(sizeof(SqList));
			q->Stu = (Student*)malloc(sizeof(Student));
			q->Stu->number = temp;
		}
		else
			break;
		while (ch != '\0')				//������һ���ַ���β������ʾһ�����ֽ���
		{
			if (!feof(fp1))
				q->Stu->name[t++] = ch;
			fread(&ch, sizeof(char), 1, fp1);
		}
		q->Stu->name[t] = '\0';         //�Ա������ֵ��ַ���ĩβ��ӽ�β����������������
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
	//�����ͷŽ��ռ䣬ֻ����ͷ���
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	L.next = NULL;
	return OK;
}