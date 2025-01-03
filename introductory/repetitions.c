#include <stdio.h>

char a[1000100];

int main() {
	scanf("%s", a);

	int cnt = 1;
	int max = 1;

	for (int i = 1; a[i]; ++i) {
		if (a[i] == a[i-1]) {
			cnt += 1;
			if (cnt > max) max = cnt;
		} else {
			cnt = 1;
		}
	}

	printf("%d\n", max);
}
