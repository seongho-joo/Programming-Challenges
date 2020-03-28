/**
 * Assignment 06 - Doublets
 */
#include <cstring>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

typedef pair<string, string> pss;

ifstream inp("p10150.inp");
ofstream out("p10150.out");

const int MAX = 25143;
vector<string> dictionary;
vector<int> parent;
vector<bool> visited;
int s, e;
pss p;

bool isDoublets(string p, string child) {
    if (p.size() != child.size()) return false;
    bool diff = false;
    for (int i = 0; i < p.size(); i++) {
        if (p[i] != child[i]) {
            if (!diff)
                diff = true;
            else
                return false;
        }
    }
    return true;
}

bool BFS(int len) {
    for (int i = 0; i < len; i++) {
        if (p.first == dictionary[i]) {
            s = i;
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        if (p.second == dictionary[i]) {
            e = i;
            break;
        }
    }

    queue<int> q;
    parent[s] = s, visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        /** 끝 단어의 인덱스와 같을 경우 참 리턴 */
        if (cur == e) return true;

        for (int i = 0; i < len; i++) {
            if (!visited[i] && isDoublets(dictionary[cur], dictionary[i])) {
                parent[i] = cur, visited[i] = true;
                q.push(i);
            }
        }
    }
    return false;
}

void print(int s, int e) {
    if (s != e) print(s, parent[e]);
    out << dictionary[e] << '\n';
}

int main() {
    string str;
    while (getline(inp, str), str != "") {
        dictionary.push_back(str);
    }
    int len = dictionary.size();

    for (int i = 0; i < len; i++)
        if (dictionary[i].back() == ' ') dictionary[i].pop_back();

    bool first = false;

    while (inp >> p.first >> p.second, p.first != "") {
        first ? out << '\n' : out << "";
        first = true;
        parent.assign(len, -1), visited.assign(len, false);
        if (p.first.size() == p.second.size() && BFS(len))
            print(s, e);
        else
            out << "No solution.\n";
        p.first = "";
    }

    inp.close(), out.close();
    return 0;
}