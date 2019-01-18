#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Vector
{
	int capasity, size;
	T* arr;

	Vector() 
	{
		arr = new T[1];
		capasity = 1;
		size = 0;
	}

	void rebuild(bool flag) 
	{
		T* new_arr;
		if (flag)
			new_arr = new T[capasity * 2];
		else
			new_arr = new T[capasity / 2];
		for (int i = 0; i < size; i++)
			new_arr[i] = arr[i];
		delete[] arr;
		arr = new_arr;
	}

	void push_back(const T &x) 
	{
		if (size == capasity) 
		{
			rebuild(true);
			capasity *= 2;
		}
		arr[size++] = x;
	}

	void pop_back() 
	{
		size--;
		if (size * 4 <= capasity && capasity >= 4) 
		{
			rebuild(false);
			capasity /= 2;
		}
	}

	T get_back() 
	{
		return arr[size - 1];
	}

	T get(const int &i) 
	{
		return arr[i];
	}
};

template <class T>
struct Queue {
	Vector<T> first, second;

	Queue() 
	{
		first = Vector<T>();
		second = Vector<T>();
	}

	void push(const T &x) 
	{
		first.push_back(x);
	}

	int get() 
	{
		if (second.size == 0) 
		{
			while (first.size > 0) 
			{
				second.push_back(first.get_back());
				first.pop_back();
			}
		}
		T res = second.get_back();
		second.pop_back();
		return res;
	}
};

const int p = 997;
const int mod = 65521;

int get_string_hash(const string &s) 
{
	int res = 0;
	for (int i = 0; i < (int)s.size(); i++)
		res = (res * p + (int)s[i]) % mod;
	return res;
}

struct hash_table
{
	Vector<string> key[mod];
	Vector<int> val[mod];

	hash_table()
	{
		for (int i = 0; i < mod; i++)
			key[i] = Vector<string>();
		for (int i = 0; i < mod; i++)
			val[i] = Vector<int>();
	}

	bool exist(const string &s)
	{
		int s_hash = get_string_hash(s);

		for (int i = 0; i < key[s_hash].size; i++)
		{
			if (key[s_hash].get(i) == s)
				return true;
		}
		return false;
	}

	void add(const string &s, const int &x)
	{
		if (exist(s))
			return;

		int s_hash = get_string_hash(s);

		key[s_hash].push_back(s);
		val[s_hash].push_back(x);
	}

	int get(const string &s)
	{
		int s_hash = get_string_hash(s);

		for (int i = 0; i < key[s_hash].size; i++)
		{
			if (key[s_hash].get(i) == s)
				return val[s_hash].get(i);
		}
		return -1;
	}
};

const int short_mod = 65536;

int main()
{
	freopen("quack.in", "r", stdin);
	freopen("quack.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Queue<int> quack = Queue<int>();
	hash_table h = hash_table();

	string s, ss;
	Vector<string> have = Vector<string>();
	int reg[26];

	for (int i = 0; cin >> s; i++)
	{
		have.push_back(s);
		if (s[0] == ':')
		{
			ss = s.substr(1, (int)s.size() - 1);
			h.add(ss, i);
		}
	}

	for (int i = 0;;)
	{
		if (i == have.size)
		{
			return 0;
		}

		s = have.get(i);

		bool number = true;
		if (s[0] == '+')
		{
			number = false;
			int x = quack.get();
			int y = quack.get();
			quack.push((x + y) % short_mod);
		}
		if (s[0] == '-')
		{
			number = false;
			int x = quack.get();
			int y = quack.get();
			quack.push((x + short_mod - y) % short_mod);
		}
		if (s[0] == '*')
		{
			number = false;
			unsigned int x = quack.get();
			unsigned int y = quack.get();
			quack.push((x * y) % short_mod);
		}
		if (s[0] == '/')
		{
			number = false;
			int x = quack.get();
			int y = quack.get();
			if (y == 0)
				quack.push(0);
			else
				quack.push(x / y);
		}
		if (s[0] == '%')
		{
			number = false;
			int x = quack.get();
			int y = quack.get();
			if (y == 0)
				quack.push(0);
			else
				quack.push(x % y);
		}
		if (s[0] == '>')
		{
			number = false;
			reg[s[1] - 'a'] = quack.get();
		}
		if (s[0] == '<')
		{
			number = false;
			quack.push(reg[s[1] - 'a']);
		}
		if (s[0] == 'P' && (int)s.size() == 1)
		{
			number = false;
			cout << quack.get() << endl;
		}
		if (s[0] == 'P' && (int)s.size() > 1)
		{
			number = false;
			cout << reg[s[1] - 'a'] << endl;
		}
		if (s[0] == 'C' && (int)s.size() == 1)
		{
			number = false;
			cout << (char)(quack.get() % 256);
		}
		if (s[0] == 'C' && (int)s.size() > 1)
		{
			number = false;
			cout << (char)(reg[s[1] - 'a'] % 256);
		}
		if (s[0] == ':')
		{
			number = false;
			ss = s.substr(1, (int)s.size() - 1);
			h.add(ss, i);
		}
		if (s[0] == 'J')
		{
			number = false;
			ss = s.substr(1, (int)s.size() - 1);
			i = h.get(ss);
			continue;
		}
		if (s[0] == 'Z')
		{
			number = false;
			if (reg[s[1] - 'a'] == 0)
			{
				ss = s.substr(2, (int)s.size() - 2);
				i = h.get(ss);
				continue;
			}
		}
		if (s[0] == 'E')
		{
			number = false;
			if (reg[s[1] - 'a'] == reg[s[2] - 'a'])
			{
				ss = s.substr(3, (int)s.size() - 3);
				i = h.get(ss);
				continue;
			}
		}
		if (s[0] == 'G')
		{
			number = false;
			if (reg[s[1] - 'a'] > reg[s[2] - 'a'])
			{
				ss = s.substr(3, (int)s.size() - 3);
				i = h.get(ss);
				continue;
			}
		}
		if (s[0] == 'Q')
			return 0;
		if (number)
		{
			int cur_num = 0;
			for (int i = (int)s.size() - 1, r = 1; i >= 0; i--, r *= 10)
				cur_num += (int)(s[i] - '0') * r;
			quack.push(cur_num % short_mod);
		}
		i++;
	}

	return 0;
}