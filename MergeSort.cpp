#include "pch.h"
#include <stdio.h>
#include <stdlib.h>


/*************************************************
Function:merge
Description: 对左右两个子数组进行归并
Input: a 需要排序的数组   b  辅助存储数组   first 该段数组的起始索引   last   该段数组的末索引
*************************************************/
void merge(int * a,int * b, int first, int last) 
{
	int middle = (first + last) / 2;
	int gap = last - first;
	int i = first;
	int j = middle+1;
	int k = first;
	for (; i <= middle && j<=last;k++)
	{
		if (a[i] < a[j])
		{
			b[k] = a[i];
			i++;
		}
		else 
		{
			b[k] = a[j];
			j++;
		}
	}
	if (i <= middle)
	{
		for (; i <=middle; i++, k++)
		{
			b[k] = a[i];
		}
	}
	else
	{
		for (; j <= last; j++, k++)
		{
			b[k] = a[j];
		}
	}
	for (int flag = first; flag <= last; flag++)
	{
		a[flag] = b[flag];
	}
}

/*************************************************
Function:mergeSort1
Description: 对需要排序数组进行递归划分，划分完毕之后在进行归并
Input: a 需要排序的数组  b  辅助存储数组   first  该段的起始索引    last  该段的末索引
*************************************************/
void mergeSort1(int * a, int * b, int first, int last) 
{
	if (last-first <= 1) 
	{
		int middle = 0;
		if (a[first] > a[last]) 
		{
			middle = a[first];
			a[first] = a[last];
			a[last] = middle;
		}
		return;
	}
	mergeSort1(a, b, first, (first + last) / 2);
	mergeSort1(a, b, (first + last) / 2 + 1, last);
	merge(a, b, first, last);
	return;
}

/*************************************************
Function:mergeSort
Description: 归并排序的对外接口
Input: a   需要排序的数组   n  数组中的元素个数
*************************************************/
void mergeSort(int * a, int n)
{
	int * b=(int *)malloc(sizeof(int)*n);
	mergeSort1(a, b, 0, n-1);
	for (int i = 0; i <= n - 1; i++)
		printf_s("%d   ", a[i]);
}


int main() {
	int a[9] = { 13,30,7,6,19,1,3,10,4 };
	printf_s("原有数组：");
	for (int i = 0; i < 9; i++)
	{
		printf_s("%d  ", a[i]);
	}
	printf_s("\n排序之后：");
	mergeSort(a, 9);
	printf_s("\n");
	system("pause");
}