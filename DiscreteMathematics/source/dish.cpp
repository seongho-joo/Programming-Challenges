#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int main() {
	FILE * inp = fopen("dish.inp", "rt");
	FILE * out = fopen("dish.out", "wt");
	
	if (inp == NULL) {
		fprintf(stderr, "can't open %s\n", "dish.inp");
		exit(1);
	}
	if (out == NULL) {
		fprintf(stderr, "can't open %s\n", "dish.out");
		exit(1);
	}

	int T = 0, count = T;
	int N = 0;
	int high = 0;
	char dish, temp;

	fscanf(inp, "%d", &T);

	while (1) {
		if (count == T) break;
		fscanf(inp, "%d", &N);
		fscanf(inp, "%c", &dish);
		if (dish == '\n') continue;
		high = 10;
		for (int i = 1; i < N; i++) {
			temp = dish;
			fscanf(inp, "%c", &dish);
			if (temp == dish)
				high += 5;
			else
				high += 10;
		}
		fprintf(out, "%d\n", high);
		count++;
	}
	fclose(inp);
	fclose(out);
	return 0;
}