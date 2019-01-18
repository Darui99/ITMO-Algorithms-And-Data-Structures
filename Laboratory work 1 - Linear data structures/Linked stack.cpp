#include <bits/stdc++.h>
using namespace std;

struct List
{
	struct Node
	{
		Node* to;
		int value;

		Node(Node* n_to, const int n_val)
		{
			this->to = n_to;
			this->value = n_val;
		}

		int get()
		{
			return this->value;
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
		return head->to->value;
	}
};

int main()
{
	freopen("stack2.in", "r", stdin);
	freopen("stack2.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	List mystack = List();

	int n;
	cin >> n;

	char c; int x;

	while (n--)
	{
		cin >> c;
		if (c == '+')
		{
			cin >> x;
			mystack.push(x);
		}
		else
		{
			cout << mystack.top() << endl;
			mystack.pop();
		}
	}

	return 0;
}