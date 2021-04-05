#include"pch.h"
#include<stdio.h>
#include<stdlib.h>

/*************************************************
Function: majority
Description: 寻找一个数组的主元
Input: A 需要查找主元的数组   n 数组中所含的元素个数
Return: 如果存在主元则返回该主元，不存在则返回-1
*************************************************/
int majority(int * A, int n)
{
	int i, count = 0, temp = A[0];
	for (i = 1; i < n; ++i)
	{
		if (A[i] == temp)
			count++;
		else {
			if (count > 0)
				count--;
			else {
				temp = A[i];
				count = 1;
			}
		}
	}
	for (i = count = 0; i < n; ++i)
	{
		if (A[i] == temp)
			count++;
	}
	if (count > n / 2)
		return temp;
	else {
		printf_s("不存在主元");
		return -1;
	}
}
void main()
{
	int a[10] = { 1,4,3,4,3,4,4,2,4,4 };
	int b[10] = { 1,1,1,2,1,4,2,2,5,6 };

	printf_s("原有数组：");
	for (int i = 0; i < 10; i++)
	{
		printf_s("%d  ", a[i]);
	}
	printf_s("\n");
	printf_s("主元：%d", majority(a, 10));
	printf_s("\n");
	system("pause");
}