#include <bits/stdc++.h>
using namespace std;

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

int main()
{
	freopen("stack1.in", "r", stdin);
	freopen("stack1.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Vector mystack = Vector();

	int n;
	cin >> n;

	char c; int x;

	while (n--)
	{
		cin >> c;
		if (c == '+')
		{
			cin >> x;
			mystack.push_back(x);
		}
		else
		{
			cout << mystack.get_back() << '\n';
			mystack.pop_back();
		}
	}

	return 0;
}