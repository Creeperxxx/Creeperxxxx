#include <iostream>
#define MAXSIZE 100
using namespace std;

//顺序栈

typedef struct
{
	int data;
}SElemType;

typedef struct
{
	SElemType* Top;
	SElemType* Base;
	int StackSize;
}SqStack;

void StackInit(SqStack& S)
{
	S.Base = new SElemType[MAXSIZE];
	if (!S.Base)
	{
		exit(OVERFLOW);
	}
	S.Top = S.Base;
	S.StackSize = MAXSIZE;
}

bool StackIsEmpty(SqStack S)
{
	if (S.Top == S.Base)
	{
		return true;
	}
	return false;
}

int StackLength(SqStack S)
{
	return S.Top - S.Base;
}

void StackClear(SqStack& S)
{
	if (S.Base)
	{
		S.Top = S.Base;
	}
}

void StackDelete(SqStack& S)
{
	if (S.Base)
	{
		delete S.Base;
		S.Base = NULL;
		S.Top = NULL;
		S.StackSize = 0;
	}
}

void StackPush(SqStack& S, SElemType e)
{
	if (S.Top - S.Base == S.StackSize)
	{
		exit(OVERFLOW);
	}
	*S.Top++ = e;
}

void StackPop(SqStack& S, SElemType& e)
{
	if (S.Top == S.Base)
	{
		exit(OVERFLOW);
	}
	e = *--S.Top;
}

//链栈

typedef struct
{
	SElemType data;
	StackNode* next;
}StackNode,*LinkStack;

void StackInit(LinkStack& S)
{
	S = NULL;
}

bool StackIsEmpty(LinkStack S)
{
	if (!S)
	{
		return true;
	}
	return false;
}

void StackPush(LinkStack& S, SElemType e)
{
	LinkStack p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
}

void StackPop(LinkStack& S, SElemType& e)
{
	if (!S)
	{
		exit(OVERFLOW);
	}
	LinkStack p = S;
	e = S->data;
	S = S->next;
	delete p;
	p = NULL;
}

//队列->循环队列 
#define MAXQSIZE 100
typedef struct
{
	int data;
}QElemType;

typedef struct
{
	QElemType* base;
	int front;
	int rear;
}SqQueue;

void QueueInit(SqQueue& Q)
{
	Q.base = new QElemType[MAXQSIZE];
	if (!Q.base)
	{
		exit(OVERFLOW);
	}
	Q.front = 0;
	Q.rear = 0;
}

int QueueGetLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

void QueueEn(SqQueue& Q, QElemType e)//留一个空间不用
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front)
	{
		exit(OVERFLOW);
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}

void QueueDe(SqQueue& Q, QElemType& e)
{
	if (Q.front == Q.rear)
	{
		exit(OVERFLOW);
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}

QElemType QueueGetHead(SqQueue Q)
{
	return Q.base[Q.front];
}

//链队

typedef struct
{
	QElemType data;
	QNode* next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void LinkQueueInit(LinkQueue& Q)
{
	Q.front = new QNode;
	if (!Q.front)
	{
		exit(OVERFLOW);
	}
	Q.rear = Q.front;
	Q.front = NULL;
}

void LinkQueueDestory(LinkQueue& Q)
{
	while (Q.front)
	{
		QueuePtr p = Q.front->next;
		delete Q.front;
		Q.front = p;	
	}
	Q.rear = NULL;
}

void LinkQueueEn(LinkQueue& Q, QElemType e)
{
	QueuePtr p = new QNode;
	if (!p)
	{
		exit(OVERFLOW);
	}
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
}

void LinkQueueDe(LinkQueue& Q, QElemType& e)
{
	if (!Q.front->next)
	{
		exit(OVERFLOW);
	}
	QueuePtr p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	if (p == Q.rear)
	{
		Q.rear = Q.front;
	}
	delete p;
}

void LinkQueueGetHead(LinkQueue Q, QElemType& e)
{
	if (!Q.front->next)
	{
		exit(OVERFLOW);
	}
	e = Q.front->next->data;
}