#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
	size_t n = (size_t)(r - l);
	if (n <= 1) return;
	int *m = l + n/2;
	sort_int_aux(l, m, tmp);
	sort_int_aux(m, r, tmp);
	merge_int(l, m, m, r, tmp);
	memcpy(l, tmp, n * sizeof(int));
}

void sort_int(int *l, int *r) {
	size_t n = (size_t)(r - l);
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

#define MAXN 400100

int a[MAXN];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		a[2*i+0] = 2*l + 0;
		a[2*i+1] = 2*r + 1;
	}

	sort_int(a, a + 2*n);

	int cnt = 0;
	int ans = 0;
	for (int i = 0; i < 2*n; ++i) {
		if (a[i] % 2 == 0) {
			cnt += 1;
			if (cnt > ans) ans = cnt;
		} else {
			cnt -= 1;
		}
	}

	printf("%d\n", ans);

}
