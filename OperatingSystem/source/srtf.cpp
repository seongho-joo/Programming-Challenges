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
    int processNum; // PID
    int arraivedTime; // Time of arrival in Ready state
    int usingTime; // CPU using time
};

int sec = 0 , cnt = 0; // CPU running time, Number of processes in ready state

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
list<int> TIME; // Save the time the processes arrive

int solution() {
    int answer = 0;
    vector<Process>::iterator cur = readyQ.begin();
    while(!readyQ.empty()) {
        /**terminated */
        if(cur->usingTime == 0) {
            cnt--;
            readyQ.erase(cur);
            if(readyQ.empty()) break;
        }
        if(sec == TIME.front()) {
            /**ready */
            while(!TIME.empty()) {
                if(sec == TIME.front()) {
                    cnt++;
                    TIME.pop_front();
                }
                else break;
            }
        }
        /** Time interrupt & Scheduler dispatch */
        sort(readyQ.begin(), readyQ.end(), compare2);
        sec++;
        /** Running */
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

    int N; // Number of process
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