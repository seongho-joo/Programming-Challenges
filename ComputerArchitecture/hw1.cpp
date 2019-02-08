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
	int square = 0; // ������
	for (int i = size; i > 0; i--)
		des += (binary[i] - 48) * (int)pow(2, square++);
	return des;
}
int Complement1(string binary) { // 1�� ����
	com1 = binary;
	int des = 0;
	int MSB = 0, sr;
	int size = binary.size();
	int square = 0;
	for (int i = 0; i < size; i++) { // 1�� 0����, 0�� 1��
		if (binary[i] == '1') com1[i] = '0';
		else com1[i] = '1';
	}
	des = Decimal(binary);
	MSB = ((binary[0] - 48)* -1);
	sr = (int)pow(2, 7);
	des = sr * MSB + des + 1; // ��ȯ�ڸ��� +1�� ������ؼ� +1�� �����ش�
	return des;
}
int Complement2(string binary) { // 2�Ǻ���
	com2 = binary;
	int MSB = 0, sr;
	int carry = 1;
	int des = 0;
	int size = binary.size();
	int square = 0;
	for (int i = 0; i < size; i++) { // 1�� 0����, 0�� 1��
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
	/* 2������ �־����� �� ��ȣ�� ũ��, 1�� ����, 2�� ������ �ٲ� ����ϴ� ����*/
	ifstream inp("input.text");
	ofstream out("output.text");
	string binary;
	cin >> binary;
	int a = Decimal(binary), b, c;
	if (binary[0] == '1') { // MSB�� 1�� �� (����)
		a *= -1;
		b = Complement1(binary);
		c = Complement2(binary);
		cout << "��ȣ�� ũ��\n" << "- 2����  : " << binary << "\n- 10���� : " << a << endl << endl;
		cout << "1�� ����\n" << "- 2����  : " << binary << "\n- ����ȭ : " << com1 << "\n- 10���� : " << b << endl << endl;
		cout << "2�� ����\n" << "- 2����  : " << binary << "\n- ����ȭ : " << com2 << "\n- 10���� : " << c << endl;
	}
	else { // MSB�� 0�� ��(���)
		b = c = a;
		cout << "��ȣ�� ũ��\n" << "- 2����  : " << binary << "\n- 10���� : " << a << endl << endl;
		cout << "1�� ����\n" << "- 2����  : " << binary << "\n- 10���� : " << b << endl << endl;
		cout << "2�� ����\\" << "- 2����  : " << binary << "\n- 10���� : " << c << endl;
	}
}