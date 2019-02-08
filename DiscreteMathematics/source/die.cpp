#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAX 6
using namespace std;

vector<int> dice; // 주사위의 모양
string Vector; // 방향
int top, front; // 주사위의 윗면, 전면
int Left, Right;
int tf, ff; // 서로 마주보는 면
int x, y;

// top = (1,4) : 1 front = (5,3) : 2
// left = (0,2) : 4, right = (2,0) : 3
// front가 마주보는면 보다 작으면 left는 마주보는 면이 더작음

int Facing(int face) { // 마주보는 면을 찾는 함수
	switch (face) {
	case 0: return 2;
	case 1: return 4;
	case 2: return 0;
	case 3: return 5;
	case 4: return 1;
	case 5: return 3;
	}
}

void leftFind() { // 왼쪽면을 찾는 함수
	switch (top) {
	case 0:
		switch (front) {
		case 1: Left = 5; break;
		case 3: Left = 1; break;
		case 4: Left = 3; break;
		case 5: Left = 4; break;
		}
		break;
	case 1:
		switch (front) {
		case 0: Left = 3; break;
		case 2: Left = 5; break;
		case 3: Left = 2; break;
		case 5: Left = 0; break;
		}
		break;
	case 2:
		switch (front) {
		case 1: Left = 3; break;
		case 3: Left = 4; break;
		case 4: Left = 5; break;
		case 5: Left = 1; break;
		}
		break;
	case 3:
		switch (front) {
		case 0: Left = 4; break;
		case 4: Left = 2; break;
		case 2: Left = 1; break;
		case 1: Left = 0; break;
		}
		break;
	case 4:
		switch (front) {
		case 0: Left = 5; break;
		case 5: Left = 2; break;
		case 2: Left = 3; break;
		case 3: Left = 0; break;
		}
		break;
	case 5:
		switch (front) {
		case 0: Left = 1; break;
		case 1: Left = 2; break;
		case 2: Left = 4; break;
		case 4: Left = 0; break;
		}
		break;
	}
	Right = Facing(Left); // 왼쪽 면을 알면 오른쪽 면을 알 수 있음
}

void solution(int N) {
	for (int i = 0; i < MAX; i++) { // top과 front 의 인덱스를 구하는 for문
		if (top == dice[i]) { top = i; break; }
	}
	for(int i = 0;i<MAX;i++)
		if (front == dice[i]) {
			front = i; break;
		}

	tf = Facing(top); ff = Facing(front);
	leftFind();
	for (int i = 0; i < N; i++) {
		switch (Vector[i]) {
		case 'E': 
			top = Left;
			tf = Facing(top); ff = Facing(front);
			leftFind();
			y++;
			break;
		case 'W':
			top = Right;
			tf = Facing(top); ff = Facing(front);
			leftFind();
			y--;
			break;
		case 'S':
			front = top;
			top = ff;
			tf = Facing(top); ff = Facing(front);
			leftFind();
			x--;
			break;
		case 'N':
			top = front;
			front = tf;
			tf = Facing(top); ff = Facing(front);
			leftFind();
			x++;
			break;
		}
	}
}

int main() {
	ifstream inp("die.inp");
	ofstream out("die.out");

	int T;
	inp >> T;
	while (T--) {
		int num;
		dice.reserve(MAX);
		for (int i = 0; i < MAX; i++) {
			inp >> num;
			dice.push_back(num);
		}
		inp >> top >> front; // 다이스의 윗면, 다이스의 전면
		int N;
		inp >> N;
		inp >> Vector;
		solution(N);
		out << y << " " << x << " " << dice[top] << " " << dice[front] << endl;
		x = 0; y = 0;
		Vector = "";
		dice.clear();
	}

	inp.close();
	out.close();
	return 0;
}