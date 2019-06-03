/**
 * Disk Scheduling Algorithm 구현
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define MAX 200

ifstream inp("disk.inp");
ofstream out("disk.out");

int realTime = 0, location;  // 사용시각, 헤드 위치
bool Reverse = true;
struct Disk {
    int time, track;  // 요청시각과 트랙
    int diff;         // 현제 헤드위치와 트랙의 차이 값
};

/** SSTF 스케쥴링 정렬 */
bool SSTF_compare(const Disk& x, const Disk& y) {
    if (realTime >= x.time && realTime >= y.time) {
        if (x.diff == y.diff) return x.time < y.time;
        return x.diff < y.diff;
    }
    return x.time < y.time;
}
/** LOOK 스케쥴링 정렬 */
bool LOOK_compare(const Disk& x, const Disk& y) {
    if (Reverse) {
        if (realTime >= x.time && realTime >= y.time) {
            if (x.track == y.track) return x.time < y.time;
            return x.track < y.track;
        }
    } else {
        if (realTime >= x.time && realTime >= y.time) {
            if (x.track == y.track) return x.time < y.time;
            return x.track > y.track;
        }
    }
    return x.time < y.time;
}

Disk d;

vector<Disk> reqQ;

void FCFS(int s);
void SSTF(int s);
void LOOK(int s);

int main() {
    string op;  // 디스크 스케쥴링 알고리즘
    int s;      // 요청을 서비스하는 시간

    inp >> op >> s;

    if (op.compare("FCFS") == 0)
        FCFS(s);
    else if (op.compare("SSTF") == 0)
        SSTF(s);
    else
        LOOK(s);

    inp.close();
    out.close();
    return 0;
}

void input() {
    while (true) {
        inp >> d.time >> d.track;
        d.diff = 0;
        if (d.time == -1) break;
        reqQ.push_back(d);
    }
}

void FCFS(int s) {
    input();
    vector<Disk>::iterator it;
    for (it = reqQ.begin(); it != reqQ.end();) {
        while (realTime >= it->time && it != reqQ.end()) {
            if (it == reqQ.begin())
                realTime = it->track + s;
            else
                realTime += abs(location - it->track) + s;
            location = it->track;
            it++;
        }
        if (it != reqQ.end()) realTime++;
    }
    out << realTime << ' ' << location << '\n';
}
/** 현재 헤드위치 - track 번호를 구하고 정렬 */
void getDifferentValue(int cur) {
    vector<Disk>::iterator it;
    for (it = reqQ.begin(); it != reqQ.end(); it++) {
        if (realTime >= it->time)
            it->diff = abs(cur - it->track);
        else
            break;
    }

    sort(reqQ.begin(), reqQ.end(), SSTF_compare);
}

void SSTF(int s) {
    input();
    vector<Disk>::iterator it;
    for (it = reqQ.begin(); it != reqQ.end();) {
        while (realTime >= it->time && it != reqQ.end()) {
            getDifferentValue(location);
            if (realTime == 0)
                realTime = it->track + s;
            else
                realTime += abs(location - it->track) + s;
            location = it->track;
            reqQ.erase(it);
        }
        if (it != reqQ.end()) realTime++;
    }
    out << realTime << ' ' << location << '\n';
}
/** track번호를 set에 입력*/
void getTrack(set<int>& temp) {
    vector<Disk>::iterator it;
    for (it = reqQ.begin(); it != reqQ.end(); it++)
        if (realTime >= it->time) temp.insert(it->track);
}
/** 현재 헤드위치에서 가장 근사한 track번호를 찾아서 반환 */
vector<Disk>::iterator setFindLocation(int location) {
    vector<Disk>::iterator cur;
    for (cur = reqQ.begin(); cur != reqQ.end(); cur++) {
        if (realTime >= cur->time) {
            /** 오름차순일 때 가장 근사한 track번호를 반환 */
            if (Reverse && location <= cur->track) return cur;
            /** 내림차순일 때 가장 근사한 track번호를 반환 */
            if (!Reverse && location >= cur->track) return cur;
        }
    }
    // realTime내에 더 이상 location 보다 큰 트랙이 없을 때 Reverse
    if (Reverse) return reqQ.begin();
    // realTime내에 더 이상 location 보다 작은 트랙이 없을 때 Reverse
    else
        return reqQ.end();
}

void LOOK(int s) {
    input();
    /** reqQ Iterator */
    vector<Disk>::iterator it;
    /** track Interator */
    set<int>::iterator cur;
    /** 오름차순, 내림차순을 판단하기 위해 선언 */
    set<int> track;
    int start, end;
    for (it = reqQ.begin(); !reqQ.empty();) {
        while (realTime >= it->time && it != reqQ.end()) {
            sort(reqQ.begin(), reqQ.end(), LOOK_compare);
            it = setFindLocation(location);
            if (realTime == 0)
                realTime = it->track + s;
            else
                realTime += abs(location - it->track) + s;
            getTrack(track);
            location = it->track;
            start = *track.begin();
            end = *--track.end();
            /** 현재시각이 다음 요청시각보다 작을 경우  */
            if (start == end && (it + 1) != reqQ.end()) {
                if ((it + 1)->track > it->track)
                    Reverse = true;
                else
                    Reverse = false;
            } else {
                /** 오름차순 */
                if (start == it->track) Reverse = true;
                /** 내림차순 */
                if (end == it->track) Reverse = false;
            }
            cur = track.find(it->track);
            track.erase(cur);
            reqQ.erase(it);
            if (it != reqQ.end()) it = reqQ.begin();
        }
        if (it != reqQ.end()) realTime++;
    }
    out << realTime << ' ' << location << '\n';
}