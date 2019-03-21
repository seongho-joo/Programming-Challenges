/**
 * Operating System Assignment
 * Shortest-Job-First Scheduling
 */
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

struct Process {
    int processNum; // 프로세스 번호
    int arraivedTime; // 도착시간
    int usingTime; // CPU 사용시간
};

int sec = 0 , cnt = 0;

bool compare1 (const Process& x, const Process& y) {
    if(x.arraivedTime == y.arraivedTime) {
        if(x.usingTime == y.usingTime) 
            return x.processNum < y.processNum;
        return x.usingTime < y.usingTime;
        }
    return x.arraivedTime < y.arraivedTime;
}

bool compare2(const Process &x, const Process &y) {
    if(sec >=x.arraivedTime && sec >= y.arraivedTime) {
        if(x.usingTime == y.usingTime) {
            if (x.arraivedTime == y.arraivedTime)
                return x.processNum < y.processNum;
            return x.arraivedTime < y.arraivedTime;
        }
        return x.usingTime < y.usingTime;
    }
    return x.arraivedTime < y.arraivedTime;
}

vector<Process> readyQ;
list<int> TIME;

int solution() {
    int answer = 0, len;
    vector<Process>::iterator cur = readyQ.begin(), next;
    while(!readyQ.empty()) {
        if(cur->usingTime == 0) {
            cnt--;
            readyQ.erase(cur);
            if(readyQ.empty()) break;
        }
        if(sec == TIME.front()) {
            while(!TIME.empty()) {
                if(sec == TIME.front()) {
                    cnt++;
                    TIME.pop_front();
                }
                else break;
            }
        }
        sort(readyQ.begin(), readyQ.end(), compare2);
        sec++;
        if(cnt > 0) {
            answer += cnt - 1;
            cur->usingTime--;
        }
    }
    return answer;
}

int main() {
    ifstream inp("srtf.inp");
    ofstream out("srtf.out");

    if (!inp.is_open()) {
		out << "Can't open file";
		exit(1);
	}

    int N; // 프로세스 개수
    inp >> N;
    readyQ.reserve(N);

    while(N--) {
        Process data;
        inp >> data.processNum >> data.arraivedTime >> data.usingTime;
        TIME.push_back(data.arraivedTime);
        readyQ.push_back(data);
    }

    TIME.sort();
    sort(readyQ.begin(), readyQ.end(), compare1);
    
    out << solution();

    inp.close();
    out.close();
    return 0;
}