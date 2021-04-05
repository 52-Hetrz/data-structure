#include "pch.h"
#include <stdio.h>
#include <stdlib.h>


/*************************************************
Function:findMin
Description: 遍历图寻找当前路径最短的连接点
Input: weight 权值矩阵   store  辅助邻接矩阵   queue  存储访问节点的数组   n  图中元素的个数
*************************************************/
void findMin(int ** weight, int **store, int queue[], int n) {
	int min = 100000;
	int flagi = 0, flagj = 0;
	for (int i = 0; i <= n - 1; i++)
	{
		if (queue[i] == 1)
		{
			for (int j = 0; j <= n - 1; j++)
			{
				if (queue[j] != 1)
				{
					if (weight[i][j] > 0 && weight[i][j] < min) {
						min = weight[i][j];
						flagi = i;
						flagj = j;
					}
				}
			}
		}
	}
	printf_s("%d——%d   \n", flagi, flagj);
	weight[flagi][flagj] = -1;
	store[flagi][flagj] = 1;
	queue[flagj] = 1;
}


/*************************************************
Function:MST
Description: 生成一个图的最小生成树，并打印结果
Input: weight 权值矩阵   store  辅助邻接矩阵   queue  存储访问节点的数组   n  图中元素的个数
*************************************************/
void MST(int **weight, int **store, int queue[], int n)
{
	int min = 100000;
	int flagi = 0, flagj = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n - 1; j++)
		{
			if (weight[i][j] > 0 && weight[i][j] < min)
			{
				min = weight[i][j];
				flagi = i;
				flagj = j;
			}
		}
	}
	printf_s("%d——%d   \n", flagi, flagj);
	weight[flagi][flagj] = -1;
	store[flagi][flagj] = 1;
	queue[flagi] = 1;
	queue[flagj] = 1;

	for (int i = 1; i <= n - 2; i++)
	{
		findMin(weight, store, queue, n);
	}

	int sum = 0;
	for (int i = 0; i <= n - 1; i++)
		sum += queue[i];
	if (sum != n)
		printf_s("无法构成最小生成树!!!");
}

int main() {
	int *weight[5];
	int *store[5];
	int a[5][5] = { 0 };
	int b[5][5] = { 0 };
	for (int i = 0; i < 5; i++) {
		weight[i] = a[i];
	}
	for (int i = 0; i < 5; i++) {
		store[i] = b[i];
	}
	weight[0][1] = 6;
	weight[0][3] = 1;
	weight[0][4] = 2;
	weight[1][2] = 2;
	weight[1][4] = 7;
	weight[3][4] = 3;
	weight[1][0] = 6;
	weight[3][0] = 1;
	weight[4][0] = 2;
	weight[2][1] = 2;
	weight[4][1] = 7;
	weight[4][3] = 3;
	weight[2][4] = 1;
	weight[4][2] = 1;
	/*weight[0][1] = 4;
	weight[1][0] = 4;
	weight[0][4] = 2;
	weight[4][0] = 2;
	weight[1][4] = 1;
	weight[4][1] = 1;*/
	printf_s("最短路径如下：\n");
	int queue[5] = { -1,-1,-1,-1,-1 };
	MST(weight, store, queue, 5);
	system("pause");
}