#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAYA printf("======================\n")
#define DBG_INT(x) printf(#x " = %d\n", (x));

typedef long long ll;

char a[49];

int di[4] = {0,-1,0,1};
int dj[4] = {1,0,-1,0};
char letra[4] = {'R', 'U', 'L', 'D'};

char visitado[7][7];

int adentro(int i, int j) {
	return 0 <= i && i < 7 && 0 <= j && j < 7;
}

int libre(int i, int j) {
	return adentro(i, j) && !visitado[i][j];
}

int di2[8] = { 0,-1,-1,-1, 0, 1, 1, 1};
int dj2[8] = { 1, 1, 0,-1,-1,-1, 0, 1};

int caminos(int i, int j, int d) {

	if (d == 48) return i == 6 && j == 0;
	if (i == 6 && j == 0) return 0;


	{
		int c = 0;
		for (int k = 0; k < 8; ++k) {
			int i2 = i+di2[k],       j2 = j+dj2[k];
			int i3 = i+di2[(k+1)%8], j3 = j+dj2[(k+1)%8];
			c += (libre(i2, j2) != libre(i3, j3));
		}
		if (c > 2) return 0;
	}

	int total = 0;

	for (int k = 0; k < 4; ++k) {
		int i_ = i + di[k], j_ = j + dj[k];
		if (!libre(i_, j_)) continue;
		if (a[d] != '?' && a[d] != letra[k]) continue;

		visitado[i_][j_] = 1;
		total += caminos(i_, j_, d+1);
		visitado[i_][j_] = 0;
	}

	return total;
}

int main() {
	scanf("%s", a);

	visitado[0][0] = 1;
	int res = caminos(0, 0, 0);
	visitado[0][0] = 0;

	printf("%d\n", res);
}
