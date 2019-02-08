#include <iostream>
#include <fstream>
#include <vector>
#define MAX 10001
using namespace std;

// ifstream cin;
// ofstream cout;

vector<int> pre;		 // 전위순회
vector<int> in;			 // 중위순회
vector<int> post;		 // 후위순회
vector<bool> orderCheck; // 트리순회 체크

void input(vector<int> &traversal, int n)
{
	for (int j = 0; j < n; j++)
	{
		int a;
		cin >> a;
		traversal.push_back(a);
	}
}

int inOrder_root(int root, int left, int right)
{
	/* 전,후위순회 에서 root를 구한 후 중위순회에서 root의 인덱스 값을 찾음*/
	if (orderCheck[0])
	{
		while (in[left] != pre[root])
			left++;
		return left;
	}
	else
	{
		while (in[left] != post[root])
			left++;
		return left;
	}
}
/*전위순회가 주어졌을 때 후위순회를 구함*/
void postOrder(int root, int left, int right)
{
	int in_root = inOrder_root(root, left, right); // 중위순회의 root 인덱스
	int L_size = in_root - left;				   // 중위순회에서 root를 기준으로 왼쪽의 개수
	int R_size = right - in_root;				   // 중위순회에서 root를 기준으로 오른쪽 개수
	int L = root + 1, R = L + L_size;			   // root의 왼쪽 자식, 오른쪽 자식
	if (left < right)
	{
		if (L_size != 0)
			postOrder(L, left, in_root - 1); // 루트의 왼쪽 서브트리 방문
		if (R_size != 0)
			postOrder(R, in_root + 1, right); // 루트의 오른쪽 서브트리 방문
	}
	post.push_back(in[in_root]);
}
/*후위순회가 주어졌을 때 전위순회를 구함*/
void preOrder(int root, int left, int right)
{
	int in_root = inOrder_root(root, left, right);
	int L_size = in_root - left;
	int R_size = right - in_root;
	int R = root - 1;
	int L = R - R_size;
	pre.push_back(in[in_root]);
	if (left < right)
	{
		if (L_size != 0)
			preOrder(L, left, in_root - 1);
		if (R_size != 0)
			preOrder(R, in_root + 1, right);
	}
}

int main()
{
	//	cin.open("tree.cin");
	//	cout.open("tree.cout");

	int n; // 노드의 개수
	cin >> n;

	pre.reserve(n);
	in.reserve(n);
	post.reserve(n);
	orderCheck.resize(3);

	for (int i = 0; i < 2; i++)
	{
		int order; // 트리의 순회 0 : 중위, -1 : 전위, 1 : 후위
		cin >> order;

		switch (order)
		{
		case -1: // 전위 순회
			orderCheck[order + 1] = true;
			input(pre, n);
			break;
		case 0: // 중위 순회
			orderCheck[order + 1] = true;
			input(in, n);
			break;
		case 1: // 후위 순회
			orderCheck[order + 1] = true;
			input(post, n);
			break;
		}
	}
	if (orderCheck[0])
	{
		postOrder(0, 0, n - 1); // 전위순회일 때 root의 인덱스는 0
		for (int i = 0; i < post.size(); i++)
			cout << post[i] << " ";
	}
	else
	{
		preOrder(n - 1, 0, n - 1); // 후위순회일 떄 root의 인덱스는 노드의 개수 -1
		for (int i = 0; i < pre.size(); i++)
			cout << pre[i] << " ";
	}

	//	cin.close();
	//	cout.close();
	return 0;
}