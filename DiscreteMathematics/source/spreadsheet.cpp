#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
// row는 숫자, column은 문자
string Number(string Cell, int size) { // 셀 이름 -> 예전 셀이름
	string result, tmp; // result는 결과 tmp는 셀이름을 넣는 변수
	stringstream  row, col; // 숫자를 문자로 바꿔주는 타입 <sstream>
	int num = 0; //  row 열 / BC23일 경우 23을 넣는 변수
	int number = 0; // col 열  BC를 55로 바꾸는 변수
	for (int i = 0; i < size; i++) {
		if (Cell[i] >= 65) 
			tmp += Cell[i];
		else {
			num *= 10;
			num += (int)(Cell[i] - 48);
		}
	}
	int j = 0, tmp_size = tmp.length();
	for (int i = tmp_size - 1; i >= 0; i--, j++) // BC가 저장되어 있으면 26^0*2 + 26^1*1
		number += (int)pow(26, i)*(tmp[j] - 64); // pow가 제곱해주는 함수
	row << num; 
	col << number;
	result = "R";
	result += row.str();
	result += "C";
	result += col.str();
	return result;
}
string Column(string Cell, int size) { // 예전 셀 이름 -> 셀 이름
	string col = "", row = "", result;
	int num = 0, index = 0; // R23C55일 경우  55를 저장하는 변수
	int div, mod;
	for (int i = 0; i < size; i++) {
		if (Cell[i + 1] == 'C') {
			index = i + 2; // R23C55 가 저장되어있으면 C를 만나고 그다음 인덱스 번호를 저장 하고 for문 종료
			break;
		}
		row += Cell[i + 1]; 
	}
	for (index; index < size; index++) { // RxxCyy 일 때 yy를 저장해주는 for문
		num *= 10;
		num += (Cell[index] - 48);
	}
	div = num / 26; 
	mod = num % 26;
	if (mod == 0) { mod = 26;  div--; } // 나머지가 0이면 알파벳이 Z라는 뜻인데 나머지를 26 더해주고 몫을 1 빼주는 조건
	if (num<27) { // num이 27보다 작으면 A~Z 하나만 나올 경우
		col += (mod + 64);
	}
	else {
		if (div > 26) { // 몫이 26보다 클 때
			while (div > 26) { // 나눈 몫이 26보다 클 때까지 돎
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