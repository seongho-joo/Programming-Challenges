/**
 * 페이지 교체 알고리즘 구현
 */
#include <algorithm>
#include <fstream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

#define MAX 20000

ifstream inp("page.inp");
ofstream out("page.out");

struct Req {
    int PID, page;  // 프로세스 번호, page 번호
};

struct State {
    int PID, page;
    bool chk;
};

Req req;
int pageFalut;
vector<Req> memory, reqQ;  // 메모리, 프로세스 요청

typedef vector<Req>::iterator It;

void FIFO(int n);  // FIFO Algorithm
void LRU(int n);   // Least Recently Use Algorithm
void OPT(int n);   // Optimal Algorithm

int main() {
    int n;
    inp >> n;

    while (true) {
        inp >> req.PID >> req.page;
        if (req.PID == -1) break;
        reqQ.push_back(req);
    }
    FIFO(n);
    LRU(n);
    OPT(n);

    inp.close();
    out.close();
    return 0;
}

void init(State& st, Req req) {
    st.page = req.page;
    st.PID = req.PID;
    st.chk = false;
}

void output() {
    for (int i = 0; i < memory.size(); i++)
        out << i << ' ' << memory[i].PID << ' ' << memory[i].page << '\n';
    memory.clear();
    pageFalut = 0;
}
/** victim page를 새로운 page로 갱신 */
void update(list<State>& q, It process) {
    State st = q.front();
    for (It it = memory.begin(); it != memory.end(); it++) {
        if (st.page == it->page && st.PID == it->PID) {
            it->page = process->page;
            q.pop_front();
            init(st, *process);
            q.push_back(st);
            break;
        }
    }
}
/** 같은 page가 존재하는지 확인 */
bool isExist(It process) {
    for (It it = memory.begin(); it != memory.end(); it++)
        if (process->PID == it->PID && process->page == it->page) return true;
    return false;
}

void FIFO(int n) {
    list<State> count[MAX];
    State st;
    for (It it = reqQ.begin(); it != reqQ.end(); it++) {
        req = *it;
        int pid = it->PID;
        /** 현재 메모리에 할당되어 있을 경우 */
        if (!memory.empty() && isExist(it)) continue;
        /** 주어진 각 프로세스에 할당될 프레임의 개수보다 작을 경우 */
        if (count[pid].size() < n) {
            /** 해당하는 프로세스가 메모리에 할당이 안되어 있을 경우 */
            pageFalut++;
            memory.push_back(req);
            init(st, req);
            count[pid].push_back(st);
        } else {
            /**
             * 주어인 프레임의 개수와 같을 경우 가장 먼저 할당된 프로세스를 경신
             */
            update(count[pid], it);
            pageFalut++;
        }
    }
    out << "FIFO: " << pageFalut << '\n';
    output();
}

void LRU(int n) {
    int pid;
    list<State> count[MAX];
    State st;
    for (It it = reqQ.begin(); it != reqQ.end(); it++) {
        req = *it;
        pid = it->PID;
        /** 현재 메모리에 할당되어 있을 경우 */
        if (!memory.empty() && isExist(it)) {
            list<State>::iterator temp;
            init(st, *it);
            count[pid].push_back(st);
            /** 현재 메모리에 할당되어 있을 경우 list seq를 갱신해줌 */
            for (temp = count[pid].begin(); temp != count[pid].end(); temp++) {
                if (temp->page == it->page) {
                    temp = count[pid].erase(temp);
                    break;
                }
            }
            continue;
        }
        /** 주어진 각 프로세스에 할당될 프레임의 개수보다 작을 경우 */
        if (count[pid].size() < n) {
            /** 해당하는 프로세스가 메모리에 할당이 안되어 있을 경우 */
            pageFalut++;
            memory.push_back(req);
            init(st, req);
            count[pid].push_back(st);
        } else {
            /**
             * 주어인 프레임의 개수와 같을 경우 가장 먼저 할당된 프로세스를 경신
             */
            update(count[pid], it);
            pageFalut++;
        }
    }
    out << "LRU: " << pageFalut << '\n';
    output();
}
/** list에 page가 존재하는지 체크 */
bool isExistQueue(It next, list<State>& q) {
    list<State>::iterator it;
    for (it = q.begin(); it != q.end(); it++)
        if (it->page == next->page) {
            it->chk = true;
            return true;
        }
    return false;
}

void countInit(list<State>& q) {
    list<State>::iterator it;
    for (it = q.begin(); it != q.end(); it++) it->chk = false;
}

void swapList(list<State>& q) {
    list<State>::iterator iter;
    for (iter = q.begin(); iter != q.end(); iter++) {
        if (!iter->chk) {
            list<State>::iterator temp = iter;
            iter = q.erase(iter);
            q.push_front(*temp);
            countInit(q);
            break;
        }
    }
}

void OPT(int n) {
    list<State> count[MAX];
    State st;
    for (It it = reqQ.begin(); it != reqQ.end(); it++) {
        req = *it;
        int pid = it->PID;
        /** 현재 메모리에 할당되어 있을 경우 */
        if (!memory.empty() && isExist(it)) continue;
        /** 주어진 각 프로세스에 할당될 프레임의 개수보다 작을 경우 */
        if (count[pid].size() < n) {
            /** 해당하는 프로세스가 메모리에 할당이 안되어 있을 경우 */
            pageFalut++;
            memory.push_back(req);
            init(st, req);
            count[pid].push_back(st);
        } else {
            /**
             * 주어인 프레임의 개수와 같을 경우 가장 먼저 할당된 프로세스를 경신
             */
            int cnt = 0;
            vector<int> page;
            for (It next = it + 1; next != reqQ.end(); next++) {
                bool flag = false;
                if (next->PID == it->PID && isExistQueue(next, count[pid])) {
                    if (!page.empty()) {
                        for (int i = 0; i < page.size(); i++) {
                            if (page[i] == next->page) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) continue;
                    }
                    page.push_back(next->page);
                    cnt++;
                }
                /** 참조되는 2개를 찾았을 시 listf를 swap시키고 종료 */
                if (n - 1 == cnt) {
                    swapList(count[pid]);
                    break;
                }
            }
            /** 참조되는 것을 못찾았거나 1개만 있을경우 */
            if (cnt < n - 1) swapList(count[pid]);
            update(count[pid], it);
            pageFalut++;
        }
    }
    out << "OPT: " << pageFalut << '\n';
    output();
}