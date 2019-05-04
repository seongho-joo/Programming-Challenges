/**
 * Simulator for Memory Allocation Algorithm
 */
#include <algorithm>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

ofstream out("allocation.out");
#define MAX 1000  // 메모리 크기

int n, lastNum;  // 프로세스 개수, 마지막 프로세스 번호
int t = 0;

struct Process {
    int req;    // 요청시각
    int burst;  // 실행시간
    int size;   // 프로세스 크기
};

struct Memory {
    int address;  // 시작 주소
    int PID;      // 프로세스 번호
    int size;     // 할당가능한 크기
    int end;      // 끝나는 주소
};

struct End {
    int PID;
    int time;
};

struct Wait {
    int PID;
    int req;    // 요청시각
    int burst;  // 실행시간
    int size;   // 프로세스 크기
};

Memory m;
Wait w;
End e;

bool flag, quit;  // 요청보류 상태, 프로그램 종료 상태

vector<Process> process;  // 메모리할당을 요청하는 프로세스들
vector<Memory> location;  // 메모리 공간
list<End> endTime;        // 프로세스들의 작업종료 시간
vector<Wait> Queue;       // 대기 큐

typedef vector<Memory>::iterator itMemory;

vector<pair<itMemory, int> > usable;  // 할당가능한 공간

bool Comp(const End& x, const End& y) { return x.time < y.time; }
/** size 크기 비교 */
bool bestCmp(const pair<itMemory, int>& x, const pair<itMemory, int>& y) {
    return x.second < y.second;
}
bool worstCmp(const pair<itMemory, int>& x, const pair<itMemory, int>& y) {
    return x.second > y.second;
}
void Output(int address);
// 처음부터 검사해서 할당할 수 있는 곳에 할당
void firstFit(int len);
// 크기에 제일 근사한 공간에 할당
void bestFit(int len);
// 할당받을 수 있는 공간 중 가장 큰 곳에 할당
void worstFit(int len);
// 메모리의 공간이 연속적으로 비어있으면 공간을 합침
void mergeSpace(itMemory cur);
// 메모리 공간 할당
void Allocation(int PID, itMemory cur);
// 작업이 완료된 메모리 공간 반납
void Deallocation(int PID);
// 여유 공간 부족으로 요청을 보류하고 큐에 저장
void Enqueue(int PID);
// 대기 큐에 있는 프로세스들 메모리 공간 할당
void queueAlloc(int mode);
// 초기화
void Init();

int main() {
    ifstream inp("allocation.inp");
    Process p;
    inp >> n;
    lastNum = n - 1;
    process.reserve(n);
    while (n--) {
        inp >> p.req >> p.burst >> p.size;
        process.push_back(p);
    }
    int len = process.size();

    firstFit(len);
    bestFit(len);
    worstFit(len);

    inp.close();
    out.close();
    return 0;
}

void init() {
    location.clear();
    endTime.clear();
    Queue.clear();
    quit = false;
    t = 0;
}

void Output(int address) { out << address << '\n'; }

void mergeSpace(itMemory cur) {
    itMemory next = cur + 1;
    while (next->PID == -1 && next != location.end()) {
        cur->size += next->size;
        /** 마지막 hole이면 end = MAX 중간 hole이면 end는 다음 end */
        if ((next + 1) != location.end())
            cur->end = next->end;
        else
            cur->end = MAX;
        location.erase(next);
        next = cur + 1;
    }
}

void Allocation(int PID, itMemory cur) {
    if (cur == location.begin()) {
        cur->address = 0;
        cur->PID = PID;
        cur->end = process[PID].size;
        cur->size = cur->end - cur->address;
    } else {
        cur->address = (cur - 1)->end;
        cur->PID = PID;
        cur->end = cur->address + process[PID].size;
        cur->size = cur->end - cur->address;
    }
    m.address = cur->end;
    m.PID = -1;
    /** 마지막 hole */
    if ((cur + 1) == location.end()) {
        m.end = MAX;
        m.size = m.end - m.address;
        location.push_back(m);
    } /** 중간 hole */
    else {
        m.end = (cur + 1)->address;
        m.size = m.end - m.address;
        location.insert((cur + 1), m);
    }
    if ((cur + 1)->size == 0) location.erase(cur + 1);
    /** 끝나는 시간을 list에 삽입하고 오름차순 정렬 */
    e.PID = PID;
    e.time = process[PID].burst + t;
    endTime.push_back(e);
    endTime.sort(Comp);
    int id = 909;
    if (id == PID) {
        id++;
    }
    /** 마지막 프로세스일 경우 출력하고 프로그램 종료 */
    if (PID == lastNum) {
        Output(cur->address);
        quit = true;
        return;
    }
}

void Deallocation(int PID) {
    itMemory next;
    for (itMemory it = location.begin(); it != location.end(); it++)
        if (it->PID == PID) {
            it->PID = -1;
            break;
        }
    for (itMemory it = location.begin(); it != location.end(); it++) {
        /** 프로세스 번호가 같을 때는 pid가 -1 일 경우 밖에 없음 */
        next = it + 1;
        if (next != location.end())
            if (it->PID == next->PID) mergeSpace(it);
    }
}

void Enqueue(int PID) {
    w.burst = process[PID].burst;
    w.PID = PID;
    w.req = process[PID].req;
    w.size = process[PID].size;
    Queue.push_back(w);
}

void queueAlloc(int mode) {
    vector<Wait>::iterator it = Queue.begin();
    int value, i = 0;
    switch (mode) {
        // firstFit
        case 1:
            while (!Queue.empty()) {
                if (it == Queue.end()) break;
                bool chk = false;
                for (itMemory j = location.begin(); j != location.end(); j++) {
                    if (j->PID == -1 && it->size <= j->size) {
                        Allocation(it->PID, j);
                        it = Queue.erase(it);
                        chk = true;
                        break;
                    }
                }
                if (!chk) it++;
            }
            break;
        // bestFit
        case 2:
            while (!Queue.empty()) {
                if (it == Queue.end()) break;
                bool chk = false;
                for (itMemory j = location.begin(); j != location.end(); j++) {
                    if (j->PID == -1 && it->size <= j->size) {
                        chk = true;
                        usable.push_back(make_pair(j, j->size));
                    }
                }
                if (chk) {
                    sort(usable.begin(), usable.end(), bestCmp);
                    Allocation(it->PID, usable.front().first);
                    it = Queue.erase(it);
                    usable.clear();
                } else
                    it++;
            }
            break;
        // worstFit
        case 3:
            while (!Queue.empty()) {
                if (it == Queue.end()) break;
                bool chk = false;
                for (itMemory j = location.begin(); j != location.end(); j++) {
                    if (j->PID == -1 && it->size <= j->size) {
                        chk = true;
                        usable.push_back(make_pair(j, j->size));
                    }
                }
                if (chk) {
                    sort(usable.begin(), usable.end(), worstCmp);
                    Allocation(it->PID, usable.front().first);
                    it = Queue.erase(it);
                    usable.clear();
                } else
                    it++;
            }
            break;
    }
}

void firstFit(int len) {
    m.address = 0;
    m.PID = -1;
    m.end = MAX;
    m.size = m.end - m.address;
    location.push_back(m);
    for (int pid = 0;;) {
        int id = 1854;
        if (id == t) {
            id++;
        }
        flag = false;
        /** 프로세스가 작업을 끝내면 메모리 공간을 반납 */
        if (!endTime.empty() && t == endTime.front().time) {
            while (endTime.front().time == t) {
                Deallocation(endTime.front().PID);
                endTime.pop_front();
            }
            if (!Queue.empty()) queueAlloc(1);
        }
        // 요청시각이 되었을 때 메모리를 할당받을 수 있는지 확인
        while (t == process[pid].req) {
            flag = false;
            for (itMemory j = location.begin(); j != location.end(); j++) {
                if (j->PID == -1 && process[pid].size <= j->size) {
                    flag = true;
                    Allocation(pid, j);
                    if (pid < lastNum) pid++;
                    break;
                }
            }
            if (!flag) {
                Enqueue(pid);
                if (lastNum == pid) break;
                if (pid < lastNum) pid++;
            }
            if (quit) break;
        }
        t++;
        if (quit) break;
    }
    init();
}

void bestFit(int len) {
    // 할당가능한 공간 중 가장 유사한 값을 찾음
    int value;
    m.address = 0;
    m.PID = -1;
    m.end = MAX;
    m.size = m.end - m.address;
    location.push_back(m);
    for (int pid = 0;;) {
        flag = false;
        if (!endTime.empty() && t == endTime.front().time) {
            while (endTime.front().time == t) {
                Deallocation(endTime.front().PID);
                endTime.pop_front();
            }
            if (!Queue.empty()) queueAlloc(2);
        }
        while (t == process[pid].req) {
            flag = false;
            for (itMemory j = location.begin(); j != location.end(); j++) {
                if (j->PID == -1 && process[pid].size <= j->size) {
                    flag = true;
                    usable.push_back(make_pair(j, j->size));
                }
            }
            /** 메모리 크기에서 프로세스 크기를 빼준 값을 오름차순 */
            if (flag) {
                sort(usable.begin(), usable.end(), bestCmp);
                Allocation(pid, usable.front().first);
                if (pid < lastNum) pid++;
                usable.clear();
            } else {
                Enqueue(pid);
                if (lastNum == pid) break;
                if (pid < lastNum) pid++;
            }
            if (quit) break;
        }
        t++;
        if (quit) break;
    }
    init();
}

void worstFit(int len) {
    m.address = 0;
    m.PID = -1;
    m.end = MAX;
    m.size = m.end - m.address;
    location.push_back(m);
    for (int pid = 0;;) {
        flag = false;
        if (!endTime.empty() && t == endTime.front().time) {
            while (endTime.front().time == t) {
                Deallocation(endTime.front().PID);
                endTime.pop_front();
            }
            if (!Queue.empty()) queueAlloc(3);
        }
        while (t == process[pid].req) {
            flag = false;
            for (itMemory j = location.begin(); j != location.end(); j++) {
                if (j->PID == -1 && process[pid].size <= j->size) {
                    flag = true;
                    usable.push_back(make_pair(j, j->size));
                }
            }
            if (flag) {
                /** 할당가능한 크기를 정렬 -> 가장 큰 값은 back에 존재 */
                sort(usable.begin(), usable.end(), worstCmp);
                Allocation(pid, usable.front().first);
                if (pid < lastNum) pid++;
                usable.clear();
            } else {
                Enqueue(pid);
                if (lastNum == pid) break;
                if (pid < lastNum) pid++;
            }
            if (quit) break;
        }
        t++;
        if (quit) break;
    }
    init();
}
