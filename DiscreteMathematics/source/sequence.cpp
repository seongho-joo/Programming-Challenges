#include <iostream>
#include <fstream>
using namespace std;

int solution(long long A, long long limit) {
	int res = 0;
	while (A <= limit) {
		if (A == 1) { 
			res++; 
			break; 
		}
		else if (A % 2 == 0) {
			A /= 2;
			res++;
		}
		else {
			A = A * 3 + 1;
			res++;
		}
	}
	return res;
}

int main() {
	ifstream inp("sequence.inp");
	ofstream out("sequence.out");

	long long A, limit;
	int cnt = 1;
	while (1) {
		inp >> A >> limit;
		if (A == -1 && limit == -1) break;
		int res;
		res = solution(A, limit);
		out << "Case " << cnt++ << ": " << "A = " << A << ", limit = " << limit << ", number of terms = " << res << endl;
	}
	
	inp.close();
	out.close();
	return 0;
}