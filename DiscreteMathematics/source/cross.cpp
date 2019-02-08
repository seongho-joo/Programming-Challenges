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
	in >> T; // ����� ��
	for(int i=1;i<=T;i++) {
		in >> N; // �迭�� ũ��
		int *LineU = new int[N];
		int *LineD = new int[N];

		for (int i = 0; i < N; i++) {
			int num;
			in >> num;
			LineU[num - 1] = i; // ������ ��ġ�� -1�� �ؼ� �־���
		}
		for (int i = 0; i < N; i++) {
			int num;
			in >> num;
			LineD[num - 1] = i; // ������ ��ġ�� -1�� �ؼ� �־���
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