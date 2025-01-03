#include <stdio.h>

int a[200100];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n;++i) {
		scanf("%d", &a[i]);
	}

	long long ops = 0;

	for (int i = 1; i < n; ++i) {
		if (a[i] < a[i-1]) {
			int dif = a[i-1] - a[i];
			a[i] += dif;
			ops += dif;
		}
	}

	printf("%lld\n", ops);
}
