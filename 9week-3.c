//3¹ø

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)


int getNextBucket(int v, int i, int M, int q, int x);
int insertItem(int *hashtable, int x, int M, int q);
int findElement(int *hashtable, int x, int M, int q);
void printhash(int *hashtable, int M);
int main()
{
	int *hashtable, M, n, q, key, result;
	char input;
	input = '\0';

	scanf("%d %d %d", &M, &n, &q);
	hashtable = (int*)malloc(sizeof(int)*M);

	for (int i = 0; i < M; i++)
		hashtable[i] = 0;


	while (input != 'e')
	{
		scanf("%c", &input);
		if (input == 'i')
		{
			if (n >= 1)
			{
				scanf("%d", &key);
				result = insertItem(hashtable, key, M, q);
				printf("%d\n", result);
			}
			n--;
		}
		else if (input == 's')
		{
			scanf("%d", &key);
			result = findElement(hashtable, key, M, q);
			if (result == -1)
				printf("%d\n", result);
			else
				printf("%d %d\n", result, key);
		}
		else if (input == 'p' || input == 'e')
		{
			printhash(hashtable, M);
			printf("\n");
		}
	}
}

int getNextBucket(int v, int i, int M, int q, int x)
{
	return (v + i * (q - (x%q))) % M;
}

int insertItem(int *hashtable, int x, int M, int q)
{
	int v, i, b;
	v = x % M;
	i = 0;
	while (i < M)
	{
		b = getNextBucket(v, i, M, q, x);
		if (hashtable[b] == 0)
		{
			hashtable[b] = x;
			return b;
		}
		else
			i++;
		printf("C");
	}
}

int findElement(int *hashtable, int x, int M, int q)
{
	int v, i, b;
	v = x % M;
	i = 0;
	while (i < M)
	{
		b = getNextBucket(v, i, M, q, x);
		if (hashtable[b] == 0)
			return -1;
		else if (x == hashtable[b])
			return b;
		else
			i++;
	}
	return -1;
}

void printhash(int *hashtable, int M)
{
	for (int i = 0; i < M; i++)
	{
		printf(" %d", hashtable[i]);
	}
}