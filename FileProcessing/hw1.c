#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define N 1000000

int arr1[N];
int arr2[N]; // 정렬된 배열
int tempArr[N];

void merge(FILE * out, int arr2_size, int arr1_size) {
	int i = 0, j = 0; int l = 0;

	while (1) {
		if (i > arr1_size && j > arr2_size) break;
		if (arr1[i] < arr2[j]) {
			fprintf(out, "%d ", arr1[i]);
			i++;
		}
		else if (arr1[i] == arr2[j]) {
			fprintf(out, "%d %d ", arr1[i], arr2[j]);
			i++; j++;
		}
		else {
			fprintf(out, "%d ", arr2[j]);
			j++;
		}
		if (i >= arr1_size) { // arr1배열을 다 돌았을때
			i++;
			for (; j < arr2_size; j++) {
				fprintf(out, "%d ", arr2[j]);
			}
			j++;
		}
		else if (j >= arr2_size) { // arr2배열을 다 돌았을때
			j++;
			for (; i < arr1_size; i++) {
				fprintf(out, "%d ", arr1[i]);
			}
			i++;
		}
	}
}



void intervalSort(int begin, int end, int interval) {
	int temp, j;
	for (int i = begin + interval; i <= end; i += interval) {
		temp = arr1[i];
		for (j = i - interval; j >= begin && temp < arr1[j]; j -= interval) {
			arr1[j + interval] = arr1[j];
		}
		arr1[j + interval] = temp;
	}
}
void shellSort(int n, FILE *out) {
	int interval = n / 2;
	while (interval >= 1) {
		for (int i = 0; i < interval; i++)
			intervalSort(i, n - 1, interval);
		for (int j = 0; j < n; j++) fprintf(out, "%d ", arr1[j]);
		fprintf(out, "\n");

		interval /= 2;
	}
}
int main() {
	FILE *inp, *out;
	inp = fopen("hw1.inp", "rt");
	out = fopen("hw1.out", "wt");
	int element, size, sortSize = 0, mergeSize = 0;
	int cnt = 0, count = 0;
	char ch;

	if (inp == NULL) {
		fprintf(stderr, "can't open %s\n", "hw1.inp");
		exit(1);
	}
	if (out == NULL) {
		fprintf(stderr, "can't open %s\n", "hw1.out");
		exit(1);
	}

	while (1) {
		for (int i = 0;; i++) {
			size = i + 1;
			fscanf(inp, "%d", &element);
			fscanf(inp, "%c", &ch);
			if (ch == '*') break;
			arr1[i] = element;
			if (ch == '\n') break;
		}
		if (ch == '*') break;
		shellSort(size, out);
		if (arr2[0] == 0 && count == 0) {
			for (int i = 0; i < size; i++) arr2[i] = arr1[i];
			memset(arr1, 0, sizeof(arr1));
			sortSize = size;
		}
		else {
			merge(out, sortSize, size);
		}
		count++;
	}
	fprintf(out, "\n*");
	fclose(inp); fclose(out);
	return 0;
}