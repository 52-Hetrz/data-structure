#include "pch.h"
#include <stdio.h>
#include <Windows.h>


/*************************************************
Function:deepCheck
Description:当将一个元素放到某个位置时，检测这个位置是否为正确的位置，如果不是正确位置，则进行交换
Input: a 要排序的数组   i 需要检测的元素索引   n  数组中的元素个数
*************************************************/
void deepCheck(int a[], int i, int n)    
{
	int middle;
	if ((2 * i + 1) <= n - 2)   //既有左子树 又有右子树
	{
	
		if (a[i] > a[2 * i + 1] &&a[i] > a[2 * i + 2]) 
		{
			return;
		}
		else 
		{
			if (a[2 * i + 1] > a[2 * i + 2]) 
			{
				middle = a[2*i+1];
				a[2 * i + 1] = a[i];
				a[i] = middle;
				deepCheck(a, 2 * i + 1, n);
			}
			else 
			{
				middle = a[2 * i + 2];
				a[2 * i + 2] = a[i];
				a[i] = middle;
				deepCheck(a, 2 * i + 2, n);
			}
		}
	}
	else if (2 * i + 1 == n - 1)    //只有左子树
	{
		if (a[2 * i + 1] > a[i]) 
		{
			middle = a[i];
			a[i] = a[2 * i + 1];
			a[2 * i + 1] = middle;
			return;
		}
	}
	else                          //无子树
		return;
}

/*************************************************
Function:makeHeap
Description: 建堆操作
Input: a 需要建堆的数组   n  数组中的元素个数
Return: 约瑟夫环的1号指针
*************************************************/
void makeHeap(int a[], int n)  
{      
	int middle;
	for (int i = n - 1; i > 0; i--) 
	{
		if (a[i] > a[(i - 1) / 2]) 
		{
			middle = a[i];
			a[i] = a[(i - 1) / 2];
			a[(i - 1) / 2] = middle;
			deepCheck(a, i, n);
		}
	}

	printf("\n建堆结果：\n");
	for (int j = 0; j < n; j++) 
	{
		printf_s("%d  ", a[j]);
	}
}


/*************************************************
Function: heapSort
Description: 对已经建好堆的数组堆排序
Input: a  需要排序的数组   n  数组中元素的个数
*************************************************/
void heapSort(int a[], int n) {

	makeHeap(a, n);
	int middle;
	for (int i = n-1; i > 0; i--)
	{
		middle = a[i];
		a[i] = a[0];
		a[0] = middle; 
		deepCheck(a, 0, i - 1);      //插入到位置时，进行检测
	}
	printf_s("\n堆排序的结果： \n");
	for (int j = 0; j < n; j++)
	{
		printf_s("%d   ", a[j]);
	}
	printf_s("\n");
}


int main() 
{
	int a[] = { 1,7,3,9,5,23,10,15 };
	printf_s("初始数组： \n");
	for (int j = 0; j < 8; j++)
	{
		printf_s("%d   ", a[j]);
	}
	heapSort(a, 8);
	system("pause");
}