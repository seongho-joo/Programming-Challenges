#include<iostream>
#include<fstream>
using namespace std;
int block[1000][1000];

void solution(int N) {
	int root, left, right;
	int tmp = N;
	while (N--) {
		for (int i = 0; i < tmp-1; i++) {
			for (int j = 0; j < i + 1; j++) {
				root = block[i][j];
				left = block[i + 1][j];
				right = block[i + 1][j + 1];
				if (right != -1 && left != -1) 
					block[i][j] = (left + right) % 100;
				else if (root != -1 && left != -1) {
					if (root - left < 0)
						block[i + 1][j + 1] = (root + 100) - left;
					else
						block[i + 1][j + 1] = root - left;
				}
				else if (root != -1 && right != -1) {
					if (root - right < 0 )
						block[i + 1][j] = (root + 100) - right;
					else
						block[i + 1][j] = root - right;
				}
			}
		}
	}
}

int main() {
	ifstream in("block.inp");
	ofstream out("block.out");
	int T;  // 경우의 수
	in >> T;
	int N, element;
	while (T--) {
		in >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < i + 1; j++) {
				in >> element;
				block[i][j] = element;
			}
		}
		solution(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				out << block[i][j];
				if (i != j)
					out << " ";
			}
			out << endl;
		}
	}
	in.close();
	out.close();
	return 0;
}