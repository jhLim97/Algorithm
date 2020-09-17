//최소신장트리 1번

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int number, nownum, *mst, n, nl;//number:간선 수,n:정점 수,nl:초기의 입력받은 n값 저장
nownum = 0;
typedef struct node
{
	struct node *next;
	int element;
	int d;
	int p;
	int torf;//큐 H안에 있는지 여부
}node;

typedef struct enode
{
	int endpoints[2];
	int weight;
}enode;

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

int changeweight(int a, int b, int n, int w)
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
		(temp + i)->weight = (edges + i)->weight;
		(temp + i)->endpoints[0] = (edges + i)->endpoints[0];
		(temp + i)->endpoints[1] = (edges + i)->endpoints[1];
	}
	(temp + interi)->weight = w;
	(temp + interi)->endpoints[0] = ai;
	(temp + interi)->endpoints[1] = bi;
	for (i = interi + 1; i < nownum; i++)
	{
		(temp + i)->weight = (edges + (i - 1))->weight;
		(temp + i)->endpoints[0] = (edges + (i - 1))->endpoints[0];
		(temp + i)->endpoints[1] = (edges + (i - 1))->endpoints[1];
	}
	free(edges);
	edges = temp;

	rearrange(interi, ai, bi, n);
	return 1;
}

void swap(int *a, int *b) //교환
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void downHeap(int *H, int i)  //자식 노드끼리 비교 시켜 작은 값을 자신과 비교 후 작은 값으로 변경하거나 자신이 이미 작을 경우 본래 값 유지
{
	int	min;  //min 작은 값 저장

	if (i * 2 <= n)
	{
		min = i * 2;
		if (i * 2 + 1 <= n)
		{
			if ((vertices + (H[i * 2 + 1] - 1))->d < (vertices + (H[min] - 1))->d)//우선순위 큐 내에서 각 정점의 d라벨의 크기를 비교
				min = i * 2 + 1;
		}

		if ((vertices + (H[i] - 1))->d > (vertices + (H[min] - 1))->d)
		{
			swap(&H[i], &H[min]);
			downHeap(H, min);
		}
	}
}


void printtree()
{
	int i, sum;
	i = 1, sum = 0;

	for (int k = 1; k < nl; k++)
	{
		sum += (vertices + (mst[k + 1] - 1))->p;//간선들의 합
	}
	while (i <= nl)
	{
		printf(" %d", mst[i]);
		i++;
	}
	printf("\n");
	printf("%d", sum);
}

void rBuildHeap(int H, int i) //재귀적 상향식 힙생성
{
	if (i <= n)
	{
		rBuildHeap(H, 2 * i);
		rBuildHeap(H, 2 * i + 1);
		downHeap(H, i);
	}
}

int removemin(int *H)
{
	int result;
	result = H[1]; //result는 반환값
	H[1] = H[n];   //최소힙의 마지막 원소를 루트로 보내고 원래 루트원소 팝
	H[n] = '\0';
	n--;
	rBuildHeap(H, 1);

	(vertices + (result - 1))->torf = 0;//우선순위 큐에서 나갔음으로 torf값을 0으로 변경
	mst[nl - n] = result;//mst트리에 삽입
	return result;
}

void primjarnikMST(int *H)
{
	int u, e, z;
	node *temp;
	for (int i = 0; i < n; i++)
	{
		(vertices + i)->d = 1000;//무한대를	의미하는 수
		(vertices + i)->p = '\0';//p널 값으로 초기화
	}
	(vertices + 0)->d = 0;
	for (int i = 0; i < n; i++)
	{
		H[i + 1] = (vertices + i)->element;//정점들 우선순위큐에 삽입
		(vertices + i)->torf = 1;//우선순위 큐에 들어있는 정점들을 torf=1로 나타냄
	}
	while (n >= 1)
	{
		u = removemin(H) - 1;
		temp = (vertices + u)->next->next;
		while (temp != NULL)
		{
			e = temp->element;
			z = opposite(u, e);
			if ((vertices + z)->torf == 1 && ((edges + e)->weight < (vertices + z)->d))//z가 큐에 속하고 무게비교
			{
				(vertices + z)->d = (edges + e)->weight;
				(vertices + z)->p = (edges + e)->weight;
				rBuildHeap(H, 1);
			}
			temp = temp->next;
		}
	}
}



int main()
{
	char input;
	int   a, b, w, nn, mm, *H;


	scanf("%d %d", &n, &number);

	nl = n;
	H = (int*)malloc(sizeof(int)*(n + 1));
	mst = (int*)malloc(sizeof(int)*(n + 1));
	vertices = (node*)malloc(sizeof(node) * n);
	edges = (enode*)malloc(sizeof(enode) * number);

	for (int i = 0; i < n; i++)
	{
		(vertices + i)->element = i + 1;
		incidencelist(vertices + i);
	}

	for (int i = 0; i < number; i++)
	{
		(edges + i)->endpoints[0] = -1;
		(edges + i)->endpoints[1] = -1;
	}

	for (int i = 0; i < number; i++)
	{
		scanf("%d %d %d", &nn, &mm, &w);
		changeweight(nn - 1, mm - 1, n, w);
	}



	primjarnikMST(H);

	printtree();



	return 0;
}