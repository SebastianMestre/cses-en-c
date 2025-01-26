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

#define MAXN 1100

int n;
int a[MAXN]; // duracion

int p[MAXN];
int q[MAXN];

int cmp_by_a(int i, int j) {
	return a[i] < a[j];
}

typedef int KeyFunction(int); // dado un valor, devuelve una clave
typedef unsigned HashFunction(int); // dada una clave, devuelve un hash

typedef struct {
	KeyFunction* kf;
	HashFunction* hf;
	unsigned cap;
	int* buffer;
} *TablaHash;

int counter = 0;
int vals[MAXN * MAXN / 2];
int idx1[MAXN * MAXN / 2];
int idx2[MAXN * MAXN / 2];

int a[MAXN];

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

int get_key(int value) {
	return vals[value];
}

unsigned get_hash(int suma) {
	return (unsigned)suma * 2654435761u;
}

int main() {

	int x;
	scanf("%d%d", &n, &x);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	TablaHash t = th_crear(3000100, get_key, get_hash);

	for (int i1 = 0; i1 < n; ++i1) {
		for (int i2 = i1+1; i2 < n; ++i2) {
			int tgt = x - a[i1] - a[i2];

			int* result = th_search(t, tgt);
			if (result) {
				int w = *result;
				int i3 = idx1[w];
				int i4 = idx2[w];

				printf("%d %d %d %d\n", i1+1, i2+1, i3+1, i4+1);
				return 0;
			}
		}

		for (int i2 = 0; i2 < i1; ++i2) {
			vals[counter] = a[i1] + a[i2];
			idx1[counter] = i1;
			idx2[counter] = i2;

			th_insert(t, counter++);
		}
	}

	printf("IMPOSSIBLE\n");
}
