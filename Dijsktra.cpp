#include "pch.h"
#include <stdio.h>
#include <Windows.h>


/*************************************************
Function:findMin
Description: 遍历图寻找当前路径最短的连接点
Input: weight 权值矩阵   store  辅助邻接矩阵   queue  存储访问节点的数组   n  图中元素的个数
*************************************************/
void findMin(int **weight, int **store, int queue[], int length[], int n) {
	int sum = 10000;
	int flagi = 0;
	int flagj = 0;
	for (int i = 0; i <= n - 1; i++)
	{
		if (queue[i] == 1)
		{
			for (int j = 0; j <= n - 1; j++)
			{
				if (queue[j] == -1)
				{
					if ((weight[i][j] + length[i]) < sum&&weight[i][j]>0)
					{
						flagi = i;
						flagj = j;
						sum = weight[i][j] + length[i];
					}
				}
			}
		}
	}
	queue[flagj] = 1;
	length[flagj] = sum;
	printf("%d -> %d \n", flagi, flagj);
}

/*************************************************
Function:DJ
Description: 检测是否存在最短路径，并打印结果
Input: weight 权值矩阵   store  辅助邻接矩阵   queue  存储访问节点的数组   n  图中元素的个数
*************************************************/
void DJ(int ** weight, int **store, int queue[], int length[], int n)
{
	for (int i = 1; i <= n - 1; i++)
	{
		findMin(weight, store, queue, length, n);
	}

	int sum = 0;
	for (int i = 0; i <= n - 1; i++) {
		sum += queue[i];
	}
	if (sum != n)
		printf_s("无法产生！！");
}

int main() {
	int *weight[7];
	int *store[7];
	int a[7][7] = { 0 };
	int b[7][7] = { 0 };
	for (int i = 0; i < 7; i++) {
		weight[i] = a[i];
	}
	for (int i = 0; i < 7; i++) {
		store[i] = b[i];
	}

	weight[0][1] = 2;
	weight[0][3] = 5;
	weight[1][3] = 1;
	weight[1][4] = 10;
	weight[2][0] = 4;
	weight[2][5] = 5;
	weight[3][2] = 2;
	//weight[3][4] = 2;
	weight[3][5] = 3;
	//weight[3][6] = 4;
	weight[4][6] = 6;
	weight[5][6] = 1;

	/*weight[0][1] = 2;
	weight[0][3] = 5;
	weight[1][3] = 1;
	weight[1][4] = 10;
	weight[2][0] = 4;
	weight[2][5] = 5;
	weight[3][2] = 2;
	weight[3][4] = 2;
	weight[3][5] = 3;*/
	int queue[7] = { 1,-1,-1,-1,-1,-1,-1 };
	int length[7] = { 0 };
	DJ(weight, store, queue, length, 7);
	system("pause");
}