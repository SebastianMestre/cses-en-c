#include <stdio.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

char a[1000100];
int cnt[256];

int main() {
	scanf("%s", a);

	for (int i = 0; a[i]; ++i) {
		cnt[a[i]]++;
	}

	char especial = '\0';
	for (char c = 'A'; c <= 'Z'; ++c) {
		if (cnt[c] % 2 == 1) {
			if (especial == '\0') {
				especial = c;
			} else {
				printf("NO SOLUTION\n");
				return 0;
			}
		}
	}

	for (char c = 'A'; c <= 'Z'; ++c) {
		for (int i = 0; i < cnt[c] / 2; ++i) {
			putchar(c);
		}
	}

	if (especial) {
		putchar(especial);
	}

	for (char c = 'Z'; c >= 'A'; --c) {
		for (int i = 0; i < cnt[c] / 2; ++i) {
			putchar(c);
		}
	}

	putchar('\n');
}

