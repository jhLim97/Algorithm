//합병정렬퀵정렬 1번
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int n, nn;

typedef struct node
{
	int elem;
	struct node *next;
}node;

typedef struct list
{
	struct node *L1;
	struct node *L2;
}list;

node* getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
}

void add(node *root, int e)
{
	int i;
	node *temp, *newnode;
	temp = root;

	if (root->elem == 0)
	{
		root->elem = e;
	}
	else
	{
		newnode = getnode();
		newnode->elem = e;
		newnode->next = NULL;


		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newnode;
	}
}

node* partition(node *root, int k)
{

	int i;
	node *A, *broot;

	A = root;
	for (i = 0; i < k - 1; i++)
	{
		A = A->next;
	}
	broot = A->next;
	A->next = NULL;
	return broot;
}


node* merge(node *L1, node *L2)
{
	node *L, *temp, *merge;
	L = NULL;



	if (L1->elem <= L2->elem)
		merge = L1;
	else
		merge = L2;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->elem <= L2->elem)
		{
			L = L1;
			temp = L->next;
			if (temp == NULL)
			{
				L1 = L->next;
				break;
			}
			if (temp->elem <= L2->elem)
				L1 = temp;
			else
			{
				L->next = L2;
				L1 = temp;
			}
		}
		else
		{
			L = L2;
			temp = L->next;
			if (temp == NULL)
			{
				L2 = L->next;
				break;
			}
			if (temp->elem >= L1->elem)
			{
				L->next = L1;
				L2 = temp;
			}
			else
				L2 = temp;
		}
	}
	if (L1 != NULL)
	{
		L->next = L1;
	}
	else if (L2 != NULL)
	{
		L->next = L2;
	}
	return merge;
}


node* mergeSort(node *root)
{
	node *broot;
	broot = NULL;
	if (root->next != NULL)
	{
		broot = partition(root, nn / 2);
		nn = nn / 2 + 1;
		root = mergeSort(root);
		broot = mergeSort(broot);
		root = merge(root, broot);
	}
	return root;
}

void main()
{
	int i, e;
	scanf("%d", &n);
	nn = n;

	node *root = getnode();
	root->elem = 0;
	root->next = NULL;

	for (i = 0; i < n; i++)
	{
		scanf("%d", &e);
		add(root, e);
	}

	root = mergeSort(root);

	while (root != NULL)
	{
		printf(" %d", root->elem);
		root = root->next;
	}


}