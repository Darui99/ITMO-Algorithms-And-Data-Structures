#include <bits/stdc++.h>
using namespace std;

struct Queue
{
	struct Vector
	{
		int capasity, size;
		int* arr;

		Vector()
		{
			arr = new int[1];
			this->capasity = 1;
			this->size = 0;
		}

		void rebuild(bool flag)
		{
			int* new_arr;
			if (flag)
				new_arr = new int[this->capasity * 2];
			else
				new_arr = new int[this->capasity / 2];
			for (int i = 0; i < this->size; i++)
				new_arr[i] = this->arr[i];
			delete[] arr;
			arr = new_arr;
		}

		void push_back(const int &x)
		{
			if (this->size == this->capasity)
			{
				rebuild(true);
				this->capasity *= 2;
			}
			arr[this->size++] = x;
		}

		void pop_back()
		{
			this->size--;
			if (this->size * 4 <= this->capasity && this->capasity >= 4)
			{
				rebuild(false);
				this->capasity /= 2;
			}
		}

		int get_back()
		{
			return arr[this->size - 1];
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
				this->second.push_back(this->first.get_back());
				this->first.pop_back();
			}
		}
		cout << this->second.get_back() << '\n';
		this->second.pop_back();
	}
};

int main()
{
	freopen("queue1.in", "r", stdin);
	freopen("queue1.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Queue myqueue = Queue();

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
			myqueue.pop();
		}
	}

	return 0;
}