#include <iostream>
#include <fstream>
using namespace std;
int main() {
	ifstream in("matrix.inp");
	ofstream out("matrix.out");
	
	int T, n;
	int index;
	int tmp = 0;
	in >> T;
	while (T--) {
		int cnt = 1;
		in >> n;
		int **arr = new int*[n];
		for (int i = 0; i < n; i++)
			arr[i] = new int[n];

		for (int i = 0; i < n; i++) { // 인덱스를 넣는 for문
			for (int j = 0; j < n; j++) {
				in >> index;
				arr[i][j] = index;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				tmp = 0;
				if (arr[i][j] > 1) {
					for (int s = 0; s < n; s++) {
						for (int t = 0; t < n; t++) {
							if (arr[i][j] == arr[i][s] + arr[t][j]) { 
								tmp = 1; break;
							}
						}
						if (tmp == 1) break;
					}
					if (tmp == 0) { cnt = 0; break; }
				}
			}
		}
		out << cnt << endl;
		delete[] arr;
	}
	in.close();
	out.close();
	return 0;
}