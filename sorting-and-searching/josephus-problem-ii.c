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

#define IMPLEMENT_ALGORITHMS(T) \
void merge_##T(T *l1, T *r1, T *l2, T *r2, T *out) { \
	while (l1 < r1 && l2 < r2) *out++ = (*l2 < *l1 ? *l2++ : *l1++); \
	while (l1 < r1) *out++ = *l1++; \
	while (l2 < r2) *out++ = *l2++; \
} \
 \
void sort_##T##_aux(T *l, T *r, T *tmp) { \
	size_t n = (size_t)(r - l); \
	if (n <= 1) return; \
	T *m = l + n/2; \
	sort_##T##_aux(l, m, tmp); \
	sort_##T##_aux(m, r, tmp); \
	merge_##T(l, m, m, r, tmp); \
	memcpy(l, tmp, n * sizeof(T)); \
} \
 \
void sort_##T(T *l, T *r) { \
	size_t n = (size_t)(r - l); \
	T *tmp = malloc(n * sizeof(T)); \
	sort_##T##_aux(l, r, tmp); \
	free(tmp); \
} \
 \
void reverse_##T(T *l, T *r) { \
	while (l < r-1) { \
		T temp = *l; \
		*l = *(r-1); \
		*(r-1) = temp; \
		++l; \
		--r; \
	} \
}

IMPLEMENT_ALGORITHMS(int)
IMPLEMENT_ALGORITHMS(ll)

#endif

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

int query_impl(int l, int r) {
	int ql = ft_query(l);
	int qr = ft_query(r);
	int x = qr - ql;
	return r - l - x;
}

int tot;
int n;

int query_array(int l, int r) {
	if (l <= r) return query_impl(l, r);
	else        return tot - query_impl(r, l);
}

ll query(int l, ll k) {
	int r = (int)((l + k) % n);
	ll vueltas = k / n;
	return tot * vueltas + query_array(l, r);
}

int eliminado[MAXN];
void eliminar(int i) {
	assert(!eliminado[i]);
	ft_update(i, 1);
	eliminado[i] = 1;
	tot--;
}

int main() {

	int k;
	scanf("%d%d", &n, &k);

	tot = n;
	
	int l = 0;
	for (int i = 0; i < n; ++i) {
		ll lo = -1;                 // FALSE
		ll hi = (ll)n * (k+1) + 10; // TRUE
		while (hi - lo > 1) {
			ll mi = (lo + hi) / 2;
			if (query(l, mi+1) >= k+1) hi = mi;
			else                       lo = mi;
		}

/*
		DBG_INT((int)hi);
		DBG_INT((int)(query(l, hi+1)));
		DBG_INT(query(l, hi+1) >= k+1);
		DBG_INT(l);
		for (int j = 0; j < n; ++j) {
			if (!eliminado[j]) {
				DBG_INT(j);
			}
		}
*/

		l = (int)((l+hi)%n);

/*
		DBG_INT(l);
		for (int j = 0; j < n; ++j) {
			printf("%d", eliminado[j]);
		}
		printf("\n");
*/

		eliminar(l);

		printf("%d", l+1);
		putchar(" \n"[i==n-1]);
	}

}
