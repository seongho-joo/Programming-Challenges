#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> entrance; // 입국심사에서 나온 순서

int solution(int N) {
	int count = 1; // 입국심사대의 수
	int temp = 1, last = 0;
	vector<int> q(N);
	q[0] = entrance[0];
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (q[j] < entrance[i]) {
				q[j] = entrance[i]; 
				break;
			}
			else if (q[last] > entrance[i]) {
				last = temp;
				q[temp++] = entrance[i];
				count++;
				break;
			}
		}
	}
	return count;
}

int main() {
	ifstream inp("entrance.inp");
	ofstream out("entrance.out");
	int T; // 경우의 수
	inp >> T;
	while (T--) {
		int N; // 입국 승객 수
		int element;
		inp >> N;
		entrance.reserve(N);
		for (int i = 0; i < N; i++) {
			inp >> element;
			entrance.push_back(element);
		}
		out << solution(N) << endl;
		entrance.clear();
	}

	inp.close();
	out.close();
	return 0;
}