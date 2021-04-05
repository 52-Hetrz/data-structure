#include "pch.h"
#include <stdio.h>
#include <stdlib.h>


/*************************************************
Function: findMaxSubsequenceSum
Description: 求一个序列的最大子序列和
Input: a 需要查找最大子序列和的序列   n 序列中所含的元素个数
Return: 返回最大子序列的和
*************************************************/
int findMaxSubsequenceSum(int * a, int n)      
{
	int max = 0;
	int sum = 0;
	for (int i = 0; i < n; i++) 
	{
		sum = sum + a[i];
		if (sum > max)
			max = sum;
		if (sum < 0)
			sum = 0;
	}
	return max;
}

int main() {
	int a[] = { 1,2,-2,5,-4,6,3 ,4};
	int b[] = { 4,-2,-3,-20,6,4,-2,5 };
	int c[] = { 1,2,3,4,-26,2,-3,4 };
	int d[] = { 2,1,-4,2,5,7,-1,-2 };
	printf_s("原有数组： ");
	for (int i = 0; i < 8; i++)
	{
		printf_s("%d ", a[i]);
	}
	printf_s("\n");
	printf_s("该序列的最大子序列的和为： \n  %d  \n", findMaxSubsequenceSum(a, 8));
	system("pause");
}