#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		int x, y;
		scanf("%d%d", &y, &x);

		int capa = x > y ? x : y;

		// impar va hacia derecha y arriba
		int orientacion = capa % 2;

		ll minimo_valor = (ll)(capa-1)*(capa-1)+1;

		int posicion = orientacion == 1 ? x - y : y - x;

		posicion += capa - 1;

		ll valor = minimo_valor + posicion;

		printf("%lld\n", valor);
	}
}

