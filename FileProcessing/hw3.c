#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define INDEX 4
int nodeCount = 1;
int count = 0;

typedef struct Trie {
	struct Trie* next[10]; // ���
	char addr[5]; // �ּ�
	int end; // 1�̸� ��
	int vNum;
}Trie;
/* �������� ����ü���� �ʱ�ȭ */
Trie *Init() {
	Trie * newNode = (Trie*)malloc(sizeof(Trie));
	newNode->end = 0;
	newNode->vNum = 0;
	newNode->addr[0] = '\0';
	for (int i = 0; i < MAX; i++)
		newNode->next[i] = NULL;
	return newNode;
}
/* ��� ���� */
void insert(Trie *root, char *key, char *addr) {
	Trie *now = root;
	for (int i = 0; i < INDEX; i++) {
		int radix = key[i] - 48;
		/* �迭�ε����� ���� NULL�� �ƴϸ� ��� ���� */
		if (now->next[radix] == NULL) {
			now->next[radix] = Init();
			if (i != 3)
				nodeCount++; // ��尳�� ī��Ʈ
		}
		now = now->next[radix]; // ���� ���� �̵� 
	}
	now->end = 1;
	now->vNum = count;
	for (int i = 0; i < 5; i++) now->addr[i] = addr[i]; // ������ ����� ���ڵ� �ּҰ��� �־���
}
/* ��ȿ���� ���� */
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
/* Trie������ �ִ� ��� key���� ã�� �Լ� */
void allSearch(Trie* now, FILE* out, char *res, int depth, int temp) {
	if (now->end) { // ������ ��� �� �� ���
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
/* whildcard�� �־������� key�� ã�� �Լ� */
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
/* whildcard�� �־����� �ʾ��� ��� key�� ã�� �Լ� */
void search(FILE* out, Trie* root, char* res) {
	int len = strlen(res);
	Trie* now = root;
	int cnt = 1;
	for (int i = 0; i<len; i++) {
		if (!now->next[res[i] - 48]) { fprintf(out, "no");  return; }
		now = now->next[res[i] - 48];
		if (i == 2) {
			for (int j = 0; j < (res[i + 1] - 48); j++)
				if (now->next[j] != NULL) cnt++; // ������忡�� �� ��° ��ȿ���ڵ����� ���
		}
	}
	if (now->end) {
		fprintf(out, "%s %d ", res, cnt); // ���
		for (int i = 0; i < 4; i++) fprintf(out, "%c", now->addr[i]);
		fprintf(out, " ");
	}
}

int main() {
	FILE *inp, *out;
	Trie *root = Init(); // root ��� ����
	inp = fopen("hw4.inp", "rt");
	out = fopen("hw4.out", "wt");

	if (inp == NULL) fprintf(stderr, "can't open FLIE\n");

	char ch = ' ';
	char key[5], addr[5]; // Ű���� �ּ�
	/* ������ ���� ������ Ű���� �ּҸ� �Է¹��� */
	while (ch != '\n') {
		fscanf(inp, "%c", &ch);
		/* '(' �� ������ Ű���� �Է¹���*/
		if (ch == '(') {
			for (int i = 0; i < INDEX; i++) fscanf(inp, "%c", &key[i]); // Ű�� �Է� 1110
			fscanf(inp, "%c", &ch); // ',' �Է�
			for (int i = 0; i < INDEX; i++) fscanf(inp, "%c", &addr[i]); // �ּҰ� �Է� 0123
			insert(root, key, addr);
			fscanf(inp, "%c", &ch); // ')' �Է� ����
		}
	}
	fprintf(out, "%d\n", nodeCount);
	vNum(root, 0); // ��ȿ���� ����
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