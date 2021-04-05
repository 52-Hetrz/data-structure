
#include "pch.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
定义节点的结构体
 */
typedef struct treeNode 
{  
	int element;            //节点所包含的元素大小
	int fatherDirection;    //0 父节点的左支  1 父节点的右支
	int leftDeepth;         //左支的深度
	int rightDeepth;        //右支的深度
	treeNode* leftChild;    //左儿子
	treeNode* rightChild;   //右儿子
	treeNode* father;       //父节点
};

treeNode * Root;            //整棵树的根节点

/*************************************************
Function:max
Description: 求两个数中的较大的数
Input:a b 两个需要比较的数字
Return: 返回两数之中较大的数字
*************************************************/
int max(int a, int b)       //求两个数的最大值
{
	if (a >= b)
		return a;
	else
		return b;
}

/*************************************************
Function:deepth
Description: 求一个节点的深度
Input:node 需要求的节点指针
Return: 返回该节点的深度
*************************************************/
int deepth(treeNode* node)  
{
	if (node == NULL)
		return -1;
	else
		return max(node->leftDeepth, node->rightDeepth);
}

/*************************************************
Function:leftLeft
Description: 当插入到某个节点的左儿子的左子树中引起不平衡时，进行旋转调整
Input:不平衡的节点
*************************************************/
void leftLeft(treeNode * root)          
{   
	if (root->father != NULL)
	{
		treeNode * nodeFather = root->father;
		treeNode * node = root->leftChild;
		node->father = nodeFather;
		if (root->fatherDirection == 0) {
			nodeFather->leftChild = node;
			node->fatherDirection = 0;
		}
		else {
			node->fatherDirection = 1;
			nodeFather->rightChild = node;
		}
		root->father = node;
		root->leftChild = node->rightChild;
		node->rightChild = root;

		root->fatherDirection = 1;
		if (root->leftChild != NULL) {
			root->leftChild->fatherDirection = 0;
		}
		root->leftDeepth = 1 + deepth(root->leftChild);
		node->rightDeepth = 1 + deepth(node->rightChild);
		nodeFather->leftDeepth = 1 +deepth(nodeFather->leftChild);
	}
	else {
		treeNode * node = root->leftChild;
		node->father = NULL;
		root->father = node;
		root->leftChild = node->rightChild;
		node->rightChild = root;
		root->fatherDirection = 1;
		if (root->leftChild != NULL) {
			root->leftChild->fatherDirection = 0;
		}
		root->leftDeepth = 1 + deepth(root->leftChild);
		node->rightDeepth = 1 + deepth(node->rightChild);
		Root = node;
	}


	/*root->leftChild = node->leftChild;
	root->leftChild->father = root;
	node->father = root->leftChild;
	node->leftChild = root->leftChild->rightChild;
	root->leftChild->rightChild = node;
	node->fatherDirection = 1;
	node->leftChild->fatherDirection = 0;
	node->leftDeepth = 1 + max(node->leftChild->leftDeepth, node->leftChild->rightDeepth);
	root->leftChild->rightDeepth = 1 + max(node->leftDeepth, node->rightDeepth);
	root->leftDeepth = 1 + max(root->leftChild->leftDeepth, root->leftChild->leftDeepth);
	*/
}

/*************************************************
Function:rightRight
Description: 当插入到某个节点的右儿子的右子树中引起不平衡时，进行旋转调整
Input:不平衡的节点
*************************************************/
void rightRight(treeNode *root) 
{              
	if (root->father != NULL)
	{
		treeNode * nodeFather = root->father;
		treeNode * node = root->rightChild;
		node->father = nodeFather;
		if (root->fatherDirection == 0) {
			nodeFather->leftChild = node;
			node->fatherDirection = 0;
		}
		else {
			nodeFather->rightChild = node;
			node->fatherDirection = 1;
		}
		root->father = node;
		root->rightChild = node->leftChild;
		node->leftChild = root;

		root->fatherDirection = 0;
		if (root->rightChild != NULL) {
			root->rightChild->fatherDirection = 1;
		}
		root->rightDeepth = 1 + deepth(root->rightChild);
		node->leftDeepth = 1 + deepth(node->leftChild);
		nodeFather->rightDeepth = 1 + deepth(nodeFather->rightChild);
	}
	else {
		treeNode * node = root->rightChild;
		node->father = NULL;
		root->father = node;
		root->rightChild = node->leftChild;
		node->leftChild = root;
		root->fatherDirection = 0;
		if (root->rightChild != NULL) {
			root->rightChild->fatherDirection = 1;
		}
		root->rightDeepth = 1 + deepth(root->rightChild);
		node->leftDeepth = 1 + deepth(node->leftChild);
		Root = node;
	}

	/*treeNode * node = root->rightChild;
	root->rightChild = node->rightChild;
	root->rightChild->father = root;
	node->father = root->rightChild;
	node->rightChild = root->rightChild->leftChild;
	root->rightChild->leftChild = node;
	node->fatherDirection = 0;
	node->rightChild->fatherDirection = 1;
	node->rightDeepth = 1 + max(node->rightChild->leftDeepth, node->rightChild->rightDeepth);
	root->rightChild->leftDeepth = 1 + (node->leftDeepth, node->rightDeepth);
	root->rightDeepth = 1 + max(root->rightChild->rightDeepth, root->rightChild->leftDeepth);
	*/
}

/*************************************************
Function:leftRight
Description: 当插入到某个节点的左儿子的右子树中引起不平衡时，进行旋转调整
Input:不平衡的节点
*************************************************/
void leftRight(treeNode* root) {
	rightRight(root->leftChild);
	leftLeft(root);
}

/*************************************************
Function:rightLeft
Description: 当插入到某个节点的右儿子的左子树中引起不平衡时，进行旋转调整
Input:不平衡的节点
*************************************************/
void rightLeft(treeNode* root) {
	leftLeft(root->rightChild);
	rightRight(root);
}

/*************************************************
Function:changeDeepth
Description: 插入一个节点时，对他的父节点进行深度调整
Input:插入的节点
*************************************************/
void changeDeepth(treeNode * sonNode) {          //传入插入的节点 改变其所有父节点的

	treeNode* node = sonNode;
	while (abs(node->leftDeepth - node->rightDeepth) < 2 && node->father!= NULL) {
		if (node->fatherDirection == 0)
			node->father->leftDeepth = 1 + deepth(node);
		else
			node->father->rightDeepth = 1 + deepth(node);
		node = node->father;
	}
	if (abs(node->leftDeepth - node->rightDeepth) >= 2) {
		if (node->leftDeepth > node->rightDeepth&&node->leftChild->leftDeepth > node->leftChild->rightDeepth)
			leftLeft(node);
		else if (node->leftDeepth > node->rightDeepth&&node->leftChild->rightDeepth > node->leftChild->leftDeepth)
			leftRight(node);
		else if (node->rightDeepth > node->leftDeepth&&node->rightChild->rightDeepth > node->rightChild->leftDeepth)
			rightRight(node);
		else
			rightLeft(node);
	}
}

/*************************************************
Function:insert
Description: 将一个数字插入到AVL树中
Input:root AVL树的根节点   element 要插入的数字
*************************************************/
void insert(treeNode* root, int element) {
	

		treeNode * node = root;
		for (; node != NULL;)                  //for循环实现节点的插入
		{
			if (element > node->element)
			{
				if (node->rightChild != NULL)
					node = node->rightChild;
				else
					break;
			}
			else if (element < node->element)
			{
				if (node->leftChild != NULL)
					node = node->leftChild;
				else
					break;
			}
		}
		treeNode * newNode = (struct treeNode *)malloc(sizeof(struct treeNode));
		newNode->element = element;
		newNode->leftDeepth = 0;
		newNode->rightDeepth = 0;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->father = node;
		if (element > node->element) {
			node->rightDeepth += 1;
			node->rightChild = newNode;
			newNode->fatherDirection = 1;
			if (node->leftChild == NULL)
				changeDeepth(newNode);
		}
		else {
			node->leftDeepth += 1;
			newNode->fatherDirection = 0;
			node->leftChild = newNode;
			if (node->rightChild == NULL)
				changeDeepth(newNode);
		}
}

void FprintTree(treeNode *node) {
	if (node != NULL) {
		printf_s("%d \n", node->element);
		FprintTree(node->leftChild);
		FprintTree(node->rightChild);
	}
	
}
void MprintTree(treeNode * node) {
	if (node != NULL) {
		FprintTree(node->leftChild);
		printf_s("%d \n", node->element);
		FprintTree(node->rightChild);
	}
}

int main() {
	int a[] = {7,23,-1,1,2};    //测试左儿子的右子树
	int b[] = { 1,23,17,12,7,14,13,15,16 };    //测试左儿子的左子树，右儿子的右子树，右儿子的左子树,左儿子左子树
	treeNode * root=(struct treeNode*)malloc(sizeof(struct treeNode));
	root->element = 0;
	root->father = NULL;
	root->leftChild = NULL;
	root->rightChild = NULL;
	root->leftDeepth = 0;
	root->rightDeepth = 0;
	root->fatherDirection = 0;
	Root = root;
	for (int i = 0; i < 9; i++) {
		insert(Root, b[i]);
	}
	printf_s("先序");
	FprintTree(Root);
	printf_s("中序");
	MprintTree(Root);

	system("pause");
}