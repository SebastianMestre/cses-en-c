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

int ft[MAXN+1];

int ft_query(int i0) {
	int x = 0;
	for (int i = i0; i > 0; i -= i & -i)
		x += ft[i];
	return x;
}

void ft_update(int i0, int x) {
	for (int i = i0+1; i <= MAXN; i += i & -i)
		ft[i] += x;
}

void compress(int *a, int n) {
	int tmp[n];
	for (int i = 0; i < n; ++i) {
		tmp[i] = a[i];
	}
	sort_int(tmp, tmp+n, default_compare_int);
	for (int i = 0; i < n; ++i) {
		a[i] = (int)(lower_bound_int(tmp, tmp+n, a[i]) - tmp);
	}
}

int x[MAXN];
int y[MAXN];
int p[MAXN];
int ans[MAXN];
int n;

int cmp_by_x(int i, int j) {
	return x[i] != x[j] ? x[i] > x[j] : y[i] < y[j];
}

void solve() {
	memset(ft, 0, sizeof(ft));

	for (int i = 0; i < n; ++i) {
		p[i] = i;
	}

	sort_int(p, p+n, cmp_by_x);

	for (int ix = 0; ix < n; ++ix) {
		int i = p[ix];
		ans[i] = ft_query(y[i] + 1);
		ft_update(y[i], 1);
	}

	for (int i = 0; i < n; ++i) {
		printf("%d", ans[i]);
		putchar(" \n"[i==n-1]);
	}
}

int main() {

	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &x[i]);
		scanf("%d", &y[i]);
	}

	compress(x, n);
	compress(y, n);

	solve();

	for (int i = 0; i < n; ++i) {
		x[i] = n-1 - x[i];
		y[i] = n-1 - y[i];
	}

	solve();


}
