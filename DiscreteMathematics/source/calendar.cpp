#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
using namespace std;

int Calendar[6][7]; // type1,2,3을 받았을 때 달력을 넣는 배열
int O_year = 1; // 1년
int O_month = 1; // 1월
int O_day = 1; // 1일

typedef struct Date {
	int year;
	int month;
	int day;
	int count;
	string date;
}Date;
Date date[2];
// 1 3 5 7 8 10 12는 31일까지
// 4 6 9 11은 30일까지
// 2월은 윤달일 때만 29일이고 아닐 때는 28일까지 (yyyy%4==0)
// 1년 1월 1일은 월요일

int Type0(); // 서로 다른 날짜의 차이를 계산하는 함수
void Date_cal(Date *date); // yyyy-m-count-date일 경우 해당 하는 달의 총 일수를 계산하는 함수
void make_Calendar(Date *date, int mod, int check); // 위의 함수 달력을 만드는 함수
int check_Date(Date *date); // 위 두 함수를 실행하고 몇 일인지 없는 값인지 판별하는 함수
int check_Type0(Date *date); // yyyy-m-d를 구했을 때 제대로된 날짜인지 판별
int main() {
	ifstream inp("calendar.inp");
	ofstream out("calendar.out");

	int type;
	while (true) {
		inp >> type;
		memset(Calendar, 0, sizeof(Calendar));
		for (int i = 0; i < 2; i++) {
			date[i].count = 0;
			date[i].date = "";
			date[i].day = 0;
			date[i].month = 0;
			date[i].year = 0;
		}
		char ch;
		int res;
		int check;
		int temp = 0;
		if (type == -1) break;
		switch (type) {
		case 0:  // yyyy-mm-dd - yyyy-mm-dd
			for (int i = 0; i < 2; i++) {
				inp >> date[i].year >> ch >> date[i].month >> ch >> date[i].day;
				check = check_Type0(&date[i]);
				if (check == -1) temp = -1;
			}
			if (temp == -1) {
				out << temp << endl;
			}
			else {
				res = Type0();
				out << res << endl;
			}
			temp = 0;
			check = 0;
			res = 0;
			break;
		case 1: // yyyy-mm-dd - yyyy-mm-cnt-date
			inp >> date[0].year >> ch >> date[0].month >> ch >> date[0].day;
			inp >> date[1].year >> ch >> date[1].month >> ch >> date[1].count >> ch >> date[1].date;
			check = check_Type0(&date[0]);
			if (check == -1) { out << -1 << endl;  check = 0; break; }
			Date_cal(&date[1]);
			res = check_Date(&date[1]);
			check = check_Type0(&date[1]);
			if (res == -1 || check == -1) out << -1 << endl;
			else {
				res = Type0();
				out << res << endl;
				memset(Calendar, 0, sizeof(Calendar)); 
			}
			check = 0;
			res = 0;
			break;
		case 2: // yyyy-mm-cnt-date - yyyy-mm-dd
			inp >> date[0].year >> ch >> date[0].month >> ch >> date[0].count >> ch >> date[0].date;
			inp >> date[1].year >> ch >> date[1].month >> ch >> date[1].day;
			Date_cal(&date[0]);
			check = check_Type0(&date[1]);
			res = check_Date(&date[0]);
			if (res == -1 || check == -1) out << -1 << endl;
			else {
				res = Type0();
				out << res << endl;
				memset(Calendar, 0, sizeof(Calendar));
			}
			check = 0;
			res = 0;
			break;
		case 3: // yyyy-mm-cnt-date
			temp = 0;
			for (int i = 0; i < 2; i++) {
				memset(Calendar, 0, sizeof(Calendar));
				inp >> date[i].year >> ch >> date[i].month >> ch >> date[i].count >> ch >> date[i].date;
				Date_cal(&date[i]);
				res = check_Date(&date[i]);
				check = check_Type0(&date[i]);
				if (res == -1 || check == -1) {
					temp = -1;
					memset(Calendar, 0, sizeof(Calendar));
				}
			}
			if (temp == -1) 
				out << temp << endl;
			else {
				res = Type0();
				out << res << endl;
				memset(Calendar, 0, sizeof(Calendar));
			}
			check = 0;
			res = 0;
			temp = 0;
			break;
		}
	}
	inp.close();
	out.close();
	return 0;
}
	
int Type0() {
	int all_day[2] = { 0,0 };
	int res;
	int year[2];
	int month[2];
	int day[2];
	for (int i = 0; i < 2; i++) {
		year[i] = date[i].year - O_year; // yyyy- 1
		month[i] = date[i].month - O_month; // mm - 1
		day[i] = date[i].day - O_day; // dd - 1
	}
	for (int i = 0; i < 2; i++) { // year 총 일 수 계산
		for (int j = 1; j <= year[i]; j++) {
			if (j % 4 == 0 && j % 100 != 0 || j % 400 == 0)
				all_day[i] += 366;
			else
				all_day[i] += 365;
		}
	}
	for (int i = 0; i < 2; i++) { // month 총 일 수 계산
		for (int j = 1; j <= month[i]; j++) {
			if (j == 1 || j == 3 || j == 5 || j == 7 || j == 8 || j == 10 || j == 12)
				all_day[i] += 31;
			else if (j != 2)
				all_day[i] += 30;
			else {
				if (date[i].year % 4 == 0 && date[i].year % 100 != 0 || date[i].year % 400 == 0)
					all_day[i] += 29;
				else
					all_day[i] += 28;
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		if (day[i] != 0) all_day[i] += day[i];
	}
	res = all_day[0] - all_day[1];
	if (res < 0) res *= -1;
	return res;
}
void make_Calendar(Date *date, int mod, int check) { // 해당하는 달력을 만드는 함수
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day = 1, month = date->month;
	if (check == 1) months[1]++;
	for (int i = 0; i < 6; i++) {
		for (int j = mod; j < 7; j++) {
			if (day <= months[month - 1])
				Calendar[i][j] = day++;
		}
		if (day > months[month - 1]) break;
		mod = 0;
	}
}
int check_Date(Date *date) {
	int month = date->month;
	int col = 0, count = 1;
	string week_date = date->date;
	string week_day[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	for (int i = 0; i < 7; i++)
		if (week_date == week_day[i]) {
			col = i; break;
		}
	for (int i = 0; i < 6; i++) {
		if (Calendar[i][col] == 0) continue;
		else {
			if (count == date->count) {
				date->day = Calendar[i][col];
				break;
			}
			else count++;
		}
	}
	if (date->day == 0) return -1;
	else return 0;
}
void Date_cal(Date *date) { // yyyy-m-count-date 인 경우
	int all_day = 0;
	int year = date->year, month = date->month;
	int mod = 0, check = 0;
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	all_day = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400; // year까지 년 수를 계산
	if (!(year % 4) && year % 100 || !(year % 400)) months[1]++;  check = 1; // 윤년 인 경우
	for (int i = 0; i < month - 1; i++) all_day += months[i];
	mod = all_day % 7 + 1;
	if (mod == 7) mod = 0;
	make_Calendar(date, mod, check);
}
int check_Type0(Date *date) {
	int year = date->year, month = date->month, day = date->day;
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((!(year % 4) && year % 100 || !(year % 400)) || !(year % 4) && year % 100)
		months[1]++;
	if (day > months[month - 1]) return -1;
	else return 0;
}