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

int BSTreeInsert(BSTreeNode** ppTree, BSTDataType x);//����һ��Ԫ�أ��ǵݹ飩
int BSTreeRemove(BSTreeNode** ppTree, BSTDataType x);//ɾ��һ��Ԫ�أ��ǵݹ飩
BSTreeNode* BSTreeFind(BSTreeNode** ppTree, BSTDataType x);//����һ��Ԫ�أ�����ָ��ýڵ��ָ�루�ǵݹ飩

int BSTreeInsertR(BSTreeNode** ppTree, BSTDataType x);//����һ��Ԫ�أ��ݹ飩
int BSTreeRemoveR(BSTreeNode** ppTree, BSTDataType x);//ɾ��һ��Ԫ�أ��ݹ飩
BSTreeNode* BSTreeFindR(BSTreeNode** ppTree, BSTDataType x);//����һ��Ԫ�أ�����ָ��ýڵ��ָ�루�ݹ飩

void BSTreeDestroy(BSTreeNode** ppTree);//����

void BSTreeInOrder(BSTreeNode** ppTree);//�������

void TestBSTree();
void TestBSTreeR();