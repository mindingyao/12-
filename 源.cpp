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
	ElemType *elem;//存储空间基址
	int length;//当前长度
	int listsize; //当前分配的存储容量
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

void main()  //测试上述函数
{
    SqList L;
    ElemType e,cur_e,pre_e,next_e;
    int i;
    int j,k;

    //线性表初始化
    if(InitList(L))
        printf("线性表已建立成功！\n");
    else
        printf("线性表建立失败！\n");

    for(j=1;j<=5;j++)
        i=ListInsert(L,1,j);  //调用ListInser_Sq函数
    printf("在L的表头依次插入1——5后，L.elem=");
    ListTraverse(L);   //调用ListTraverse_Sq函数
    printf("L.length=%d\n",L.length);

    i=ListEmpty(L);  //调用ListEmpty_Sq函数
    printf("L是否空：i=%d,空为1，非空为0\n",i);
    i=ClearList(L);  //调用ListClear_Sq函数
    printf("清空后L.length=%d\n",L.length);
    i=ListEmpty(L);  //再次调用ListEmpty_Sq函数
    printf("L是否空：i=%d,空为1，非空为0\n",i);

    for(j=1;j<=10;j++)
        i=ListInsert(L,1,j);  //调用ListInser_Sq函数
    printf("在L的表头依次插入1——10后，L.elem=");
    ListTraverse(L);   //调用ListTraverse_Sq函数
    printf("L.length=%d\n",L.length);
    pre_e=PriorElem(L,3,pre_e);  //找3的前驱元素
    printf("3的前驱元素是%d",pre_e);
    next_e=NextElem(L,3,next_e);  //找3的后驱元素
    printf("3的后驱元素是%d",next_e);
    GetElem(L,5,e);   //调用GetElem_Sq函数
    printf("第5 个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j); //调用LocateElem_Sq函数
        if(k)
            printf("第%d 个元素的值为%d\n",k,j);
        else
            printf("没有值为%d 的元素\n",j);
    }
  
    k=ListLength(L); //k 为表长
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(L,j,e); //删除第j 个数据
        if(i==ERROR)
            printf("删除第%d 个数据失败\n",j);
        else
            printf("删除第%d 个的元素值为：%d\n",j,e);
    }
    printf("依次输出L 的元素：");
    ListTraverse(L);
}










	











