#include <stdio.h>
#include <stdlib.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int *codes(int n) {
	if (n == 0) {
		int *b = malloc(sizeof(int));
		b[0] = 0;
		return b;
	}
	int len = 1<<n;
	int *a = codes(n-1);
	int *b = malloc(len * sizeof(int));
	for (int i = 0; i < len/2; ++i) {
		b[i]       = a[i] * 2;
		b[len-i-1] = a[i] * 2 + 1;
	}
	free(a);
	return b;
}

int main() {

	int n;
	scanf("%d", &n);

	int *a = codes(n);

	for (int i = 0; i < (1<<n); ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d", (a[i] >> j) & 1);
		}
		printf("\n");
	}

	free(a);

}
