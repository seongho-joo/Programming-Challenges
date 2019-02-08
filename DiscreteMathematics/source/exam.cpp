#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string goodWord; // ���� ���ڵ��� ����
string combination; // a?a
string caseWord; // combination���� ���� ����
int st_cnt;


int StarCheck(int i) { // * �� ��
	string star = "";
	int cnt = 0, size;
	size = caseWord.size() - combination.size() + 1;
	if (size == 0) return size;

	for (int j = i; j < size + i; j++) star += caseWord[j];
	for (int k = 0; k < star.size(); k++) {
		for (int l = 0; l < goodWord.size(); l++) {
			if (star[k] == goodWord[l]) cnt++;
		}
	}
	if (cnt >= star.size()) return -1;
	else return size;
}

bool QuestionCheck(int i, int k) { // ? �� ��
	int cnt = 0;
	for (int j = 0; j < goodWord.size(); j++) {
		if (goodWord[j] != caseWord[k]) cnt++;
		else {
			cnt = 0;
			break;
		}
	}
	if (cnt == goodWord.size()) return false;
	return true;
}

bool Check() { // caseWord a?a combination aba
	int st_size = 0, size;
	bool check;
	for (int i = 0, k = 0; i < combination.size(); i++, k++) {
		if (st_size == 1) {
			if (size == 0)
				k -= 1;
			else
				k += (size - 1);
			st_size = 0;
		}
		if (combination[i] != caseWord[k]) {
			switch (combination[i]) {
			case '*': {
				st_size = 1;
				size = StarCheck(i);
				if (size == -1) return false;
				break;
			}
			case '?': {
				check = QuestionCheck(i, k);
				if (!check) return false;
				break;
			}
			default: return false;
			}
		}
	}
	return true;
}

int main() {
	ifstream inp("exam.inp");
	ofstream out("exam.out");
	int T;
	inp >> T;
	for (int i = 1; i <= T; i++) {
		int Q; // ���� ��
		inp >> goodWord;
		inp >> combination; // �������ڷ� ���� �� �ִ� ���� ex) a?a
		inp >> Q;
		out << "Test Case: #" << i << endl;
		while (Q--) {
			inp >> caseWord; // ������ �ܾ� ex) aba
			if (Check())
				out << "Yes" << endl;
			else
				out << "No" << endl;
			caseWord = "";
		}
		combination = "";
	}
	inp.close(); out.close();
	return 0;
}