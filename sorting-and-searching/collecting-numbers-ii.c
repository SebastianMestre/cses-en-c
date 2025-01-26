#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

#define BIG 1000000001LL

ll pair(int l, int r) { return l * BIG + r; }
int fst(ll p) { return (int)(p / BIG); }
int snd(ll p) { return (int)(p % BIG); }

int min_int(int a, int b) { return a < b ? a : b; }
int abs_int(int x) { return x < 0 ? -x : x; }
void swap_int(int *a, int *b) { int temp = *a; *a = *b; *b = temp; }

#define MAXN 200100

int a[MAXN];
int b[MAXN];

int mayor[MAXN];
int vueltas = 1;
int n;

void actualizar_vueltas(int i) {
	if (i == 0 || i == n) return;
	if (b[i] < b[i-1]) {
		if (mayor[i] == 0) {
			mayor[i] = 1;
			vueltas++;
		}
	} else {
		if (mayor[i] == 1) {
			mayor[i] = 0;
			vueltas--;
		}
	}
}

int main() {
	int m;
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
		--a[i];
	}

	for (int i = 0; i < n; ++i) {
		b[a[i]] = i;
	}

	for (int i = 1; i < n; ++i) {
		if (b[i] < b[i-1]) {
			vueltas++;
			mayor[i] = 1;
		}
	}

	for (int w = 0; w < m; ++w) {
		int i, j;
		scanf("%d%d", &i, &j);
		--i; --j;

		int x = a[i], y = a[j];

		swap_int(&a[i], &a[j]);
		swap_int(&b[x], &b[y]);

		actualizar_vueltas(x);
		actualizar_vueltas(x+1);
		actualizar_vueltas(y);
		actualizar_vueltas(y+1);

		printf("%d\n", vueltas);
	}

}
