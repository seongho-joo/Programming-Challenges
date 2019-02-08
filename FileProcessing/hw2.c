#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define N 110
#define MAX 1000000
int M, table[N]; // 배열크기, 해쉬테이블
int check[MAX];
char ch; // *을 받을 변수
double alpha; // 곱할 실수 값
int key; // 키 값

		 // key값을 해쉬테이블에서 찾는 함수
void printTable(FILE *out) {
	for (int i = 0; i < M; i++) {
		if (table[i] != 0)
			fprintf(out, "[%d,%d]\n", i, table[i]);
		else continue;
	}
}
// 해쉬값을 계산하는 함수
void hashCal() {
	int temp = key * alpha; // mul을 0.xx로 만드는 변수
	double mul = key * alpha;
	int index;
	mul -= temp; // 뒤에 소숫점만 사용함
	mul = floorf(mul * 100) / 100; // 소수점 2번째 자리이후로 버림
	index = (int)(mul * M); // 해쉬테이블에 인덱스를 사용할 변수
	if (table[index] != 0) { // 충돌이 발생했을 때
		for (int i = index; i < M; i++) {
			if (i == M - 1 && table[i] != 0) i %= M - 1; //  M-1번 자리가 찼으면 모드를 사용해 0으로 다시 이동
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
		if (ch == '*') // *을 받으면 종료
			break;
		if (check[key]) continue; // 중복된 값이 있을 때
		else hashCal();
	}
	printTable(out);
	fprintf(out, "*");

	fclose(inp);
	fclose(out);
	return 0;
}