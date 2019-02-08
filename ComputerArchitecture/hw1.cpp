#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;
string com1, com2;
int Decimal(string binary) {
	int des = 0;
	int size = binary.size() - 1;
	int square = 0; // 제곱근
	for (int i = size; i > 0; i--)
		des += (binary[i] - 48) * (int)pow(2, square++);
	return des;
}
int Complement1(string binary) { // 1의 보수
	com1 = binary;
	int des = 0;
	int MSB = 0, sr;
	int size = binary.size();
	int square = 0;
	for (int i = 0; i < size; i++) { // 1은 0으로, 0은 1로
		if (binary[i] == '1') com1[i] = '0';
		else com1[i] = '1';
	}
	des = Decimal(binary);
	MSB = ((binary[0] - 48)* -1);
	sr = (int)pow(2, 7);
	des = sr * MSB + des + 1; // 순환자리를 +1을 해줘야해서 +1을 더해준다
	return des;
}
int Complement2(string binary) { // 2의보수
	com2 = binary;
	int MSB = 0, sr;
	int carry = 1;
	int des = 0;
	int size = binary.size();
	int square = 0;
	for (int i = 0; i < size; i++) { // 1은 0으로, 0은 1로
		if (binary[i] == '1') com2[i] = '0';
		else com2[i] = '1';
	}
	if ((com2[7] - 48) + carry == 1) {
		com2[7] = '1'; carry = 0;
	}
	else {
		for (int i = size - 1; i >= 0; i--) {
			if ((com2[i] - 48) + carry == 2) {
				carry = 1; com2[i] = '0';
				continue;
			}
			else {
				com2[i] = '1';
				break;
			}
		}
	}
	des = Decimal(binary);
	MSB = ((binary[0] - 48)* -1);
	sr = (int)pow(2, 7);
	des = sr * MSB + des;
	return des;
}
int main() {
	/* 2진수가 주어졌을 때 부호와 크기, 1의 보수, 2의 보수로 바꿔 출력하는 과제*/
	ifstream inp("input.text");
	ofstream out("output.text");
	string binary;
	cin >> binary;
	int a = Decimal(binary), b, c;
	if (binary[0] == '1') { // MSB가 1일 때 (음수)
		a *= -1;
		b = Complement1(binary);
		c = Complement2(binary);
		cout << "부호와 크기\n" << "- 2진수  : " << binary << "\n- 10진수 : " << a << endl << endl;
		cout << "1의 보수\n" << "- 2진수  : " << binary << "\n- 보수화 : " << com1 << "\n- 10진수 : " << b << endl << endl;
		cout << "2의 보수\n" << "- 2진수  : " << binary << "\n- 보수화 : " << com2 << "\n- 10진수 : " << c << endl;
	}
	else { // MSB가 0일 때(양수)
		b = c = a;
		cout << "부호와 크기\n" << "- 2진수  : " << binary << "\n- 10진수 : " << a << endl << endl;
		cout << "1의 보수\n" << "- 2진수  : " << binary << "\n- 10진수 : " << b << endl << endl;
		cout << "2의 보수\\" << "- 2진수  : " << binary << "\n- 10진수 : " << c << endl;
	}
}