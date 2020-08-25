//2¹ø

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int getNextBucket(int v, int i, int M);
int insertItem(int *hashtable, int x, int M);
int findElement(int *hashtable, int x, int M);
int main()
{
	int *hashtable, M, m, key, result;
	char input;
	input = '\0';

	scanf("%d %d", &M, &m);
	hashtable = (int*)malloc(sizeof(int)*M);

	for (int i = 0; i < M; i++)
		hashtable[i] = 0;

	scanf("%c", &input);
	while (input != 'e')
	{
		if (input == 'i')
		{
			if (m >= 1)
			{
				scanf("%d", &key);
				result = insertItem(hashtable, key, M);
				printf("%d\n", result);
			}
			m--;
		}
		else if (input == 's')
		{
			scanf("%d", &key);
			result = findElement(hashtable, key, M);
			if (result == -1)
				printf("%d\n", result);
			else
				printf("%d %d\n", result, key);
		}
		scanf("%c", &input);
	}
}

int getNextBucket(int v, int i, int M)
{
	return (v + i) % M;
}

int insertItem(int *hashtable, int x, int M)
{
	int v, i, b;
	v = x % M;
	i = 0;
	while (i < M)
	{
		b = getNextBucket(v, i, M);
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

int findElement(int *hashtable, int x, int M)
{
	int v, i, b;
	v = x % M;
	i = 0;
	while (i < M)
	{
		b = getNextBucket(v, i, M);
		if (hashtable[b] == 0)
			return -1;
		else if (x == hashtable[b])
			return b;
		else
			i++;
	}
	return -1;
}