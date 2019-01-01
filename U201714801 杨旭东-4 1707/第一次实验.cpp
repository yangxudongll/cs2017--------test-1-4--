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
	int flag;                 //���ڱ�Ǳ��ʼ��״̬
}SqList;
typedef struct                //���ڱ��������Ա�Ľṹ
{
	SqList* Sq;               //˳���ָ��
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
	int count = 0;             //�������㵱ǰ������
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
		printf("    ��ǰ���������Ǳ�%d\n", count+1);
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~14]:");
		scanf("%d", &op);
		int i, j, k, e;
		switch (op)
		{
		case 1:{
				   if (IntiaList(M.Sq[count]) == -1) printf("�Ѿ���ʼ���������ظ�����\n");
				   else if (IntiaList(M.Sq[count]))printf("���Ա����ɹ�\n");
			   else printf("���Ա���ʧ��\n"); system("pause"); }
			break;
		case 2:
			i = DestroyList(M.Sq[count]);
			if (i==OK)
				printf("\n�Ѿ��ɹ�����˳���\n");
			if (i == -1)
				printf("��û�г�ʼ��\n");
			system("pause");
			break;
		case 3:
			if (ClearList(M.Sq[count]) == -1)printf("\n���ȳ�ʼ������\n");
			else
				printf("\n���Ѿ����\n");
			system("pause");
			break;
		case 4:
			i = ListEmpty(M.Sq[count]);
			if (i)printf("\n��ǿ�\n");
			else if (i == -1)
				printf("��û�г�ʼ��");
			else
				printf("\n��Ϊ��\n");
			system("pause");
			break;
		case 5:
			i = ListLength(L,e);
			if (i==-1)printf("\n���ȳ�ʼ����\n");
			else
				printf("\n��ĳ���Ϊ%d\n",e);
			system("pause");
			break;
		case 6:
			printf("��������Ҫ��ȡ��Ԫ�ص�λ��\n");
			scanf("%d", &i);
			j = GetElem(M.Sq[count], i, e);
			if (j == -1)
			{
				printf("��û�г�ʼ��\n");
				break;
			}
			if (j==1)
				printf("\n��%d��Ԫ��Ϊ%d\n",i,e);
			else
				printf("\n�����������ǻ�û�г�ʼ����\n");
			system("pause");
			break;
		case 7:
			printf("������Ԫ��\n");
			scanf("%d", &e);
			j = LocateElem(M.Sq[count], e);
			if (j == -1)
				printf("��û�г�ʼ��\n");
			if (!j)printf("Ԫ�ز�����\n");
			else
				printf("\nԪ��%d���е�%dλ��\n",e,j);
			system("pause");
			break;
		case 8:
			printf("������Ԫ��\n");
			scanf("%d", &j);
			i = PriorElem(M.Sq[count], j, k);
			if (i == -1)
			{
				printf("��û�г�ʼ��"); break;
			}
			if (i == 0)printf("���ȳ�ʼ��\n");
			else if (i == 2)printf("Ԫ�ز����ڻ�û��ǰ��\n");
			else
				printf("\n%d��ǰ��Ԫ��Ϊ%d\n",j,k);
			system("pause");
			break;
		case 9:
			printf("������Ԫ��\n");
			scanf("%d", &j);
			i = NextElem(M.Sq[count], j, k);
			if (i == -1){ printf("���ȳ�ʼ��\n"); }
			else if (i == 2)printf("Ԫ�ز����ڻ�û�к��\n");
			else
				printf("\n%d�ĺ��Ԫ��Ϊ%d\n", j, k);
			system("pause");
			break;
		case 10:
			printf("\n��������Ҫ�����Ԫ��λ��\n");
			scanf("%d", &j);
			printf("��������Ҫ����Ԫ��\n");
			scanf("%d", &k);
			i = ListInsert(M.Sq[count], j, k);
			if (i == -1)
			{
				printf("��û�г�ʼ��\n"); break;
			}
			if (i == 0)printf("�������\n");
			else
				printf("\n����ɹ�\n", k);
			system("pause");
			break;
		case 11:
			printf("��������Ҫɾ��Ԫ��λ��\n");
			scanf("%d", &j);
			i = ListDelete(M.Sq[count], j, k);
			if (i == -1)
			{
				printf("��û�г�ʼ��\n"); break;
			}
			if (i == 0)printf("�������\n");
			else
				printf("\nɾ���ɹ�,ɾ��Ԫ��Ϊ%d\n",k);
			system("pause");
			break;
		case 12:  
			i = ListTrabverse(M.Sq[count]);
			if (i == -1){ printf("��û�г�ʼ��\n");}
			if (i==0) printf("���Ա��ǿձ�\n");
			system("pause");
			break;
		case 13:
			if (ListSave(M.Sq[count]) == -1){ printf("��û�г�ʼ��"); break; }
			else printf("����ɹ�!\n");
			system("pause");
			break;
		case 14:
			i = List_Load_from_File(M.Sq[count]);
			if (i==0){ printf("����ʧ��!\n"); }
			else{ printf("����ɹ�!\n");}
			system("pause");
			break;
		case 15:
			Add_List(M);
			printf("��ӱ�%d�ɹ�\n",M.length+1);
			count = M.length;
			system("pause");
			break;
		case 16:
			if (M.length == 0){ printf("��ǰ��û�б����\n"); }
			else{
				if (count < M.length)count++;
				else count =0;
				printf("�Ѿ��л�����%d\n", count+1);
			}
			system("pause");
			break;
		case 17:
			if (M.length == 0){ printf("��ǰ��û�б����\n"); }
			else{
				if (Delete_List(M, count))printf("�Ѿ�ɾ����%d\n", count+1);
				else
					printf("ɾ��ʧ��\n");
				count--;
			}
			system("pause");
			break;
		case 0:break;
		}
	}
	printf("��ӭ�´�ʹ�ñ�ϵͳ\n");
}
status IntiaList(SqList &L)
{
	if (L.flag==1)return -1;         //L.flag==1,˵��˳����Ѿ�������ʼ����Ϊ�����˷ѣ���Ӧ��Ϊ�����룬ֱ�ӷ���
	else
	{
		L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
		if (!L.elem)return ERROR;
		L.flag = 1;                  //��flag��Ϊ1������Ѿ�������ʼ��
		L.length = 0;
		L.listsize = LIST_INIT_SIZE;
		return OK;
	}
}
status ListInsert(SqList &L, int i, ElemType e)
{
	if (i<1 || i>L.length+1)return ERROR;           //����λ�ò���ȷ
	if (L.flag == 0)return -1;
	if (L.length >= L.listsize)                     //������Ϊ�䶯̬���ӿռ�
	{
		L.elem = (ElemType*)realloc(L.elem, (LISTINCREMENT + L.listsize)*sizeof(ElemType));
		if (!L.elem)return ERROR;
		L.listsize += LISTINCREMENT;
	}
	++L.length;
	int j = L.length;
	for (; j >= i; j--)L.elem[j] = L.elem[j - 1];   //�������ҵ�����λ��
	L.elem[i - 1] = e;                              //��ɲ���
	return OK;
}
status DestroyList(SqList &L)
{
	if (L.flag == 0)return -1;      //flagΪ0��˵��������
	else
	{
		L.flag = 0;                 //�ͷſռ䣬������־��Ϊ0
		free(L.elem);
		return OK;
	}
	
}
status ClearList(SqList &L)
{
	if (L.flag==0)return -1;
	else L.length = 0;             //����Ϊ0����ձ�
	return OK;
}
int ListLength(SqList L,ElemType &e)
{
	if (L.flag==0)return -1;        //���жϱ��Ƿ����
	e = L.length;
	return OK;
}
status ListEmpty(SqList L)
{
	if (L.flag==0)return -1;         //���жϱ��Ƿ����
	if (L.length == 0)return 0;		 //��Ϊ0��˵����Ϊ��
	else return 1;
}
status GetElem(SqList &L, int i, ElemType &e)
{
	if (L.flag==0)return -1;			 //���жϱ��Ƿ����
	if (i<1 || i>L.length)return ERROR; //��ȡԪ�ص�λ�ò���ȷ
	e = L.elem[i-1];
	return OK;
}
status LocateElem(SqList L, ElemType e)
{
	int i = 1,j=0;
	if (L.flag == 0)return -1;          //���жϱ��Ƿ����
	while (i <= L.length&&L.elem[j++]!=e)i++;    //����Ԫ��
	if (i <= L.length)return i;
	else return 0;
}
status PriorElem(SqList L, ElemType cur, ElemType &pre_e)
{
	if (L.flag == 0)return -1;           //���жϱ��Ƿ����
	int i = 0;
	while (L.elem[i] != cur)i++;         //����Ԫ��λ��
	if (i == 0)return 2;                 //��һ��Ԫ�أ�û��ǰ��
	else
		pre_e = L.elem[i - 1];           //����Ԫ��
	return OK;
}
status NextElem(SqList L, ElemType cur, ElemType &next_e)
{
	if (L.flag==0)return -1;             //���жϱ��Ƿ����
	int i=0;
	while (L.elem[i] != cur&&i<L.length)i++;
	if (i == L.length-1)return 2;              //��βԪ��û�к��
	else if (L.elem[i] != cur)return 2;        //Ԫ��û���ҵ�
	else 
		next_e = L.elem[i + 1];
	return OK;
}
status ListDelete(SqList &L, int i, ElemType &e)
{
	if (L.flag == 0)return -1;
	if ((i<1 )||( i>L.length))return ERROR;          //Ԫ��λ�ô���
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
	if (L.flag == 0)return -1;              //���жϱ��Ƿ����
	if (L.length==0)return ERROR;
	int i = 0;
	while (i <= L.length-1)printf("\n%d\t", L.elem[i++]);  //����˳���
	printf("\n");
	return OK;
}
status ListSave(SqList &L)
{
	if (L.flag == 0)return -1;
	FILE *fout;
	fout = fopen("D://abc.txt", "w");
	for (int i = 0; i < L.length; i++)
		fwrite(&L.elem[i], sizeof(int), 1, fout);//�ѱ��е�����д�뵽�ļ��б���
	fclose(fout);
	return OK;
}
status List_Load_from_File(SqList&L)
{
	printf("1. ��յ�ǰ������    2. ���ص���ǰ���\n");
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
		if (L.flag == 0){ printf("��ǰ������!\n"); flag = 0; }
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
		printf("�������\n");
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
