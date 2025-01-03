#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {
	int n;
	scanf("%d", &n);

	int res = 1;
	for (int i = 0; i < n; ++i) {
		res *= 2;
		res %= 1000000007;
	}

	printf("%d\n", res);

}
