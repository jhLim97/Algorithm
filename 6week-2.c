//»çÀü 2¹ø

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int main()
{
	int *A, n, m, k, i, j, result, r;
	scanf("%d %d", &n, &k);

	A = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", A + i);
	}

	r = n - 1;
	i = 0, j = n - 1;
	if (A[r] < k)
	{
		result = n;
		i = j + 1;
	}


	while (i <= j)
	{
		m = (i + j) / 2;
		if (k > A[m])
			i = m + 1;
		else if (k < A[m])
		{
			if (A[m - 1] < k)
			{
				result = m;
				break;
			}
			j = m - 1;
		}
		else {
			result = m;
			break;
		}
	}
	printf(" %d", result);

	return 0;

}