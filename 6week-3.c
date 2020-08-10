//»çÀü 3¹ø

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

int main()
{
	int a, b, n, k, i, l, r, m;
	char *A;

	scanf("%d %d %d\n", &a, &b, &n);
	A = (char*)malloc(sizeof(char)*n);
	scanf("%s", A);

	l = a, r = b;
	for (i = 0; i < n; i++)
	{
		m = (l + r) / 2;
		if (A[i] == 'Y')
			l = m + 1;
		else if (A[i] == 'N')
			r = m;
	}
	printf("%d", l);

	return 0;

}