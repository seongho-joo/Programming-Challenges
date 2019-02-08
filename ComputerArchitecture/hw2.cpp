#include <iostream>
#include <cmath>
#include <fstream>
#define MAX 8
#define SHIFT 16
using namespace std;
string multiplicand = "00000000"; //�ǽ¼�
string multiplier = multiplicand; // �¼�
string product = "0000000000000000"; // ���� ���
int x, y; // �ǽ¼�, �¼�
string Complement(string binary, int size) { // �ǽ¼��� �¼��� ���� �� �� 2�� ����ȭ
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
string binarization(int decimal) { // �������� 2������ ��ȯ
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
class Shift_adder { // ����Ʈ-���� �˰���
public:
	int decimal() { // ���� �κа��� 10������ ��ȯ
		int res = 0;
		int square = 0;
		for (int i = SHIFT - 1; i > 0; i--)
			res += (product[i] - 48) * (int)pow(2, square++);
		if (product[0] == '1') res -= pow(2, 15);
		return res;
	}
	void adder(string temp) { // �����κа� ����
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
	void rightShift() { // ���� �κа� ����Ʈ
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
	string operationMulti(string tmp) { // �ǽ¼� ����Ʈ
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
	void multiplication() { // ����
		string tmp = "00000000";
		tmp += multiplicand;
		tmp = operationMulti(tmp);
		for (int i = MAX - 1; i > -1; i--) { //  i �¼�
			string temp = "0000000000000000"; //  ���� �κа�
			for (int j = SHIFT - 1; j > -1; j--) { // j �ǽ¼�
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
class Booth { // booth �˰���
public:
	string boothShift(string temp) { // left shift �Լ�
		string tmp = "0000000000000000";
		for (int i = SHIFT - 1; i > 0; i--)
			tmp[i - 1] = temp[i];
		return tmp;
	}
	Booth() {
		if (x < 0) multiplicand = Complement(multiplicand, MAX); // ���� �̸� 2�� ����ȭ
		if (y < 0) multiplier = Complement(multiplier, MAX); // ���� �� �� 2�� ����ȭ
		Shift_adder sa; // add�Լ� ����Ϸ��� ����
		string booth = multiplier; // 00 11 10 01 �Ǵ�
		string temp;
		if (x>0) // �ǽ¼��� ��� �� ��
			temp = "00000000";
		else temp = "11111111"; // ������ ��
		temp += multiplicand;
		booth += "0"; // LSB�� 0 �߰�
		product = "0000000000000000"; // �κа� �ʱ�ȭ
		for (int i = MAX; i > 0; i--) {
			if (booth[i] == '0' && booth[i - 1] == '0') { // shifting
				temp = boothShift(temp);
			}
			else if (booth[i] == '1' && booth[i - 1] == '1') { // shifting
				temp = boothShift(temp);
			}
			else if (booth[i] == '0' && booth[i - 1] == '1') { // 10 : sub + shifting
				string complent = Complement(temp, SHIFT); // 2�� ������ �ٲٰ� add
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
	/*�ǽ¼��� �¼��� �־����� �� ����-����Ʈ �˰���� booth�˰������� ��������� ��Ÿ���� ����*/
	ifstream inp("input.text");
	ofstream out("output.text");
	Shift_adder sa;
	cin >> x >> y;
	if (x > 127 || y > 127) {
		out << "Error : Overflow ���α׷��� �����մϴ�.\n" << endl;
		return 0;
	}
	else if (x < -128 || y < -128) {
		out << "Error : Overflow ���α׷��� �����մϴ�.\n" << endl;
		return 0;
	}
	else {
		multiplicand = binarization(x); // �ǽ¼� 2����ȭ
		multiplier = binarization(y); // �¼� 2����ȭ
		sa.multiplication(); // ����Ʈ-���� �˰��� �Լ�
		cout << "����Ʈ-���� �˰���2 {" << endl << "  product : ";
		for (int i = 0; i < SHIFT; i++) {
			if (i == 3 || i == 7 || i == 11) cout << product[i] << " "; // 4ĭ�� ��� ���
			else cout << product[i];;
		}
		cout << endl << "  Decimal : " << sa.decimal() << "\n}" << "\nBooth �˰��� {\n";
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