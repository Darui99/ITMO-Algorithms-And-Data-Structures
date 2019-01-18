#include <bits/stdc++.h>
using namespace std;

struct List
{
	struct Node
	{
		Node* to;
		int val;

		Node(Node* n_to, const int &nc)
		{
			this->to = n_to;
			this->val = nc;
		}
	};

	Node* head;

	List()
	{
		this->head = new Node(nullptr, 0);
	}

	void push(const int &x)
	{
		Node* p = new Node(head->to, x);
		head->to = p;
	}

	void pop()
	{
		head->to = head->to->to;
	}

	int top()
	{
		return head->to->val;
	}

	bool empty()
	{
		return (head->to == nullptr);
	}
};

int main()
{
	freopen("postfix.in", "r", stdin);
	freopen("postfix.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	char c;
	List q = List(); // q - stack

	int a, b;

	while (cin >> c)
	{
		if ('0' <= c && c <= '9')
			q.push((int)(c - '0'));
		else
		{
			b = q.top(); q.pop();
			a = q.top(); q.pop();

			if (c == '+')
				q.push(a + b);
			if (c == '-')
				q.push(a - b);
			if (c == '*')
				q.push(a * b);
		}
	}

	cout << q.top();

	return 0;
}