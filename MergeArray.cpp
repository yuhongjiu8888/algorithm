#include <stdio.h>

//合并两个有序数组，把b合并到a中
void MergeArray(int a[], int m, int b[], int n) {
	int *p = &a[m - 1];
	int *q = &b[n - 1];
	int *r = &a[m + n - 1];

	while (m + n > 0) {
		if (m > 0 && n > 0) {
			if (*p > *q) {
				*r = *p;
				--m;
				--p;
				--r;
			}
			else {
				*r = *q;
				--n;
				--q;
				--r;
			}
		}
		else {
			while (m--) {
				*r = *p;
				--p;
				--r;
			}

			while (n--) {
				*r = *q;
				--q;
				--r;
			}
		}
	}
}

int main()
{
	int a[10] = { 1,3,5,7,9 };
	int b[] = { 2,4,6,8,10 };
	int m = 5;
	int n = 5;

	MergeArray(a, m, b, n);
	for (int i = 0; i < m+n; i++) {
		printf("%d\n", a[i]);
	}
	

	return 0;
}