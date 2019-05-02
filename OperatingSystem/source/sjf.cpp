/**
 * Operating System Assignment
 * Shortest-Job-First Scheduling
 */
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Process {
    int processNum; // 프로세스 번호
    int arraivedTime; // 도착시간
    int usingTime; // CPU 사용시간
    int startPoint; // CPU 사용을 시작한 시간
};

int endTime = 0;

vector<Process> readyQ;

// 우선 도착시간 우선 정렬
bool comp1(const Process& x, const Process& y) {
    if(x.arraivedTime == 0 && y.arraivedTime == 0) return x.usingTime < y.usingTime;
    if(x.arraivedTime == y.arraivedTime) return x.usingTime < y.usingTime;
    return x.arraivedTime < y.arraivedTime;
}
// CPU 사용시간이 짧은 순서로 재정렬
bool comp2(const Process& x, const Process& y) {
    if(endTime >= x.arraivedTime && endTime >= y.arraivedTime) {
        if(x.usingTime == y.usingTime) 
            return x.processNum < y.processNum;
        return x.usingTime < y.usingTime;
    }
    if(x.arraivedTime == y.arraivedTime) return x.usingTime < y.usingTime;
    return x.arraivedTime < y.arraivedTime;
}
/**
 * endTime이 arraivedTime보다 크면 usingTime순 으로 정렬한다.
 */
void solveSeq() {
    endTime = readyQ[0].usingTime;
    vector<Process>::iterator it = readyQ.begin();
    for(int i = 1; i < readyQ.size(); i++) {
            it++;
            sort(it, readyQ.end(), comp2);
            // CPU가 놀고 있을 때 프로세스가 readyQ로 들어왔을 경우
            if(readyQ[i - 1].startPoint + readyQ[i - 1].usingTime <= readyQ[i].arraivedTime) {
                readyQ[i].startPoint = readyQ[i].arraivedTime;
                endTime = readyQ[i].startPoint + readyQ[i].usingTime;
            }
            else {
                readyQ[i].startPoint = endTime;
                endTime += readyQ[i].usingTime; 
            }
        }
}

int solution() {
    int answer = 0;
    solveSeq();
    for(int i = 1; i < readyQ.size(); i++)
        /**
         * 프로세스 시작 포인트와 도착시간이 같을 경우 
         * 지연 시간은 0 이다.
         */
        if(readyQ[i].startPoint == readyQ[i].arraivedTime)
            answer += 0;
        else
            answer += readyQ[i].startPoint - readyQ[i].arraivedTime;

    return answer;
}

int main() {
    ifstream inp("sjf.inp");
    ofstream out("sjf.out");

    if (!inp.is_open()) {
		fprintf(stderr, "can't open\n");
		exit(1);
	}

    int N; // process of number
    inp >> N;

    readyQ.reserve(N);
    Process process;

    while(N--) {
        inp >> process.processNum >> process.arraivedTime >> process.usingTime;
        process.startPoint = 0;
        readyQ.push_back(process);
    }

    sort(readyQ.begin(), readyQ.end(), comp1);

    out << solution();

    inp.close();
    out.close();
    return 0;
}