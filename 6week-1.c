//»çÀü 1¹ø
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int main()
{
	int *A, n, k, i, result;
	scanf("%d %d", &n, &k);

	A = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", A + i);
	}

	result = seek(A, 0, n - 1, k);
	printf(" %d", result);

	return 0;

}

int seek(int *A, int l, int r, int k)
{
	if (A[l] > k)
		return -1;
	int m;
	if (l == r)
		return l;
	m = (l + r) / 2;
	if (k > A[m])
	{
		if (k < A[m + 1])
			return m;
		seek(A, m + 1, r, k);
	}
	else if (k < A[m])
		seek(A, l, m - 1, k);
	else
		return m;
}