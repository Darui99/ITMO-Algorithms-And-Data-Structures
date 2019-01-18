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
	Node* tail;

	List()
	{
		this->head = new Node(nullptr, 0);
		this->tail = new Node(nullptr, 0);
	}

	void push(const int &x)
	{
		Node* p = new Node(nullptr, x);
		if (tail->to != nullptr)
			tail->to->to = p;
		tail->to = p;
		if (head->to == nullptr)
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
	freopen("queue2.in", "r", stdin);
	freopen("queue2.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

List myqueue = List();

	int n;
	cin >> n;

	char c; int x;

	while (n--)
	{
		cin >> c;
		if (c == '+')
		{
			cin >> x;
			myqueue.push(x);
		}
		else
		{
			cout << myqueue.top() << '\n';
			myqueue.pop();
		}
	}
	
	return 0;
}