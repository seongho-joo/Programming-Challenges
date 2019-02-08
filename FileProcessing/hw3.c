#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define INDEX 4
int nodeCount = 1;
int count = 0;

typedef struct Trie {
	struct Trie* next[10]; // 노드
	char addr[5]; // 주소
	int end; // 1이면 끝
	int vNum;
}Trie;
/* 노드생성과 구조체값들 초기화 */
Trie *Init() {
	Trie * newNode = (Trie*)malloc(sizeof(Trie));
	newNode->end = 0;
	newNode->vNum = 0;
	newNode->addr[0] = '\0';
	for (int i = 0; i < MAX; i++)
		newNode->next[i] = NULL;
	return newNode;
}
/* 노드 삽입 */
void insert(Trie *root, char *key, char *addr) {
	Trie *now = root;
	for (int i = 0; i < INDEX; i++) {
		int radix = key[i] - 48;
		/* 배열인덱스의 값이 NULL이 아니면 노드 생성 */
		if (now->next[radix] == NULL) {
			now->next[radix] = Init();
			if (i != 3)
				nodeCount++; // 노드개수 카운트
		}
		now = now->next[radix]; // 다음 노드로 이동 
	}
	now->end = 1;
	now->vNum = count;
	for (int i = 0; i < 5; i++) now->addr[i] = addr[i]; // 마지막 기수에 레코드 주소값을 넣어줌
}
/* 유효숫자 정렬 */
void vNum(Trie * root, int hight) {
	if (hight == 3) {
		count = 1;
		for (int i = 0; i < MAX; i++) {
			if (root->next[i]) root->next[i]->vNum = count++;
		}
	}
	for (int i = 0; i < MAX; i++) {
		if (root->next[i])
			vNum(root->next[i], hight + 1);
	}
	
}
/* Trie구조에 있는 모든 key값을 찾는 함수 */
void allSearch(Trie* now, FILE* out, char *res, int depth, int temp) {
	if (now->end) { // 마지막 노드 일 때 출력
		fprintf(out, "%s %d ", res, now->vNum);
		for (int i = 0; i < 4; i++) fprintf(out, "%c", now->addr[i]);
		fprintf(out, " ");
	}
	for (int i = 0; i < MAX; i++) {
		if (now->next[i]) {
			res[depth] = i + 48;
			res[depth + 1] = 0;
			allSearch(now->next[i], out, res, depth + 1, temp);
			//if (strlen(res) != depth) count = 1;
		}
	}
}
/* whildcard가 주어졌을때 key를 찾는 함수 */
void whildCard(Trie* root, FILE* out, char *res) {
	Trie* now = root;
	int len = strlen(res);
	for (int i = 0; i < len; i++) {
		int radix = res[i] - 48;
		if (now->next[radix] == NULL) { fprintf(out, "no");  return; }
		now = now->next[radix];
	}
	allSearch(now, out, res, len, len);
}
/* whildcard가 주어지지 않았을 경우 key를 찾는 함수 */
void search(FILE* out, Trie* root, char* res) {
	int len = strlen(res);
	Trie* now = root;
	int cnt = 1;
	for (int i = 0; i<len; i++) {
		if (!now->next[res[i] - 48]) { fprintf(out, "no");  return; }
		now = now->next[res[i] - 48];
		if (i == 2) {
			for (int j = 0; j < (res[i + 1] - 48); j++)
				if (now->next[j] != NULL) cnt++; // 리프노드에서 몇 번째 유효레코드인지 계산
		}
	}
	if (now->end) {
		fprintf(out, "%s %d ", res, cnt); // 출력
		for (int i = 0; i < 4; i++) fprintf(out, "%c", now->addr[i]);
		fprintf(out, " ");
	}
}

int main() {
	FILE *inp, *out;
	Trie *root = Init(); // root 노드 생성
	inp = fopen("hw4.inp", "rt");
	out = fopen("hw4.out", "wt");

	if (inp == NULL) fprintf(stderr, "can't open FLIE\n");

	char ch = ' ';
	char key[5], addr[5]; // 키값과 주소
	/* 개행을 만날 때까지 키값과 주소를 입력받음 */
	while (ch != '\n') {
		fscanf(inp, "%c", &ch);
		/* '(' 를 만나면 키값을 입력받음*/
		if (ch == '(') {
			for (int i = 0; i < INDEX; i++) fscanf(inp, "%c", &key[i]); // 키값 입력 1110
			fscanf(inp, "%c", &ch); // ',' 입력
			for (int i = 0; i < INDEX; i++) fscanf(inp, "%c", &addr[i]); // 주소값 입력 0123
			insert(root, key, addr);
			fscanf(inp, "%c", &ch); // ')' 입력 받음
		}
	}
	fprintf(out, "%d\n", nodeCount);
	vNum(root, 0); // 유효숫자 정렬
	char trie[5] = "";
	while (1) {
		for (int i = 0; i < INDEX; i++) {
			fscanf(inp, "%c", &ch);
			if (ch == '*') {
				whildCard(root, out, trie);
				fprintf(out, "\n");
				memset(trie, '\0', sizeof(trie));
				count = 1;
				break;
			}
			else trie[i] = ch;
		}
		int len = strlen(trie);
		if (len==4) {
			search(out, root, trie);
			memset(trie, '\0', sizeof(trie));
			fprintf(out, "\n");
		}
		fscanf(inp, "%c", &ch); // ' ' or '\n' 
		if (ch == '\n') break;
	}
	fprintf(out, "*");
	free(root);
	fclose(inp); fclose(out);
	return 0;
}