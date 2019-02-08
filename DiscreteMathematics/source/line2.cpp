#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

typedef struct Line {
	int *Origin; // ���� ����
	int *Final; // �ٲ� ����
	int *result; // 1~n���� ���� ���� ����
}Line;

// ���� �� �ִ� ���� 0 ~ n - 1
// 1�� ����� ���� �������� �� ������ 2~n�� 1�̻� ����
// ���� ������ 1�� ����� �ٲ� ������ 1���� �� ������ 2 ~ n�� n-1���ϸ� ����
// �� ���� �ڿ� �ִ� ����� ������ �տ� ������ ���� �� +1 : Calculator �Լ�
void Calculator(Line line, int i, int j, int n) { // origin���Ҷ� final���Ұ� ������ final�� ���Ҹ� ���� ��ġ�� �ٲ���
	for (int k = j; k < i; k++) {
		int temp = line.Final[k];
		line.Final[k] = line.Final[k + 1];
		line.Final[k + 1] = temp;
	}
}

void solution(int n, Line line) {
	int man = 0, person = 0, cnt = 0;
	man = line.Origin[0];
	line.result[man - 1] = 0; // ���� ù ��° �� ����� 0�� �� ���� �� ������ 0���� �ʱ�ȭ
	for (int i = n - 1; i >= 0; i--) {
		if (man == line.Origin[i]) continue;
		for (int j = 0; j < n; j++) {
			if (line.Origin[i] == line.Final[j]) {
				person = line.Origin[i];
				line.result[person - 1] = i - j;
				Calculator(line, i, j, n);
				break;
			}
		}
	}
}

int main() {
	ifstream inp("line2.inp");
	ofstream out("line2.out");
	Line line;

	int T; // ����� ��
	inp >> T;
	int n; // ��� ��
	while (T--) {
		inp >> n;
		line = { 0, };
		line.Final = new int[n];
		line.Origin = new int[n];
		line.result = new int[n];

		for (int i = 0; i < n; i++)
			inp >> line.Origin[i];
		for (int i = 0; i < n; i++)
			inp >> line.Final[i];
		solution(n, line);
		for (int i = 0; i < n; i++) {
			if (i < n - 1) 
				out << line.result[i] << " ";
			else 
				out << line.result[i];
		}
		out << endl;
		n = 0;
	}

	delete line.Final;
	delete line.Origin;
	delete line.result;
	inp.close();
	out.close();
	return 0;
}