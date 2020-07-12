//우선순위 큐 2번
#define   _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int *arr, n, i, j, temp, emp;
	n = 0, i = 0, j = 0, temp = 0, emp = 0;

	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int)*n);

	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	for (i = 1; i < n; i++)
	{
		emp = arr[i];
		j = i - 1;
		while ((j >= 0 && (arr[j] > emp)))
		{
			arr[j + 1] = arr[j];
			j = j - 1;

		}
		arr[j + 1] = emp;
	}

	for (i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}

	return 0;
}