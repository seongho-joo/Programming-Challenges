/**
 * Assignment 03 : Tree Construction 1
 */
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

ifstream inp("tree.inp");
ofstream out("tree.out");

stack<int> st;
vector<string> str;

void preorder(int len) {
    out << "\nPreorder\n";
    int num = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ")") continue;
        if (str[i] == "(")
            out << 'r' << num++ << '\n';
        else
            out << str[i] << '\n';
    }
}

void inorder(int len) {
    out << "Inorder\n";
    int num = 0, sta;
    for (int i = 0; i < len; i++) {
        if (str[i] == "(")
            st.push(num++);
        else if (str[i] != ")") {
            out << str[i] << "\n";
            if (!st.empty()) {
                out << "r" << st.top() << '\n';
                st.pop();
            }
        }
    }
}

int main() {
    int T;
    inp >> T;

    string input;

    while (T--) {
        stack<string> EXIT;
        while (true) {
            inp >> input;
            str.push_back(input);
            if (input == "(") EXIT.push(input);
            if (input == ")") EXIT.pop();
            if (EXIT.empty()) break;
        }
        int len = str.size();
        for (int i = 0; i < str.size(); i++) out << str[i] << ' ';
        preorder(len);
        inorder(len);
        str.clear();
    }

    inp.close();
    out.close();
    return 0;
}