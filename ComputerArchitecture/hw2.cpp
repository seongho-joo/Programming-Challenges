#include <iostream>
#include <cmath>
#include <fstream>
#define MAX 8
#define SHIFT 16
using namespace std;
string multiplicand = "00000000"; //피승수
string multiplier = multiplicand; // 승수
string product = "0000000000000000"; // 곱셈 결과
int x, y; // 피승수, 승수
string Complement(string binary, int size) { // 피승수와 승수가 음수 일 때 2의 보수화
	int carry = 1;
	for (int i = 0; i < size; i++) {
		if (binary[i] == '1') binary[i] = '0';
		else binary[i] = '1';
	}
	if ((binary[size - 1] - 48) + carry == 1) {
		binary[size - 1] = '1'; carry = 0;
	}
	else {
		for (int i = size - 1; i >= 0; i--) {
			if ((binary[i] - 48) + carry == 2) {
				carry = 1; binary[i] = '0';
				continue;
			}
			else {
				binary[i] = '1';
				break;
			}
		}
	}
	return binary;
}
string binarization(int decimal) { // 십진수를 2진수로 변환
	string binary = "00000000";
	if (decimal < 0) decimal *= -1;
	for (int i = MAX - 1; i > 0; i--) {
		binary[i] = (decimal % 2) + 48;
		decimal /= 2;
		if (decimal < 2) {
			binary[--i] = decimal + 48;
			break;
		}
	}
	return binary;
}
class Shift_adder { // 쉬프트-덧셈 알고리즘
public:
	int decimal() { // 누적 부분곱을 10진수로 변환
		int res = 0;
		int square = 0;
		for (int i = SHIFT - 1; i > 0; i--)
			res += (product[i] - 48) * (int)pow(2, square++);
		if (product[0] == '1') res -= pow(2, 15);
		return res;
	}
	void adder(string temp) { // 누적부분곱 덧셈
		int carry = 0;
		for (int i = SHIFT - 1; i >= 0; i--) {
			if (temp[i] == '0' || product[i] == '0') {
				int num = (temp[i] - 48) + (product[i] - 48);
				product[i] = num + 48;
			}
			else {
				carry = 1;
				product[i] = '0';
				for (int j = i - 1; j >= 0; j--) {
					if ((temp[j] - 48) + carry == 2) {
						carry = 1; temp[j] = '0';
					}
					else {
						temp[j] = '1';
						break;
					}
				}
			}
		}
	}
	void rightShift() { // 누적 부분곱 쉬프트
		for (int i = SHIFT - 1; i >= 0; i--) {
			if (product[i] == '0') continue;
			else {
				if (i + 1 > SHIFT - 1) product[i] = '0';
				else {
					product[i + 1] = product[i];
					product[i] = '0';
				}
			}
		}
	}
	string operationMulti(string tmp) { // 피승수 쉬프트
		string shift = "0000000000000000";
		for (int i = SHIFT - 1; i > -1; i--) {
			if (tmp[i] == '0') continue;
			else {
				if (i - 8 == -1) break;
				shift[i - 8] = tmp[i];
			}
		}
		return shift;
	}
	void multiplication() { // 곱셈
		string tmp = "00000000";
		tmp += multiplicand;
		tmp = operationMulti(tmp);
		for (int i = MAX - 1; i > -1; i--) { //  i 승수
			string temp = "0000000000000000"; //  누적 부분곱
			for (int j = SHIFT - 1; j > -1; j--) { // j 피승수
				if (multiplier[i] == '0') break;
				else {
					if (tmp[j] == '0') continue;
					int calc = (tmp[j] - 48) * (multiplier[i] - 48);
					temp[j] = calc + 48;
				}
			}
			adder(temp);
			rightShift();
		}
		if (x < 0 && y >0 || x > 0 && y < 0)
			product = Complement(product, SHIFT);
	}
};
class Booth { // booth 알고리즘
public:
	string boothShift(string temp) { // left shift 함수
		string tmp = "0000000000000000";
		for (int i = SHIFT - 1; i > 0; i--)
			tmp[i - 1] = temp[i];
		return tmp;
	}
	Booth() {
		if (x < 0) multiplicand = Complement(multiplicand, MAX); // 음수 이면 2의 보수화
		if (y < 0) multiplier = Complement(multiplier, MAX); // 음수 일 때 2의 보수화
		Shift_adder sa; // add함수 사용하려고 선언
		string booth = multiplier; // 00 11 10 01 판단
		string temp;
		if (x>0) // 피승수가 양수 일 때
			temp = "00000000";
		else temp = "11111111"; // 음수일 때
		temp += multiplicand;
		booth += "0"; // LSB에 0 추가
		product = "0000000000000000"; // 부분곱 초기화
		for (int i = MAX; i > 0; i--) {
			if (booth[i] == '0' && booth[i - 1] == '0') { // shifting
				temp = boothShift(temp);
			}
			else if (booth[i] == '1' && booth[i - 1] == '1') { // shifting
				temp = boothShift(temp);
			}
			else if (booth[i] == '0' && booth[i - 1] == '1') { // 10 : sub + shifting
				string complent = Complement(temp, SHIFT); // 2의 보수로 바꾸고 add
				sa.adder(complent); // 0000 0000 0000 0000 + 1111 1010
				temp = boothShift(temp);
			}
			else { // 01 : add + shifting
				sa.adder(temp);
				temp = boothShift(temp);
			}
		}
		//if (x < 0 && y >0 || x > 0 && y < 0)
		//product = Complement(product, SHIFT);
	}
};
int main() {
	/*피승수와 승수를 주어졌을 때 덧셈-시프트 알고리즘과 booth알고리즘으로 곱셈결과를 나타내는 과제*/
	ifstream inp("input.text");
	ofstream out("output.text");
	Shift_adder sa;
	cin >> x >> y;
	if (x > 127 || y > 127) {
		out << "Error : Overflow 프로그램을 종료합니다.\n" << endl;
		return 0;
	}
	else if (x < -128 || y < -128) {
		out << "Error : Overflow 프로그램을 종료합니다.\n" << endl;
		return 0;
	}
	else {
		multiplicand = binarization(x); // 피승수 2진수화
		multiplier = binarization(y); // 승수 2진수화
		sa.multiplication(); // 시프트-덧셈 알고리즘 함수
		cout << "시프트-덧셈 알고리즘2 {" << endl << "  product : ";
		for (int i = 0; i < SHIFT; i++) {
			if (i == 3 || i == 7 || i == 11) cout << product[i] << " "; // 4칸씩 끊어서 출력
			else cout << product[i];;
		}
		cout << endl << "  Decimal : " << sa.decimal() << "\n}" << "\nBooth 알고리즘 {\n";
		Booth booth;
		cout << "  product : ";
		for (int i = 0; i < SHIFT; i++) {
			if (i == 3 || i == 7 || i == 11) cout << product[i] << " ";
			else cout << product[i];;
		}
		cout << endl << "  Decimal : " << sa.decimal() << "\n}\n";
	}
	inp.close();
	out.close();
	return 0;
}