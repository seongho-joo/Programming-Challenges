#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

priority_queue < long long, vector<long long>, greater<long long> > arr; // ÃÖ¼Ò heap

long long solution() {
	long long sum = 0;
	while (true) {
		long long element_1 = arr.top(); arr.pop();
		long long element_2 = arr.top(); arr.pop();

		sum += element_1 + element_2;

		if (arr.empty())
			return sum;
		else 
			arr.push(element_1 + element_2);
	}
}

int main() {
	ifstream inp("add.inp");
	ofstream out("add.out");

	int element;
	long long res = 0;
	while (true) {
		int n;
		inp >> n;
		if (n == 0) break;
		for (int i = 0; i < n; i++) {
			inp >> element;
			arr.push(element);
		}
		res = solution();
		out << res << endl;
	}

	inp.close();
	out.close();
	return 0;
}