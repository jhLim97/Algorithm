//우선순위 큐 1번
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

	for (i = n - 1; i > 0; i--)
	{
		temp = arr[i];
		emp = i;
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[emp] < arr[j])
			{
				emp = j;
			}
		}
		arr[i] = arr[emp];
		arr[emp] = temp;
	}

	for (i = 0; i < n; i++)
	{
		printf(" %d", arr[i]);
	}

	return 0;
}