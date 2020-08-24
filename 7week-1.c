//Å½»öÆ®¸® 1¹ø
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

typedef struct node
{
	int key;
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

node *getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
}


int findElement(int k, node *root)
{
	node *w;
	w = treeSearch(root, k);
	if (isExternal(w) == 1)
		return 0;
	else
		return w->key;
}

node *treeSearch(node *v, int k)
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

void expandExternal(node *w)
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

void insertItem(int k, node *root)
{
	node *w;
	w = treeSearch(root, k);
	w->key = k;
	expandExternal(w);
	return;
}
int isExternal(node *w)
{
	if ((w->lChild == NULL) && (w->rChild == NULL))
		return 1;
	else
		return 0;
}

int isInternal(node *w)
{
	if ((w->lChild != NULL) || (w->rChild != NULL))
		return 1;
	else
		return 0;
}

node *sibling(node *w)
{
	if (w->parent == NULL)
		return 0;
	if ((w->parent)->lChild == w)
		return (w->parent)->rChild;
	else
		return (w->parent)->lChild;
}

node *inOrderSucc(node *w)
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
	if (w->parent == NULL)
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
}

int removeElement(int k, node *root)
{
	int rk;
	node *w, *z, *y;
	w = treeSearch(root, k);
	if (isExternal(w) == 1)
		return 0;
	rk = w->key;
	z = w->lChild;
	if (isExternal(z) == 0)
		z = w->rChild;

	if (isExternal(z) == 1)
		reduceExternal(z);
	else
	{
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(z);
	}
	return rk;
}

void traveltree(node *root)
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
		case 'q':
		{	exit = 0;
		break;
		}

		}
	}

}