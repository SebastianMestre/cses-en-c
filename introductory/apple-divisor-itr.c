#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int n;
int a[20];

int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	int res = 1000000000;
	for (int m = 0; m < (1<<(n-1)); m++) {
		ll suma = 0;
		for (int i = 0; i < n; ++i) {
			if ((m>>i) & 1) suma += a[i];
			else            suma -= a[i];
		}
		if (suma < 0) suma = -suma;
		if (suma < res) res = suma;
	}

	printf("%d\n", res);

}
