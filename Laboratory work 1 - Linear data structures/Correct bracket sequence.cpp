#include <bits/stdc++.h>
using namespace std;

struct List
{
	struct Node
	{
		Node* to;
		char c;

		Node(Node* n_to, const char nc)
		{
			this->to = n_to;
			this->c = nc;
		}
	};

	Node* head;

	List()
	{
		this->head = new Node(nullptr, 0);
	}

	void push(const char &x)
	{
		Node* p = new Node(head->to, x);
		head->to = p;
	}

	void pop()
	{
		head->to = head->to->to;
	}

	char top()
	{
		return head->to->c;
	}

	bool empty()
	{
		return (head->to == nullptr);
	}
};

string s;

void solve()
{
	int n = (int)s.size();

	List q = List(); // q - stack
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '(' || s[i] == '[')
		{
			q.push(s[i]);
			continue;
		}
		if (s[i] == ')')
		{
			if (q.empty() || q.top() != '(')
			{
				cout << "NO\n";
				return;
			}
			q.pop();
		}
		if (s[i] == ']')
		{
			if (q.empty() || q.top() != '[')
			{
				cout << "NO\n";
				return;
			}
			q.pop();
		}
	}
	if (q.empty())
	    cout << "YES\n";
	else
	    cout << "NO\n";
	return;
}

int main()
{
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (cin >> s)
		solve();

	return 0;
}