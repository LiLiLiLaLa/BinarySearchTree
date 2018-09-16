#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

typedef int BSTDataType;

typedef struct BSTreeNode
{
	struct BSTreeNode* _left;
	struct BSTreeNode* _right;
	BSTDataType _data;
}BSTreeNode;

int BSTreeInsert(BSTreeNode** ppTree, BSTDataType x);//插入一个元素（非递归）
int BSTreeRemove(BSTreeNode** ppTree, BSTDataType x);//删除一个元素（非递归）
BSTreeNode* BSTreeFind(BSTreeNode** ppTree, BSTDataType x);//查找一个元素，返回指向该节点的指针（非递归）

int BSTreeInsertR(BSTreeNode** ppTree, BSTDataType x);//插入一个元素（递归）
int BSTreeRemoveR(BSTreeNode** ppTree, BSTDataType x);//删除一个元素（递归）
BSTreeNode* BSTreeFindR(BSTreeNode** ppTree, BSTDataType x);//查找一个元素，返回指向该节点的指针（递归）

void BSTreeDestroy(BSTreeNode** ppTree);//销毁

void BSTreeInOrder(BSTreeNode** ppTree);//中序遍历

void TestBSTree();
void TestBSTreeR();