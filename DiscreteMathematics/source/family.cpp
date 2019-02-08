#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#define MAX 500002
#pragma warning(disable:4996)
using namespace std;

vector<int> ft; // ���赵
vector<int> check; // �鸰 ���� üũ

int heightCheck(int parent, int height, int N) {
	for (int i = parent;;) {
		if (check[i] != 0) { // i�� �̹� ����� ������ ���
			height += check[i];
			height--;
			return height;
		}
		else if (ft[i] != 0) {
			height++;
			parent = ft[parent];
			i = parent;
			if (height == N) break;
		}
		else {
			check[i] = 1; // i�� root �� ���
			break;
		}
	}
	return height;
}

int parentCheck(int N) {
	int parent;
	int i;
	int height = 1, temp;
	int result = 0;
	for (i = 1; i <= N; i++) {
		height = 1;
		if (ft[i]!=0) {
			height++;
			parent = ft[i];
			temp = heightCheck(parent, height, N);
			result = result > temp ? result : temp;
			check[i] = temp;
			if (result == N) 
				break;
		}
		else check[i] = 1; // i�� root �� ���
	}
	return result;
}

int main() {
	FILE *inp = fopen("family.inp", "rt");
	ofstream out("family.out");
	
	int T; // ����� ��
	int N; // ���赵�� ���� ��
	int p, c; 
	fscanf(inp, "%d", &T);
	while (T--) {
		fscanf(inp, "%d", &N);
		ft.resize(MAX);
		check.resize(MAX);
		for(int i=1;i<N;i++) {
			fscanf(inp, "%d %d", &p, &c);
			ft[c] = p;
		}
		int result = parentCheck(N);
		out << result << endl;
		ft.clear();
		check.clear();
	}
	fclose(inp);
	out.close();
	return 0;
}