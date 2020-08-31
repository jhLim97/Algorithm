//그래프표현1번

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int number = 8;
typedef struct node
{
	struct node *next;
	int element;
}node;

typedef struct enode
{
	int endpoints[2];
	int element;
}enode;



node *getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
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
	if (n >= 6 || n <= -1)
	{
		printf("-1\n");
		return;
	}
	node *temp;
	int av, m;
	temp = (vertices + n)->next->next;

	while (temp != NULL)
	{
		m = temp->element;
		av = opposite(n, m);
		printf(" %d %d", (vertices + av)->element, (edges + m)->element);
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

void rearrange(int interi, int ai, int bi, int pm)//pm은 추가인지 삭제인지 알려주는 인자,interi는 삽입 또는 삭제위치
{
	node *temp, *stemp;//stemp는 노드 삭제시 사용되는 노드
	int m;

	for (int i = 0; i < 6; i++)
	{
		temp = (vertices + i)->next->next;
		stemp = (vertices + i)->next;
		while (temp != NULL)
		{
			m = temp->element;
			if (m >= interi)
			{
				if (pm == 1)
					temp->element = m + 1;
				else
				{
					if ((m == interi && i == ai) || (m == interi && i == bi))
					{
						temp = stemp;
						stemp = stemp->next;
						temp->next = temp->next->next;
						free(stemp);
					}
					else
						temp->element = m - 1;
				}
			}
			stemp = temp;
			temp = temp->next;
		}
		if (pm == 1)
		{
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

}


int changeweight(int a, int b, int w)
{
	enode *temp;
	int i, out, ai, bi, change, interi, outeri;
	out = 2;
	for (i = 0; i < 6; i++)
	{
		if ((vertices + i)->element == a)
		{
			ai = i;
			out--;
		}
		if ((vertices + i)->element == b)
		{
			bi = i;
			out--;
		}
	}
	if (out != 0)
		return -1;

	if (ai > bi)
	{
		change = bi;
		bi = ai;
		ai = change;
	}
	i = 0;

	if (w == 0)
	{
		for (i = 0; i < number; i++)
		{
			if ((edges + i)->endpoints[0] == ai && (edges + i)->endpoints[1] == bi)
			{
				outeri = i;
				break;
			}
		}
		if (i == number)//잘 체크하기 ->필요없는듯
			return -1;
		number--;
		temp = (enode*)malloc(sizeof(enode) * number);
		for (i = 0; i < outeri; i++)
		{
			(temp + i)->element = (edges + i)->element;
			(temp + i)->endpoints[0] = (edges + i)->endpoints[0];
			(temp + i)->endpoints[1] = (edges + i)->endpoints[1];
		}
		for (i = outeri; i < number; i++)
		{
			(temp + i)->element = (edges + (i + 1))->element;
			(temp + i)->endpoints[0] = (edges + (i + 1))->endpoints[0];
			(temp + i)->endpoints[1] = (edges + (i + 1))->endpoints[1];
		}
		free(edges);
		edges = temp;
		rearrange(outeri, ai, bi, 0);
		return 1;
	}
	while (i < number)
	{
		if ((edges + i)->endpoints[0] == ai && (edges + i)->endpoints[1] == bi)
		{
			(edges + i)->element = w;
			return 1;
		}
		i++;
	}

	number++;//확장 될 크기

	for (i = 0; i <= number - 2; i++)
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
		(temp + i)->element = (edges + i)->element;
		(temp + i)->endpoints[0] = (edges + i)->endpoints[0];
		(temp + i)->endpoints[1] = (edges + i)->endpoints[1];
	}
	(temp + interi)->element = w;
	(temp + interi)->endpoints[0] = ai;
	(temp + interi)->endpoints[1] = bi;
	for (i = interi + 1; i < number; i++)
	{
		(temp + i)->element = (edges + (i - 1))->element;
		(temp + i)->endpoints[0] = (edges + (i - 1))->endpoints[0];
		(temp + i)->endpoints[1] = (edges + (i - 1))->endpoints[1];
	}
	free(edges);
	edges = temp;

	rearrange(interi, ai, bi, 1);
	return 1;
}

int main()
{
	char input;
	int quit, a, b, w, number, output;
	input = '\0';
	quit = 1;
	vertices = (node*)malloc(sizeof(node) * 6);
	edges = (enode*)malloc(sizeof(enode) * 8);

	for (int i = 0; i < 6; i++)
	{
		(vertices + i)->element = i + 1;
		incidencelist(vertices + i);
	}

	vertices->next->next = getnode();
	vertices->next->next->element = 0;
	vertices->next->next->next = getnode();
	vertices->next->next->next->element = 1;
	vertices->next->next->next->next = getnode();
	vertices->next->next->next->next->element = 2;
	vertices->next->next->next->next->next = getnode();
	vertices->next->next->next->next->next->element = 3;
	vertices->next->next->next->next->next->next = NULL;//노드1

	(vertices + 1)->next->next = getnode();
	(vertices + 1)->next->next->element = 0;
	(vertices + 1)->next->next->next = getnode();
	(vertices + 1)->next->next->next->element = 4;
	(vertices + 1)->next->next->next->next = NULL;//노드2

	(vertices + 2)->next->next = getnode();
	(vertices + 2)->next->next->element = 1;
	(vertices + 2)->next->next->next = getnode();
	(vertices + 2)->next->next->next->element = 4;
	(vertices + 2)->next->next->next->next = getnode();
	(vertices + 2)->next->next->next->next->element = 5;
	(vertices + 2)->next->next->next->next->next = NULL;//노드3

	(vertices + 3)->next->next = getnode();
	(vertices + 3)->next->next->element = 2;
	(vertices + 3)->next->next->next = NULL;//노드4

	(vertices + 4)->next->next = getnode();
	(vertices + 4)->next->next->element = 5;
	(vertices + 4)->next->next->next = getnode();
	(vertices + 4)->next->next->next->element = 6;
	(vertices + 4)->next->next->next->next = getnode();
	(vertices + 4)->next->next->next->next->element = 7;
	(vertices + 4)->next->next->next->next->next = NULL;//노드5

	(vertices + 5)->next->next = getnode();
	(vertices + 5)->next->next->element = 3;
	(vertices + 5)->next->next->next = getnode();
	(vertices + 5)->next->next->next->element = 7;
	(vertices + 5)->next->next->next->next = NULL;//노드6

	edges->element = 1;
	edges->endpoints[0] = 0;
	edges->endpoints[1] = 1;
	(edges + 1)->element = 1;
	(edges + 1)->endpoints[0] = 0;
	(edges + 1)->endpoints[1] = 2;
	(edges + 2)->element = 1;
	(edges + 2)->endpoints[0] = 0;
	(edges + 2)->endpoints[1] = 3;
	(edges + 3)->element = 2;
	(edges + 3)->endpoints[0] = 0;
	(edges + 3)->endpoints[1] = 5;
	(edges + 4)->element = 1;
	(edges + 4)->endpoints[0] = 1;
	(edges + 4)->endpoints[1] = 2;
	(edges + 5)->element = 4;
	(edges + 5)->endpoints[0] = 2;
	(edges + 5)->endpoints[1] = 4;
	(edges + 6)->element = 4;
	(edges + 6)->endpoints[0] = 4;
	(edges + 6)->endpoints[1] = 4;
	(edges + 7)->element = 3;
	(edges + 7)->endpoints[0] = 4;
	(edges + 7)->endpoints[1] = 5;

	scanf("%c", &input);
	while (input != 'q')
	{
		if (input == 'a')
		{
			scanf("%d", &number);
			getchar(); adjacentVertices(number - 1);
		}
		else if (input == 'm')
		{
			scanf("%d %d %d", &a, &b, &w);
			getchar(); output = changeweight(a, b, w);
			if (output == -1)
				printf("-1\n");
		}
		scanf("%c", &input);
	}
	return 0;
}