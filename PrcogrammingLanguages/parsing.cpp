#include <iostream>
#include <string>

using namespace std;

string word;
string::iterator cur;

void NextWord();
bool Factor();
bool Expr();
bool Term();
bool Eprime();
bool Tprime();

int main() {
    getline(cin, word);
    cur = word.begin();
    while (*cur == ' ') cur++;
    if (Expr() && cur == word.end())
        cout << "Good\n";
    else
        cout << "Error\n";
    return 0;
}

void NextWord() {
    cur++;
    while (*cur == ' ') cur++;
}

bool Expr() {
    if (!Term())
        return false;
    else {
        if (cur == word.end() || *cur == '\n') return true;
        return Eprime();
    }
}

bool Eprime() {
    if (*cur == '+' || *cur == '-') {
        NextWord();
        if (!Term())
            return false;
        else {
            if (cur == word.end() || *cur == '\n') return true;
            return Eprime();
        }
    }
    /** Epime -> ε */
    return true;
}

bool Term() {
    if (!Factor())
        return false;
    else {
        if (cur == word.end() || *cur == '\n') return true;
        return Tprime();
    }
}

bool Tprime() {
    if (*cur == '*' || *cur == '/') {
        NextWord();
        if (!Factor())
            return false;
        else {
            if (cur == word.end() || *cur == '\n') return true;
            Tprime();
        }
    }
    /** Tprime -> ε */
    return true;
}

bool Factor() {
    if (*cur == '(') {
        NextWord();
        if (!Expr())
            return false;
        else if (*cur != ')')
            return false;
    } else if ((*cur < '1' && *cur > '9') ||
               ((*cur < 'a' && *cur > 'z') || (*cur < 'A' && *cur > 'Z')))
        return false;
    NextWord();
    return true;
}