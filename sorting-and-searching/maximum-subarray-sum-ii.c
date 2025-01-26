#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));
#define DBG_LL(x) printf(#x " = %lld\n", (x));

#define forr(i,a,b) for(int i = (int)(a); i < (int)(b); ++i)
#define forn(i,n) forr(i,0,n)

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

ll *lower_bound_ll(ll *l, ll *r, ll x) {
	while (l != r) {
		ll *m = l + (r-l) / 2;
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
int n, k;
int x[MAXN];
int a, b;

ll t[MAXN];
ll c[MAXN];

int tc[MAXN];

int perm[MAXN];

int cmp_t(int i, int j) { return t[i] < t[j]; }

#define BK 500

int cnt[MAXN];
int sb[MAXN / BK + 1];

void insert(int x) {
	cnt[x] += 1;
	sb[x/BK] += 1;
}

void erase(int x) {
	cnt[x] -= 1;
	sb[x/BK] -= 1;
}

int minimo() {
	int i = 0;
	while (i < n+1 && cnt[i] == 0) {
		if (i%BK == 0 && sb[i/BK] == 0 && i+BK < n+1) i += BK;
		else                                          i += 1;
	}
	return i;
}

int main() {
	scanf("%d%d%d", &n, &a, &b);
	forn(i, n) scanf("%d", &x[i]);

	t[0] = 0;
	forn(i, n) t[i+1] = t[i] + x[i];

	forn(i, n+1) perm[i] = i;
	sort_int(perm, perm+n+1, cmp_t);
	forn(i, n+1) c[i] = t[perm[i]];
	forn(i, n+1) tc[i] = lower_bound_ll(c, c+n+1, t[i]) - c;

	ll ans = LLONG_MIN;

	forr(r, a, n+1) {
		if (r-a >= 0) insert(tc[r-a]);
		ll cand = t[r] - c[minimo()];
		if (ans < cand) ans = cand;
		if (r-b >= 0) erase(tc[r-b]);
	}

	printf("%lld\n", ans);
}
