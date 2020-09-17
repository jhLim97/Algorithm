//2번
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int number, nownum, n, numl, vv[3];//number:간선 수,n:정점 수,numl:초기의 입력받은 number값 저장
nownum = 0;

typedef struct disjoint//분리집합의 레코드
{
	int size;
	struct node *head;
	struct node *tail;
}disjoint;

disjoint *sack;

typedef struct Que
{
	int u;
	int v;
	int weight;
}Q;

typedef struct node
{
	struct node *next;
	int element;
	struct node *set;//소속집합
}node;

typedef struct enode
{
	int endpoints[2];
	int weight;
}enode;

node *vertices;
enode *edges;

void changeweight(int a, int b, int n, int w)
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

	return;
}

void swap(Q *H, int a, int b) //교환
{
	int utemp, vtemp, wtemp;
	utemp = (H + a)->u;
	vtemp = (H + a)->v;
	wtemp = (H + a)->weight;
	(H + a)->u = (H + b)->u;
	(H + a)->v = (H + b)->v;
	(H + a)->weight = (H + b)->weight;
	(H + b)->u = utemp;
	(H + b)->v = vtemp;
	(H + b)->weight = wtemp;
}

void downHeap(Q *H, int i)  //자식 노드끼리 비교 시켜 작은 값을 자신과 비교 후 작은 값으로 변경하거나 자신이 이미 작을 경우 본래 값 유지
{
	int	min;  //min 작은 값 저장

	if (i * 2 <= number)
	{
		min = i * 2;
		if (i * 2 + 1 <= number)
		{
			if ((H + (i * 2 + 1))->weight < (H + (min))->weight)//우선순위 큐 내에서 각 간선의 무게를 비교
				min = i * 2 + 1;
		}

		if ((H + i)->weight > (H + min)->weight)
		{
			swap(H, i, min);
			downHeap(H, min);
		}
	}
}

void printtree(Q *mst)
{
	int i, sum;
	i = 1, sum = 0;

	for (int k = 1; k < n; k++)
	{
		printf(" %d", (mst + k)->weight);
	}
	while (i < n)
	{
		sum += (mst + i)->weight;
		i++;
	}
	printf("\n");
	printf("%d", sum);
}

void rBuildHeap(Q *H, int i) //재귀적 상향식 힙생성
{
	if (i <= number)
	{
		rBuildHeap(H, 2 * i);
		rBuildHeap(H, 2 * i + 1);
		downHeap(H, i);
	}
}

void removemin(Q *H)
{
	vv[0] = (H + 1)->u;//vv는 우선순위 큐에서 최소 값의 정보를 갖음
	vv[1] = (H + 1)->v;
	vv[2] = (H + 1)->weight;
	swap(H, 1, number);
	number--;
	rBuildHeap(H, 1);
}

void unionsack()//배낭 합병
{
	int i, j;
	for (i = 0; i < n; i++)//해당정점(vv[0])이 속해있는 분리집합의 인덱스 구하기 
	{
		if ((sack + i)->head == (vertices + vv[0])->set)
			break;
	}
	for (j = 0; j < n; j++)//해당정점(vv[1])이 속해있는 분리집합의 인덱스 구하기 
	{
		if ((sack + j)->head == (vertices + vv[1])->set)
			break;
	}
	if ((sack + i)->size <= (sack + j)->size)//크기가 작은 것을 큰것에 합병시키기
	{
		node *temp;
		temp = (sack + i)->head;
		if (temp != NULL)
			(sack + j)->tail->next = temp;
		while (temp != NULL)
		{
			if (temp->next == NULL)
				(sack + j)->tail = temp;
			temp->set = (sack + j)->head;
			temp = temp->next;
		}
		(sack + i)->head = NULL;
		(sack + i)->tail = NULL;
		(sack + j)->size += (sack + i)->size;
		(sack + i)->size = 0;
	}
	else
	{
		node *temp;
		temp = (sack + j)->head;
		if (temp != NULL)
			(sack + i)->tail->next = temp;
		while (temp != NULL)
		{
			if (temp->next == NULL)
				(sack + i)->tail = temp;
			temp->set = (sack + i)->head;
			temp = temp->next;
		}
		(sack + j)->head = NULL;
		(sack + j)->tail = NULL;
		(sack + i)->size += (sack + j)->size;
		(sack + j)->size = 0;

	}
}

void kruskalmst(Q *H, Q *mst)
{
	int n1, n2;
	for (int i = 0; i < n; i++)
	{
		(vertices + i)->next = NULL;
		(sack + i)->size = 1;
		(sack + i)->head = (vertices + i);
		(sack + i)->tail = (vertices + i);
		(vertices + i)->set = (sack + i)->head;
	}

	for (int i = 0; i < number; i++)//우선순위 큐에 간선 넣어둠
	{
		(H + (i + 1))->u = (edges + i)->endpoints[0];
		(H + (i + 1))->v = (edges + i)->endpoints[1];
		(H + (i + 1))->weight = (edges + i)->weight;
	}
	rBuildHeap(H, 1);

	while (number >= 1)
	{

		removemin(H);//Q의 가장작은 무게 간선의 u,v값 
		if ((vertices + vv[0])->set != (vertices + vv[1])->set)//두 개의 정점이 한 배낭안에 있지 않다면
		{
			(mst + (numl - number))->u = vv[0];//mst트리에 저장
			(mst + (numl - number))->v = vv[1];
			(mst + (numl - number))->weight = vv[2];
			unionsack();//합병
		}
		else
			numl--;
	}
}

int main()
{
	char input;
	int   a, b, w, nn, mm;
	Q *H, *mst;

	scanf("%d %d", &n, &number);

	numl = number;//number값 저장해둠
	sack = (disjoint*)malloc(sizeof(disjoint)*n);//sack n개
	H = (Q*)malloc(sizeof(Q)*(number + 1));
	mst = (Q*)malloc(sizeof(Q)*n);//n-1 개
	vertices = (node*)malloc(sizeof(node) * n);
	edges = (enode*)malloc(sizeof(enode) * number);

	for (int i = 0; i < n; i++)
	{
		(vertices + i)->element = i + 1;
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

	kruskalmst(H, mst);

	printtree(mst);

	return 0;
}