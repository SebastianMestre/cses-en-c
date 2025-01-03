#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {
	int q;
	scanf("%d", &q);

	while (q--) {
		ll k;
		scanf("%lld", &k);
		k -= 1;

		ll cant_num = 9;
		ll mini_num = 1;
		for (int d = 1; d <= 17; ++d) {

			ll cant_dig = cant_num * d;

			if (k < cant_dig) {

				ll k_dig = k % d;
				ll k_num = k / d;

				ll num = mini_num + k_num;

				ll i_dig = d-1 - k_dig;

				while (i_dig--) num /= 10;

				ll dig = num % 10;

				printf("%lld\n", dig);

				break;
			} else {
				k -= cant_dig;
			}

			cant_num *= 10;
			mini_num *= 10;
		}
	}
}
