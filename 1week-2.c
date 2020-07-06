//2¹ø
#define   _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}node;


node *getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
}
void addtree(node *pnode, int b, int c);

void initialize(node *root, int a, int b, int c)
{
	root->data = a;
	root->left = NULL;
	root->right = NULL;
	addtree(root, b, c);
}

void addtree(node *pnode, int b, int c)
{
	node *B, *C;
	B = getnode();
	C = getnode();
	B->data = b;
	C->data = c;
	pnode->left = B;
	pnode->right = C;
	B->left = NULL;
	B->right = NULL;
	C->left = NULL;
	C->right = NULL;
	if (b == 0)
	{
		pnode->left = NULL;
		free(B);
	}
	if (c == 0)
	{
		pnode->right = NULL;
		free(C);
	}
}

void maketree(node *root, int a, int b, int c)
{
	if (root != NULL)
	{
		if (root->data == a)
		{
			addtree(root, b, c);
		}
		else
		{
			maketree(root->left, a, b, c);
			maketree(root->right, a, b, c);
		}
	}
}



void seek(node *root, char *direction)
{
	int i;
	node *temp;
	i = 0;

	temp = root;
	printf(" %d", temp->data);
	while (direction[i] != '\0')
	{
		if (direction[i] == 'L')
		{
			temp = temp->left;
			if (temp != NULL)
				printf(" %d", temp->data);
		}
		else if (direction[i] == 'R')
		{
			temp = temp->right;
			if (temp != NULL)
				printf(" %d", temp->data);
		}
		i++;
	}
}


int main()
{
	int n, s, i, a, b, c;
	char direction[100];
	n = 0, s = 0, a = 0, b = 0, c = 0;

	node *root;
	root = getnode();

	scanf("%d", &n);

	scanf("%d %d %d", &a, &b, &c);
	initialize(root, a, b, c);


	for (i = 0; i < n - 1; i++)
	{
		scanf("%d %d %d", &a, &b, &c);

		maketree(root, a, b, c);
	}

	scanf("%d", &s);

	for (i = 0; i < s; i++)
	{
		scanf("%s", direction);
		seek(root, direction);
		printf("\n");
	}

	return 0;
}
