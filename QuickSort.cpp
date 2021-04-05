#include "pch.h"
#include <stdio.h>
#include <stdlib.h>


/*************************************************
Function:insertSort
Description: 当元素数量较少时，使用插入排序
Input: a   需要排序的数组    left   需要排序数组段起始索引    right  需要排序的数组段末索引
*************************************************/
void insertSort(int a[], int left, int right) {   
	int flag;
	for (int i = left+1; i <= right; i++) {
		if (a[i] < a[i - 1]) {
			flag = a[i];
			a[i] = a[i - 1];
			a[i - 1] = flag;
			if (i > left + 1) {
				i = i - 2;
			}
		}
	}
}


/*************************************************
Function:findHub
Description: 寻找枢纽元，并对已比较的元素位置进行调整
Input: a  需要查找枢纽元的数组   left   该数组段的起始索引    right   该数组段的末索引
Return: 返回枢纽元
*************************************************/
int findHub(int * a, int left,int right) {
	int flag;
	int middle = (left+right) / 2;
	if (a[left] > a[right]) {
		flag = a[left];
		a[left] = a[right];
		a[right] = flag;
	}
	if (a[middle] > a[right]) {
		flag = a[middle];
		a[middle] = a[right];
		a[right] = flag;
	}
	if (a[left] > a[middle]) {
		flag = a[middle];
		a[middle] = a[left];
		a[left] = flag;
	}
	flag = a[middle];
	a[middle] = a[right - 1];
	a[right - 1] = flag;
	 
	return a[right - 1];
}


/*************************************************
Function:quickSort
Description: 对数组进行快排
Input: a  需要排序的数组      left  数组段的起始索引   right   数组段的末索引
*************************************************/
void quickSort(int a[], int left,int right) {
	int flag;
	if (right - left >= 3)
	{
		int hub = findHub(a, left, right);
		int i = left, j = right - 1;
		while (true)
		{
			while (a[++i] < hub) {}
			while (a[--j] > hub) {}
			if (i < j) {
				flag = a[i];
				a[i] = a[j];
				a[j] = flag;
			}
			else
				break;
		}
		flag = a[i];
		a[i] = a[right - 1];
		a[right - 1] = flag;
		quickSort(a, left, i - 1);
		quickSort(a, i + 1, right);
	}
	else
		insertSort(a, left, right);
}


int main() {
	int a[] = { 3,2,5,9,6,8,0,7,1 };
	printf_s("原有数组：\n");
	for (int i = 0; i < 9; i++)
		printf_s("%d  ", a[i]);
	quickSort(a, 0,8);
	printf_s("\n");
	printf_s("排序之后数组：\n");
	for (int i = 0; i < 9; i++)
		printf_s("%d  ", a[i]);
	printf_s("\n");
	system("pause");
}