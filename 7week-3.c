//Ž��Ʈ�� 3��
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

typedef struct node
{
	int key;
	int height;
	struct node *parent;
	struct node *lChild;
	struct node *rChild;
}node;

node *root;

int findElement(int k, node *root);
node *treeSearch(node *v, int k);
void insertItem(int k, node *root);
int isExternal(node *w);
int isInternal(node *w);
node *sibling(node *w);
node *inOrderSucc(node *w);
node *reduceExternal(node *z);
int removeElement(int k, node *root);
void expandExternal(node *w);
void searchAndFixAfterInsertion(node *w);
int updateHeight(node *w);
int isBalanced(node *w);
node *restructure(node *x, node *y, node *z);
void searchAndFixAfterRemoval(node *w);

node *getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
}

int max1(int a, int b)//�ִ� �� ��ȯ
{
	if (a >= b)
		return a;
	else
		return b;
}


int findElement(int k, node *root)//���� Ʈ������ Ű k�� ������ ��带 ã�� �� ��忡 ����� ���Ҹ� ��ȯ
{
	node *w;
	w = treeSearch(root, k);
	if (isExternal(w) == 1)
		return 0;
	else
		return w->key;
}

node *treeSearch(node *v, int k)//���� Ʈ������ Ű k�� ������ ��带 ��ȯ
{
	if (isExternal(v) == 1)
		return v;
	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->lChild, k);
	else
		return treeSearch(v->rChild, k);
}

void expandExternal(node *w)//�ܺγ��Ȯ��
{
	node *l, *r;
	l = getnode();
	r = getnode();
	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	w->lChild = l;
	w->rChild = r;
}

int updateHeight(node *w)//��� w�� ���̸� (�ʿ��ϸ�) ������ �� ���� ���θ� ��ȯ
{
	int h;
	node *l, *r;
	l = w->lChild;
	r = w->rChild;
	h = max1(l->height, r->height) + 1;
	if (h != w->height)
	{
		w->height = h;
		return 1;//����
	}
	else
		return 0;//���ž���
}

int isBalanced(node *w)//��� w�� ���̱��� ���θ� ��ȯ
{
	int gap, result;
	node *l, *r;
	l = w->lChild;
	r = w->rChild;
	if (l->height >= r->height)
		gap = l->height - r->height;
	else
		gap = r->height - l->height;
	if (gap < 2)
		return 1;//��������
	else
		return 0;//��߶���
}

node *restructure(node *x, node *y, node *z)//3-��� ������ ������ �� (���ŵ�) 3-����� ��Ʈ�� ��ȯ
{
	node *a, *b, *c, *T0, *T1, *T2, *T3;
	if (z->key < y->key && y->key < x->key)
	{
		a = z, b = y, c = x;
		T0 = a->lChild, T1 = b->lChild, T2 = c->lChild, T3 = c->rChild;
	}
	else if (x->key < y->key && y->key < z->key)
	{
		a = x, b = y, c = z;
		T0 = a->lChild, T1 = a->rChild, T2 = b->rChild, T3 = c->rChild;
	}
	else if (z->key < x->key && x->key < y->key)
	{
		a = z, b = x, c = y;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}
	else
	{
		a = y, b = x, c = z;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}

	if (z->parent == NULL)//z�� ��Ʈ�� ���
	{
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z)
	{
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else
	{
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	a->lChild = T0;//b�� ��Ʈ�� �ϴ� ��Ʈ�� ����
	T0->parent = a;
	a->rChild = T1;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	T2->parent = c;
	c->rChild = T3;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(node *w)//�����˻縦 �����ϰ� �ұ����� ������ ������ ���� ���̱��� �Ӽ��� ȸ��
{
	node *z, *y, *x;
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL)//w�� ��Ʈ�� ���
		return;
	z = w->parent;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)//z�� ��Ʈ�� ���
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->lChild->height > z->rChild->height)//y�� z�� ���� �ڽ�
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)//x�� y�� ���� �ڽ�
		x = y->lChild;
	else
		x = y->rChild;

	restructure(x, y, z);
	return;
}

void insertItem(int k, node *root)//���� Ʈ���� Ű k�� ������ �� ��带 ����
{
	node *w;
	w = treeSearch(root, k);
	if (isInternal(w) == 1)
		return;
	else
	{
		w->key = k;
		expandExternal(w);
		searchAndFixAfterInsertion(w);
		return;
	}
}
int isExternal(node *w)//��� w�� �ܺγ������ ���θ� ��ȯ
{
	if ((w->lChild == NULL) && (w->rChild == NULL))
		return 1;//�ܺγ��
	else
		return 0;//�ܺγ�� �ƴ�
}

int isInternal(node *w)//��� w�� ���γ������ ���θ� ��ȯ
{
	if ((w->lChild != NULL) || (w->rChild != NULL))
		return 1;//���γ��
	else
		return 0;//���γ�� �ƴ�
}

node *sibling(node *w)//�ֵ��̳�� ��ȯ
{
	if (w->parent == NULL)//w�� ��Ʈ�� ���
		return 0;
	if ((w->parent)->lChild == w)
		return (w->parent)->rChild;
	else
		return (w->parent)->lChild;
}

node *inOrderSucc(node *w)//��� w�� ������ȸ �İ��ڸ� ��ȯ
{
	w = w->rChild;
	if (isExternal(w) == 1)
		return 0;
	while (isInternal(w->lChild) == 1)
		w = w->lChild;
	return w;
}

node *reduceExternal(node *z)
{
	node *g, *w, *zs, *temp;
	w = z->parent;
	zs = sibling(z);
	if (w->parent == NULL)//w�� ��Ʈ�� ���
	{
		root = zs;
		zs->parent = NULL;
	}
	else
	{
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}
	free(z);
	free(w);
	return zs;
}

void searchAndFixAfterRemoval(node *w)//�����˻� ���� �� ���� �ұ����� ������� ������ ���� ���̱��� �Ӽ� ȸ�� 
{
	node *z, *y, *x, *b;
	z = w;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)//z�� ��Ʈ�� ���
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else
	{
		if (z->lChild == y)
			x = y->lChild;
		else
			x = y->rChild;
	}
	b = restructure(x, y, z);
	if (b->parent == NULL)//b�� ��Ʈ�� ��� ����
		return;
	searchAndFixAfterRemoval(b->parent);

}

int removeElement(int k, node *root)//���� Ʈ������ k�� ������ ��带 ������ ��, reduceExternal �۾����� ������ ����� �θ� ��� w�� ���� searchAndFixAfterRemoval(w) �Լ��� �̿��Ͽ� �����˻� �� ������ ����
{
	int e;
	node *w, *z, *y, *zs;
	w = treeSearch(root, k);
	if (isExternal(w) == 1)
		return 0;
	e = w->key;
	z = w->lChild;
	if (isExternal(z) == 0)
		z = w->rChild;

	if (isExternal(z) == 1)
		zs = reduceExternal(z);
	else
	{
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		zs = reduceExternal(z);
	}

	searchAndFixAfterRemoval(zs->parent);
	return e;
}

void traveltree(node *root)//������ȸ �μ�
{
	if (isExternal(root) == 1)
		return;
	printf(" %d", root->key);
	if (isExternal(root->lChild) == 0)
		traveltree(root->lChild);

	if (isExternal(root->rChild) == 0)
		traveltree(root->rChild);

}


void main()
{
	char input;
	int key, result, exit;
	exit = 1;
	root = getnode();
	//root->parent = getnode();
	//root->lChild = getnode();
	//root->rChild = getnode();
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;

	while (exit)
	{
		scanf("%c", &input);
		switch (input)
		{
		case 'i':
		{
			getchar();
			scanf("%d", &key);	insertItem(key, root);
			break;
		}
		case 'd':
		{
			getchar();
			scanf("%d", &key);  result = removeElement(key, root);
			if (result == 0)
				printf("X\n");
			else
				printf("%d\n", result);
			break;
		}
		case 's':
		{
			getchar();
			scanf("%d", &key); result = findElement(key, root);
			if (result == 0)
				printf("X\n");
			else
				printf("%d\n", result);
			break;
		}
		case 'p':
		{
			traveltree(root);
			printf("\n");
			break;
		}
		case 'q': //����
		{	exit = 0;
		break;
		}

		}
	}

}
