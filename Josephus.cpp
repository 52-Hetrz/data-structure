#include"pch.h"
#include<stdio.h>
#include<stdlib.h>


/*约瑟夫环中元素的结构体*/
typedef struct people {
	int numb;	/*该成员的编码*/
	people *pre;	/*成员的前一个元素*/
	people *next;	/*该成员的下一个元素*/
};

/*************************************************
Function:CreateCircle
Description: 生成一个约瑟夫环
Input: 环中的人数
Return: 约瑟夫环的1号指针
*************************************************/
people* CreateCircle(int n) {
	struct people *first, *p1, *p2, *last;
	first = (struct people *)malloc(sizeof(struct people));
	last = (struct people *)malloc(sizeof(struct people));
	p1 = (struct people *)malloc(sizeof(struct people));
	first->pre = last;
	last->next = first;
	for (int i = 1; i <= n; i++)
	{
		if (i == 1)
		{
			first->numb = i;
			p1 = first;
		}
		else if (i == n)
		{
			p1->next = last;
			last->numb = i;
			last->pre = p1;
		}
		else
		{
			p2 = (struct people*)malloc(sizeof(struct people));
			p1->next = p2;
			p2->pre = p1;
			p2->numb = i;
			p1 = p2;
		}
	}
	return first;
}

/*************************************************
Function:clear
Description: 在约瑟夫环中清除一个元素
Input: 需要清除的元素的指针
*************************************************/
void clear(people* p)
{
	printf_s("清除 ：%d \n", p->numb);
	struct people* p1, *p2;
	p1 = p->pre;
	p2 = p->next;
	p1->next = p2;
	p2->pre = p1;
}

/*************************************************
Function: find
Description: 寻找约瑟夫环问题的解
Input: n 约瑟夫环中总的人数   m 每次清除的间隔   p 约瑟夫环的一号元素的指针
*************************************************/
void find(int n, int m, people*p)
{
	struct people* p1, *p2;
	p1 = CreateCircle(n);
	for (int i = 1; i <= n - 1; i++)
	{
		for (int j = 1; j < m; j++)
		{
			p1 = p1->next;
		}
		p2 = p1->next;
		clear(p1);
		p1 = p2;
	}

	printf("最终：\n%d \n", p1->numb);

}

void main() 
{
	int n, m;
	printf_s("请输入约瑟夫环的人数：");
	scanf_s("%d", &n);
	printf_s("请输入约瑟夫环的报数间隔：");
	scanf_s("%d", &m);
	find(n, m, CreateCircle(n));
	system("pause");
}