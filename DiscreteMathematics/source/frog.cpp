#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#define MAX 100
using namespace std;
vector< pair<char, int> > Stone;

int East(int path, int D) {// 서 -> 동
	int distance = 0;
	int length = Stone.size() - 1;
	for (int i = length; i >= 0; i--) {
		if (Stone[i].second < 0) {
			if (length + 1 == 1) {
				distance = D;
				path = max(path, distance);
				continue;
			}
			else if(i==0){
				if (Stone[i + 1].second < 0)
					distance = Stone[i + 2].second;
				else
					distance = Stone[i + 1].second;
				path = max(path, distance);
				continue;
			}
			else {
				
				continue;
			}
		}
		if ((i == length - 1 || i == length) && distance == 0) {
			distance = D - Stone[i].second;
			path = max(path, distance);
			continue;
		}
		else {
			if (i == 0) {
				if (Stone[i + 1].second < 0)
					distance = Stone[i + 2].second - Stone[i].second;
				else
					distance = Stone[i + 1].second - Stone[i].second;
				path = max(distance, path);
			}
			else {
				if (Stone[i - 1].second < 0) {
					if (i - 2 < 0) {
						distance = Stone[i + 2].second - Stone[i].second;
						path = max(distance, path);
						distance = Stone[i].second;
						path = max(distance, path);
					}
					else {
						if (Stone[i + 1].second < 0)
							distance = Stone[i + 2].second - Stone[i].second;
						else
							distance = Stone[i + 1].second - Stone[i].second;
						path = max(distance, path);
						continue;
					}
				}
				else {
					if (i - 1 < 0) {
						distance = Stone[i].second;
						path = max(distance, path);
						continue;
					}
					else {
						if (Stone[i + 1].second < 0)
							distance = Stone[i + 2].second - Stone[i].second;
						else
							distance = Stone[i + 1].second - Stone[i].second;
					}
				}
				path = max(path, distance);
			}
		}
	}
	return path;
}
int West(int D) {
	int path = 0, distance = 0;
	int length = Stone.size();
	for (int i = 0; i < length; i++) {
		if (Stone[i].first == 'B') {
			if (path == 0) {
				path = Stone[i].second; continue;
			}
			else {
				if (Stone[i - 1].first == 'S' && Stone[i - 1].second < 0)
					distance = Stone[i].second - (-1 * Stone[i - 1].second);
				else if (Stone[i - 1].first == 'S' && Stone[i - 1].second > 0)
					distance = Stone[i].second - (-1 * Stone[i - 2].second);
				else
					distance = Stone[i].second - Stone[i - 1].second;
				path = max(distance, path);
				if (i + 1 == length) {
					distance = D - Stone[i].second;
					path = max(distance, path);
					continue;
				}
				continue;
			}
		} // B일 때까지의 if문
		else { // S일 때
			if (path == 0) {
				path = Stone[i].second;
				Stone[i].second *= -1; // 한 번 밟으면 다시 못밟음
				if (length != 1) {
					if (Stone[i + 1].first == 'S') {
						if (i + 2 == length) {
							distance = D - (-1 * Stone[i].second);
							path = max(distance, path);
							i++; continue;
						}
						else {
							i++; continue;
						}
					}
				}
				continue;
			}
			else {
				if (i + 1 == length) { // S가 홀수 일 때
					if (Stone[i - 1].first == 'S') {
						distance = Stone[i].second - (-1 * Stone[i - 2].second);
						path = max(distance, path);
					}
					else {
						distance = Stone[i].second - Stone[i - 1].second;
						path = max(distance, path);
					}
					distance = D - Stone[i].second;
					path = max(distance, path);
					Stone[i].second *= -1;
					i++; continue;
				}
				else if (Stone[i + 1].first == 'S') {
					if (i + 2 == length) { // S가 짝수 일 때
						if (Stone[i - 1].first == 'B') {
							distance = Stone[i].second - Stone[i - 1].second;
							path = max(distance, path);
						}
						else {
							distance = Stone[i].second - (-1 * Stone[i - 2].second);
							path = max(distance, path);
						}
						distance = D - Stone[i].second;
						path = max(distance, path);
						Stone[i].second *= -1;
						i++; continue;
					}
					else {
						if (Stone[i - 1].first == 'B') {
							distance = Stone[i].second - Stone[i - 1].second;
							path = max(distance, path);
							Stone[i].second *= -1;
							i++; continue;
						}
						else {
							distance = Stone[i].second - (-1 * Stone[i - 2].second);
							path = max(distance, path);
							Stone[i].second *= -1;
							i++; continue;
						}
					}
				}
				else {
					if (Stone[i - 1].first == 'B') {
						distance = Stone[i].second - Stone[i - 1].second;
						path = max(distance, path);
						Stone[i].second *= -1; continue;
					}
					else {
						distance = Stone[i].second - (-1 * Stone[i - 2].second);
						path = max(distance, path);
						Stone[i].second *= -1; continue;
					}
				}
			}
		}
	}
	path = East(path, D);
	return path;
}

int main() {
	ifstream inp("frog.inp");
	ofstream out("frog.out");
	Stone.reserve(MAX);
	int T;
	inp >> T;
	int N, D; // 돌의 개수, 돌과 돌사이에 거리
	char k, ch; // 돌 종류, -
	int size;
	int i = 1;
	while (T--) {
		inp >> N >> D;
		while (N--) {
			inp >> k >> ch >> size;
			Stone.push_back(make_pair(k, size));
		}
		out << "Case " << i++ << ": " << West(D) << endl;
		Stone.clear();
	}
	inp.close();
	out.close();
	return 0;
}