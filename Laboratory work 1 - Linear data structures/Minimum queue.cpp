#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m, k, a, b, c, x;

struct Queue
{
	struct Vector
	{
		int size;
		int* arr;
		int* minu;

		Vector()
		{
			arr = new int[m];
			minu = new int[m];
			this->size = 0;
		}

		void push_back(const int &x)
		{
			if (this->size == 0)
				minu[this->size] = x;
			else
				minu[this->size] = min(minu[this->size - 1], x);
			arr[this->size++] = x;
		}

		void pop_back()
		{
			this->size--;
		}

		int back()
		{
			return arr[this->size - 1];
		}

		int top_min()
		{
			return minu[this->size - 1];
		}

		bool empty()
		{
			return (this->size == 0);
		}
	};

	Vector first, second;

	Queue()
	{
		this->first = Vector();
		this->second = Vector();
	}

	void push(const int &x)
	{
		this->first.push_back(x);
	}

	void pop()
	{
		if (this->second.size == 0)
		{
			while (this->first.size > 0)
			{
				this->second.push_back(this->first.back());
				this->first.pop_back();
			}
		}
		this->second.pop_back();
	}

	int get_min()
	{
		if (first.empty())
			return second.top_min();
		if (second.empty())
			return first.top_min();
		return min(first.top_min(), second.top_min());
	}
};

int main()
{
	//freopen("queue1.in", "r", stdin);
	//freopen("queue1.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int prev[2];
	prev[0] = prev[1] = 0;
	cin >> n >> m >> k >> a >> b >> c;
	
	Queue q = Queue();

	long long sum = 0ll;
	for (int i = 0; i < n; i++)
	{
		if (i < k)
		{
			cin >> x;
			if (i == k - 2)
				prev[0] = x;
			if (i == k - 1)
				prev[1] = x;
		}
		else
		{
			x = a * prev[0] + b * prev[1] + c;
			prev[0] = prev[1];
			prev[1] = x;
		}
		q.push(x);

		if (i - m + 1 >= 0)
		{
			sum += (long long)q.get_min();
			q.pop();
		}
	}
	cout << sum;

	return 0;
}