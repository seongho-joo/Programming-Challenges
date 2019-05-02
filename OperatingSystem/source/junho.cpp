#include <cstdio>
#include <string>
#include <vector>
using namespace std;
#pragma warning(disable : 4996)

bool temp;
int n, m, i, j, process;
int Allocation[50][50], Max[50][50], Need[50][50], Now[50];
int arr[50];
typedef vector<int> c;
typedef pair<int, int> pii;

c now;
vector<pair<pii, c> > queue;

string a = "request", b = "release";
string s;

void request(int process, c &now, int Re) {
    bool check = true;

    for (i = 0; i < m; i++) {
        if (Now[i] < now[i] ||
            Max[process][i] < Allocation[process][i] + now[i]) {
            check = false;
            break;
        }
    }

    if (check == false) {
        if (Re == 1) queue.push_back({{1, process}, now});
    } else {
        bool check2 = false;
        bool check3 = false;
        for (i = 0; i < n; i++) {
            check2 = true;
            for (j = 0; j < m; j++) {
                if (i == process) {
                    if ((Need[i][j] - now[j]) > (Now[j] - now[j])) {
                        check2 = false;
                        break;
                    }
                } else {
                    if (Need[i][j] > (Now[j] - now[j])) {
                        check2 = false;
                        break;
                    }
                }
            }
            check3 = check2;
            if (check3 == true) break;
        }

        if (check3 == false) {
            if (Re == 1) queue.push_back({{1, process}, now});
        } else {  // check3 == true
            for (i = 0; i < m; i++) {
                Now[i] -= now[i];
                Allocation[process][i] += now[i];
                Need[process][i] -= now[i];
            }
            if (Re == 0) temp = true;
        }
    }
}

void release(int process, c &now, int Re) {
    bool check = true;
    for (i = 0; i < m; i++) {
        if (Allocation[process][i] < now[i]) {
            check = false;
            break;
        }
    }
    if (check == false) {
        if (Re == 1) queue.push_back({{0, process}, now});
    } else {
        for (i = 0; i < m; i++) {
            Allocation[process][i] -= now[i];
            Now[i] += now[i];
            Need[process][i] += now[i];
        }
        if (Re == 0) temp = true;
    }
}

void find() {
    for (int i = 0; i < queue.size(); i++) {
        temp = false;
        if (queue[i].first.first == 1) {
            request(queue[i].first.second, queue[i].second, 0);
            if (temp == true) queue.erase(queue.begin() + i), i = -1;
        } else {
            release(queue[i].first.second, queue[i].second, 0);
            if (temp == true) queue.erase(queue.begin() + i), i = -1;
        }
    }
}

int main() {
    FILE *input = fopen("banker.inp", "r");
    FILE *output = fopen("banker.out", "w");

    fscanf(input, "%d%d", &n, &m);
    for (i = 0; i < m; i++) fscanf(input, "%d", &Now[i]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) fscanf(input, "%d", &Max[i][j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) fscanf(input, "%d", &Allocation[i][j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) Need[i][j] = Max[i][j] - Allocation[i][j];

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) Now[j] -= Allocation[i][j];

    now.resize(m);

    while (1) {
        s.clear();
        char ch;
        fscanf(input, "%c", &ch);
        if (ch == '\n' || ch == ' ') continue;
        if (ch == 'r') {
            s.push_back(ch);
            for (i = 1; i < 7; i++) {
                fscanf(input, "%c", &ch);
                s.push_back(ch);
            }
        }

        if (s.compare(a) != 0 && s.compare(b) != 0)
            break;
        else {
            fscanf(input, "%d", &process);

            for (i = 0; i < m; i++) fscanf(input, "%d", &now[i]);

            if (s.compare(a) == 0) {  // request

                request(process, now, 1);

                for (i = 0; i < m; i++) fprintf(output, "%d ", Now[i]);
                fprintf(output, "\n");
            } else {  // release
                release(process, now, 1);
                find();

                for (i = 0; i < m; i++) fprintf(output, "%d ", Now[i]);
                fprintf(output, "\n");
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}