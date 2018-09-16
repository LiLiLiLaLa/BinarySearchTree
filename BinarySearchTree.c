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
	//空树
	if (*ppTree == NULL)
	{
		*ppTree = BuyBSTreeNode(x);
		return 1;
	}
	cur = *ppTree;
	while (cur)
	{
		//小于当前往左找
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		//大于当前往右找
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		//等与当前不插入
		else
		{
			return 0;
		}
	}
	//走到此处证明cur=NULL,上一步位置为parent
	if (parent->_data < x)
	{
		parent->_right = BuyBSTreeNode(x);//大于parent插入右边
	}
	else
	{
		parent->_left = BuyBSTreeNode(x);//小于插入左边
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
			//开始删除
			//左为空
			if (cur->_left == NULL)
			{
				//有可能删除的元素在根节点，那么他的parent为空
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
			//右为空
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
	//没找到
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
	//cur为空
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
	//插入的元素已存在
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
	//找到x
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
		//左右均有元素
		else
		{
			BSTreeNode* replace = (*ppTree)->_right;
			//找到要删除结点右子树最小的一个
			while (replace->_left)
			{
				replace = replace->_left;
			}
			//把找到的数字替换到原本x的结点处
			(*ppTree)->_data = replace->_data;
			//删掉与x替换的值的本来结点，它是x右子树做小的一个，必定在左下角，删除它会进入remove函数最前面左子树或右子树为空的情况
			return BSTreeRemoveR(&((*ppTree)->_right), replace->_data);
		}
	}
	return 1;
}

BSTreeNode* BSTreeFindR(BSTreeNode** ppTree, BSTDataType x)
{
	//空树查找失败
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
	//找到了
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