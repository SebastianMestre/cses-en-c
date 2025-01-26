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

#define LLEGA 0
#define SE_VA 1
typedef struct {
	int tag, time, id;
} Evt;

int n;
Evt events[MAXN*2];
int p[2*MAXN];
int ans[MAXN];

#define BLK 500
int libre[MAXN];
int libre_blk[MAXN/BLK+1];

int cmp_evt(int i, int j) {
	if (events[i].time == events[j].time)
		return events[i].tag < events[j].tag;
	return events[i].time < events[j].time;
}

int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		events[i*2+0] = (Evt) { LLEGA, l, i };
		events[i*2+1] = (Evt) { SE_VA, r, i };
	}

	for (int i = 0; i < 2*n; ++i) p[i] = i;
	sort_int(p, p+2*n, cmp_evt);

	for (int i = 0; i < n; ++i) {
		libre[i] += 1;
		libre_blk[i/BLK] += 1;
	}

	for (int ix = 0; ix < 2*n; ++ix) {
		int i = p[ix];

		if (events[i].tag == LLEGA) {
			int j = 0;
			while (!libre_blk[j/BLK]) j += BLK;
			while (!libre[j]) j++;
			ans[events[i].id] = j;
			libre[j] -= 1;
			libre_blk[j/BLK] -= 1;
		} else {
			int j = ans[events[i].id];
			libre[j] += 1;
			libre_blk[j/BLK] += 1;
		}
	}

	int max_hab = 0;
	for (int i = 0; i < n; ++i) {
		if (ans[i] > max_hab) {
			max_hab = ans[i];
		}
	}
	printf("%d\n", max_hab+1);

	for (int i = 0; i < n; ++i) {
		printf("%d", ans[i]+1);
		putchar(" \n"[i==n-1]);
	}

}
