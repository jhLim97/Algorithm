#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

int H[100] = { 0 };
int n = 0;
void insertItem(int key);

int removeMax();

void upHeap(int i);

void downHeap(int i);

void printHeap();


void insertItem(int key)
{
	n++;
	H[n] = key;
	upHeap(n);
}


void upHeap(int i)
{
	int temp;

	if (i > 1)
	{
		if (H[i] >= H[i / 2])
		{
			temp = H[i];
			H[i] = H[i / 2];
			H[i / 2] = temp;
			upHeap(i / 2);
		}
	}
}



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



int removeMax()
{
	int key;
	key = H[1];
	H[1] = H[n];
	H[n] = 0;
	n = n - 1;
	downHeap(1);
	return key;
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


void main()
{
	int num, dnum;
	char order;
	dnum = 0;

	scanf("%c", &order);

	while (order != 'q')
	{
		switch (order)
		{
		case 'i': {
			getchar(); scanf("%d", &num);
			insertItem(num);
			printf("0\n");
			break; }
		case 'd': {
			dnum = removeMax();
			printf("%d\n", dnum);
			break;
		}
		case 'p': {
			printHeap();
			break;
		}
		}
		if (n == 99)
			break;
		getchar();
		scanf("%c", &order);
	}


}

