/**
 * Operating System Assignment
 * First Come - First Out
 */
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

typedef struct Process {
    int processNum; // 프로세스 번호
    int arraivedTime; // 도착시간
    int usingTime; // CPU 사용시간
    int startPoint; // CPU 사용을 시작한 시간
}Process;

vector<Process> readyQue;

bool comp(const Process& x, const Process& y) {
    if(x.arraivedTime == y.arraivedTime) return x.processNum < y.processNum;
    return x.arraivedTime < y.arraivedTime;
}

int solve() {
    int anwser = 0;
    readyQue[0].startPoint = 0;
    readyQue[1].startPoint = readyQue[0].usingTime;

    // 프로세스 마다 각 사용을 시작하는 시간을 저장
    for(int i = 2; i < readyQue.size(); i++) {
        /**
         * 전에 사용했던 프로세스가 현재 도착한 프로세스의 시간 보다
         * 작을 경우 시작시간은 프로세스의 도착시간이다.
         */
        if(readyQue[i - 1].startPoint + readyQue[i - 1].usingTime <= readyQue[i].arraivedTime)
            readyQue[i].startPoint = readyQue[i].arraivedTime;
        else
            readyQue[i].startPoint = readyQue[i - 1].usingTime + readyQue[i - 1].startPoint;
    }
    
    for(int i = 1; i < readyQue.size(); i++)
        /**
         * 프로세스 시작 포인트와 도착시간이 같을 경우 
         * 지연 시간은 0 이다.
         */
        if(readyQue[i].startPoint == readyQue[i].arraivedTime)
            anwser += 0;
        else
            anwser += readyQue[i].startPoint - readyQue[i].arraivedTime;

    return anwser;
}

int main() {
    ifstream inp("fcfs.inp");
    ofstream out("fcfs.out");

    int N; // 프로세스의 개수
    inp >> N;
    readyQue.reserve(N);

    Process process;
    
    while(N--) {
        inp >> process.processNum >> process.arraivedTime >> process.usingTime;
        process.startPoint = 0;
        readyQue.push_back(process);
    }

    sort(readyQue.begin(), readyQue.end(), comp);

    out << solve();

    inp.close();
    out.close();
    return 0;
}