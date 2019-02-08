#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct Node {
	int key;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
	int height; // ����
}Node;

int height(Node* root); // root�� ������ȯ
void adjust_hegith(Node* root); // ���ʼ���Ʈ���� ������ ����Ʈ���� ��������
Node* Init(int key, Node* parent); // �������� �ʱ�ȭ
Node* rotateLeft(Node *root); // ���� ȸ��
Node* rotateRight(Node *root); // ������ ȸ��
Node* Balance(Node *root); // �����μ��� ���� LL, LR, RR, RL �Ǻ�
Node* Insert(Node *root, int key); // ��� ����
Node* L_find(Node* root); // ���� ����Ʈ������ ���� ū �� ��ȯ
Node* Delete(Node *root, int key); // ��� ����
void preOrder(Node* root, FILE* out); // ������ȸ�� ���

int main() {
	FILE *inp, *out;
	Node * root;
	inp = fopen("hw4.inp", "rt");
	out = fopen("hw4.out", "wt");

	//if (inp == NULL) fprintf(stderr, "can't open FLIE\n");

	int key = 0;
	char ch = ' ';
	fscanf(inp, "%d", &key);
	fscanf(inp, "%c", &ch);
	root = Init(key, NULL);
	/* input ���� */
	while (ch != '\n') {
		fscanf(inp, "%d", &key);
		fscanf(inp, "%c", &ch);
		root = Insert(root, key);
	}
	preOrder(root, out);
	fprintf(out, "\n");
	/* input ���� */
	while (1) {
		fscanf(inp, "%d", &key);
		fscanf(inp, "%c", &ch);
		root = Delete(root, key);
		if (ch == '\n') break;
	}
	preOrder(root, out);
	fprintf(out, "\n*");
	fclose(inp); fclose(out);
	return 0;
}
int height(Node* root) { return root ? root->height : 0; }
void adjust_hegith(Node* root) {
	if (root == NULL) return;
	root->height = 1 + max(height(root->left), height(root->right));
}
Node* Init(int key, Node* parent) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->height = 1;
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = parent;

	return newNode;
}
Node* rotateRight(Node* root) {
	Node* newRoot = root->left;
	Node* parent = root->parent;

	if (parent) {
		if (parent->left == root) parent->left = newRoot;
		else parent->right = newRoot;
	}
	newRoot->parent = root->parent;
	root->parent = newRoot;
	root->left = newRoot->right;

	if (root->left) root->left->parent = root;
	newRoot->right = root;
	adjust_hegith(root);
	adjust_hegith(newRoot);
	return newRoot;
}

Node* rotateLeft(Node* root) {
	Node* newRoot = root->right;
	Node* parent = root->parent;

	if (parent) {
		if (parent->right == root) parent->right = newRoot;
		else parent->left = newRoot;
	}
	newRoot->parent = root->parent;
	root->parent = newRoot;
	root->right = newRoot->left;

	if (root->right) root->right->parent = root;
	newRoot->left = root;
	adjust_hegith(root);
	adjust_hegith(newRoot);
	return newRoot;

}

Node* Balance(Node* root) {
	if (height(root->left) - height(root->right) > 1) { 
		/* LL -> rotate Right  */
		if (height(root->left->left) > height(root->left->right)) root = rotateRight(root);
		/* LR -> rotateLeft, rotateRitght */
		else {
			rotateLeft(root->left); 
			root = rotateRight(root);
		}
	}
	else if (height(root->right) - height(root->left) > 1) {
		/* RR -> roteateLeft */
		if (height(root->right->right) > height(root->right->left)) root = rotateLeft(root);
		/* LR -> retateRight, rotateLeft */
		else {
			rotateRight(root->right);
			root = rotateLeft(root);
		}
	}
	return root;
}

Node* Insert(Node* root, int key) {
	Node* current = root;
	while (current->key != key) {
		if (current->key > key) { // Ű ���� ���� ��庸�� ������ ���� ����Ʈ�� ����
			if (current->left) current = current->left;
			else {
				current->left = Init(key, current);
				current = current->left;
			}
		}
		else if (current->key < key) { // Ű ���� ���� ��庸�� ũ�� ������ ����Ʈ�� ����
			if (current->right) current = current->right;
			else {
				current->right = Init(key, current);
				current = current->right;
			}
		}
		else return root; // Ʈ�����ο� �ִ� ���� ������ �Լ� ����
	} do {
		current = current->parent;
		adjust_hegith(current);
		current = Balance(current);
	} while (current->parent);

	return current;
}

Node* L_find(Node *root) {
	if (root == NULL) return NULL;
	else if (root->right == NULL) return root;
	else L_find(root->right);
}


Node* Delete(Node *root, int key) {
	Node *temp = NULL, *child = temp; 
	Node *L_subTree = temp; // NULL�� �ʱ�ȭ
	if (root == NULL) return root;
	else if (key < root->key) 
		root->left = Delete(root->left, key);
	else if (key > root->key) 
		root->right = Delete(root->right, key);
	/* ����Ʈ���� ������ 2�� ��� */
	else if (root->left && root->right) {
		/* ���� ����Ʈ������ ���� ū ���� ���� */
		L_subTree = L_find(root->left);
		temp = L_subTree;
		root->key = temp->key;
		root->left = Delete(root->left, root->key);
	}
	else {
		temp = root;
		if (root->left) child = root->left;
		else if (root->right) child = root->right;
		else child = NULL;
		free(temp);
		return child;
	}
	adjust_hegith(root);
	root = Balance(root);
	return root;
}

void preOrder(Node* root, FILE* out) {
	if (root == NULL) return;
	else {
		fprintf(out, "%d ", root->key);
		preOrder(root->left, out);
		preOrder(root->right, out);
	}
}