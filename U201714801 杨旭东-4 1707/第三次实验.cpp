#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define LIST_SIZE_LENGTH 20
#define LISTINCREMENT 10

typedef struct Student
{
	char name[20];
	int number;
	int birthday;
}Student;

typedef struct tree
{
	Student *Stu;
	struct tree* lchild;
	struct tree *rchild;
}BiTnode,*BiTree;



void main()
{



}