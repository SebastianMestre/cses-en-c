#include <stdio.h>
#include <stdlib.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

void f(int n, int a, int b) {
	if (n == 1) {
		printf("%d %d\n", a, b);
	} else {
		int c = 6 - a - b;
		f(n-1, a, c);
		printf("%d %d\n", a, b);
		f(n-1, c, b);
	}
}

int main() {

	int n;
	scanf("%d", &n);

	printf("%d\n", (1<<n)-1);

	f(n, 1, 3);

}
