#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct hashTable {
	const int MAXN = (int)1e+6 + 3;
	bool sieve[(int)1e+6 + 3];
	vector <int> prime;

	void build() {
		for (int i = 2; i < MAXN; i++)
			sieve[i] = true;
		for (int i = 2; i < MAXN; i++) {
			if (sieve[i]) {
				prime.push_back(i);
				for (ll k = i * 1ll * i; k < MAXN; k += i)
					sieve[k] = false;
			}
		}
	}

	mt19937 rng_58;

	int random(int n) {
		return rng_58() % n;
	}
	//----------------------------------------------------
	int a, b, capacity, size, maxLen;
	vector < vector<int> > arr, newArr;

	void gen() {
		a = random(777) + 37;
		b = random(123450) + 37;
		capacity = prime[random((int)prime.size())];
	}

	hashTable()  {
		build();
		gen();
		maxLen = 0;
		arr.resize(capacity);
	}

	void rebuild() {
		while (maxLen * 4 >= size && size > 50) {
			gen();
			newArr.resize(capacity);
			for (int i = 0; i < (int)arr.size(); i++) {
				for (int j = 0; j < (int)arr[i].size(); j++) {
					ll cur = (a * 1ll * arr[i][j] + b) % capacity;
					newArr[cur].push_back(arr[i][j]);
				}
			}
			arr.swap(newArr);
			newArr.clear();
			maxLen = 0;
			for (int i = 0; i < (int)arr.size(); i++) {
				maxLen = max(maxLen, (int)arr[i].size());
			}
		}
	}

	bool exists(int x) {
		ll cur = ((a * 1ll * x + b) % capacity + capacity) % capacity;
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i] == x)
				return true;
		}
		return false;
	}

	void insert(int x) {
		if (exists(x))
			return;
		ll cur = ((a * 1ll * x + b) % capacity + capacity) % capacity;
		arr[cur].push_back(x);
		size++;
		maxLen = max(maxLen, (int)arr[cur].size());
		rebuild();
	}

	void extract(int x) {
		ll cur = ((a * 1ll * x + b) % capacity + capacity) % capacity;
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i] == x) {
				arr[cur].erase(arr[cur].begin() + i);
				size--;
				return;
			}
		}
	}
};

int main() {
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	hashTable q = hashTable();
	string s;
	int x;

	while (cin >> s >> x) {
		if (s == "insert")
			q.insert(x);
		if (s == "delete")
			q.extract(x);
		if (s == "exists") {
			if (q.exists(x)) {
				cout << "true\n";
			} else {
				cout << "false\n";
			}
		}
	}
	return 0;
}
