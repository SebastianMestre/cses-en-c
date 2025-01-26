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

#endif


#define MAXN 200100
int n, k;
int a[MAXN];
int b[MAXN];

#define BK 500

int cnt[MAXN];
int sb[MAXN / BK + 1];
ll ac[MAXN / BK + 1];

void act(int p, int v) {
	cnt[p] += v;
	sb[p/BK] += v;
	ac[p/BK] += v * b[p];
}

int mediana() {
	int p = (k-1)/2;
	int i = 0;
	int suma = 0;
	while (suma <= p) {
		if (i%BK == 0 && suma + sb[i/BK] <= p) {
			suma += sb[i/BK];
			i += BK;
		} else {
			suma += cnt[i];
			i += 1;
		}
	}
	return i-1;
}

void suma_y_cant(int l, int r, int* out_cant, ll* out_suma) {
	int cant = 0;
	ll suma = 0;
	while (l < r) {
		if (l%BK == 0 && l+BK <= r) {
			suma += ac[l/BK];
			cant += sb[l/BK];
			l += BK;
		} else {
			suma += (ll)cnt[l] * b[l];
			cant += cnt[l];
			l += 1;
		}
	}
	*out_suma = suma;
	*out_cant = cant;
}

int main() {
	scanf("%d%d", &n, &k);
	forn(i, n) scanf("%d", &a[i]);

	forn(i, n) b[i] = a[i];
	sort_int(b, b+n, default_compare_int);
	forn(i, n) a[i] = lower_bound_int(b, b+n, a[i]) - b;

	forn(i, k) act(a[i], 1);

	forn(i, n-k+1) {
		if (i > 0) {
			act(a[i+k-1], 1);
			act(a[i-1], -1);
			putchar(' ');
		}

		int x = mediana();

		int cant_menores; ll suma_menores;
		suma_y_cant(0, x, &cant_menores, &suma_menores);

		int cant_mayores; ll suma_mayores;
		suma_y_cant(x+1, n, &cant_mayores, &suma_mayores);

		ll costo_sup = suma_mayores - (ll) b[x] * cant_mayores;
		ll costo_inf = (ll)b[x] * cant_menores - suma_menores;

		printf("%lld", costo_sup + costo_inf);
	}
	putchar('\n');

}
