#include<iostream>
#include<fstream>
using namespace std;

int solution(int N, int *LineU, int *LineD) {
	int cross = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			if (LineU[i]<LineU[j] && LineD[i]>LineD[j]) cross++;
			else if (LineU[i] > LineU[j] && LineD[i] < LineD[j]) cross++;
		}
	}
	return cross;
}
int main() {
	ifstream  in("cross.inp");
	ofstream out("cross.out");

	int T, N;
	in >> T; // 경우의 수
	for(int i=1;i<=T;i++) {
		in >> N; // 배열의 크기
		int *LineU = new int[N];
		int *LineD = new int[N];

		for (int i = 0; i < N; i++) {
			int num;
			in >> num;
			LineU[num - 1] = i; // 원소의 위치를 -1을 해서 넣어줌
		}
		for (int i = 0; i < N; i++) {
			int num;
			in >> num;
			LineD[num - 1] = i; // 원소의 위치를 -1을 해서 넣어줌
		}
		
		int res = solution(N, LineU, LineD);

		out << "Case " << i << ": " << res << "\n";
		delete[] LineU;
		delete[] LineD;
	}
	in.close();
	out.close();
	return 0;
}