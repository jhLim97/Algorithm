//합병정렬퀵정렬2번

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable : 4996)

int findPivot(int *A, int start, int end);

void inPlaceQuickSort(int *A, int l, int r);

void swap(int *A, int l, int r);

int *inPlacePartition(int *A, int l, int r, int k);

void printarray(int *A, int n);


int main()
{
	int *arr, n, i;
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int)*n);

	for (i = 0; i < n; i++)
	{
		scanf("%d", arr + i);
	}

	inPlaceQuickSort(arr, 0, n - 1);

	printarray(arr, n);

	return 0;


}

int findPivot(int *A, int start, int end)
{
	int Pivot;
	srand(time(NULL));
	Pivot = rand() % (end + 1 - start) + start;

	return Pivot;
}

void inPlaceQuickSort(int *A, int l, int r)
{

	int k, *B, b0, b1;

	if (l >= r)
		return;

	k = findPivot(A, l, r);
	B = inPlacePartition(A, l, r, k);
	b0 = B[0] - 1;
	b1 = B[1] + 1;
	inPlaceQuickSort(A, l, b0);
	inPlaceQuickSort(A, b1, r);
}

void swap(int *A, int l, int r)
{
	int temp;
	temp = A[l];
	A[l] = A[r];
	A[r] = temp;
}

int *inPlacePartition(int *A, int l, int r, int k)
{
	int B[2], i, j, p;
	i = l, j = r - 1;

	p = A[k];
	swap(A, k, r);

	while (i <= j)
	{
		while (i <= j && A[i] < p)
			i++;
		while (i <= j && A[j] >= p)
			j--;
		if (i < j)
			swap(A, i, j);
	}
	swap(A, i, r);

	i = l, j = r;
	while (i <= j)
	{
		if (A[i] == p)
		{
			B[0] = i;
			break;
		}
		i++;
	}
	while (i + 1 <= j)
	{
		if (A[i + 1] != p)
			break;
		i++;
	}
	B[1] = i;

	return B;
}

void printarray(int *A, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf(" %d", A[i]);
	}
}