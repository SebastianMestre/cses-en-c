#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

#if 1

typedef int ComparatorInt(int, int);

int default_compare_int(int i, int j) {
	return i < j;
}

void merge_int(int *l1, int *r1, int *l2, int *r2, int *out, ComparatorInt* cmp) {
	while (l1 < r1 && l2 < r2) *out++ = (cmp(*l2, *l1) ? *l2++ : *l1++);
	while (l1 < r1) *out++ = *l1++;
	while (l2 < r2) *out++ = *l2++;
}

void sort_int_aux(int *l, int *r, int *tmp, ComparatorInt* cmp) {
	size_t n = (size_t)(r - l);
	if (n <= 1) return;
	int *m = l + n/2;
	sort_int_aux(l, m, tmp, cmp);
	sort_int_aux(m, r, tmp, cmp);
	merge_int(l, m, m, r, tmp, cmp);
	memcpy(l, tmp, n * sizeof(int));
}

void sort_int(int *l, int *r, ComparatorInt* cmp) {
	size_t n = (size_t)(r - l);
	int *tmp = malloc(n * sizeof(int));
	sort_int_aux(l, r, tmp, cmp);
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


#define BIG_INT 1000000001LL

ll pair(int l, int r) { return l * BIG_INT + r; }
int fst(ll p) { return (int)(p / BIG_INT); }
int snd(ll p) { return (int)(p % BIG_INT); }

int min_int(int a, int b) { return a < b ? a : b; }
int max_int(int a, int b) { return a > b ? a : b; }
int abs_int(int x) { return x < 0 ? -x : x; }
void swap_int(int *a, int *b) { int temp = *a; *a = *b; *b = temp; }

int *upper_bound_int(int *l, int *r, int x) {
	while (l != r) {
		int *m = l + (r-l) / 2;
		if (*m > x) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	return l;
}

int *lower_bound_int(int *l, int *r, int x) {
	while (l != r) {
		int *m = l + (r-l) / 2;
		if (*m >= x) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	return l;
}

#endif

#define MAXN 200100

int n;
int a[MAXN]; // duracion

int p[MAXN];
int q[MAXN];

int cmp_by_a(int i, int j) {
	return a[i] < a[j];
}

int main() {

	int x;
	scanf("%d%d", &n, &x);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	for (int i = 0; i < n; ++i) {
		p[i] = i;
	}
	sort_int(p, p+n, cmp_by_a);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			// fijo i y tambien j

			int wq = 0;
			for (int w = 0; w < n; ++w) {
				if (p[w] != i && p[w] != j) {
					q[wq++] = p[w];
				}
			}

			int target = x - a[i] - a[j];

			int r = n-2;
			for (int l = 0; r - l >= 2; ++l) {
				while (r - l >= 2 && a[q[l]] + a[q[r-1]] > target) --r;
				if (r - l >= 2 && a[q[l]] + a[q[r-1]] == target) {
					int k = q[l];
					int z = q[r-1];
					printf("%d %d %d %d\n", i+1, j+1, k+1, z+1);
					return 0;
				}
			}
		}
	}

	printf("IMPOSSIBLE\n");
}
