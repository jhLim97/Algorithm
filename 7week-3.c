//탐색트리 3번
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

int max1(int a, int b)//최대 값 반환
{
	if (a >= b)
		return a;
	else
		return b;
}


int findElement(int k, node *root)//현재 트리에서 키 k를 저장한 노드를 찾아 그 노드에 저장된 원소를 반환
{
	node *w;
	w = treeSearch(root, k);
	if (isExternal(w) == 1)
		return 0;
	else
		return w->key;
}

node *treeSearch(node *v, int k)//현재 트리에서 키 k를 저장한 노드를 반환
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

void expandExternal(node *w)//외부노드확장
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

int updateHeight(node *w)//노드 w의 높이를 (필요하면) 갱신한 후 갱신 여부를 반환
{
	int h;
	node *l, *r;
	l = w->lChild;
	r = w->rChild;
	h = max1(l->height, r->height) + 1;
	if (h != w->height)
	{
		w->height = h;
		return 1;//갱신
	}
	else
		return 0;//갱신안함
}

int isBalanced(node *w)//노드 w의 높이균형 여부를 반환
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
		return 1;//균형맞음
	else
		return 0;//언발란스
}

node *restructure(node *x, node *y, node *z)//3-노드 개조를 수행한 후 (갱신된) 3-노드의 루트를 반환
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

	if (z->parent == NULL)//z가 루트인 경우
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

	a->lChild = T0;//b를 루트로 하는 부트리 제작
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

void searchAndFixAfterInsertion(node *w)//균형검사를 수행하고 불균형이 있으면 개조를 통해 높이균형 속성을 회복
{
	node *z, *y, *x;
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;
	if (w->parent == NULL)//w가 루트인 경우
		return;
	z = w->parent;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)//z가 루트인 경우
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->lChild->height > z->rChild->height)//y는 z의 높은 자식
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)//x는 y의 높은 자식
		x = y->lChild;
	else
		x = y->rChild;

	restructure(x, y, z);
	return;
}

void insertItem(int k, node *root)//현재 트리에 키 k를 저장한 새 노드를 삽입
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
int isExternal(node *w)//노드 w가 외부노드인지 여부를 반환
{
	if ((w->lChild == NULL) && (w->rChild == NULL))
		return 1;//외부노드
	else
		return 0;//외부노드 아님
}

int isInternal(node *w)//노드 w가 내부노드인지 여부를 반환
{
	if ((w->lChild != NULL) || (w->rChild != NULL))
		return 1;//내부노드
	else
		return 0;//내부노드 아님
}

node *sibling(node *w)//쌍둥이노드 반환
{
	if (w->parent == NULL)//w가 루트인 경우
		return 0;
	if ((w->parent)->lChild == w)
		return (w->parent)->rChild;
	else
		return (w->parent)->lChild;
}

node *inOrderSucc(node *w)//노드 w의 중위순회 후계자를 반환
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
	if (w->parent == NULL)//w가 루트인 경우
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

void searchAndFixAfterRemoval(node *w)//균형검사 수행 후 만약 불균형이 있을경우 개조를 통해 높이균형 속성 회복 
{
	node *z, *y, *x, *b;
	z = w;
	while (updateHeight(z) && isBalanced(z))
	{
		if (z->parent == NULL)//z가 루트인 경우
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
	if (b->parent == NULL)//b가 루트일 경우 종료
		return;
	searchAndFixAfterRemoval(b->parent);

}

int removeElement(int k, node *root)//현재 트리에서 k를 저장한 노드를 삭제한 후, reduceExternal 작업으로 삭제된 노드의 부모 노드 w에 대해 searchAndFixAfterRemoval(w) 함수를 이용하여 균형검사 및 수리를 수행
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

void traveltree(node *root)//전위순회 인쇄
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
		case 'q': //종료
		{	exit = 0;
		break;
		}

		}
	}

}
