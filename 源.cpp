#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define TRUE 1  
#define FALSE 0  
#define OK 1  
#define ERROR 0  
#define INFEASIBLE -1  
#define OVERFLOW -2  
  
#define LIST_INST_SIZE 5  
#define LISTINCREMENT 1  

typedef int Status;
typedef int ElemType;

typedef struct
{
	ElemType *elem;//�洢�ռ��ַ
	int length;//��ǰ����
	int listsize; //��ǰ����Ĵ洢����
}SqList;

Status InitList(SqList &L)
{
	L.elem = (ElemType *)malloc(LIST_INST_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);
    L.length = 0;
	L.listsize = LIST_INST_SIZE;
}

Status DestroyList(SqList &L)
{
	if(L.elem == NULL)
		return ERROR;
	else
	{
		free(L.elem);
		L.length = 0;
		L.listsize = 0;
		return OK;
	}
}

Status ClearList(SqList &L)
{
	if(L.elem == NULL)
		return ERROR;
	else
	{
		L.length = 0;
		return OK;
	}
}

Status ListEmpty(SqList &L)
{
	if(L.length = 0)
		return true;
	else 
		return false;
}

Status ListLength(SqList &L)
{
	return L.length;
}

Status GetElem(SqList L,int i,ElemType &e)
{
	if(i<1 || (i>L.length))
		return OVERFLOW;
	e = *(L.elem +i-1);
	return OK;
}

int LocateElem(SqList L,ElemType e)
{
   int i;
   ElemType *p;
   p = L.elem;
   while(i<=L.length && (*p++!=e))
	   i++;
   if(i<=L.length)
	   return i;
   else
	   return 0;
}

Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
{
	int i =2;
	ElemType *p = L.elem+1;
	while(i<=L.length && *p++!=cur_e)
	{
		p++;
		i++;
	}
	if(i>L.length)
		return INFEASIBLE;
	else
	{
		pre_e = *--p;
		return OK;
	}
}

Status NextElem(SqList L,ElemType cur_e,ElemType &next_e)
{
	int i =1;
	ElemType *p = L.elem;
	while(i<L.length && *p++!=cur_e)
	{
		p++;
		i++;
	}
	if(i==L.length)
		return INFEASIBLE;
	else
	{
		next_e = *++p;
		return OK;
	}
}

Status ListInsert(SqList &L,int i,ElemType e)
{
	ElemType *newbase,*q,*p;
	if(i<1||i>L.length+1)
		return ERROR;
	if(L.length>L.listsize)
	{
		newbase = (ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase)
			return ERROR;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	q = L.elem+i-1;
	for(p = L.elem+L.length - 1;p>=q;--p)
		*(p+1) = *p;

		*q = e;
		++L.length;
		return OK;
}

Status ListDelete(SqList &L,int i,ElemType &e)
{
    ElemType *p,*q;
	if(i<1||i>L.length)
		return ERROR;
	p = L.elem +i-1;
	e = *p;
	q = L.elem+L.length-1;
	for(++p;p<=q;++p)
		*(p-1)=*p;
	L.length--;
	return OK;
}

Status ListTraverse(SqList L)
{
	ElemType *p;
	int i;
	p = L.elem;
	for(i=1;i>L.length;i++)
	{
		printf("%d\n",*p++);
	}
	return OK;
}

void main()  //������������
{
    SqList L;
    ElemType e,cur_e,pre_e,next_e;
    int i;
    int j,k;

    //���Ա��ʼ��
    if(InitList(L))
        printf("���Ա��ѽ����ɹ���\n");
    else
        printf("���Ա���ʧ�ܣ�\n");

    for(j=1;j<=5;j++)
        i=ListInsert(L,1,j);  //����ListInser_Sq����
    printf("��L�ı�ͷ���β���1����5��L.elem=");
    ListTraverse(L);   //����ListTraverse_Sq����
    printf("L.length=%d\n",L.length);

    i=ListEmpty(L);  //����ListEmpty_Sq����
    printf("L�Ƿ�գ�i=%d,��Ϊ1���ǿ�Ϊ0\n",i);
    i=ClearList(L);  //����ListClear_Sq����
    printf("��պ�L.length=%d\n",L.length);
    i=ListEmpty(L);  //�ٴε���ListEmpty_Sq����
    printf("L�Ƿ�գ�i=%d,��Ϊ1���ǿ�Ϊ0\n",i);

    for(j=1;j<=10;j++)
        i=ListInsert(L,1,j);  //����ListInser_Sq����
    printf("��L�ı�ͷ���β���1����10��L.elem=");
    ListTraverse(L);   //����ListTraverse_Sq����
    printf("L.length=%d\n",L.length);
    pre_e=PriorElem(L,3,pre_e);  //��3��ǰ��Ԫ��
    printf("3��ǰ��Ԫ����%d",pre_e);
    next_e=NextElem(L,3,next_e);  //��3�ĺ���Ԫ��
    printf("3�ĺ���Ԫ����%d",next_e);
    GetElem(L,5,e);   //����GetElem_Sq����
    printf("��5 ��Ԫ�ص�ֵΪ��%d\n",e);
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j); //����LocateElem_Sq����
        if(k)
            printf("��%d ��Ԫ�ص�ֵΪ%d\n",k,j);
        else
            printf("û��ֵΪ%d ��Ԫ��\n",j);
    }
  
    k=ListLength(L); //k Ϊ��
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(L,j,e); //ɾ����j ������
        if(i==ERROR)
            printf("ɾ����%d ������ʧ��\n",j);
        else
            printf("ɾ����%d ����Ԫ��ֵΪ��%d\n",j,e);
    }
    printf("�������L ��Ԫ�أ�");
    ListTraverse(L);
}










	











