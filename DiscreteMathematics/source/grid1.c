#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("grid1.inp", "rt");
	FILE *out = fopen("grid1.out", "wt");
	int N, M, t, k, s;
	int count = 0;
	int res = 1, T, cnt = 0;
	int mod, div;
	fscanf(inp, "%d", &T);
	while (T--) {
		fscanf(inp, "%d %d %d %d %d", &N, &M, &t, &k, &s);
		if (t == 1) {
			mod = s % M; div = s / M;
			if (mod == 0) {
				div--; mod = M;
			}
			switch (k) {
			case 1: { // ¡¬ªÛ
				if (div % 2 == 0) { // -> πÊ«‚
					res = M * div + mod;
					fprintf(out, "%d\n", res);
					break;
				}
				else { // <- πÊ«‚
					res = M * div + M + 1 - mod;
					fprintf(out, "%d\n", res);
					break;
				}
			}
			case 2: { // øÏªÛ
				if (div % 2 == 0) {
					res = M * div + M + 1 - mod;
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = M * div + mod;
					fprintf(out, "%d\n", res);
					break;
				}
			}
			case 3: { // øÏ«œ
				if (div % 2 == 0) {
					res = (N - 1 - div)*M + (M - mod + 1);
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = (N - 1 - div)*M + mod;
					fprintf(out, "%d\n", res);
					break;
				}
			}
			case 4: { // ¡¬«œ
				if (div % 2 == 0) {
					res = (N - 1 - div)*M + mod;
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = (N - 1 - div)*M + (M - mod + 1);
					fprintf(out, "%d\n", res);
					break;
				}
			}
			}
		}
		else {
			int line = (s - 1) / N;
			switch (k) {
			case 1: { // ¡¬ªÛ
				if (line % 2 == 0) {
					res = 1 + line + ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = 1 + line + ((N - 1)*M) - ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
			}
			case 2: { // øÏªÛ
				if (line % 2 == 0) {

					res = M - line + ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = M - line + ((N - 1)*M) - ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
			}
			case 3: { // øÏ«œ
				if (line % 2 == 0) {
					res = N * M - line - ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = N * M - line - ((N - 1)*M) + ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}

			}
			case 4: { // ¡¬«œ
				if (line % 2 == 0) {
					res = (N*M - (M - 1)) + line - ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
				else {
					res = (N*M - (M - 1)) + line - ((N - 1)*M) + ((s - 1) % N)*M;
					fprintf(out, "%d\n", res);
					break;
				}
			}
			}

		}
	}
	return 0;
}