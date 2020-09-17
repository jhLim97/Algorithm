//2��
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int number, nownum, n, numl, vv[3];//number:���� ��,n:���� ��,numl:�ʱ��� �Է¹��� number�� ����
nownum = 0;

typedef struct disjoint//�и������� ���ڵ�
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
	struct node *set;//�Ҽ�����
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
	nownum++;//Ȯ�� �� ũ��
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
	interi = i;//e�� ������ ����� ����
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

void swap(Q *H, int a, int b) //��ȯ
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

void downHeap(Q *H, int i)  //�ڽ� ��峢�� �� ���� ���� ���� �ڽŰ� �� �� ���� ������ �����ϰų� �ڽ��� �̹� ���� ��� ���� �� ����
{
	int	min;  //min ���� �� ����

	if (i * 2 <= number)
	{
		min = i * 2;
		if (i * 2 + 1 <= number)
		{
			if ((H + (i * 2 + 1))->weight < (H + (min))->weight)//�켱���� ť ������ �� ������ ���Ը� ��
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

void rBuildHeap(Q *H, int i) //����� ����� ������
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
	vv[0] = (H + 1)->u;//vv�� �켱���� ť���� �ּ� ���� ������ ����
	vv[1] = (H + 1)->v;
	vv[2] = (H + 1)->weight;
	swap(H, 1, number);
	number--;
	rBuildHeap(H, 1);
}

void unionsack()//�賶 �պ�
{
	int i, j;
	for (i = 0; i < n; i++)//�ش�����(vv[0])�� �����ִ� �и������� �ε��� ���ϱ� 
	{
		if ((sack + i)->head == (vertices + vv[0])->set)
			break;
	}
	for (j = 0; j < n; j++)//�ش�����(vv[1])�� �����ִ� �и������� �ε��� ���ϱ� 
	{
		if ((sack + j)->head == (vertices + vv[1])->set)
			break;
	}
	if ((sack + i)->size <= (sack + j)->size)//ũ�Ⱑ ���� ���� ū�Ϳ� �պ���Ű��
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

	for (int i = 0; i < number; i++)//�켱���� ť�� ���� �־��
	{
		(H + (i + 1))->u = (edges + i)->endpoints[0];
		(H + (i + 1))->v = (edges + i)->endpoints[1];
		(H + (i + 1))->weight = (edges + i)->weight;
	}
	rBuildHeap(H, 1);

	while (number >= 1)
	{

		removemin(H);//Q�� �������� ���� ������ u,v�� 
		if ((vertices + vv[0])->set != (vertices + vv[1])->set)//�� ���� ������ �� �賶�ȿ� ���� �ʴٸ�
		{
			(mst + (numl - number))->u = vv[0];//mstƮ���� ����
			(mst + (numl - number))->v = vv[1];
			(mst + (numl - number))->weight = vv[2];
			unionsack();//�պ�
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

	numl = number;//number�� �����ص�
	sack = (disjoint*)malloc(sizeof(disjoint)*n);//sack n��
	H = (Q*)malloc(sizeof(Q)*(number + 1));
	mst = (Q*)malloc(sizeof(Q)*n);//n-1 ��
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