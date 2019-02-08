#include<iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

typedef struct Football {
	int A_score; // 원정 골
	int Victory; // 승점
	int goal; // 골득실
	int rank; // 랭킹 rank 원소가 클수록 순위는 높음
}Football;

void Calculate(Football football[40], int away, int home, int a_score, int h_score) { // 승점구하는 함수
	football[away - 1].goal += a_score - h_score;
	football[home - 1].goal += h_score - a_score;
	football[away - 1].A_score += a_score;
	if (a_score > h_score) // away가 이겼을 때
		football[away - 1].Victory += 3;
	else if (a_score == h_score) { // 비겼을 때
		football[away - 1].Victory += 1;
		football[home - 1].Victory += 1;
	}
	else // home이 이겼을 때
		football[home - 1].Victory += 3;
}

void Rank(Football rank[40], int team) { // 순위 구하는 함수
	for (int i = 0; i < team - 1; i++) {
		for (int j = i + 1; j < team; j++) {
			if (rank[i].Victory < rank[j].Victory)
				rank[i].rank++;
			else if (rank[i].Victory > rank[j].Victory)
				rank[j].rank++;
			else { // 승점이 같을 때
				if (rank[i].goal < rank[j].goal)
					rank[i].rank++;
				else if (rank[i].goal > rank[j].goal)
					rank[j].rank++;
				else {// 골득실이 같을 때
					if (rank[i].A_score < rank[j].A_score)
						rank[i].rank++;
					else if (rank[i].A_score > rank[j].A_score)
						rank[j].rank++;
				}
			}
		}
	}
}

int main() {
	ifstream inp("soccer.inp");
	ofstream out("soccer.out");
	Football football[40];

	int T;
	inp >> T;
	int team, round; // 팀 수, 라운드
	int game = 0; // 한 라운드 동안 경기 수
	char ch;
	int away, home, away_score, home_score;
	for (int t = 1; t <= T; t++) {
		for (int k = 0; k < 40; k++) {
			football[k].A_score = 0;
			football[k].goal = 0;
			football[k].rank = 1;
			football[k].Victory = 0;
		}
		inp >> team >> round;
		game = (team - 1)*round*team;
		for (int i = 0; i < game; i++) {
			inp >> away >> ch >> home >> away_score >> home_score;
			Calculate(football, away, home, away_score, home_score);
		}
		Rank(football, team);
		out << "Test Case #" << t << ":";
		for (int i = 0; i < team; i++)
			out << " " << football[i].rank;
		for (int i = 0; i < team; i++) football[i].rank = 1;
		out << endl;
	}
	inp.close();
	out.close();
	return 0;
}