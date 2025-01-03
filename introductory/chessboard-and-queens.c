#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

char a[8][9];

int adentro(int i, int j) {
	return 0 <= i && i < 8 && 0 <= j && j < 8;
}

int amenaza(int i, int j, int di, int dj) {
	do {
		i += di, j += dj;
	} while (adentro(i, j) && a[i][j] != 'R');
	return adentro(i, j);
}

int reinas(int i) {
	if (i == 8) 
		return 1;

	int total = 0;

	for (int j = 0; j < 8; ++j) {
		if (a[i][j] == '*') continue;

		if (amenaza(i, j, -1, 0)) continue;
		if (amenaza(i, j, -1, 1)) continue;
		if (amenaza(i, j, -1, -1)) continue;

		a[i][j] = 'R';

		total += reinas(i+1);

		a[i][j] = '.';
	}

	return total;
}

int main() {

	for (int i = 0; i < 8; ++i) {
		scanf("%s", a[i]);
	}

	printf("%d\n", reinas(0));
}
