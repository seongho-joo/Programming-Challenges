#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define N 110
#define MAX 1000000
int M, table[N]; // �迭ũ��, �ؽ����̺�
int check[MAX];
char ch; // *�� ���� ����
double alpha; // ���� �Ǽ� ��
int key; // Ű ��

		 // key���� �ؽ����̺��� ã�� �Լ�
void printTable(FILE *out) {
	for (int i = 0; i < M; i++) {
		if (table[i] != 0)
			fprintf(out, "[%d,%d]\n", i, table[i]);
		else continue;
	}
}
// �ؽ����� ����ϴ� �Լ�
void hashCal() {
	int temp = key * alpha; // mul�� 0.xx�� ����� ����
	double mul = key * alpha;
	int index;
	mul -= temp; // �ڿ� �Ҽ����� �����
	mul = floorf(mul * 100) / 100; // �Ҽ��� 2��° �ڸ����ķ� ����
	index = (int)(mul * M); // �ؽ����̺� �ε����� ����� ����
	if (table[index] != 0) { // �浹�� �߻����� ��
		for (int i = index; i < M; i++) {
			if (i == M - 1 && table[i] != 0) i %= M - 1; //  M-1�� �ڸ��� á���� ��带 ����� 0���� �ٽ� �̵�
			if (table[i] == 0) {
				table[i] = key;
				break;
			}
		}
	}
	else
		table[index] = key;
	check[key] = 1;
}

int main() {
	FILE *inp = fopen("hw2.inp", "rt");
	FILE *out = fopen("hw2.out", "wt");
	if (inp == NULL) {
		fprintf(stderr, "can't open %s\n", "hw2.inp");
		exit(1);
	}
	if (out == NULL) {
		fprintf(stderr, "can't open %s\n", "hw2.out");
		exit(1);
	}

	fscanf(inp, "%d", &M);
	fscanf(inp, "%lf", &alpha);
	while (1) {
		fscanf(inp, "%d", &key);
		fscanf(inp, "%c", &ch);
		if (ch == '*') // *�� ������ ����
			break;
		if (check[key]) continue; // �ߺ��� ���� ���� ��
		else hashCal();
	}
	printTable(out);
	fprintf(out, "*");

	fclose(inp);
	fclose(out);
	return 0;
}