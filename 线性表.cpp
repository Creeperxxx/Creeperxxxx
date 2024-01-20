#include <iostream>
using namespace std;

//线性表顺序存储
#define MAXSIZE 100
typedef struct
{
	int* Elem;
	int Length;
}SqList;

void InitList_Sq(SqList& L)
{
	L.Elem = new int[MAXSIZE];
	if (!L.Elem)
	{
		exit(OVERFLOW);
	}
	L.Length = 0;
}

void Destory_Sq(SqList& L)
{
	if (L.Elem)
	{
		delete L.Elem;
	}
	L.Length = 0;
}

int GetLength_Sq(SqList L)
{
	return L.Length;
}

bool IsEmpty_Sq(SqList L)
{
	if (L.Length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GetElem_Sq(SqList L, int i, int& e)
{
	if (i<1 || i>L.Length)
	{
		exit(OVERFLOW);
	}
	e = L.Elem[i - 1];
}

int LocateElem_Sq(SqList L, int e)
{
	for (int i = 0; i < L.Length; i++)
	{
		if (L.Elem[i] == e)
		{
			return i + 1;
		}
	}
	return -1;
}

void ElemInsert_Sq(SqList& L, int i, int e)
{
	if (i<1 || i>MAXSIZE || L.Length >= MAXSIZE)
	{
		exit(OVERFLOW);
	}
	for (int j = L.Length-1; j >= i - 1; j--)
	{
		L.Elem[j + 1] = L.Elem[j];
	}
	L.Elem[i - 1] = e;
	L.Length++;
}

void ElemDelete_Sq(SqList& L, int i, int& e)
{
	if (i<1 || i>L.Length)
	{
		exit(OVERFLOW);
	}
	e = L.Elem[i - 1];
	for (int j = i - 1; j < L.Length - 1; j++)
	{
		L.Elem[j] = L.Elem[j + 1];
	}
	L.Length--;
}

void ListUnion_Sq(SqList& La, SqList Lb)//合并ab,无排序要求
{
	int La_Len = GetLength_Sq(La);
	int Lb_Len = GetLength_Sq(Lb);
	int e;
	for (int i = 1; i <= Lb_Len; i++)
	{
		GetElem_Sq(Lb, i, e);
		if (LocateElem_Sq(La, e) == -1)
		{
			ElemInsert_Sq(La, La_Len++, e);
		}
	}
	return;
}

void ListUnionDe_Sq(SqList La, SqList Lb, SqList Lc)//合并ab,递减排序
{
	int La_Len = GetLength_Sq(La);
	int Lb_Len = GetLength_Sq(Lb);
	int* La_P = La.Elem;
	int* Lb_P = Lb.Elem;
	int Lc_Len = GetLength_Sq(Lc);
	while (La_Len && Lb_Len)
	{
		if (*La_P > *Lb_P)
		{
			ElemInsert_Sq(Lc, ++Lc_Len, *Lb_P++);
			Lb_Len--;
		}
		else
		{
			ElemInsert_Sq(Lc, ++Lc_Len, *La_P++);
			La_Len--;
		}
	}

	while (!La_Len&&Lb_Len)
	{
		ElemInsert_Sq(Lc, ++Lc_Len, *Lb_P++);
		Lb_Len--;
	}
	while (!Lb_Len && La_Len)
	{
		ElemInsert_Sq(Lc, ++Lc_Len, *La_P++);
		La_Len--;
	}
	Lc.Length = Lc_Len;
}
//线性表链式存储
typedef struct
{
	int data;
	LNode* next;
}LNode, * LinkList;

void InitList_L(LinkList& L)
{
	L = new LNode;
	L->next = NULL;
}

bool ListIsEmpty(LinkList& L)
{
	if (L->next)
	{
		return false;
	}
	return true;
}

void ListDelete_L(LinkList& L)
{
	LinkList p;
	while (L)
	{
		p = L->next;
		delete L;
		L = p;
	}
}

void ListClear_L(LinkList& L)
{
	LinkList p;
	while (L->next)
	{
		p = L->next;
		delete L;
		L = p;
	}
}

int ListLength_L(LinkList& L)
{
	LinkList p = L->next;
	int ListLength = 0;
	while (p)
	{
		p = p->next;
		ListLength++;
	}
	return ListLength;
}

void ListGetElem_L(LinkList& L, int i, int& e)
{
	LinkList p = L->next;
	int j = 0;
	while (p)
	{
		j++;
		if (i == j)
		{
			e == p->data;
		}
		p = p->next;
	}
	exit(OVERFLOW);
}

LNode* ListLocateElem_L(LinkList& L, int e)
{
	LinkList& p = L->next;
	while (p&&p->data!=e)
	{
		p = p->next;
	}
	return p;
}

void ListInsert(LinkList& L, int i, int e)
{
	LinkList p = new LNode;
	LinkList q = L;
	int j = 1;
	p->data = e;
	while (q&&i!=j++)
	{
		q = q->next;
	}
	if (!q)
	{
		exit(OVERFLOW);
	}
	p->next = q->next;
	q->next = p;
}

void ListElemDelete_L(LinkList& L, int i, int& e)
{
	LinkList q = L;
	int j = 1;
	while (q && i != j++)
	{
		q = q->next;
	}
	if (!q)
	{
		exit(OVERFLOW);
	}
	e = q->next->data;
	delete q->next;
	q->next = q->next->next;
}

void ListCreateHead_L(LinkList& L, int n)
{
	for (int i = 0; i < n; i++)
	{
		LinkList p = new LNode;
		cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}

void ListCreateTail_L(LinkList& L, int n)
{
	LinkList q = L;
	for (int i = 0; i < n; i++)
	{
		LinkList p = new LNode;
		p->next = NULL;
		cin >> p->data;
		q->next = p;
		q = p;
	}
}

void ListUnion_L(LinkList& La, LinkList& Lb, LinkList& Lc)
{
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	Lc = pa->data > pb->data ? Lb : La;
	LinkList Ld = Lc == La ? Lb : La;
	delete Ld;
	LinkList pc=Lc;
	while (pa && pb)
	{
		if (pa->data > pb->data)
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		else
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
	}
	pc->next = pa ? pa : pb;
	return;
}
//循环链表
LinkList ListConnect_L(LinkList& Ta, LinkList& Tb)
{
	LinkList p = Ta->next;
	Ta->next = Tb->next->next;
	delete Tb->next;
	Tb->next = p;
	return Tb;
}

//双向链表
typedef struct
{
	int data;
	DuLNode* prior;
	DuLNode* next;
}DuLNode,*DuLinkList;

DuLinkList ListGetElem_DuL(DuLinkList L, int i)
{
	DuLinkList p = L->next;
	int j = 1;
	while (p && i != j)
	{
		p = p->next;
	}
	return p;
}

void ListInsert_DuL(DuLinkList& L, int i, int e)
{
	DuLinkList p = ListGetElem_DuL(L, i);
	if (!p)
	{
		exit(OVERFLOW);
	}
	DuLinkList x = new DuLNode;
	x->data = e;
	p->prior->next = x;
	x->prior = p->prior;
	x->next = p;
	p->prior = x;
	return;
}

void ListDelete_DuL(DuLinkList& L, int i, int& e)
{
	DuLinkList p = ListGetElem_DuL(L, i);
	if (!p)
	{
		exit(OVERFLOW);
	}
	p->prior->next = p->next;
	p->next->prior = p->prior;
	e = p->data;
	delete p;
	return;
}