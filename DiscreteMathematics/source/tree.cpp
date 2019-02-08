#include <iostream>
#include <fstream>
#include <vector>
#define MAX 10001
using namespace std;

// ifstream cin;
// ofstream cout;

vector<int> pre;		 // ������ȸ
vector<int> in;			 // ������ȸ
vector<int> post;		 // ������ȸ
vector<bool> orderCheck; // Ʈ����ȸ üũ

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
	/* ��,������ȸ ���� root�� ���� �� ������ȸ���� root�� �ε��� ���� ã��*/
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
/*������ȸ�� �־����� �� ������ȸ�� ����*/
void postOrder(int root, int left, int right)
{
	int in_root = inOrder_root(root, left, right); // ������ȸ�� root �ε���
	int L_size = in_root - left;				   // ������ȸ���� root�� �������� ������ ����
	int R_size = right - in_root;				   // ������ȸ���� root�� �������� ������ ����
	int L = root + 1, R = L + L_size;			   // root�� ���� �ڽ�, ������ �ڽ�
	if (left < right)
	{
		if (L_size != 0)
			postOrder(L, left, in_root - 1); // ��Ʈ�� ���� ����Ʈ�� �湮
		if (R_size != 0)
			postOrder(R, in_root + 1, right); // ��Ʈ�� ������ ����Ʈ�� �湮
	}
	post.push_back(in[in_root]);
}
/*������ȸ�� �־����� �� ������ȸ�� ����*/
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

	int n; // ����� ����
	cin >> n;

	pre.reserve(n);
	in.reserve(n);
	post.reserve(n);
	orderCheck.resize(3);

	for (int i = 0; i < 2; i++)
	{
		int order; // Ʈ���� ��ȸ 0 : ����, -1 : ����, 1 : ����
		cin >> order;

		switch (order)
		{
		case -1: // ���� ��ȸ
			orderCheck[order + 1] = true;
			input(pre, n);
			break;
		case 0: // ���� ��ȸ
			orderCheck[order + 1] = true;
			input(in, n);
			break;
		case 1: // ���� ��ȸ
			orderCheck[order + 1] = true;
			input(post, n);
			break;
		}
	}
	if (orderCheck[0])
	{
		postOrder(0, 0, n - 1); // ������ȸ�� �� root�� �ε����� 0
		for (int i = 0; i < post.size(); i++)
			cout << post[i] << " ";
	}
	else
	{
		preOrder(n - 1, 0, n - 1); // ������ȸ�� �� root�� �ε����� ����� ���� -1
		for (int i = 0; i < pre.size(); i++)
			cout << pre[i] << " ";
	}

	//	cin.close();
	//	cout.close();
	return 0;
}