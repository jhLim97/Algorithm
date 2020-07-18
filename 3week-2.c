#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H[100] = { 0 };
int n;

void downHeap(int i);

void printHeap();

void rBuildHeap(int i);

/*void buildHeap();*/


void downHeap(int i)
{
	int small, temp;

	if (H[i * 2] != 0)
	{
		small = i * 2;
		if (H[i * 2 + 1] != 0)
		{
			if (H[i * 2 + 1] > H[small])
				small = i * 2 + 1;
		}

		if (H[i] < H[small])
		{
			temp = H[i];
			H[i] = H[small];
			H[small] = temp;
			downHeap(small);
		}
	}
}

void printHeap()
{
	int i;
	i = 1;
	while (i <= n)
	{
		printf(" %d", H[i]);
		i++;
	}
	printf("\n");
}

void rBuildHeap(int i)
{
	if (i <= n)
	{
		rBuildHeap(2 * i);
		rBuildHeap(2 * i + 1);
		downHeap(i);

	}
}

/*void buildHeap()
{
	int i;

	for (i = n / 2; i >= 1; i--)
		downHeap(i);

}*/

void main()
{
	int i;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)
	{
		scanf("%d", &H[i]);
	}

	rBuildHeap(1);
	printHeap();
}

