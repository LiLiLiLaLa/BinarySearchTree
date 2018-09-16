#include "BinarySearchTree.h"

BSTreeNode* BuyBSTreeNode(BSTDataType x)
{
	BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	node->_left = NULL;
	node->_right = NULL;
	node->_data = x;
	return node;
}

int BSTreeInsert(BSTreeNode** ppTree, BSTDataType x)
{
	BSTreeNode* cur = NULL;
	BSTreeNode* parent = NULL;
	//����
	if (*ppTree == NULL)
	{
		*ppTree = BuyBSTreeNode(x);
		return 1;
	}
	cur = *ppTree;
	while (cur)
	{
		//С�ڵ�ǰ������
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		//���ڵ�ǰ������
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		//���뵱ǰ������
		else
		{
			return 0;
		}
	}
	//�ߵ��˴�֤��cur=NULL,��һ��λ��Ϊparent
	if (parent->_data < x)
	{
		parent->_right = BuyBSTreeNode(x);//����parent�����ұ�
	}
	else
	{
		parent->_left = BuyBSTreeNode(x);//С�ڲ������
	}
	return 1;
}

int BSTreeRemove(BSTreeNode** ppTree, BSTDataType x)
{
	BSTreeNode* cur = NULL;
	BSTreeNode* parent = NULL;
	cur = *ppTree;
	while (cur)
	{
		if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_data>x)
		{
			parent = cur;
			cur = cur->_left;
		}
		else
		{
			//��ʼɾ��
			//��Ϊ��
			if (cur->_left == NULL)
			{
				//�п���ɾ����Ԫ���ڸ��ڵ㣬��ô����parentΪ��
				if (parent == NULL)
				{
					*ppTree = cur->_right;
				}
				else
				{
					if (cur == parent->_left)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
				}
			}
			//��Ϊ��
			else if (cur->_right == NULL)
			{
				if (parent == NULL)
				{
					*ppTree = cur->_left;
				}
				else
				{
					if (cur == parent->_left)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
				}
			}
			else
			{
				BSTreeNode* replace = cur->_right;
				while (replace->_left)
				{
					replace = replace->_left;
				}
				cur->_data = replace->_data;
				return BSTreeRemove(&cur->_right, replace->_data);
			}
			free(cur);
			return 1;
		}
	}
	//û�ҵ�
	return 0;
}

BSTreeNode* BSTreeFind(BSTreeNode** ppTree, BSTDataType x)
{
	BSTreeNode* cur = *ppTree;
	while (cur)
	{
		if (cur->_data < x)
		{
			cur = cur->_right;
		}
		else if (cur->_data>x)
		{
			cur = cur->_left;
		}
		else
		{
			return cur;
		}
	}
	//curΪ��
	return NULL;
}

int BSTreeInsertR(BSTreeNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		*ppTree = BuyBSTreeNode(x);
		return 1;
	}
	if ((*ppTree)->_data > x)
	{
		return BSTreeInsert(&((*ppTree)->_left), x);
	}
	else if ((*ppTree)->_data < x)
	{
		return BSTreeInsert(&((*ppTree)->_right), x);
	}
	//�����Ԫ���Ѵ���
	else
		return 0;
}

int BSTreeRemoveR(BSTreeNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		return -1;
	}
	if ((*ppTree)->_data < x)
	{
		return BSTreeRemoveR(&((*ppTree)->_right), x);
	}
	else if ((*ppTree)->_data > x)
	{
		return BSTreeRemoveR(&((*ppTree)->_left), x);
	}
	//�ҵ�x
	else
	{
		BSTreeNode* del = *ppTree;
		if ((*ppTree)->_left == NULL)
		{
			*ppTree = (*ppTree)->_right;
			free(del);
		}
		else if ((*ppTree)->_right = NULL)
		{
			*ppTree = (*ppTree)->_left;
			free(del);
		}
		//���Ҿ���Ԫ��
		else
		{
			BSTreeNode* replace = (*ppTree)->_right;
			//�ҵ�Ҫɾ�������������С��һ��
			while (replace->_left)
			{
				replace = replace->_left;
			}
			//���ҵ��������滻��ԭ��x�Ľ�㴦
			(*ppTree)->_data = replace->_data;
			//ɾ����x�滻��ֵ�ı�����㣬����x��������С��һ�����ض������½ǣ�ɾ���������remove������ǰ����������������Ϊ�յ����
			return BSTreeRemoveR(&((*ppTree)->_right), replace->_data);
		}
	}
	return 1;
}

BSTreeNode* BSTreeFindR(BSTreeNode** ppTree, BSTDataType x)
{
	//��������ʧ��
	if (*ppTree == NULL)
	{
		return NULL;
	}
	if ((*ppTree)->_data > x)
	{
		return BSTreeFindR(&((*ppTree)->_left), x);
	}
	else if ((*ppTree)->_data < x)
	{
		return BSTreeFindR(&((*ppTree)->_right), x);
	}
	//�ҵ���
	else
	{
		return *ppTree;
	}
}

void BSTreeDestroy(BSTreeNode** ppTree)
{
	if ((*ppTree) == NULL)
	{
		return;
	}
	BSTreeDestroy(&((*ppTree)->_left));
	BSTreeDestroy(&((*ppTree)->_right));
	free(*ppTree);
	*ppTree = NULL;
}

void BSTreeInOrder(BSTreeNode** ppTree)
{
	if (*ppTree == NULL)
	{
		return;
	}
	BSTreeInOrder(&(*ppTree)->_left);
	printf("%d ", (*ppTree)->_data);
	BSTreeInOrder(&(*ppTree)->_right);
}

void TestBSTree()
{
	int i = 0;
	BSTreeNode* tree = NULL;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (i; i < (sizeof(a) / sizeof(a[0])); i++)
	{
		BSTreeInsert(&tree, a[i]);
	}
	BSTreeInOrder(&tree);
	printf("\n");
	printf("%d\n", BSTreeFind(&tree, 5)->_data);
}

void TestBSTreeR()
{
	int i = 0;
	BSTreeNode* tree = NULL;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (i; i < (sizeof(a) / sizeof(a[0])); i++)
	{
		BSTreeInsertR(&tree, a[i]);
	}
	BSTreeInOrder(&tree);
	printf("\n");
	BSTreeRemoveR(&tree, 0);
	//	BSTreeRemoveR(&pTree, 1);
	//	BSTreeRemoveR(&pTree, 2);
	//	BSTreeRemoveR(&pTree, 3);
	//	BSTreeRemoveR(&pTree, 4);
	//	BSTreeRemoveR(&pTree, 5);
	//	BSTreeRemoveR(&pTree, 6);
	//	BSTreeRemoveR(&pTree, 7);
	//	BSTreeRemoveR(&pTree, 8);
	//	BSTreeRemoveR(&pTree, 9);
	//	BSTreeRemoveR(&pTree, 10);
	BSTreeInOrder(&tree);
	printf("\n");
	printf("%d\n", BSTreeFindR(&tree, 5)->_data);
	BSTreeDestroy(&tree);
}