#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

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


typedef int KeyFunction(int); // dado un valor, devuelve una clave
typedef unsigned HashFunction(int); // dada una clave, devuelve un hash

typedef struct {
	KeyFunction* kf;
	HashFunction* hf;
	unsigned cap;
	int* buffer;
} *TablaHash;

TablaHash th_crear(unsigned cap, KeyFunction* kf, HashFunction* hf) {
	TablaHash t = malloc(sizeof(*t));
	t->kf = kf;
	t->hf = hf;
	t->cap = cap;
	t->buffer = malloc(cap * sizeof(int));
	memset(t->buffer, -1, cap * sizeof(int));
	return t;
}

void th_insert(TablaHash t, int value) {
	int key = t->kf(value);
	unsigned hash = t->hf(key);
	unsigned pos = hash % t->cap;

	while (1) {
		if (t->buffer[pos] == -1) {
			t->buffer[pos] = value;
			break;
		} else if (t->kf(t->buffer[pos]) == key) {
			// ya esta insertado
			// no hago nada
			break;
		} else {
			pos += 1;
			if (pos == t->cap) pos = 0;
		}
	}
}

int *th_search(TablaHash t, int key) {
	unsigned hash = t->hf(key);
	unsigned pos = hash % t->cap;

	while (1) {
		if (t->buffer[pos] == -1) {
			return NULL;
		} else if (t->kf(t->buffer[pos]) == key) {
			return &t->buffer[pos];
		} else {
			pos += 1;
			if (pos == t->cap) pos = 0;
		}
	}
}

#define MAXN 200100
int n;
int a[MAXN];

int t[MAXN];

int get_key(int idx) {
	return t[idx];
}

unsigned get_hash(int key) {
	return (unsigned)((unsigned long long)key * 2654435761u);
}

TablaHash th;
int cant[MAXN];

int mod(int x) {
	int y = x % n;
	if (y < 0) y += n;
	return y;
}

int add(int x, int y) {
	int z = x + y;
	return z - n * (z >= n);
}

int opp(int x) {
	int y = n - x;
	if (y == n) y = 0;
	return y;
}

int sub(int x, int y) {
	return add(x, opp(y));
}

int main() {

	scanf("%d", &n);
	forn(i, n) scanf("%d", &a[i]);
	forn(i, n) a[i] = mod(a[i]);

	forn(i, n) t[i+1] = add(t[i], a[i]);

	th = th_crear(1500100, get_key, get_hash);

	ll ans = 0;
	forn(r, n+1) {

		int* it = th_search(th, t[r]);
		if (it != NULL) {
			int pos = *it;
			ans += cant[pos];
			cant[pos]++;
		} else {
			th_insert(th, r);
			cant[r] = 1;
		}
	}

	printf("%lld\n", ans);
}
