#include <iostream>
using namespace std;
#define MAXLEN 255
#define CHUNKSIZE 80

//串的顺序存储
typedef struct
{
	int data;
}SElemType;

typedef struct
{
	char ch[MAXLEN + 1];
	int length;
}SString;

//串的链式存储
typedef struct
{
	char ch[CHUNKSIZE];
	Chunk* next;
}Chunk;

typedef struct
{
	Chunk* Head;
	Chunk* Tail;
	int Curlen;
}LString;

//BF复杂版
//int Index_BF(SString S, SString T)//BF匹配法
//{
//	int i = 0;
//	int j = 0;
//	int T_Len = T.length;
//	int S_Len = S.length;
//	while (i < S_Len - T_Len + 1)
//	{
//		for (j = 0; j < T_Len; j++)
//		{
//			if (S.ch[i] == T.ch[j])
//			{
//				i++;
//			}
//			else
//			{
//				i = i - j + 1;
//				break;
//			}
//		}
//		if (j == T_Len)
//		{
//			return i - j;
//		}
//	}
//	return 0;
//}

int Index_BF(SString S, SString T)
{
	int i = 1;
	int j = 1;
	while (i <= S.length && j <= T.length)
	{
		if (S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T.length)
	{
		return i - j + 1;
	}
	else
	{
		return 0;
	}
}

//BV1C84y1q7LA
int Index_KMP(SString S, SString T, int* nextval)
{
	int i = 1;
	int j = 1;
	while (i <=S.length&&j<=T.length)
	{
		if (j==0||S.ch[i] == T.ch[j])
		{
			i++;
			j++;
		}
		else
		{
			j = nextval[j];
		}
	}
	if (j > T.length)
	{
		return i - T.length;
	}
	else
	{
		return 0;
	}
}

void Index_Next(SString patt,int* next)
{
	next[1] = 0;
	int i = 1;
	int j = 0;//j为i的next值
	while (i < patt.length)
	{
		if (j == 0 || patt.ch[i] == patt.ch[j])
		{
			next[++i] = ++j;
		}
		else
		{
			j=next[j];
		}
	}
}

void Index_Nextval(SString patt,int* next, int* nextval)
{
	int i = 1;
	int j = 0;
	next[1] = 0;
	nextval[1] = 0;
	while (i < patt.length)
	{
		if (j == 0 || patt.ch[i] == patt.ch[j])
		{
			next[++i] = ++j;
			if (patt.ch[i] != patt.ch[next[i]])
			{
				nextval[i] = next[i];
			}
			else
			{
				nextval[i] = nextval[next[i]];
			}
		}
		else
		{
			j = next[j];
		}
	}
}

//数组
//1.稀疏数组一般用三元表和以三元表为基础添加down和right(down为该元素该列下边的第一
//个数，right为该元素改行右边的第一个数

//广义表
//1.类似集合，其中元素可以是单个原子，也可以是个广义表
//2.表头：第一个元素 表尾：除表头外所有元素构成的表

