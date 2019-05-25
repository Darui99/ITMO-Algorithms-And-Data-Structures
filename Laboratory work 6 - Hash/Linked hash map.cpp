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

	LinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void push(Node* v) {
		if (head == nullptr) {
			head = tail = v;
			return;
		}
		tail->next = v;
		v->prev = tail;
		tail = v;
	}

	void pop(Node* v) {
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
};

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
	int p, capacity, size, maxLen;
	vector < vector< pair<string, Node*> > > arr, newArr;
	LinkedList q;

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
		q = LinkedList();
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

	string get(const string &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key)
				return arr[cur][i].second->val.second;
		}
		return "none";
	}

	string prev(const string &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				if (arr[cur][i].second->prev == nullptr) {
					return "none";
				} else {
					return arr[cur][i].second->prev->val.second;
				}
			}
		}
		return "none";
	}

	string next(const string &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				if (arr[cur][i].second->next == nullptr) {
					return "none";
				} else {
					return arr[cur][i].second->next->val.second;
				}
			}
		}
		return "none";
	}

	void insert(const string &key, const string &val) {
		int cur = getHash(key);
		bool flag = true;
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				arr[cur][i].second->val.second = val;
				flag = false;
				break;
			}
		}
		if (flag) {
			Node* p = new Node(make_pair(key, val));
			q.push(p);
			arr[cur].push_back(make_pair(key, p));
			size++;
		}
		rebuild();
	}

	void extract(const string &key) {
		int cur = getHash(key);
		for (int i = 0; i < (int)arr[cur].size(); i++) {
			if (arr[cur][i].first == key) {
				q.pop(arr[cur][i].second);
				arr[cur].erase(arr[cur].begin() + i);
				size--;
				return;
			}
		}
	}
};

int main() {
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    hashTable q = hashTable();
	string s, a, b;
	while (cin >> s) {
		if (s == "put") {
			cin >> a >> b;
			q.insert(a, b);
		}
		if (s == "delete") {
			cin >> a;
			q.extract(a);
		}
		if (s == "get") {
			cin >> a;
			cout << q.get(a) << '\n';
		}
		if (s == "prev") {
			cin >> a;
			cout << q.prev(a) << '\n';
		}
		if (s == "next") {
			cin >> a;
			cout << q.next(a) << '\n';
		}
	}
	return 0;
}
