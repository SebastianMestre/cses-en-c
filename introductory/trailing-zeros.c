#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {
	int n;
	scanf("%d", &n);

	int res = 0;
	int pot = 1;
	for (int i = 0; i < 13; ++i) {
		pot *= 5;
		res += n / pot;
	}

	printf("%d\n", res);

}
