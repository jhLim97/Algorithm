//1¹ø
#define   _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

int num = 0;

typedef struct node
{
	int elem;
	struct node *prev;
	struct node *next;
}node;

typedef struct list
{
	node *H;
	node *T;
}list;

void initialize(list *plist)
{
	plist->H = (node*)malloc(sizeof(node));
	plist->T = (node*)malloc(sizeof(node));

	plist->H->prev = NULL;
	plist->T->next = NULL;
	plist->H->next = plist->T;
	plist->T->prev = plist->H;
}

void add(list *plist, int r, char e)
{
	int i;
	node *temp, *newnode;

	newnode = (node*)malloc(sizeof(node));
	newnode->elem = e;
	temp = plist->H;

	for (i = 0; i < r; i++)
	{
		temp = temp->next;
	}

	newnode->prev = temp->prev;
	newnode->next = temp;
	temp->prev->next = newnode;
	temp->prev = newnode;

	num++;
}

void delete(list *plist, int r)
{
	int i;
	node *temp, *Prev, *Next;

	temp = plist->H;

	for (i = 0; i < r; i++)
	{
		temp = temp->next;
	}

	Prev = temp->prev;
	Next = temp->next;

	Prev->next = Next;
	Next->prev = Prev;

	free(temp);
	num--;
}

int get(list *plist, int r)
{
	int i;
	node *temp;

	temp = plist->H;

	for (i = 0; i < r; i++)
	{
		temp = temp->next;
	}

	return temp->elem;
}

void print(list *plist)
{
	int i;
	node *temp;

	temp = plist->H;

	while (temp != plist->T)
	{
		temp = temp->next;
		printf("%c", temp->elem);
	}
}

int main()
{
	int i, n, r;
	char emp, e, result;
	list *plist;
	plist = (list*)malloc(sizeof(list));

	initialize(plist);

	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		getchar();
		scanf("%c", &emp);
		switch (emp)
		{
		case 'A': getchar(); scanf("%d", &r);
			getchar();	scanf("%c", &e);
			if (r <= 0 || r > num + 1)
			{
				printf("invalid position\n");
				break;
			}
			add(plist, r, e);
			break;
		case 'D': getchar(); scanf("%d", &r);
			if (r <= 0 || r > num)
			{
				printf("invalid position\n");
				break;
			}
			delete(plist, r);
			break;
		case 'G': getchar(); scanf("%d", &r);
			if (r <= 0 || r > num)
			{
				printf("invalid position\n");
				break;
			}
			result = get(plist, r);
			printf("%c\n", result);
			break;
		case 'P': print(plist);
			printf("\n");
			break;
		}
	}
	return 0;
}
