#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#define NULL 0;


/*************************************************
Function:change
Description: 进制的转换
Input: numb 需要转换的十进制数   B 要转换成的进制数
Return: 返回B进制数
*************************************************/
int change(int numb, int B)
{
	int flag = 0;
	int gap = 1;
	int m;
	while (numb > 0)
	{
		flag = flag + (numb%B) * gap;
		numb = numb / B;
		gap *= 10;
	}
	return flag;
}

/*用来表示桶中数据的结构体*/
typedef struct numb {
	int n;
	numb * next;
};


/*************************************************
Function:sort
Description: 对数组进行以B为基数的基数排序
Input: map[] 需要排序的数组   N  数组中元素的个数   B  基数
*************************************************/
void sort(int map[], int N, int B)    
{
	struct numb* a[100];
	struct numb* b[100];
	int max = 0;
	int k;
	for (k = 0; k < N; k++)							 //寻找最大元素
	{
		//map[k] = change(map[k], B);
		if (map[k] > max)
			max = map[k];
	}
	for (int gap = 1; max / gap > 0; gap *= B)		//进行基数排序
	{
		int flag;
		int i;
		int l;
		for (i = 0; i < B; i++)						//建桶
		{
			a[i] = (struct numb*)malloc(sizeof(struct numb));
			a[i]->n = -1;
			a[i]->next = NULL;
			b[i] = a[i];
		}
		for (int j = 0; j < N; j++)					 //入桶
		{
			struct numb* middle = (struct numb*)malloc(sizeof(struct numb));
			middle->n = -1;
			middle->next = NULL;
			flag = (map[j] / gap) % B;
			b[flag]->n = map[j];
			b[flag]->next = middle;
			b[flag] = b[flag]->next;
		}
		for (l = 0, k = 0; l < N && k < B; k++)   //出桶
		{
			struct numb* m;
			m = a[k];
			while (m->n != -1)
			{
				map[l++] = m->n;
				m = m->next;
			}
		}
	}
}

/*************************************************
Function:creat
Description: 生成一个用来排序的数组
Input: a[] 用来盛放数字的数组  n  数组的大小  m  数组中元素的最大值
*************************************************/
void creat(int a[], int n, int m)       
{
	a[0] = m;
	for (int i = 1; i < n; i++)
	{
		a[i] = rand() % m;
	}
}

/*************************************************
Function:create1
Description: 生成一个用来排序的数组，其中的元素已经排好序
Input: a[]  用来盛放数据的数组   n 数组的大小
*************************************************/
void creat1(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		a[i] = i;
	}
}


/*************************************************
Function: create2
Description: 生成一个顺序完全颠倒的数组
Input: a[]  用俩盛放数据的数组  n  数组的大小
*************************************************/
void creat2(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		a[i] = n - i;
	}
}

void main()
{
	int a[20];
	creat(a, 20, 1000);
	printf_s("排序之前： \n");
	for (int i = 0; i < 20; i++) {
		printf_s("%d  \n", a[i]);
	}
	sort(a, 20, 10);
	printf_s("基数排序之后：\n");
	for (int i = 0; i < 20; i++) {
		printf_s("%d  \n", a[i]);
	}
	printf_s("\n");
	system("pause");
}
