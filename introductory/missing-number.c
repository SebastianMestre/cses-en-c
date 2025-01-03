#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);

	int suma = 0;
	for (int i = 1; i <= n; ++i) {
		suma ^= i;
	}

	for (int i = 0; i < n-1; ++i) {
		int x;
		scanf("%d", &x);
		suma ^= x;
	}

	printf("%d\n", suma);
}
