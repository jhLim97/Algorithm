//그래프순회1번
#include<stdlib.h>
#pragma warning(disable : 4996)

int number, nownum;
nownum = 0;
typedef struct node
{
	struct node *next;
	int element;
	int label;
}node;

typedef struct enode
{
	int endpoints[2];
}enode;

void edgesprint();


node *getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
	return N;
}

node *vertices;
enode *edges;

void incidencelist(node *vertices)
{
	node *headincidence;
	headincidence = getnode();
	headincidence->next = NULL;
	vertices->next = headincidence;
}

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

void adjacentVertices(int n)
{
	node *temp;
	int av, m;
	temp = (vertices + n)->next->next;

	while (temp != NULL)
	{
		m = temp->element;
		av = opposite(n, m);
		printf(" %d", (vertices + av)->element);
		temp = temp->next;
	}
	printf("\n");
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
	node *temp;
	int m;

	for (int i = 0; i < n; i++)
	{
		temp = (vertices + i)->next->next;
		while (temp != NULL)
		{
			m = temp->element;
			if (m >= interi)
			{
				temp->element = m + 1;
			}
			temp = temp->next;
		}

		if (i == ai || i == bi)
		{
			temp = (vertices + i)->next;
			if (temp->next == NULL)
			{
				addnode(interi, (vertices + i)->next);
			}
			else
			{
				while (temp->next != NULL)
				{
					m = temp->next->element;
					if (m < interi)
					{
						if (temp->next->next == NULL)
						{
							addnode(interi, temp->next);
							break;
						}
						else
						{
							if (temp->next->next->element > interi)
							{
								addnode(interi, temp->next);
								break;
							}
						}
					}
					else if (m > interi)
					{
						addnode(interi, (vertices + i)->next);
						break;
					}
					temp = temp->next;
				}
			}

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

void DFS(node * u)
{
	int k, m, av, j;
	if (u->label != 1)
	{
		printf("%d\n", u->element);
		u->label = 1;
		if (u->next->next == NULL)
		{
			return;
		}
		else
		{
			node * use;
			use = u->next->next;

			while (use != NULL)
			{
				m = use->element;
				j = u->element - 1;
				av = opposite(j, m);
				if ((vertices + av)->label == 0)
					DFS(vertices + av);
				use = use->next;
			}
			return;
		}
	}
}



int main()
{
	char input;
	int   a, b, w, output, n, s, *arr, nn, mm;


	scanf("%d %d %d", &n, &number, &s);

	vertices = (node*)malloc(sizeof(node) * n);
	edges = (enode*)malloc(sizeof(enode) * number);
	arr = (int*)malloc(sizeof(int)*(n + 1));

	for (int i = 0; i < n; i++)
	{
		(vertices + i)->element = i + 1;
		incidencelist(vertices + i);
		(vertices + i)->label = 0;
		arr[i] = -1;
	}
	arr[n] = -1;

	for (int i = 0; i < number; i++)
	{
		(edges + i)->endpoints[0] = -1;
		(edges + i)->endpoints[1] = -1;
	}

	for (int i = 0; i < number; i++)
	{
		scanf("%d %d", &nn, &mm);
		changeweight(nn - 1, mm - 1, n);
	}

	DFS((vertices + (s - 1)));


	return 0;
}