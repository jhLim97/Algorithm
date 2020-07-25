#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int n, nn;
int H[100] = { 0 };

void rBuildHeap(int i);

void downHeap(int i);

void insertItem(int key);

void upHeap(int i);


void downHeap(int i)
{
	int big, temp;

	if (i * 2 <= nn)
	{
		big = i * 2;
		if (i * 2 + 1 <= nn)
		{
			if (H[i * 2 + 1] > H[big])
				big = i * 2 + 1;
		}

		if (H[i] < H[big])
		{
			temp = H[i];
			H[i] = H[big];
			H[big] = temp;
			downHeap(big);
		}
	}
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

void inPlaceHeapSort()
{
	int i, temp;


	for (i = n; i >= 2; i--)
	{
		temp = H[1];
		H[1] = H[i];
		H[i] = temp;
		nn--;
		downHeap(1);
	}

}

printfArray()
{
	int i;
	for (i = 1; i <= n; i++)
	{
		printf(" %d", H[i]);
	}
}

void main()
{
	int i;
	scanf("%d", &n);

	nn = n;

	for (i = 1; i <= n; i++)
	{
		scanf("%d", H + i);
	}
	rBuildHeap(1);
	inPlaceHeapSort();
	printfArray();
}
