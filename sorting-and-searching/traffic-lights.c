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

typedef struct { int mx, mn, cant; } Val;
Val const neutro = { INT_MIN, INT_MAX, 0 };
Val suma(Val a, Val b) {
	return (Val) { max_int(a.mx, b.mx), min_int(a.mn, b.mn), a.cant + b.cant };
};

#define MAX_NODOS (MAXN * 3 * 30)
typedef struct {
	Val val;
	int l, r;
} Nodo;
Nodo nodos[MAX_NODOS];
int node_counter = 0;

int n;

typedef int Tree;
Tree const empty_tree = -1;

#define ST_SIZE (1<<30)

Tree make_node() {
	int t = node_counter++;
	nodos[t].val = neutro;
	nodos[t].l = nodos[t].r = empty_tree;
	return t;
}

Val get_val(Tree t) {
	if (t == empty_tree) return neutro;
	return nodos[t].val;
}

Tree insert_aux(Tree t, int x, int l, int r) {
	if (t == empty_tree) t = make_node();
	if (r - l == 1) {
		nodos[t].val = suma(nodos[t].val, (Val) { x, x, 1 });
		return t;
	}
	int m = l + (r - l) / 2;
	if (x < m) nodos[t].l = insert_aux(nodos[t].l, x, l, m);
	else       nodos[t].r = insert_aux(nodos[t].r, x, m, r);
	nodos[t].val = suma(get_val(nodos[t].l), get_val(nodos[t].r));
	return t;
}

Tree erase_aux(Tree t, int x, int l, int r) {
	if (t == empty_tree) assert(0);
	if (r - l == 1) {
		nodos[t].val = suma(nodos[t].val, (Val) { x, x, -1 });
		if (nodos[t].val.cant == 0) nodos[t].val = neutro;
		return t;
	}
	int m = l + (r - l) / 2;
	if (x < m) nodos[t].l = erase_aux(nodos[t].l, x, l, m);
	else       nodos[t].r = erase_aux(nodos[t].r, x, m, r);
	nodos[t].val = suma(get_val(nodos[t].l), get_val(nodos[t].r));
	return t;
}

Tree insert(Tree t, int x) { return insert_aux(t, x, 0, ST_SIZE); }
Tree erase(Tree t, int x) { return erase_aux(t, x, 0, ST_SIZE); }

int ql, qr;
Val query_aux(Tree t, int l, int r) {
	if (t == empty_tree) return neutro;
	if (qr <= l || r <= ql) return neutro;
	if (ql <= l && r <= qr) return nodos[t].val;
	int m = l + (r - l) / 2;
	return suma(query_aux(nodos[t].l, l, m), query_aux(nodos[t].r, m, r));
}
Val query(Tree t, int l, int r) { ql = l; qr = r; return query_aux(t, 0, ST_SIZE); }
int anterior(Tree t, int x) { return query(t, 0, x).mx; }
int siguiente(Tree t, int x) { return query(t, x+1, ST_SIZE).mn; }
int get_max(Tree t) { return query(t, 0, ST_SIZE).mx; }

int main() {
	int x;
	scanf("%d%d", &x, &n);

	Tree semaforos = empty_tree;
	Tree diferencias = empty_tree;

	semaforos = insert(semaforos, 0);
	semaforos = insert(semaforos, x);
	diferencias = insert(diferencias, x);

	for (int i = 0; i < n; ++i) {
		int v;
		scanf("%d", &v);

		int a = anterior(semaforos, v);
		int b = siguiente(semaforos, v);
		semaforos = insert(semaforos, v);

		diferencias = erase(diferencias, b - a);
		diferencias = insert(diferencias, v - a);
		diferencias = insert(diferencias, b - v);

		int ans = get_max(diferencias);

		printf("[%d %d]", i, ans);
		putchar(" \n"[i == n-1]);
	}

}
