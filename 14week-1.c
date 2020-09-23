//최단경로 1번
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct edge
{
	struct edge* before;
	struct edge* next;
	int u;
	int v;
	int d;
}edge;


typedef struct vertex
{
	edge* edge;
	int vertex;
	int d;
}vertex;

typedef struct Sack
{
	int vertex;
	int d;
}Sack;

int j, k, s;
vertex* Q;
int p;

void buildHeap(vertex* Q, int p)
{
	int i;
	for (i = p / 2; i >= 1; i--)
	{
		downHeap(Q, i, p);
	}
}

int downHeap(vertex* Q, int i, int p)
{
	int left, right, tmpn, dtmp, vtmp;
	left = 2 * i; right = 2 * i + 1;
	vertex* tmp;
	struct node* ntmp;
	struct edge* etmp;


	if (left > p)
		return;
	tmpn = left;

	if (right <= p)
	{
		if (Q[right].d < Q[tmpn].d)
		{
			tmpn = right;
		}
	}
	if (Q[i].d < Q[tmpn].d)
		return;

	tmp = &Q[i];
	vtmp = Q[i].vertex;
	dtmp = Q[i].d;
	etmp = Q[i].edge;

	Q[i] = Q[tmpn];

	Q[tmpn].vertex = vtmp;
	Q[tmpn].d = dtmp;
	Q[tmpn].edge = etmp;

	downHeap(Q, tmpn, p);

}

void create_vertex(vertex *v)
{

	for (int i = 0; i < j; i++)
	{
		v[i].vertex = i + 1;
		v[i].edge = (edge*)malloc(sizeof(edge));
		v[i].edge->next = NULL;
		v[i].edge->before = NULL;
	}
}

void add_edge(vertex *vertices, int u, int v, int distance)
{
	edge* tmp;
	tmp = (edge*)malloc(sizeof(edge));
	tmp->next = NULL;


	while (vertices[u - 1].edge->next != NULL)
	{
		vertices[u - 1].edge = vertices[u - 1].edge->next;
	}
	vertices[u - 1].edge->u = u;
	vertices[u - 1].edge->v = v;
	vertices[u - 1].edge->d = distance;

	vertices[u - 1].edge->next = tmp;
	tmp->before = vertices[u - 1].edge;

	while (vertices[u - 1].edge->before != NULL)
	{
		vertices[u - 1].edge = vertices[u - 1].edge->before;
	}

}

void Dijkstra(vertex *v)
{
	Sack* sack;
	int i = 0, check = 0;
	vertex* u, *z;

	for (i = 0; i < j; i++)
	{
		v[i].d = 30000;
	}
	v[s - 1].d = 0;

	Q = (vertex*)malloc((j + 1) * sizeof(vertex));
	sack = (Sack*)malloc(j * sizeof(Sack));

	for (i = 1; i <= j; i++)
	{
		Q[i] = v[s - 1];
		s++;
		if (s == j + 1)
			s = 1;
	}p = j; i = 0;


	u = (vertex*)malloc(sizeof(vertex));

	while (p != 0)
	{
		u->d = Q[1].d;
		u->edge = Q[1].edge;
		u->vertex = Q[1].vertex;
		sack[Q[1].vertex - 1].vertex = Q[1].vertex;
		sack[Q[1].vertex - 1].d = Q[1].d;

		Q[1] = Q[p];
		p--;


		buildHeap(Q, p);

		while (u->edge->next != NULL) {

			z = &v[u->edge->v - 1];

			for (i = 1; i <= p; i++) {
				if (z->vertex == Q[i].vertex) {
					check++;
					break;
				}
			}
			if (check == 1) {
				if (u->d + u->edge->d < z->d) {
					z->d = u->d + u->edge->d;
					Q[i].d = z->d;
					buildHeap(Q, p);
				}
			}
			u->edge = u->edge->next;

			check = 0;
		}


	}

	for (int i = 0; i < j; i++)
	{
		if (sack[i].d != 0 && sack[i].d != 30000)
			printf("%d %d\n", sack[i].vertex, sack[i].d);
	}

}

int main()
{
	int u, v, d;
	vertex* vertices; edge* e;

	scanf("%d %d %d", &j, &k, &s);

	vertices = (vertex*)malloc(j * sizeof(vertex));

	create_vertex(vertices);


	for (int i = 0; i < k; i++)
	{
		scanf("%d %d %d", &u, &v, &d);
		add_edge(vertices, u, v, d);
		add_edge(vertices, v, u, d);
	}


	Dijkstra(vertices);

}