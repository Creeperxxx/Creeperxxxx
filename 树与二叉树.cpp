#include <iostream>
using namespace std;
#define MAXSIZE 100
//度：结点子树个数	*树的度：所有结点度的最大值

typedef struct
{
	int data;
	void (*print)(TElemType T);
}TElemType;

typedef struct
{
	BiNode data[MAXSIZE];
	int front;
	int rear;
}BTQueue;

typedef struct
{
	TElemType data;
	BiNode* Ichild;
	BiNode* Rchild;
}BiNode,*Bitree;

typedef struct
{
	TElemType data;
	struct TriTNode* Ichild;
	struct TriTNode* parent;
	struct TriTNode* Rchild;
}TriTNode,*TriTree;//三叉链表

typedef struct
{
	Bitree Base;
	Bitree Top;
	int StackSise;
}BTStack;

void BTStackInit(BTStack& S);
bool BTStackIsEmpyt(BTStack& S);
void Push_BTStack(BTStack& S, Bitree T);
void Pop_BtStack(BTStack& S, BiNode& T);
void visit(Bitree T);
void PreOrderTraverse_Bt(Bitree T);
void InOrderTraverse(Bitree T);
void LevelOrder(Bitree T);
void BTQueueInit(BTQueue& Q);
bool BTQueueIsEmpty(BTQueue& Q);
void EnBTQueue(BTQueue& Q,Bitree T);
void DeBTQueue(BTQueue& Q, Bitree T);

int main()
{
	return;
}

void BTStackInit(BTStack& S)
{
	S.Base = new BiNode[MAXSIZE];
	if (!S.Base)
	{
		exit(OVERFLOW);
	}
	S.Top = S.Base;
	S.StackSise = MAXSIZE;
}

bool BTStackIsEmpyt(BTStack& S)
{
	if (S.Base == S.Top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Push_BTStack(BTStack& S, Bitree T)
{
	if (S.Top - S.Base == S.StackSise)
	{
		exit(OVERFLOW);
	}
	*S.Top++ = *T;
}

void Pop_BtStack(BTStack& S, BiNode& T)
{
	if (S.Base == S.Top)
	{
		exit(OVERFLOW);
	}
	S.Top--;
	T = *S.Top;
}

void visit(Bitree T)
{
	return;
}

void PreOrderTraverse_Bt(Bitree T)
{
	if (T == NULL)
	{
		return;
	}
	visit(T);
	PreOrderTraverse_Bt(T->Ichild);
	PreOrderTraverse_Bt(T->Rchild);
}//此乃先序遍历，中序和后序只不过是将45——48按情况调换先后顺序罢了

void InOrderTraverse(Bitree T)//栈实现中序遍历
{
	Bitree p;
	p = T;
	BTStack S;
	BTStackInit(S);
	while (p || !BTStackIsEmpyt(S))
	{
		if (p)
		{
			Push_BTStack(S, p);
			p = p->Ichild;
		}
		else
		{
			Pop_BtStack(S, *p);
			visit(p);
			p = p->Rchild;
		}
	}
}

void LevelOrder(Bitree T)//队列遍历二叉树
{
	Bitree p;
	p = T;
	BTQueue qu;
	BTQueueInit(qu);
	EnBTQueue(qu, p);
	while (!BTQueueIsEmpty(qu))
	{
		DeBTQueue(qu, p);
		visit(p);
		if (p->Ichild != NULL)
		{
			EnBTQueue(qu, p->Ichild);
		}
		if (p->Rchild != NULL)
		{
			EnBTQueue(qu, p->Rchild);
		}
	}
}//原理：根结点入队，出队，访问，然后入队其孩子，重复

void BTQueueInit(BTQueue& Q)
{
	Q.front = 0;
	Q.rear = 0;
}

bool BTQueueIsEmpty(BTQueue& Q)
{
	if (Q.front == Q.rear)
	{
		return true;
	}
	return false;
}

void EnBTQueue(BTQueue& Q,Bitree T)
{
	if ((Q.rear - Q.front + 1) % MAXSIZE == 0)
	{
		exit(OVERFLOW);
	}
	Q.data[Q.rear] = *T;
	Q.rear = (Q.rear + 1) % MAXSIZE;
}

void DeBTQueue(BTQueue& Q, Bitree T)
{
	if (Q.front == Q.rear)
	{
		exit(OVERFLOW);
	}
	*T = Q.data[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
}

void print(TElemType T)
{
	printf("%d", T.data);
	return;
}
