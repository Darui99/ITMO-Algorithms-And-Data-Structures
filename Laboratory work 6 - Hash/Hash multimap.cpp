#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	Node* prev;
	Node* next;
	pair<string, string> val;

	Node() {
		prev = next = nullptr;
		val = make_pair("", "");
	}

	Node(const pair<string, string> &nv) {
		prev = next = nullptr;
		val = nv;
	}
};

struct LinkedList {
	Node* head;
	Node* tail;
	int size;

	LinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void push(Node* v) {
		size++;
		if (head == nullptr) {
			head = tail = v;
			return;
		}
		tail->next = v;
		v->prev = tail;
		tail = v;
	}

	void pop(Node* v) {
		size--;
		if (v->prev != nullptr) {
			v->prev->next = v->next;
		}
		if (v->next != nullptr) {
			v->next->prev = v->prev;
		}
		if (v == tail)
			tail = v->prev;
		if (v == head)
			head = v->next;
	}

	void dump() {
		cout << size << " ";
		Node* v = head;
		for (int i = 0; i < size; i++) {
			cout << v->val.second << " ";
			v = v->next;
		}
	}

	Node* peek() {
		size--;
		Node* res = tail;
		if (tail->prev != nullptr) {
			tail->prev->next = nullptr;
			tail = tail->prev;
		} else {
			head = tail = nullptr;
		}
		return res;
	}
};

struct hashMap {
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
	int p, capacity, size, maxLen;
	vector < vector< pair< pair<string, string>, Node*> > > arr, newArr;

	void gen() {
		p = random(777) + 37;
		capacity = prime[random((int)prime.size())];
	}

	int getHash(const string &s) {
		int res = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			res = (res * p + (int)s[i]) % capacity;
		}
		return res;
	}

	int getHash(const pair<string, string> &s) {
		int res = (getHash(s.first) * p + getHash(s.second)) % capacity;
		return res;
	}

	hashMap()  {
		build();
		gen();
		maxLen = 0;
		arr.resize(capacity);
		size = 0;
	}

	void rebuild() {
		while (maxLen * 4 >= size && size > 50) {
			gen();
			newArr.resize(capacity);
			for (int i = 0; i < (int)arr.size(); i++) {
				for (int j = 0; j < (int)arr[i].size(); j++) {
					int cur = getHash(arr[i][j].first);
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

	Node* get(const pair<string, string> &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key)
				return arr[cur][i].second;
		}
		return nullptr;
	}

	bool exists(const pair<string, string> &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key)
				return true;
		}
		return false;
	}

	void insert(const pair<string, string> &key, Node* val) {
		int cur = getHash(key);
		bool flag = true;
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				arr[cur][i].second = val;
				flag = false;
				break;
			}
		}
		if (flag) {
			arr[cur].push_back(make_pair(key, val));
			size++;
		}
		rebuild();
	}

	void extract(const pair<string, string> &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				arr[cur].erase(arr[cur].begin() + i);
				size--;
				return;
			}
		}
	}
};

hashMap q = hashMap();

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
	int p, capacity, maxLen, size;
	vector < vector< pair<string, LinkedList> > > arr, newArr;

	void gen() {
		p = random(777) + 37;
		capacity = prime[random((int)prime.size())];
	}

	int getHash(const string &s) {
		int res = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			res = (res * p + (int)s[i]) % capacity;
		}
		return res;
	}

	hashTable()  {
		build();
		gen();
		maxLen = 0;
		arr.resize(capacity);
		size = 0;
	}

	void rebuild() {
		while (maxLen * 4 >= size && size > 50) {
			gen();
			newArr.resize(capacity);
			for (int i = 0; i < (int)arr.size(); i++) {
				for (int j = 0; j < (int)arr[i].size(); j++) {
					int cur = getHash(arr[i][j].first);
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

	void get(const string &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				arr[cur][i].second.dump();
				cout << '\n';
				return;
			}
		}
		cout << "0\n";
	}

	void insert(const string &key, const string &val) {
		if (q.exists(make_pair(key, val)))
			return;
		Node* p = new Node(make_pair(key, val));
		int cur = getHash(key);
		bool flag = true;
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				arr[cur][i].second.push(p);
				q.insert(make_pair(key, val), p);
				flag = false;
				break;
			}
		}
		if (flag) {
			arr[cur].push_back(make_pair(key, LinkedList()));
			arr[cur].back().second.push(p);
			q.insert(make_pair(key, val), p);
		}
		size++;
		rebuild();
	}

	void extract(const string &key, const string &val) {
		if (!q.exists(make_pair(key, val)))
			return;
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				arr[cur][i].second.pop(q.get(make_pair(key, val)));
				q.extract(make_pair(key, val));
				size--;
				return;
			}
		}
	}

	void extract(const string &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				while (arr[cur][i].second.size > 0) {
					Node* v = arr[cur][i].second.peek();
					q.extract(v->val);
				}
			}
		}
	}
};

int main() {
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    hashTable h = hashTable();

	string s, a, b;
	while (cin >> s) {
		if (s == "put") {
			cin >> a >> b;
			h.insert(a, b);
		}
		if (s == "delete") {
			cin >> a >> b;
			h.extract(a, b);
		}
		if (s == "deleteall") {
			cin >> a;
			h.extract(a);
		}
		if (s == "get") {
			cin >> a;
			h.get(a);
		}
	}
	return 0;
}
