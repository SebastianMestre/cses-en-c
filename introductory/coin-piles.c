#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {

	int t;
	scanf("%d", &t);

	while (t--) {
		int a, b;
		scanf("%d%d", &a, &b);

		int mini = a < b ? a : b;

		int dif_abs = a - b;
		if (dif_abs < 0) dif_abs = -dif_abs;

		if ((a + b) % 3 == 0 && mini >= dif_abs) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}


}
