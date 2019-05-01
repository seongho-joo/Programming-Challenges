#include <stdio.h>
#pragma warning(disable : 4996)

struct process {
    int Num;
    int source[50];
};

struct process ready[1000];
int n, m, MAX[50][50], Allocation[50][50], Available[50], source[50];
int front = 0, rear = 0;

int safeCheck() {  // 안전상태 체크
    int check[50] = {0};
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (check[i] == 0) {
                for (int j = 0; j < m; j++) {
                    if (Allocation[i][j] + Available[j] >=
                        MAX[i][j]) {  // MAX값 이상일 경우에는 안전
                        if (j == m - 1) {
                            check[i] = 1;
                        }
                    } else
                        break;  // 그렇지않으면 보류
                }
            } else
                continue;
        }
    }
    for (int i = 0; i < n; i++) {
        if (check[i] == 1)
            break;
        else if (check[i] == 0 && i == n - 1)
            return 0;  // 모두 안전하지 않으면
    }
    return 1;
}

void requestPlay(int processNum, int request[]) {  // request
    int useCheck = 0;
    for (int i = 0; i < m; i++) {
        Allocation[processNum][i] += request[i];
        Available[i] -= request[i];
        if (Available[i] < 0 ||
            Allocation[processNum][i] > MAX[processNum][i]) {
            // 있을 수 없는 조건일 경우 취소
            useCheck = 1;
            if (Available[i] < 0 &&
                Allocation[processNum][i] <= MAX[processNum][i]) {
                // 레디 queue에 enqueue
                ready[rear].Num = processNum;
                for (int j = 0; j < m; j++) {
                    ready[rear].source[j] = request[j];
                }
                rear++;
                useCheck = 0;
            }
            for (int j = 0; j <= i; j++) {
                Allocation[processNum][j] -= request[j];
                Available[j] += request[j];
            }
            break;
        }
    }
    if (safeCheck() == 0 && useCheck == 0) {
        ready[rear].Num = processNum;
        for (int j = 0; j < m; j++) {
            ready[rear].source[j] = request[j];
        }
        rear++;
        for (int j = 0; j <= m; j++) {
            Allocation[processNum][j] -= request[j];
            Available[j] += request[j];
        }
    }
}

void releasePlay(int processNum, int release[]) {  // release
    for (int i = 0; i < m; i++) {
        Allocation[processNum][i] -= release[i];
        Available[i] += release[i];
    }
    if (front != rear) {
        int i = front, c = rear;
        while (i < c) {
            requestPlay(ready[front].Num, ready[front].source);
            front++, i++;
        }
    }
}

int main() {
    FILE *inp = fopen("banker.inp", "r");
    FILE *out = fopen("banker.out", "w");
    fscanf(inp, "%d %d", &n, &m);
    for (int i = 0; i < m; i++) {  // 자원 총 갯수
        fscanf(inp, "%d", &source[i]);
        Available[i] = source[i];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf(inp, "%d", &MAX[i][j]);  // 요구하는 갯수
    for (int i = 0; i < n; i++) {           // 현재 할당 받은 거
        for (int j = 0; j < m; j++) {
            fscanf(inp, "%d", &Allocation[i][j]);
            Available[j] -= Allocation[i][j];
        }
    }
    // 입력
    char word[20];

    while (1) {
        fscanf(inp, "%s", &word);
        if (word[0] == 'q')
            break;  // quit

        else if (word[2] == 'q') {  // request
            int processNum, request[50], useCheck = 0;
            fscanf(inp, "%d ", &processNum);
            for (int i = 0; i < m; i++) fscanf(inp, "%d ", &request[i]);
            // request 내용 입력
            requestPlay(processNum, request);
        }

        else {  // release
            int processNum, release[50], useCheck = 0;
            fscanf(inp, "%d ", &processNum);
            for (int i = 0; i < m; i++) fscanf(inp, "%d ", &release[i]);
            // release 내용 입력
            releasePlay(processNum, release);
        }
        for (int i = 0; i < m; i++) {
            printf("%d ", Available[i]);
        }
        printf("\n");
    }
    fclose(inp);
    fclose(out);
    return 0;
}