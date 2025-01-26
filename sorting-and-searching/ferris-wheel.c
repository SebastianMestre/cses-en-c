#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

#if 1
void merge_int(int *l1, int *r1, int *l2, int *r2, int *out) {
	while (l1 < r1 && l2 < r2) *out++ = (*l2 < *l1 ? *l2++ : *l1++);
	while (l1 < r1) *out++ = *l1++;
	while (l2 < r2) *out++ = *l2++;
}

void sort_int_aux(int *l, int *r, int *tmp) {
	int n = r - l;
	if (n <= 1) return;
	int *m = l + n/2;
	sort_int_aux(l, m, tmp);
	sort_int_aux(m, r, tmp);
	merge_int(l, m, m, r, tmp);
	memcpy(l, tmp, n * sizeof(int));
}

void sort_int(int *l, int *r) {
	int n = r - l;
	int *tmp = malloc(n * sizeof(int));
	sort_int_aux(l, r, tmp);
	free(tmp);
}

void reverse_int(int *l, int *r) {
	while (l < r-1) {
		int temp = *l;
		*l = *(r-1);
		*(r-1) = temp;
		++l;
		--r;
	}
}
#endif

int a[200100];

int main() {
	int n, x;
	scanf("%d%d", &n, &x);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	sort_int(a, a+n);
	reverse_int(a, a+n);

	int k = 0;
	for (int i = 0; i < n-k-1; ++i) {
		if (a[i] + a[n-k-1] <= x) {
			++k;
		}
	}

	printf("%d\n", n - k);
}
