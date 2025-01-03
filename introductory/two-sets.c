#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

int main() {
	int n;
	scanf("%d", &n);

	if (n%4 == 1 || n%4 == 2) {
		printf("NO\n");
		return 0;
	} else if (n%4 == 0 || n%4 == 3) {
		int c = (n%4 == 3);
		printf("YES\n");
		printf("%d\n", (n+c)/2-c);
		for (int i = 1; i <= (n+c)/4; ++i) {
			if (i-c != 0) printf("%d ", i-c);
			printf("%d ", (n+c)+1-i-c);
		}
		printf("\n");
		printf("%d\n", (n+c)/2);
		for (int i = (n+c)/4+1; i <= (n+c)/2; ++i) {
			printf("%d ", i-c);
			printf("%d ", (n+c)+1-i-c);
		}
		printf("\n");
	}

}
