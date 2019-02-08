#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string solution(string str) {
	string A = "000000";
	string B = "001111";
	string C = "010011";
	string D = "011100";
	string E = "100110";
	string F = "101001";
	string G = "110101";
	string H = "111010";
	string res, word;
	int arr[8] = { 0, };
	int size = str.length();
	for (int i = 0; i < size; i++) {
		word += str[i];
		if (word.length() == 6) {
			for (int j = 0; j < str.length(); j++) {
				if (word[j] == A[j]) arr[0]++;
				if (word[j] == B[j]) arr[1]++;
				if (word[j] == C[j]) arr[2]++;
				if (word[j] == D[j]) arr[3]++;
				if (word[j] == E[j]) arr[4]++;
				if (word[j] == F[j]) arr[5]++;
				if (word[j] == G[j]) arr[6]++;
				if (word[j] == H[j]) arr[7]++;
			}
			if (arr[0] == 5 || arr[0] == 6) res += "A"; 
			else if (arr[1] == 5 || arr[1] == 6) res += "B";
			else if (arr[2] == 5 || arr[2] == 6) res += "C";
			else if (arr[3] == 5 || arr[3] == 6) res += "D";
			else if (arr[4] == 5 || arr[4] == 6) res += "E";
			else if (arr[5] == 5 || arr[5] == 6) res += "F";
			else if (arr[6] == 5 || arr[6] == 6) res += "G";
			else if (arr[7] == 5 || arr[7] == 6) res += "H";
			else res += "X";
			word = "";
			for (int k = 0; k < 8; k++)
				arr[k] = 0;
			
		}
	}
	return res;
}

int main() {
	ifstream in("mail.inp");
	ofstream out("mail.out");
	int t;
	in >> t;
	int T;
	string str, res;

	while (t--) {
		in >> T;
		in >> str;
		res = solution(str);
		out << res << endl;
	}

	in.close(); out.close();
	return 0;
}