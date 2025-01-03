#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {
	int n;
	scanf("%d", &n);

	int const hc[9] = { -1, 0, 6, 28, 96, 252, 550, 1056, 1848 };

	ll c1 = 78;
	ll c2 = 208;
	ll c3 = 298;
	ll c4 = 252;

	for (int k = 1; k <= n; ++k) {
		if (k <= 4) {
			printf("%d\n", hc[k]);
		} else {
			printf("%lld\n", c4);
			c4 += c3;
			c3 += c2;
			c2 += c1;
			c1 += 12;
		}
	}
}

