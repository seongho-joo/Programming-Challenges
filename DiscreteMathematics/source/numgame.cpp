#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> Table;

void Init() { // Table 초기화 함수
	Table.reserve(10000);
	for (char i = '1'; i <= '9'; i++) {
		for (char j = '1'; j <= '9'; j++) {
			if (i == j) continue;
			else {
				for (char k = '1'; k <= '9'; k++) {
					if (i == k || j == k) continue;
					else {
						for (char l = '1'; l <= '9'; l++) {
							if (i == l || j == l || k == l) continue;
							string s = "";
							s += i;
							s += j;
							s += k;
							s += l;
							Table.push_back(s);
						}
					}
				}
			}
		}
	}
}

int StrikeCheck(string v_num, string num) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) 
		if (v_num[i] == num[i]) cnt++;

	return cnt;
}

int BallCheck(string v_num, string num) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++) 
			if (i != j && v_num[j] == num[i]) cnt++;

	return cnt;
}

void Solution(string num, int strike, int ball) {
	vector<string> newTable;
	newTable.reserve(10000);
	for (int i = 0; i < Table.size(); i++) {
		if (StrikeCheck(Table[i], num) == strike && BallCheck(Table[i], num) == ball)
			newTable.push_back(Table[i]);
	}
	Table = newTable;
	newTable.clear();
}

int main() {
	ifstream inp("numgame.inp");
	ofstream out("numgame.out");
	int T; // 경우의 수
	int k, strike, ball;
	string num;
	inp >> T;
	while (T--) {
		inp >> k;
		Init();
		while (k--) {
			inp >> num;
			inp >> strike >> ball;
			Solution(num, strike, ball);
		}
		out << Table.size() << endl;
		if (Table.size() < 6) {
			for (int i = 0; i < Table.size(); i++) 
				out << Table[i] << endl;
		}
		else {
			for (int i= 0; i <= 2; i++)
				out << Table[i] << endl;
			for(int i = Table.size()-3;i<Table.size();i++)
				out << Table[i] << endl;
		}
		Table.clear();
	}
	inp.close();
	out.close();
	return 0;
}