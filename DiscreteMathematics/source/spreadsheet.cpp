#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
// row�� ����, column�� ����
string Number(string Cell, int size) { // �� �̸� -> ���� ���̸�
	string result, tmp; // result�� ��� tmp�� ���̸��� �ִ� ����
	stringstream  row, col; // ���ڸ� ���ڷ� �ٲ��ִ� Ÿ�� <sstream>
	int num = 0; //  row �� / BC23�� ��� 23�� �ִ� ����
	int number = 0; // col ��  BC�� 55�� �ٲٴ� ����
	for (int i = 0; i < size; i++) {
		if (Cell[i] >= 65) 
			tmp += Cell[i];
		else {
			num *= 10;
			num += (int)(Cell[i] - 48);
		}
	}
	int j = 0, tmp_size = tmp.length();
	for (int i = tmp_size - 1; i >= 0; i--, j++) // BC�� ����Ǿ� ������ 26^0*2 + 26^1*1
		number += (int)pow(26, i)*(tmp[j] - 64); // pow�� �������ִ� �Լ�
	row << num; 
	col << number;
	result = "R";
	result += row.str();
	result += "C";
	result += col.str();
	return result;
}
string Column(string Cell, int size) { // ���� �� �̸� -> �� �̸�
	string col = "", row = "", result;
	int num = 0, index = 0; // R23C55�� ���  55�� �����ϴ� ����
	int div, mod;
	for (int i = 0; i < size; i++) {
		if (Cell[i + 1] == 'C') {
			index = i + 2; // R23C55 �� ����Ǿ������� C�� ������ �״��� �ε��� ��ȣ�� ���� �ϰ� for�� ����
			break;
		}
		row += Cell[i + 1]; 
	}
	for (index; index < size; index++) { // RxxCyy �� �� yy�� �������ִ� for��
		num *= 10;
		num += (Cell[index] - 48);
	}
	div = num / 26; 
	mod = num % 26;
	if (mod == 0) { mod = 26;  div--; } // �������� 0�̸� ���ĺ��� Z��� ���ε� �������� 26 �����ְ� ���� 1 ���ִ� ����
	if (num<27) { // num�� 27���� ������ A~Z �ϳ��� ���� ���
		col += (mod + 64);
	}
	else {
		if (div > 26) { // ���� 26���� Ŭ ��
			while (div > 26) { // ���� ���� 26���� Ŭ ������ ��
				col += (mod + 64);
				mod = div % 26;
				div /= 26;
				if (mod == 0) { div--; mod = 26; }
			}
			col += (mod + 64);
			col += (div + 64);
			int size = col.length();
			for (int i = 0; i < size / 2; i++) {
				char tmp = col[i];
				col[i] = col[size - 1 - i];
				col[size - 1 - i] = tmp;
			}
		}
		else {
			col += (div + 64);
			col += (mod + 64);
		}
	}
	result += (col + row);
	return result;
}
int main() {
	ifstream inp("spreadsheet.inp");
	ofstream out("spreadsheet.out");
	
	int T;
	inp >> T;
	string Cell, res;
	while (T--) {
		inp >> Cell;
		int size = Cell.length();
		if (Cell[0] == 'R' &&  Cell[1] < 65) 
				res = Column(Cell, size);
			
		else 
			res = Number(Cell, size);
		out << res << endl;
	}
	inp.close();
	out.close();
	return 0;
}