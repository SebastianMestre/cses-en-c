#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

#if 1
void merge_int(int *l1, int *r1, int *l2, int *r2, int *out) {
	while (l1 < r1 && l2 < r2) *out++ = (*l2 < *l1 ? *l2++ : *l1++);
	while (l1 < r1) *out++ = *l1++;
	while (l2 < r2) *out++ = *l2++;
}

void sort_int_aux(int *l, int *r, int *tmp) {
	int n = r - l;
	if (n <= 1) return;
	int *m = l + n/2;
	sort_int_aux(l, m, tmp);
	sort_int_aux(m, r, tmp);
	merge_int(l, m, m, r, tmp);
	memcpy(l, tmp, n * sizeof(int));
}

void sort_int(int *l, int *r) {
	int n = r - l;
	int *tmp = malloc(n * sizeof(int));
	sort_int_aux(l, r, tmp);
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
#endif


#define MAXN 200100
#define X    500

int a[MAXN];
int mini[(MAXN+X-1)/X];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	sort_int(a, a+n);

	int const bn = (n+X-1)/X;

	for (int i = 0; i < bn; ++i) {
		mini[i] = a[i * X];
	}

	for (int i = 0; i < m; ++i) {
		int t;
		scanf("%d", &t);

		int ans = -1;

		for (int b = bn-1; b >= 0; --b) {
			if (mini[b] <= t) {

				int l = b*X;
				int r = l+X;
				if (r > n) r = n;

				for (int j = r-1; j >= l; --j) {
					if (a[j] <= t) {

						ans = a[j];
						a[j] = INT_MAX;

						mini[b] = INT_MAX;
						for (int k = l; k < r; ++k) {
							if (a[k] != INT_MAX) {
								mini[b] = a[k];
								break;
							}
						}

						break;
					}
				}

				break;
			}
		}

		printf("%d\n", ans);
	}
}
