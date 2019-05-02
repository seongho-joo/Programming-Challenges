/**
 * Implementation of a Simulator for Banker's Algorithm
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ifstream inp("banker.inp");
ofstream out("banker.out");

struct Wait {
    int PID;
    vector<int> req;
};

// 총 자원의 수, 프로세스가 요청한 자원의 수, 할당받을 수 있는 자원의 수
vector<int> resource, request, Av, release;
// 최대 요청가능한 자원 수, 현재 할당받은 자원의 수, 필요한 자원의 수
vector<vector<int> > MAX, Alloc, Need;
vector<Wait> waiting;
int n, m;  // 프로세스 개수, 자원의 종류

void Input(vector<vector<int> >& v);
void output();
void getNeed();                          // Need계산
void getAv();                            // Av계산
bool isSafe(vector<int>& req, int PID);  // safe상태인지 확인함
// 프로세스의 요청이 할당받을 수 있는지 확인함
bool isAlloc(vector<int>& req, int PID);

int main() {
    inp >> n >> m;
    Wait wait;

    resource.reserve(m);
    request.reserve(m);
    release.reserve(m);
    Av.resize(m);
    MAX.resize(n, vector<int>(m));
    Alloc.resize(n, vector<int>(m));
    Need.resize(n, vector<int>(m));
    waiting.reserve(n);

    int input;
    for (int i = 0; i < m; i++) {
        inp >> input;
        resource.push_back(input);
    }

    Input(MAX);
    Input(Alloc);
    getAv();
    getNeed();

    while (true) {
        string str;
        bool flag = false;
        int PID;
        inp >> str;
        if (str.compare("request") == 0) {
            /** 자원할당 요청 */
            inp >> PID;
            for (int i = 0; i < m; i++) {
                inp >> input;
                request.push_back(input);
            }
            // /** Need보다 큰 수는 요청할 수 없음 */
            // for (int i = 0; i < m; i++) {
            //     if (MAX[PID][i] < request[i] + Alloc[PID][i]) {
            //         flag = true;
            //         break;
            //     }
            // }
            if (isAlloc(request, PID)) {
                // 안정상태일 때 요청을 들어줌
                if (isSafe(request, PID))
                    for (int i = 0; i < m; i++) {
                        Av[i] -= request[i];
                        Alloc[PID][i] += request[i];
                        Need[PID][i] -= request[i];
                    }
                else {
                    /**
                     * unsafe상태이기 때문에 대기 큐에 넣고 요청 보류
                     */
                    wait.PID = PID;
                    wait.req = request;
                    waiting.push_back(wait);
                }
            }
            request.clear();
        } else if (str.compare("release") == 0) {
            /** 자원 반납 */
            inp >> PID;
            for (int i = 0; i < m; i++) {
                inp >> input;
                Alloc[PID][i] -= input;
                Need[PID][i] += input;
                Av[i] += input;
            }
            if (!waiting.empty()) {
                vector<Wait>::iterator it = waiting.begin();
                /** 대기queue에 들어온 순서대로 할당가능한지 판단 */
                while (it != waiting.end()) {
                    if (!isAlloc(it->req, it->PID)) {
                        it++;
                        continue;
                    }
                    if (isSafe(it->req, it->PID)) {
                        for (int i = 0; i < m; i++) {
                            Av[i] -= it->req[i];
                            Alloc[it->PID][i] += it->req[i];
                            Need[it->PID][i] -= it->req[i];
                        }
                        waiting.erase(it);
                        it = waiting.begin();
                    } else
                        it++;
                }
            }
        } else  // quit일 경우 프로그램 종료
            break;
        output();
    }

    inp.close();
    out.close();
    return 0;
}

void Input(vector<vector<int> >& v) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) inp >> v[i][j];
}

void output() {
    for (int i = 0; i < m; i++) out << Av[i] << ' ';
    out << '\n';
}

void getAv() {
    int allocSum = 0;
    for (int i = 0; i < m; i++) {
        allocSum = 0;
        for (int j = 0; j < n; j++) allocSum += Alloc[j][i];
        Av[i] = resource[i] - allocSum;
    }
}

void getNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) Need[i][j] = MAX[i][j] - Alloc[i][j];
}

bool isSafe(vector<int>& req, int PID) {
    vector<int> av = Av;
    vector<vector<int> > need = Need, alloc = Alloc;
    vector<bool> complete(n, false);
    bool flag;
    int count = 0, i = 0;  // 할당 완료된 수
    /** 할당가능한 자원의 수에서 요청한 할당 수를 빼줌 */
    for (int i = 0; i < m; i++) {
        alloc[PID][i] += req[i];
        av[i] -= req[i];
        need[PID][i] -= req[i];
        /** 현재 가지고 있는 자원보다 요청한 자원이 더 많을 경우 */
        if (av[i] < 0) return false;
    }
    while (true) {
        flag = false;
        /** 안전순열이 존재하지 않음 */
        if (i >= n) return false;
        /** 안전순열이 존재 */
        if (count == n) break;
        /** 할당완료 됨 */
        if (complete[i]) {
            i++;
            continue;
        }
        for (int j = 0; j < m; j++) {
            if (need[i][j] > av[j]) {
                /** NEED[i]보다 av보다 클 경우 다음 프로세스로 넘어감 */
                flag = true;
                i++;
                break;
            }
        }
        if (!flag) {
            /** 작업이 완료된 프로세스가 자원들을 반납했다고 가정 */
            for (int j = 0; j < m; j++) av[j] += alloc[i][j];
            complete[i] = true;
            count++;
            i = 0;
        }
    }
    return true;
}

bool isAlloc(vector<int>& req, int PID) {
    for (int i = 0; i < m; i++)
        if (MAX[PID][i] < req[i] + Alloc[PID][i]) return false;
    return true;
}