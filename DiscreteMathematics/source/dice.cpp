#include<iostream>
#include<fstream>

using namespace std;

int Find_index(int i) {
	switch (i) {
	case 0: return 5;
	case 1: return 3;
	case 2: return 4;
	case 3: return 1;
	case 4: return 2;
	case 5: return 0;
	}
	return -1;
}
int Find_top(int *dice, int j) {
	for (int i = 0; i < 6; i++)
		if (dice[i] == j) return i;
	return -1;
}
int solution(int **dice, int T) {
	int result = 0, sum = 0, max = 0;
	int top, floor;
	
	for (int i = 1; i <=6; i++) {
		top = Find_top(dice[0], i);
		floor = Find_index(top);
		for (int j = 0; j < 6; j++) {
			if (top != j && floor != j)
				if (max < dice[0][j]) max = dice[0][j];
		}
		sum += max;
		max = 0;

		for (int j = 1; j < T; j++) {
			floor = Find_top(dice[j], dice[j - 1][top]);
			top = Find_index(floor);
			for (int k = 0; k < 6; k++) {
				if (top != k && floor != k) {
					if (max < dice[j][k]) max = dice[j][k];
				}
			}
			sum += max;
			max = 0;
		}
		if (result < sum) result = sum;

		sum = 0;
	}
	return result;
}
	int main() {
		ifstream inp("dice.inp");
		ofstream out("dice.out");

		int T;
		inp >> T;

		int **dice = new int*[T];
		for (int i = 0; i < T; i++)
			dice[i] = new int[6];
		for (int i = 0; i < T; i++) {
			for (int j = 0; j < 6; j++)
				inp >> dice[i][j];
		}

		out << solution(dice, T);

		inp.close();
		out.close();
		return 0;
	}