//2번
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int number, nownum;
nownum = 0;
int **adjacency;
typedef struct node
{
	struct node *next;
	int element;
	int label;//왔다 갔는지 여부(기존 0으로 초기화>
}node;

typedef struct enode
{
	int endpoints[2];
}enode;



node *getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
}

node *vertices;
enode *edges;

int opposite(int v, int m)
{
	int u, w;
	u = (edges + m)->endpoints[0];
	w = (edges + m)->endpoints[1];
	if (v == u)
		return w;
	else
		return u;
}

void addnode(int interi, node *temp)
{
	node *newnode, *stemp;
	newnode = getnode();
	newnode->element = interi;
	newnode->next = temp->next;
	temp->next = newnode;
}

void rearrange(int interi, int ai, int bi, int n)
{
	int m, j;
	for (int i = 0; i < n; i++)
	{
		j = 0;
		while (j < n)
		{
			m = adjacency[i][j];

			if (i == ai)
			{
				if (j == bi)
					adjacency[i][j] = interi;
			}
			else if (i == bi)
			{
				if (j == ai)
					adjacency[i][j] = interi;
			}

			if (m >= interi)
				adjacency[i][j] = m + 1;
			j++;
		}
	}
}


int changeweight(int a, int b, int n)
{
	enode *temp;
	int i, out, ai, bi, change, interi, outeri;

	ai = a, bi = b;

	if (ai > bi)
	{
		change = bi;
		bi = ai;
		ai = change;
	}
	nownum++;//확장 될 크기
	i = 0;

	for (i = 0; i <= nownum - 2; i++)
	{
		if ((edges + i)->endpoints[0] > ai)
			break;
		if ((edges + i)->endpoints[0] == ai)
		{
			if ((edges + (i + 1))->endpoints[0] > ai)
			{
				if ((edges + i)->endpoints[1] <= bi)
				{
					i++;
					break;
				}
			}
			else if ((edges + (i + 1))->endpoints[0] == ai)
			{
				if ((edges + i)->endpoints[1] <= bi && (edges + (i + 1))->endpoints[1] >= bi)
				{
					i++;
					break;
				}
				if ((edges + i)->endpoints[1] > bi)
					break;
			}
		}
		if ((edges + i)->endpoints[0] < ai)
		{
			if ((edges + (i + 1))->endpoints[0] > ai)
			{
				i++;
				break;
			}
			else if ((edges + (i + 1))->endpoints[0] == ai)
			{
				if ((edges + (i + 1))->endpoints[1] >= bi)
				{
					i++;
					break;
				}
			}
		}
	}
	interi = i;//e에 삽입할 노드의 순서
	temp = (enode*)malloc(sizeof(enode) * number);
	for (i = 0; i < interi; i++)
	{
		(temp + i)->endpoints[0] = (edges + i)->endpoints[0];
		(temp + i)->endpoints[1] = (edges + i)->endpoints[1];
	}
	(temp + interi)->endpoints[0] = ai;
	(temp + interi)->endpoints[1] = bi;
	for (i = interi + 1; i < nownum; i++)
	{
		(temp + i)->endpoints[0] = (edges + (i - 1))->endpoints[0];
		(temp + i)->endpoints[1] = (edges + (i - 1))->endpoints[1];
	}
	free(edges);
	edges = temp;

	rearrange(interi, ai, bi, n);
	return 1;
}

void bfs(int n, int *arr)
{
	int i, j, m, k, av, p, count, lcount, u;
	i = 0, p = 0, count = 1, lcount = 1, u = 0;

	while (arr[i] != -1)
	{
		u = count - 1;
		for (i = p; i < count; i++)
		{
			m = arr[i];
			for (j = 0; j < n; j++)
			{
				k = adjacency[j][m];
				if (k != -1)
				{
					av = opposite(m, k);
					if ((vertices + av)->label == 0)
					{
						u++;
						arr[u] = (vertices + av)->element - 1;
						(vertices + av)->label = 1;
						lcount++;
					}
				}
			}
		}
		p = i;
		count = lcount;
	}
}

int main()
{
	int w, n, m, s, nn, mm, k, *arr, i, j;

	scanf("%d %d %d", &n, &number, &s);


	adjacency = (int**)malloc(sizeof(int*)*n);
	arr = (int*)malloc(sizeof(int)*(n + 1));

	for (int i = 0; i < n; i++)
	{
		adjacency[i] = (int*)malloc(sizeof(int)*n);
		arr[i] = -1;
	}
	arr[n] = -1;

	vertices = (node*)malloc(sizeof(node) * n);
	edges = (enode*)malloc(sizeof(enode) * number);

	for (int i = 0; i < n; i++)
	{
		(vertices + i)->element = i + 1;
		(vertices + i)->label = 0;
	}

	for (int i = 0; i < number; i++)
	{
		(edges + i)->endpoints[0] = -1;
		(edges + i)->endpoints[1] = -1;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			adjacency[i][j] = -1;
		}
	}

	for (int i = 0; i < number; i++)
	{
		scanf("%d %d", &nn, &mm);
		changeweight(nn - 1, mm - 1, n);
	}


	arr[0] = (vertices + (s - 1))->element - 1;
	(vertices + (s - 1))->label = 1;

	bfs(n, arr);

	for (int i = 0; i < n; i++)
		printf("%d\n", arr[i] + 1);
	return 0;
}
