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

#define MAXN 200100

#define BIG 1000000001LL

ll a[MAXN];

ll pair(int l, int r) { return l * BIG + r; }
int fst(ll p) { return (int)(p / BIG); }
int snd(ll p) { return (int)(p % BIG); }

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		a[i] = pair(r, l);
	}

	sort_ll(a, a+n);

	int reach = 0;
	int ans = 0;

	for (int i = 0; i < n; ++i) {
		if (snd(a[i]) >= reach) {
			reach = fst(a[i]);
			ans++;
		}
	}

	printf("%d\n", ans);
}
