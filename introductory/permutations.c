#include <stdio.h>

int a[200100];

int main() {
	int n;
	scanf("%d", &n);

	if (n == 2 || n == 3) {
		printf("NO SOLUTION\n");
	} else if (n == 4) {
		printf("2 4 1 3\n");
	} else {
		for (int i = 0; i < n; ++i) {
			if (i % 2 == 0) {
				printf("%d", i / 2 + 1);
			} else {
				printf("%d", i / 2 + (n+1) / 2 + 1);
			}
			putchar(" \n"[i == n-1]);
		}
	}
}
