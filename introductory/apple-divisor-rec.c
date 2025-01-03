#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int n;
int a[20];

int res = 1000000000;
ll suma = 0;

void bt(int i) {
	if (i == n) {
		ll mi_suma = suma > 0 ? suma : -suma;
		if (mi_suma < res) res = mi_suma;
	} else {
		for (int op = 0; op <= 1; ++op) {
			if (op) suma += a[i];
			else    suma -= a[i];
			bt(i+1);
			if (op) suma -= a[i];
			else    suma += a[i];
		}
	}
}

int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}

	bt(0);
	printf("%d\n", res);

}
