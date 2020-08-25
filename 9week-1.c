//해쉬테이블 1번

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

typedef struct node
{
	struct node *next;
	int key;
}node;


void insertItem(node *hashtable, int x, int M)
{
	int v;
	node *addnode, *temp;
	addnode = (node*)malloc(sizeof(node));
	addnode->next = NULL;
	addnode->key = x;
	v = x % M;
	temp = (hashtable + v);

	if (temp->next == NULL)
	{
		temp->next = addnode;
	}
	else
	{
		addnode->next = temp->next;
		temp->next = addnode;
	}
}

int findElement(node *hashtable, int x, int M)
{
	int v, rank, exist;
	node *temp;
	rank = 1, exist = 0;
	v = x % M;
	temp = (hashtable + v);
	while (temp->next != NULL)
	{
		if (temp->next->key == x)
		{
			exist = 1;
			break;
		}
		temp = temp->next;
		rank++;
	}

	if (exist == 1)
		return rank;
	else
		return 0;
}

int removeElement(node *hashtable, int x, int M)
{
	int v, rank, exist;
	node *temp, *remove;
	remove = NULL;
	rank = 1, exist = 0;
	v = x % M;
	temp = (hashtable + v);
	while (temp->next != NULL)
	{
		if (temp->next->key == x)
		{
			remove = temp->next;
			if (temp->next->next == NULL)
				temp->next = NULL;
			else
				temp->next = temp->next->next;
			exist = 1;
			break;
		}
		temp = temp->next;
		rank++;
	}

	free(remove);

	if (exist == 1)
		return rank;
	else
		return 0;
}

void printhash(node *hashtable, int M)
{
	node *temp;
	for (int i = 0; i < M; i++)
	{
		temp = (hashtable + i);
		while (temp->next != NULL)
		{
			printf(" %d", temp->next->key);
			temp = temp->next;
		}
	}
	printf("\n");
}

int main()
{
	int M, key, result;
	char input;
	node *hashtable;
	input = '\0';

	scanf("%d", &M);
	hashtable = (node*)malloc(sizeof(node)*M);

	for (int i = 0; i < M; i++)
	{
		(hashtable + i)->next = NULL;
	}

	scanf("%c", &input);
	while (input != 'e')
	{
		if (input == 'i')
		{
			scanf("%d", &key);
			insertItem(hashtable, key, M);
		}
		else if (input == 's')
		{
			scanf("%d", &key);
			result = findElement(hashtable, key, M);
			printf("%d\n", result);
		}
		else if (input == 'd')
		{
			scanf("%d", &key);
			result = removeElement(hashtable, key, M);
			printf("%d\n", result);
		}
		else if (input == 'p')
		{
			printhash(hashtable, M);
		}
		scanf("%c", &input);
	}
}