#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

char a[10];
int cnt = 0;
char b[40320][10];

int n;
int h[26];

char c[10];
void bt(int i) {
	if (i == n) {
		strcpy(b[cnt++], c);
	} else {
		for (int j = 0; j < 26; ++j) {
			if (h[j]) {
				c[i] = 'a' + j;
				h[j]--;

				bt(i+1);

				h[j]++;
				c[i] = '\0';
			}
		}
	}
}

int main() {
	scanf("%s", a);

	for (int i = 0; a[i]; ++i) {
		n++;
		h[a[i] - 'a']++;
	}

	bt(0);

	printf("%d\n", cnt);

	for (int i = 0; i < cnt; ++i) {
		puts(b[i]);
	}

}
