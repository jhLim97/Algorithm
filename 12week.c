//방향그래프 1번

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int *toporder;
int n, m;

typedef struct vnode
{
	char name;
	struct node *outedges;
	struct node *inedges;
	int indegree;
}vnode;

typedef struct enode
{
	int origin;
	int destination;
}enode;

typedef struct node
{
	struct node *next;
	int element;
}node;

typedef struct Graph
{
	vnode *vertices;
	enode *edges;
}Graph;

Graph G;

int isempty();
void enqueue(int v);
int dequeue();
void initqueue();
void buildGraph();
void insertVertex(char vname, int i);
void insertDirectedEdge(char uname, char wname, int i);
int index(char vname);
void addFirst(node *H, int i);
void topologicalSort();
void initializegraph();

node* getnode()
{
	node *N;
	N = (node*)malloc(sizeof(node));
	return N;
}

typedef struct QUEUE
{
	int f;
	int r;
	int *queue;
}QUEUE;

QUEUE Q;

int main()
{
	buildGraph();

	topologicalSort();

	if (toporder[0] == 0)
		printf("0");
	else
	{
		for (int i = 1; i <= n; i++)
			printf("%c ", G.vertices[toporder[i]].name);
	}
}

void buildGraph()
{
	char vname, uname, wname;

	scanf("%d", &n);
	getchar();

	toporder = (int*)malloc(sizeof(int)*(n + 1));
	Q.queue = (int*)malloc(sizeof(int)*n);
	G.vertices = (vnode*)malloc(sizeof(vnode)*n);


	for (int i = 0; i < n; i++)
	{
		scanf("%c", &vname);
		getchar();
		G.vertices[i].outedges = getnode();
		G.vertices[i].inedges = getnode();
		insertVertex(vname, i);
	}

	scanf("%d", &m);
	getchar();

	G.edges = (enode*)malloc(sizeof(enode)*m);
	for (int i = 0; i < m; i++)
	{
		scanf("%c %c", &uname, &wname);
		getchar();
		insertDirectedEdge(uname, wname, i);
	}

	return;
}

void insertVertex(char vname, int i)
{
	G.vertices[i].name = vname;
	G.vertices[i].outedges->next = NULL;
	G.vertices[i].inedges->next = NULL;
	G.vertices[i].indegree = 0;
}

void insertDirectedEdge(char uname, char wname, int i)
{
	int u, w;
	u = index(uname);
	w = index(wname);

	G.edges[i].origin = u;
	G.edges[i].destination = w;

	addFirst(G.vertices[u].outedges, i);
	addFirst(G.vertices[w].inedges, i);

	G.vertices[w].indegree++;
	return;
}

int index(char vname)
{
	for (int i = 0; i < n; i++)
		if (G.vertices[i].name == vname)
			return i;

}

void addFirst(node *H, int i)
{
	node *newnode;
	newnode = getnode();
	newnode->element = i;
	newnode->next = H->next;
	H->next = newnode;
	return;
}

void initqueue()
{
	Q.f = 0;
	Q.r = n - 1;
	return;
}

int isempty()
{
	if ((Q.r + 1) % n == Q.f)
		return 1;
	else
		return 0;
}

void enqueue(int v)
{
	Q.r = (Q.r + 1) % n;
	Q.queue[Q.r] = v;
	return;
}
int dequeue()
{
	int v;
	v = Q.queue[Q.f];
	Q.f = (Q.f + 1) % n;
	return v;
}

void topologicalSort()
{
	int *in, t, u, w, e;
	node *temp;
	in = (int*)malloc(sizeof(int)*n);

	initqueue();

	for (int i = 0; i < n; i++)
	{
		in[i] = G.vertices[i].indegree;
		if (in[i] == 0)
			enqueue(i);//i맞어? u는머야?? 해설참조
	}
	t = 1;

	while (!isempty())//check
	{
		u = dequeue();//
		toporder[t] = u;
		t++;
		temp = G.vertices[u].outedges->next;
		while (temp != NULL)
		{
			e = temp->element;
			w = G.edges[e].destination;
			in[w]--;
			if (in[w] == 0)
				enqueue(w);
			temp = temp->next;
		}
	}

	if (t <= n)
		toporder[0] = 0;
	else
		toporder[0] = 1;

	return;
}