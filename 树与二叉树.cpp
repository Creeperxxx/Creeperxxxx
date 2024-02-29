#include <iostream>
using namespace std;
#define MAXSIZE 100
#define TElemType int
//�ȣ������������	*���Ķȣ����н��ȵ����ֵ

//typedef struct
//{
//	int data;
//	void (*print)(TElemType T);
//}TElemType;

typedef struct BiNode
{
	TElemType data;
	struct BiNode* Ichild;
	struct BiNode* Rchild;
}BiNode,*Bitree;

typedef struct
{
	BiNode data[MAXSIZE];
	int front;
	int rear;
}BTQueue;

typedef struct TriTNode
{
	TElemType data;
	struct TriTNode* Ichild;
	struct TriTNode* parent;
	struct TriTNode* Rchild;
}TriTNode,*TriTree;//��������

typedef struct
{
	Bitree Base;
	Bitree Top;
	int StackSise;
}BTStack;

typedef struct BiThrNode//����������
{
	int data;
	int ilag;
	int rtag;
	struct BiThrNode* ichild;
	struct BiThrNode* rchild;
}BiThrNode, * BiThrTree;

//���Ĵ洢
typedef struct
{
	int data;
	int parent;
}PTNode;

typedef struct//��˫������
{
	PTNode nodes[MAXSIZE];
	int r;
	int n;
}PTree;

typedef struct CTNode
{
	int child;
	struct CTNode* next;
}CTNode,*ChildPtr;

typedef struct//�Һ�������
{
	TElemType data;
	CTNode* firstchild;
}CTBox;

typedef struct CSNode //��������洢��������ת��Ϊ������
{
	TElemType data;
	struct CSNode* firstchild;
	struct CSNode* nextsibling;
}CSNode, * CSTree;

typedef struct//�����������
{
	int weight;
	int parent;
	int ich;
	int rch;
}HTNode,*HuffmanTree;

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
void CreateBiTree(Bitree& T);
void CopyBitree(Bitree T, Bitree& NewT);
int DepthBitree(Bitree T);
int BiNodeCount(Bitree T);
int BiNodeLeafCount(Bitree T);
void CreateHuffmanTree(HuffmanTree& HT, int n);
void HuffmanSelectMin(HuffmanTree HT, int n, int& S1, int& S2);
void PrintHuffmanTree(HuffmanTree HT, int n);

int main()
{
	HuffmanTree HT=NULL;
	int n = 8;
	CreateHuffmanTree(HT, n);
	PrintHuffmanTree(HT, 2 * n - 1);
	system("pause");
	return 0;
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
}//�����������������ͺ���ֻ�����ǽ�45����48����������Ⱥ�˳�����

void InOrderTraverse(Bitree T)//ջʵ���������
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
		//	Pop_BtStack(S, *p);
			visit(p);
			p = p->Rchild;
		}
	}
}

void LevelOrder(Bitree T)//���б���������
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
}//ԭ���������ӣ����ӣ����ʣ�Ȼ������亢�ӣ��ظ�

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

//void print(TElemType T)
//{
//	printf("%d", T.data);
//	return;
//}

void CreateBiTree(Bitree& T)//�������ABC##DE#G##F###��������� #��ʾ�ս��
{
	char ch;
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		if (!(T = new BiNode))
		{
			exit(OVERFLOW);
		}
		/*T->data.data = ch;*/
		CreateBiTree(T->Ichild);//�ݹ�
		CreateBiTree(T->Rchild);
	}
	return;
}

void CopyBitree(Bitree T, Bitree& NewT)//���壺���Ƹ��ڵ�
{
	if (T == NULL)
	{
		NewT = T;
		return;
	}
	NewT = new BiNode;
	if (!NewT)
	{
		exit(OVERFLOW);
	}
	NewT->data = T->data;
	CopyBitree(T->Ichild, NewT->Ichild);//�ݹ�
	CopyBitree(T->Rchild, NewT->Rchild);
	return;
}

int DepthBitree(Bitree T)
{
	if (T == NULL)
	{
		return 0;
	}
	int m;
	int n;
	m = DepthBitree(T->Ichild);
	n = DepthBitree(T->Rchild);
	return (m > n ? m : n) + 1;
}

int BiNodeCount(Bitree T)
{
	if (T == NULL)
	{
		return 0;
	}
	return BiNodeCount(T->Ichild) + BiNodeCount(T->Rchild) + 1;
}

int BiNodeLeafCount(Bitree T)
{
	if (T == NULL)
	{
		return 0;
	}
	if (T->Ichild == NULL && T->Rchild == NULL)
	{
		return 1;
	}
	return BiNodeLeafCount(T->Ichild) + BiNodeLeafCount(T->Rchild);
}

void CreateHuffmanTree(HuffmanTree& HT, int n)
{
	if (n <= 1)
	{
		return;
	}
	int m = 2 * n - 1;
	HT = new HTNode[m+1];
	for (int i = 1; i <= m; i++)
	{
		HT[i].parent = 0;
		HT[i].ich = 0;
		HT[i].rch = 0;
	}
	
	for (int i = 1; i <= n; i++)
	{
		cin >> HT[i].weight;
	}//����Ϊ����������ʼ��
	int min1;
	int min2;
	for (int i = n + 1; i <= m; i++)
	{
		HuffmanSelectMin(HT, i-1, min1, min2);
		HT[i].weight = HT[min1].weight + HT[min2].weight;
		HT[i].ich = min1;
		HT[i].rch = min2;
		HT[min1].parent = i;
		HT[min2].parent = i;
	}
	return;
}

void HuffmanSelectMin(HuffmanTree HT, int n, int& S1, int& S2)
{
	int index = 0;
	S1 = 0;
	S2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent != 0)
		{
			continue;
		}
		if (index == 0)
		{
			S1 = i;
			index++;
			continue;
		}
		if (index == 1)
		{
			if (HT[i].weight < HT[S1].weight)
			{
				S2 = S1;
				S1 = i;
			}
			else
			{
				S2 = i;
			}
			index++;
			continue;
		}
		if (HT[i].weight <= HT[S1].weight)
		{
			S2 = S1;
			S1 = i;
		}
		else if (HT[i].weight<HT[S2].weight)
		{
			S2 = i;
		}
	}
}

void PrintHuffmanTree(HuffmanTree HT, int n)
{
	int a = 4;
	cout << "index\t" << "weight\t" << "parent\t"<<"ich\t" << "rch\t" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << i << "\t" << HT[i].weight << "\t" << HT[i].parent
			<<"\t"<<HT[i].ich << "\t"<< HT[i].rch << "\t" << endl;
	}
	return;
}