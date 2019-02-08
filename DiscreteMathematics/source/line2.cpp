#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

typedef struct Line {
	int *Origin; // 원래 순서
	int *Final; // 바뀐 순서
	int *result; // 1~n까지 뽑은 수를 저장
}Line;

// 뽑을 수 있는 수는 0 ~ n - 1
// 1번 사람이 제일 마지막에 서 있으면 2~n은 1이상 뽑음
// 원래 순서의 1번 사람이 바뀐 순서에 1번에 또 있으면 2 ~ n은 n-1이하를 뽑음
// 나 보다 뒤에 있는 사람이 나보다 앞에 있으면 뽑은 수 +1 : Calculator 함수
void Calculator(Line line, int i, int j, int n) { // origin원소랑 final원소가 같으면 final의 원소를 원래 위치로 바꿔줌
	for (int k = j; k < i; k++) {
		int temp = line.Final[k];
		line.Final[k] = line.Final[k + 1];
		line.Final[k + 1] = temp;
	}
}

void solution(int n, Line line) {
	int man = 0, person = 0, cnt = 0;
	man = line.Origin[0];
	line.result[man - 1] = 0; // 제일 첫 번째 선 사람은 0번 만 뽑을 수 있으니 0으로 초기화
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

	int T; // 경우의 수
	inp >> T;
	int n; // 사람 수
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